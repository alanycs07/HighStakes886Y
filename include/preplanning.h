#ifndef PREPLANNING_H
#define PREPLANNING_H

#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <stdexcept>

class trajectory {
private:
  double parameter = 0; // bezier curve parameter (was t)
  std::pair<double, double> firstDerivative;
  double totalDistance = 0;

  // Gaussian quadrature coefficients for integration
  std::vector<std::vector<double>> coeff{
      {0.1279381953467522, -0.0320284464313028},
      {0.1279381953467522, 0.0320284464313028},
      {0.1258374563468283, -0.09555943373680815},
      {0.1258374563468283, 0.09555943373680815},
      {0.1216704729278034, -0.1575213398480817},
      {0.1216704729278034, 0.1575213398480817},
      {0.1155056680537256, -0.21689675381302255},
      {0.1155056680537256, 0.21689675381302255},
      {0.1074442701159656, -0.2727107356944198},
      {0.1074442701159656, 0.2727107356944198},
      {0.0976186521041139, -0.32404682596848775},
      {0.0976186521041139, 0.32404682596848775},
      {0.0861901615319533, -0.3700620957892772},
      {0.0861901615319533, 0.3700620957892772},
      {0.0733464814110803, -0.41000099298695145},
      {0.0733464814110803, 0.41000099298695145},
      {0.0592985849154368, -0.44320776350220055},
      {0.0592985849154368, 0.44320776350220055},
      {0.0442774388174198, -0.4691372760013664},
      {0.0442774388174198, 0.4691372760013664},
      {0.0285313886289337, -0.48736427798565475},
      {0.0285313886289337, 0.48736427798565475},
      {0.0123412297999872, -0.49759360999851065},
      {0.0123412297999872, 0.49759360999851065}};

  // Matrix of control points (each control point is a vector {x, y})
  std::vector<std::vector<double>> ctrlPts;

  // Compute first derivative at parameter t using the standard cubic Bezier
  // derivative
  void derivative(double t) {
    double xD = 3 * pow(1 - t, 2) * (ctrlPts[1][0] - ctrlPts[0][0]) +
                6 * (1 - t) * t * (ctrlPts[2][0] - ctrlPts[1][0]) +
                3 * t * t * (ctrlPts[3][0] - ctrlPts[2][0]);
    double yD = 3 * pow(1 - t, 2) * (ctrlPts[1][1] - ctrlPts[0][1]) +
                6 * (1 - t) * t * (ctrlPts[2][1] - ctrlPts[1][1]) +
                3 * t * t * (ctrlPts[3][1] - ctrlPts[2][1]);
    firstDerivative = std::make_pair(xD, yD);
  }

  // Compute curvature using the derivative and second derivative at parameter t
  double curvature(double t) {
    derivative(t);
    double x2 = ctrlPts[0][0] * (-6 * t + 6) + ctrlPts[1][0] * (18 * t - 12) +
                ctrlPts[2][0] * (-18 * t + 6) + ctrlPts[3][0] * 6 * t;
    double y2 = ctrlPts[0][1] * (-6 * t + 6) + ctrlPts[1][1] * (18 * t - 12) +
                ctrlPts[2][1] * (-18 * t + 6) + ctrlPts[3][1] * 6 * t;
    
    // Added check for zero denominator to avoid division by zero
    double denominator = firstDerivative.first * firstDerivative.first + 
                         firstDerivative.second * firstDerivative.second;
    if (fabs(denominator) < 1e-10) {
        return 0.0; // Return zero curvature for nearly straight segments
    }
    
    return (firstDerivative.first * y2 - firstDerivative.second * x2) /
           pow(denominator, 1.5);
  }

  // Generate a velocity based on curvature, acceleration, and remaining
  // distance
  double generateVelocity(double t, double traveledDistance) {
    double curv = curvature(t);
    
    // Check for near-zero curvature to avoid division by zero
    double curvatureVel = (fabs(curv) < 1e-10) ? 
                          robotspeed : 
                          sqrt(9.81 * 39.97 * fabs(1 / curv) * frictionCoefficient);
    
    double accelVel =
        sqrt(current_speed * current_speed + 2 * acceleration * distanceStep);
    double deaccelVel =
        sqrt(2 * deacceleration * (totalDistance - traveledDistance));
    
    // Handle negative values that could lead to NaN
    if (deaccelVel < 0) deaccelVel = robotspeed;
    
    return std::min({accelVel, robotspeed, curvatureVel, deaccelVel}) *
           robot_direction;
  }

