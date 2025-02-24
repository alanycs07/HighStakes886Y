#ifndef PREPLANNING_H
#define PREPLANNING_H

#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>

class trajectory {
private:
  double traveledD = 0;
  double distance = 0;
  double t = 0;
  std::pair<double, double> firstDerivative;

  // Gaussian quadrature coefficients for integration (same as before)
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
  // ctrlPts[0] = start, ctrlPts[1] = control point 1,
  // ctrlPts[2] = control point 2, ctrlPts[3] = end.
  std::vector<std::vector<double>> ctrlPts;

  // Compute first derivative at parameter t using the standard cubic Bezier
  // derivative.
  void derivative() {
    double xD = 3 * pow(1 - t, 2) * (ctrlPts[1][0] - ctrlPts[0][0]) +
                6 * (1 - t) * t * (ctrlPts[2][0] - ctrlPts[1][0]) +
                3 * t * t * (ctrlPts[3][0] - ctrlPts[2][0]);
    double yD = 3 * pow(1 - t, 2) * (ctrlPts[1][1] - ctrlPts[0][1]) +
                6 * (1 - t) * t * (ctrlPts[2][1] - ctrlPts[1][1]) +
                3 * t * t * (ctrlPts[3][1] - ctrlPts[2][1]);
    firstDerivative = std::make_pair(xD, yD);
  }

  std::pair<double, double> get_derivative() {
    derivative();
    return firstDerivative;
  }

  // Compute curvature using the derivative and second derivative.
  double curvature() {
    double x2 = ctrlPts[0][0] * (-6 * t + 6) + ctrlPts[1][0] * (18 * t - 12) +
                ctrlPts[2][0] * (-18 * t + 6) + ctrlPts[3][0] * 6 * t;
    double y2 = ctrlPts[0][1] * (-6 * t + 6) + ctrlPts[1][1] * (18 * t - 12) +
                ctrlPts[2][1] * (-18 * t + 6) + ctrlPts[3][1] * 6 * t;
    return (firstDerivative.first * y2 - firstDerivative.second * x2) /
           pow(firstDerivative.first * firstDerivative.first +
                   firstDerivative.second * firstDerivative.second,
               1.5);
  }

  // Generate a velocity based on curvature, acceleration, and remaining
  // distance.
  double generateVelocity() {
    double curv = curvature();
    double curvatureVel =
        sqrt(9.81 * 39.97 * fabs(1 / curv) * frictionCoefficient);
    double accelVel = current_speed + acceleration * 0.01;
    double deaccelVel = sqrt(2 * deacceleration * (distance - traveledD));
    return std::min({accelVel, robotspeed, curvatureVel, deaccelVel}) *
           robot_direction;
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
  std::vector<std::pair<double, double>> points;
  int robot_direction = 1;
  double frictionCoefficient = 0.6;
  double current_speed = 0, current_angle;
  double acceleration, deacceleration, robotspeed;
  std::deque<double> targetLinearVelocity;
  std::deque<double> targetAngle;
  std::deque<double> targetAngularVelocity;

  // New constructor:
  // Instead of two poses and stretch factors, we now simply pass in a 4x2
  // matrix of control points. Each control point is specified as {x, y} in
  // order: start, control point 1, control point 2, and end.
  trajectory(const std::vector<std::vector<double>> &controlPoints,
             double accel, double deaccel, double max_speed, double direction,
             double friction = 0.6)
      : ctrlPts(controlPoints) {

    // Set robot parameters.
    robot_direction = direction;
    acceleration = accel * 12; // Convert to inches per second if necessary.
    deacceleration = deaccel * 12;
    robotspeed = max_speed * 12;
    frictionCoefficient = friction;

    // Set initial position from the start control point.
    double x = ctrlPts[0][0];
    double y = ctrlPts[0][1];

    // Determine the initial heading from the derivative at t = 0.
    // For a cubic Bezier, the derivative at t = 0 is 3*(P1 - P0).
    current_angle =
        atan2(ctrlPts[1][1] - ctrlPts[0][1], ctrlPts[1][0] - ctrlPts[0][0]);

    // Precompute the total distance along the curve using Gaussian quadrature.
    for (int i = 0; i < 24; i++) {
      t = coeff[i][1] + 0.5;
      derivative();
      double distanceP = sqrt(firstDerivative.first * firstDerivative.first +
                              firstDerivative.second * firstDerivative.second);
      distance += coeff[i][0] * distanceP;
    }
    distance *= 0.5;
    t = 0;

    // Generate points along the Bezier curve.
    while (true) {
      derivative();
      current_speed = fabs(generateVelocity());
      double derivMag = sqrt(firstDerivative.first * firstDerivative.first +
                             firstDerivative.second * firstDerivative.second);
      if (derivMag == 0)
        derivMag = 1;
      t += current_speed * 0.01 / derivMag;
      if (t >= 1)
        break;

      traveledD += current_speed * 0.01;
      targetLinearVelocity.push_back(current_speed * robot_direction / 12);

      double oldX = x, oldY = y;
      // Cubic Bezier curve formula.
      double t1 = 1 - t;
      x = t1 * t1 * t1 * ctrlPts[0][0] + 3 * t1 * t1 * t * ctrlPts[1][0] +
          3 * t1 * t * t * ctrlPts[2][0] + t * t * t * ctrlPts[3][0];
      y = t1 * t1 * t1 * ctrlPts[0][1] + 3 * t1 * t1 * t * ctrlPts[1][1] +
          3 * t1 * t * t * ctrlPts[2][1] + t * t * t * ctrlPts[3][1];

      points.push_back(std::make_pair(x, y));
      double angle =
          atan2(robot_direction * (y - oldY), robot_direction * (x - oldX));
      if (angle < 0)
        angle += 2 * M_PI;
      targetAngle.push_back(angle);
      double angularVelocity = anglewrap(angle, current_angle) / 0.01;
      targetAngularVelocity.push_back(angularVelocity);
      current_angle = angle;
    }

    // Append the final control point and corresponding velocities.
    points.push_back(std::make_pair(ctrlPts[3][0], ctrlPts[3][1]));
    targetAngle.push_back(current_angle);
    targetAngularVelocity.push_back(anglewrap(current_angle, current_angle) /
                                    0.01);
    targetLinearVelocity.push_back(0.001);
  }
};

#endif
