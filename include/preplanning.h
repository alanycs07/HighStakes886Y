#ifndef PREPLANNING_H
#define PREPLANNING_H

#include <algorithm>
#include <cmath>
#include <vector>

// Struct holding the state at a point along the trajectory.
struct Pose {
  double x;               // x-coordinate
  double y;               // y-coordinate
  double theta;           // target (heading) angle in radians
  double linear_velocity; // in feet per second (conversion applied)
  double angular_velocity;// in radians per second
};

class trajectory {
private:
  // Control points for the cubic Bezier curve: start, control point 1, control point 2, end.
  std::vector<std::vector<double>> ctrlPts;

  // Total arc length along the curve (computed once).
  double totalDistance;

  // Gaussian quadrature coefficients (24-point) used for integration.
  // Each entry is {weight, node}. These nodes are in the interval [-0.5, 0.5].
  std::vector<std::vector<double>> coeff{
      {0.1279381953467522, -0.0320284464313028},
      {0.1279381953467522,  0.0320284464313028},
      {0.1258374563468283, -0.09555943373680815},
      {0.1258374563468283,  0.09555943373680815},
      {0.1216704729278034, -0.1575213398480817},
      {0.1216704729278034,  0.1575213398480817},
      {0.1155056680537256, -0.21689675381302255},
      {0.1155056680537256,  0.21689675381302255},
      {0.1074442701159656, -0.2727107356944198},
      {0.1074442701159656,  0.2727107356944198},
      {0.0976186521041139, -0.32404682596848775},
      {0.0976186521041139,  0.32404682596848775},
      {0.0861901615319533, -0.3700620957892772},
      {0.0861901615319533,  0.3700620957892772},
      {0.0733464814110803, -0.41000099298695145},
      {0.0733464814110803,  0.41000099298695145},
      {0.0592985849154368, -0.44320776350220055},
      {0.0592985849154368,  0.44320776350220055},
      {0.0442774388174198, -0.4691372760013664},
      {0.0442774388174198,  0.4691372760013664},
      {0.0285313886289337, -0.48736427798565475},
      {0.0285313886289337,  0.48736427798565475},
      {0.0123412297999872, -0.49759360999851065},
      {0.0123412297999872,  0.49759360999851065}
  };

  // Evaluate the derivative of the cubic Bezier at parameter t.
  std::pair<double, double> derivative(double t) {
    double t1 = 1 - t;
    double xD = 3 * t1 * t1 * (ctrlPts[1][0] - ctrlPts[0][0]) +
                6 * t1 * t * (ctrlPts[2][0] - ctrlPts[1][0]) +
                3 * t * t * (ctrlPts[3][0] - ctrlPts[2][0]);
    double yD = 3 * t1 * t1 * (ctrlPts[1][1] - ctrlPts[0][1]) +
                6 * t1 * t * (ctrlPts[2][1] - ctrlPts[1][1]) +
                3 * t * t * (ctrlPts[3][1] - ctrlPts[2][1]);
    return std::make_pair(xD, yD);
  }

  // Evaluate the cubic Bezier point at parameter t.
  std::pair<double, double> bezierPoint(double t) {
    double t1 = 1 - t;
    double x = t1 * t1 * t1 * ctrlPts[0][0] +
               3 * t1 * t1 * t   * ctrlPts[1][0] +
               3 * t1 * t   * t * ctrlPts[2][0] +
               t * t * t       * ctrlPts[3][0];
    double y = t1 * t1 * t1 * ctrlPts[0][1] +
               3 * t1 * t1 * t   * ctrlPts[1][1] +
               3 * t1 * t   * t * ctrlPts[2][1] +
               t * t * t       * ctrlPts[3][1];
    return std::make_pair(x, y);
  }

  // Compute the arc length from 0 to t using 24-point Gaussian quadrature.
  // (The integration is scaled for an arbitrary upper limit t.)
  double arcLength(double t) {
    double s = 0.0;
    // Map each node from [-0.5, 0.5] to [0, t]:
    // u = t * (node + 0.5), du = t/1 * d(node+0.5) so that the scaling factor is t/2.
    for (int i = 0; i < 24; i++) {
      double u = t * (coeff[i][1] + 0.5);
      auto d = derivative(u);
      double mag = std::sqrt(d.first * d.first + d.second * d.second);
      s += coeff[i][0] * mag;
    }
    s *= t * 0.5;
    return s;
  }

