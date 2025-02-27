#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include "LTV.hpp"
#include <limits>
#include <random>
#include <vector>

constexpr float MAP_HALF = 70.5f;
constexpr float MAP_MIN = -MAP_HALF;
constexpr float MAP_MAX = MAP_HALF;
constexpr float PI = 3.14159265358979323846f;
constexpr float PI2 = 2 * PI;
constexpr float RAD_TO_DEG = 180.0f / PI;
constexpr float INV_SQRT_2PI = 0.3989422804014327f;

#define cast_uint32_t static_cast<uint32_t>
static inline float fastpow2(float p) {
  float offset = (p < 0) ? 1.0f : 0.0f;
  float clipp = (p < -126) ? -126.0f : p;
  int w = clipp;
  float z = clipp - w + offset;
  union {
    uint32_t i;
    float f;
  } v = {cast_uint32_t((1 << 23) *
                       (clipp + 121.2740575f + 27.7280233f / (4.84252568f - z) -
                        1.49012907f * z))};

  return v.f;
}

static inline float fastexp(float p) { return fastpow2(1.442695040f * p); }

static inline float fasterpow2(float p) {
  float clipp = (p < -126) ? -126.0f : p;
  union {
    uint32_t i;
    float f;
  } v = {cast_uint32_t((1 << 23) * (clipp + 126.94269504f))};
  return v.f;
}

static inline float fasterexp(float p) { return fasterpow2(1.442695040f * p); }

// In this compass heading system:
//   0 radians (0°) is North (positive Y axis)
//   π/2 radians (90°) is East (positive X axis)
//   π radians (180°) is South (negative Y axis)
// Angles increase clockwise.

struct Particle {
  float x, y, weight;
};

struct SensorConfig {
  float dx, dy, angle; // dx: forward offset, dy: right offset, angle: mounting
                       // offset in degrees
};

class ParticleFilter {
  std::vector<Particle> particles;
  std::mt19937 gen{std::random_device{}()};
  std::normal_distribution<float> pos_noise;
  std::ranlux24_base de;
  float cum_distance = 0.0f;

  // Additional parameters to ensure unit consistency and reduce drift:
  const float motion_scale; // scales the odometry displacement to map units
  const float sensor_scale; // converts sensor readings to map units
  const float resample_distance_threshold; // threshold (in map units) to
                                           // trigger resampling

  // Sensor cache (local robot frame)
  struct Sensor {
    float dx, dy; // sensor offset: dx forward, dy right
    float angle;  // sensor mounting offset (in radians, compass convention)
  };
  std::vector<Sensor> sensors;

public:
  // The constructor now accepts optional parameters for scaling and noise
  // tuning.
  ParticleFilter(
      size_t n, const std::vector<SensorConfig> &sc, float start_x,
      float start_y, float start_spread = 1.0f, float noise = 0.25f,
      float motion_scale_ = 1.0f, // default: same units as map
      float sensor_scale_ =
          1.0f, // default: sensor reading already in map units
      float lateral_noise_factor_ = 0.01f, // much lower than forward noise
      float resample_distance_threshold_ = 2.0f) // threshold in map units
      : pos_noise(0.0f, noise), motion_scale(motion_scale_),
        sensor_scale(sensor_scale_),
        resample_distance_threshold(resample_distance_threshold_) {
    particles.resize(n);
    std::normal_distribution<float> dist_x(start_x, start_spread);
    std::normal_distribution<float> dist_y(start_y, start_spread);

    for (auto &p : particles) {
      p.x = std::clamp(dist_x(gen), MAP_MIN, MAP_MAX);
      p.y = std::clamp(dist_y(gen), MAP_MIN, MAP_MAX);
      p.weight = 1.0f / n;
    }
    // Convert sensor mounting angles from degrees to radians.
    float fein = M_PI / 180.0f;
    for (const auto &s : sc) {
      sensors.push_back({s.dx, s.dy, s.angle * fein});
    }
  }