  // Evaluate point on Bezier curve at parameter t
  std::pair<double, double> evaluatePoint(double t) {
    // Clamp t to [0,1] range to ensure valid values
    t = std::max(0.0, std::min(1.0, t));
    
    double t1 = 1 - t;
    double x = t1 * t1 * t1 * ctrlPts[0][0] + 3 * t1 * t1 * t * ctrlPts[1][0] +
               3 * t1 * t * t * ctrlPts[2][0] + t * t * t * ctrlPts[3][0];
    double y = t1 * t1 * t1 * ctrlPts[0][1] + 3 * t1 * t1 * t * ctrlPts[1][1] +
               3 * t1 * t * t * ctrlPts[2][1] + t * t * t * ctrlPts[3][1];
    return std::make_pair(x, y);
  }

  // Wrap angles to the range [-pi, pi]
  double anglewrap(double target, double actual) {
    double error = target - actual;
    while (error >= M_PI)
      error -= 2 * M_PI;
    while (error <= -M_PI)
      error += 2 * M_PI;
    return error;
  }

public:
  double frictionCoefficient = 0.6;
  int robot_direction = 1;
  double current_speed = 0;
  double current_angle;
  double acceleration, deacceleration, robotspeed;
  double max_angular_velocity; // New parameter for maximum angular velocity
  double distanceStep; // User-defined distance between points

  // Path data stored by distance
  std::vector<double> distancePoints;               // Distances along path
  std::vector<std::pair<double, double>> positions; // Coordinates (x,y)
  std::vector<double> parameters;                   // Parameter t values
  std::vector<double> targetLinearVelocity;  // Linear velocity at each point
  std::vector<double> targetAngle;           // Heading angle at each point
  std::vector<double> targetAngularVelocity; // Angular velocity at each point

  // Constructor taking control points and step size, now with max angular velocity
  trajectory(const std::vector<std::vector<double>> &controlPoints,
             double accel, double deaccel, double max_speed, double direction,
             double stepDistance, double max_angular_vel = M_PI,
             double friction = 0.6)
      : ctrlPts(controlPoints), distanceStep(stepDistance) {

    // Validate control points
    if (controlPoints.size() != 4) {
      throw std::invalid_argument("Exactly 4 control points required for cubic Bezier");
    }
    
    for (const auto& point : controlPoints) {
      if (point.size() != 2) {
        throw std::invalid_argument("Each control point must have exactly 2 coordinates (x,y)");
      }
    }

    // Set robot parameters
    robot_direction = direction;
    acceleration = accel * 12; // Convert to inches per second if necessary
    deacceleration = deaccel * 12;
    robotspeed = max_speed * 12;
    frictionCoefficient = friction;
    max_angular_velocity = max_angular_vel; // Store max angular velocity

    // Calculate initial heading from first segment
    current_angle =
        atan2(ctrlPts[1][1] - ctrlPts[0][1], ctrlPts[1][0] - ctrlPts[0][0]);

    // Calculate total path length using Gaussian quadrature
    for (int i = 0; i < 24; i++) {
      double t = coeff[i][1] + 0.5;
      derivative(t);
      double segmentLength =
          sqrt(firstDerivative.first * firstDerivative.first +
               firstDerivative.second * firstDerivative.second);
      totalDistance += coeff[i][0] * segmentLength;
    }
    totalDistance *= 0.5;

    // Initialize first point
    double traveledDistance = 0;
    parameter = 0;
    distancePoints.push_back(traveledDistance);
    positions.push_back(std::make_pair(ctrlPts[0][0], ctrlPts[0][1]));
    parameters.push_back(parameter);
    targetLinearVelocity.push_back(0);
    targetAngle.push_back(current_angle);
    targetAngularVelocity.push_back(0);

    // Generate points at equal distance intervals
    while (traveledDistance < totalDistance && parameter < 1.0) {
      // Calculate next distance point
      traveledDistance += distanceStep;
      if (traveledDistance > totalDistance) {
        traveledDistance = totalDistance;
      }

      // Calculate derivative at current parameter value
      derivative(parameter);
      double derivMag = sqrt(firstDerivative.first * firstDerivative.first +
                             firstDerivative.second * firstDerivative.second);

      // Prevent division by zero
      if (derivMag < 1e-10) {
        derivMag = 1e-10;
      }

      // Increment parameter proportionally to distance step and inverse of
      // derivative magnitude
      double deltaT = distanceStep / derivMag;
      parameter += deltaT;

      if (parameter >= 1.0) {
        parameter = 1.0;
      }

      // Calculate position at this parameter
      auto point = evaluatePoint(parameter);
      auto prevPoint = positions.back();

      // Calculate velocity
      current_speed = fabs(generateVelocity(parameter, traveledDistance));

      // Calculate angle
      double angle = atan2(robot_direction * (point.second - prevPoint.second),
                           robot_direction * (point.first - prevPoint.first));
      
      // Calculate angular velocity and limit it
      double angleDiff = anglewrap(angle, current_angle);
      double rawAngularVelocity = angleDiff * current_speed / distanceStep;
      
      // Apply maximum angular velocity limit
      double angularVelocity = std::max(-max_angular_velocity, 
                                        std::min(max_angular_velocity, rawAngularVelocity));
      
      // If we need to limit angular velocity, also limit linear velocity to maintain path
      if (fabs(rawAngularVelocity) > max_angular_velocity && fabs(angleDiff) > 1e-6) {
        double scaleFactor = fabs(max_angular_velocity / rawAngularVelocity);
        current_speed *= scaleFactor;
      }

      // Store data
      distancePoints.push_back(traveledDistance);
      positions.push_back(point);
      parameters.push_back(parameter);
      targetLinearVelocity.push_back(current_speed * robot_direction / 12);
      targetAngle.push_back(angle);
      targetAngularVelocity.push_back(angularVelocity);

      current_angle = angle;
    }

    // Ensure final point is added if not already
    if (parameter >= 1.0 && (distancePoints.back() < totalDistance - 1e-6 ||
        (positions.back().first != evaluatePoint(1.0).first || 
         positions.back().second != evaluatePoint(1.0).second))) {
      
      parameter = 1.0;
      auto finalPoint = evaluatePoint(1.0);
      distancePoints.push_back(totalDistance);
      positions.push_back(finalPoint);
      parameters.push_back(1.0);
      targetLinearVelocity.push_back(0);
      targetAngle.push_back(current_angle);
      targetAngularVelocity.push_back(0);
    }
  }