  // Given a distance s (0 <= s <= totalDistance), find the corresponding parameter t
  // using Newton’s method. (The derivative of arcLength is |B′(t)|.)
  double findTforDistance(double s) {
    if (s <= 0)
      return 0;
    if (s >= totalDistance)
      return 1;
    // Initial guess: proportion of the total distance.
    double t = s / totalDistance;
    const int max_iter = 10;
    const double tol = 1e-5;
    for (int i = 0; i < max_iter; i++) {
      double currentArc = arcLength(t);
      double error = currentArc - s;
      auto d = derivative(t);
      double speed = std::sqrt(d.first * d.first + d.second * d.second);
      if (speed < 1e-6)
        break;
      double dt = error / speed;
      t -= dt;
      t = std::max(0.0, std::min(1.0, t));
      if (std::fabs(dt) < tol)
        break;
    }
    return t;
  }

  // Compute a target linear velocity at the given parameter t (and traveled distance s)
  // based on curvature, acceleration, and deceleration limits.
  double generateVelocity(double t, double traveledS) {
    auto d = derivative(t);
    double speed = std::sqrt(d.first * d.first + d.second * d.second);
    // Estimate the second derivative using finite differences.
    double h = 1e-5;
    auto d_plus = derivative(std::min(t + h, 1.0));
    auto d_minus = derivative(std::max(t - h, 0.0));
    double xDD = (d_plus.first - d_minus.first) / (2 * h);
    double yDD = (d_plus.second - d_minus.second) / (2 * h);
    // Curvature = |B′ × B″| / |B′|³.
    double curv = (speed > 1e-6) ? std::fabs(d.first * yDD - d.second * xDD) / (speed * speed * speed) : 0;
    double v_curve = (curv > 1e-6) ? std::sqrt(9.81 * 39.97 * (1.0 / curv) * frictionCoefficient) : robotspeed;
    // Compute velocity limits from acceleration/deceleration.
    double v_accel = std::sqrt(current_speed * current_speed + 2 * acceleration * traveledS);
    double v_decel = std::sqrt(2 * deacceleration * (totalDistance - traveledS));
    double v = std::min({v_accel, v_decel, robotspeed, v_curve});
    return v;
  }

public:
  // Dynamic parameters (all speeds in inches per second and accelerations in inches per second^2).
  double acceleration;    // maximum acceleration
  double deacceleration;  // maximum deceleration
  double robotspeed;      // maximum linear speed
  double frictionCoefficient;
  double current_speed;   // initial speed

  // The constructor takes the 4x2 control point matrix along with the dynamics.
  // Note: The acceleration, deacceleration, and speeds are multiplied by 12 to convert units.
  trajectory(const std::vector<std::vector<double>> &controlPoints,
             double accel, double deaccel, double max_speed, double init_speed,
             double friction)
      : ctrlPts(controlPoints),
        acceleration(accel * 12),
        deacceleration(deaccel * 12),
        robotspeed(max_speed * 12),
        frictionCoefficient(friction),
        current_speed(init_speed * 12) {
    // Compute the total distance along the Bezier curve (from t=0 to t=1).
    totalDistance = arcLength(1.0);
  }

  // Given a distance s along the curve, compute and return the corresponding Pose.
  // This method performs an on-the-fly inversion (via Newton’s method) of the arc-length function.
  Pose getStateAtDistance(double s) {
    // Clamp s to the valid range.
    s = std::max(0.0, std::min(s, totalDistance));
    // Invert arc-length to obtain the corresponding Bezier parameter t.
    double t = findTforDistance(s);
    auto pt = bezierPoint(t);
    auto d = derivative(t);
    double heading = std::atan2(d.second, d.first);
    if (heading < 0)
      heading += 2 * M_PI;
    // Determine the target linear velocity at this point.
    double v = generateVelocity(t, s);
    // Angular velocity is approximated as curvature times linear velocity.
    double speed = std::sqrt(d.first * d.first + d.second * d.second);
    double h = 1e-5;
    auto d_plus = derivative(std::min(t + h, 1.0));
    auto d_minus = derivative(std::max(t - h, 0.0));
    double xDD = (d_plus.first - d_minus.first) / (2 * h);
    double yDD = (d_plus.second - d_minus.second) / (2 * h);
    double curv = (speed > 1e-6) ? std::fabs(d.first * yDD - d.second * xDD) / (speed * speed * speed) : 0;
    double omega = curv * v;
    // Assemble the Pose.
    Pose pose;
    pose.x = pt.first;
    pose.y = pt.second;
    pose.theta = heading;
    // Convert linear velocity from inches per second to feet per second.
    pose.linear_velocity = v / 12.0;
    pose.angular_velocity = omega;
    return pose;
  }

  // Returns the total distance along the curve.
  double getTotalDistance() const {
    return totalDistance;
  }
};

#endif