  // Update the particle filter.
  // Parameters:
  //   compass_heading: current robot heading (in radians, compass style: 0 =
  //   North, CW positive) vl, vr: left and right wheel speeds (in odometry
  //   units per second) dt: time delta readings: array of sensor measurements
  //   (in sensor units)
  void update(float prev_heading, float compass_heading, float vl,
              const float *readings) {
    // In compass coordinates:
    //   forward vector: (sin(compass_heading), cos(compass_heading))
    //   right vector: (cos(compass_heading), -sin(compass_heading))
    float deltaY = vl;
    if (compass_heading != 0.0f) {
      deltaY = 2 * std::sin(compass_heading / 2) * (deltaY / compass_heading);
    }
    cum_distance += std::fabs(deltaY);

    float avg_heading = prev_heading + compass_heading / 2;

    for (auto &p : particles) {
      // Update particle's position:
      //   forward component: (sin_h, cos_h)
      //   lateral component: (cos_h, -sin_h)
      p.x = std::clamp(p.x + deltaY * std::sin(avg_heading) + pos_noise(gen),
                       MAP_MIN, MAP_MAX);
      p.y = std::clamp(p.y + deltaY * std::cos(avg_heading) + pos_noise(gen),
                       MAP_MIN, MAP_MAX);
    }
    float cos_h = std::cos(prev_heading);
    float sin_h = std::sin(prev_heading);

    // Sensor update: adjust particle weights based on sensor readings.
    float total_weight = 0.0f;
    for (auto &p : particles) {
      float weight = 1.0f;
      for (size_t i = 0; i < sensors.size(); ++i) {
        if (readings[i] >= 9998.0f)
          continue;

        const auto &s = sensors[i];

        // Convert to math angle (0 along positive X, CCW positive).
        float sensor_math_angle =
            std::fmod(PI / 2 - prev_heading + s.angle, PI2);
        std::cout << "sensor math angle: " << sensor_math_angle << std::endl;
        std::cout << "actual angle: " << prev_heading * DEG_TO_RAD << std::endl;
        // Update weight using a Gaussian error model.
        weight *= exp_approx(wall_distance(p.x + s.dx * cos_h + s.dy * sin_h,
                                           p.y - s.dx * sin_h + s.dy * cos_h,
                                           sensor_math_angle) -
                                 readings[i],
                             1.5f);
      }
      p.weight = std::max(weight, 0.000001f);
      total_weight += weight;
    }
    float inv_total = 1.0f / total_weight;
    for (auto &p : particles)
      p.weight *= inv_total;

    if (total_weight == 0.0f)
      return;
    std::cout << "resampling: " << std::endl;

    // Resample if enough (scaled) distance has been accumulated.
    if (cum_distance < resample_distance_threshold)
      return;
    cum_distance = 0.0f;

    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    float randWeight = distribution(de);

    std::vector<Particle> oldParticles = particles;

    size_t j = 0;
    float cumulativeWeight = 0.0f;
    size_t numParticles = particles.size();

    for (size_t i = 0; i < numParticles; i++) {
      float target = (static_cast<float>(i) + randWeight) / numParticles;
      while (cumulativeWeight < target && j < numParticles) {
        cumulativeWeight += oldParticles[j].weight;
        j++;
      }
      if (j > 0) {
        particles[i] = oldParticles[j - 1];
        particles[i].weight = 1.0f / numParticles;
      }
    }
  }

  // Estimate the robot's position as a weighted average of the particles.
  std::pair<float, float> estimate() const {
    float x = 0.0f, y = 0.0f;
    for (const auto &p : particles) {
      x += p.x * p.weight;
      y += p.y * p.weight;
    }
    return {x, y};
  }

private:
  // Compute the distance from (x0, y0) to the nearest wall along the direction
  // theta. theta is given in math coordinates (0 along positive X, CCW
  // positive).
  float wall_distance(double x0, double y0, double theta) {
    const double wall_min = MAP_MIN;
    const double wall_max = MAP_MAX;
    double min_dist = std::numeric_limits<double>::infinity();

    double cos_theta = std::cos(theta);
    double sin_theta = std::sin(theta);

    // Check intersection with vertical walls.
    if (fabs(cos_theta) > 1e-6) {
      double target_x = (cos_theta < 0) ? wall_min : wall_max;
      double t_x = (target_x - x0) / cos_theta;
      if (t_x >= 0) {
        double y_inter = y0 + t_x * sin_theta;
        if (y_inter >= wall_min && y_inter <= wall_max)
          min_dist = t_x;
      }
    }

    // Check intersection with horizontal walls.
    if (fabs(sin_theta) > 1e-6) {
      double target_y = (sin_theta < 0) ? wall_min : wall_max;
      double t_y = (target_y - y0) / sin_theta;
      if (t_y >= 0) {
        double x_inter = x0 + t_y * cos_theta;
        if (x_inter >= wall_min && x_inter <= wall_max)
          min_dist = std::min(min_dist, t_y);
      }
    }
    return min_dist;
  }

  // Gaussian probability approximation for sensor error.
  float exp_approx(float error, float sigma) {
    float diff = error / sigma;
    return (INV_SQRT_2PI / sigma) * fastexp(-0.5f * diff * diff);
  }
};

#endif // LOCALIZATION_H