  // Function to get path information at a specific distance
  std::vector<double> getInfoAtDistance(double distance) {
    // Clamp distance to valid range
    distance = std::max(0.0, std::min(distance, totalDistance));

    // Handle empty path case
    if (distancePoints.empty()) {
      return {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    }

    // Find nearest distance points
    size_t index = 0;
    while (index < distancePoints.size() - 1 &&
           distancePoints[index + 1] < distance) {
      index++;
    }

    // If exact match
    if (fabs(distancePoints[index] - distance) < 1e-6) {
      return {
          positions[index].first,      // x coordinate
          positions[index].second,     // y coordinate
          targetAngle[index],          // target angular (heading)
          targetLinearVelocity[index], // target linear velocity
          targetAngularVelocity[index], // angular velocity
          parameters[index]            // parameter t
      };
    }

    // Interpolate between points
    if (index < distancePoints.size() - 1) {
      // Prevent division by zero
      double denominator = distancePoints[index + 1] - distancePoints[index];
      double ratio = (denominator < 1e-10) ? 0.0 : 
                     (distance - distancePoints[index]) / denominator;

      double x = positions[index].first +
                 ratio * (positions[index + 1].first - positions[index].first);
      double y =
          positions[index].second +
          ratio * (positions[index + 1].second - positions[index].second);
      double angle =
          targetAngle[index] +
          ratio * anglewrap(targetAngle[index + 1], targetAngle[index]);
      double velocity = targetLinearVelocity[index] +
                        ratio * (targetLinearVelocity[index + 1] -
                                 targetLinearVelocity[index]);
      double param = parameters[index] +
                     ratio * (parameters[index + 1] - parameters[index]);
      double angVelocity = targetAngularVelocity[index] +
                           ratio * (targetAngularVelocity[index + 1] -
                                    targetAngularVelocity[index]);

      return {x, y, angle, velocity, angVelocity, param};
    }

    // Fallback to last point
    return {positions.back().first,       positions.back().second,
            targetAngle.back(),           targetLinearVelocity.back(),
            targetAngularVelocity.back(), parameters.back()};
  }

  // Get total path distance
  double getTotalDistance() { return totalDistance; }
  
  // Get maximum angular velocity
  double getMaxAngularVelocity() { return max_angular_velocity; }
  
  // Set maximum angular velocity and recalculate path if needed
  void setMaxAngularVelocity(double max_ang_vel) {
    // Update parameter
    max_angular_velocity = max_ang_vel;
    
    // Recalculate angular velocities with the new limit
    for (size_t i = 1; i < targetAngularVelocity.size() - 1; i++) {
      if (fabs(targetAngularVelocity[i]) > max_angular_velocity) {
        double scaleFactor = max_angular_velocity / fabs(targetAngularVelocity[i]);
        targetAngularVelocity[i] = targetAngularVelocity[i] > 0 ? 
                                   max_angular_velocity : -max_angular_velocity;
        
        // Scale down linear velocity to maintain path accuracy
        targetLinearVelocity[i] *= scaleFactor;
      }
    }
  }
};

#endif