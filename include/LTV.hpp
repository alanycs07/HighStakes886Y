#ifndef LTV_HPP
#define LTV_HPP

#include "Eigen/Dense"
#include "dare.h"
#include "lemlibglobals.hpp"
#include <deque>

#define DEG_TO_RAD M_PI / 180.0f

inline Eigen::Matrix<double, 3, 3> S;

inline double fmod_positive(double x, double y) {
  double tmp = std::fmod(x, y);
  return x < 0 ? tmp + y : tmp;
}

inline Matrixd<2, 1> LTVController(Matrixd<3, 3> Q, Matrixd<2, 2> R,
                                   Matrixd<3, 1> Target, Matrixd<3, 1> current,
                                   double velocity, double angular, double dt) {
  Matrixd<3, 3> A{{0, 0, 0}, {0, 0, velocity}, {0, 0, 0}};
  Matrixd<3, 2> B{{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}};
  Matrixd<3, 3> discA;
  Matrixd<3, 2> discB;

  discretize(A, B, dt, &discA, &discB);

  DARE<3, 2>(discA, discB, Q, R.llt(), &S);

  auto bTranspose = discB.transpose();

  auto k = (bTranspose * S * discB + R).llt().solve(bTranspose * S * discA);
  double theta = current[2];
  double cos_theta = cos(theta);
  double sin_theta = sin(theta);

  Eigen::Matrix<double, 3, 3> rotation;
  rotation << cos_theta, sin_theta, 0, -sin_theta, cos_theta, 0, 0, 0, 1;
  Matrixd<2, 1> u = k * (rotation * (Target - current));
  return Matrixd<2, 1>{u[0] + velocity, u[1] + angular};
}

inline void follow(std::deque<double> linear, std::deque<double> angular,
                   std::deque<double> heading,
                   std::vector<std::pair<double, double>> points) {
  int i = 0;
  Matrixd<3, 3> Q{{100, 0, 0}, {0, 100, 0}, {0, 0, 57.2957796}};
  Matrixd<2, 2> R{{0.0154332066, 0}, {0, 2.0}};
  for (auto point : points) {
    Matrixd<3, 1> Target{point.first, point.second, heading[i]};
    Matrixd<3, 1> current{chassis.getPose().x, chassis.getPose().y,
                          fmod_positive(90 - chassis.getPose().theta, 360) *
                              DEG_TO_RAD};
    Matrixd<2, 1> control =
        LTVController(Q, R, Target, current, linear[i], angular[i], 0.01);
    double left = control[0] - 6 * control[1];
    double right = control[0] + 6 * control[1];
    drivetrain.leftMotors->move_velocity(left * 60 * (36.0 / 48) / 2.75 * M_PI);
    drivetrain.rightMotors->move_velocity(right * 60 * (36.0 / 48) / 2.75 *
                                          M_PI);
    i++;
    pros::delay(10);
  }
  drivetrain.leftMotors->move(0);
  drivetrain.rightMotors->move(0);
}

inline double sinc(double x) {
  if (std::abs(x) < 1e-9) {
    return 1.0 - 1.0 / 6.0 * x * x;
  } else {
    return std::sin(x) / x;
  }
}/*

inline void followRamsete(std::deque<double> linear, std::deque<double> angular,
                          std::deque<double> heading,
                          std::vector<std::pair<double, double>> points) {
  int i = 0;
  double b = 2.00;
  double zeta = 0.7;
  for (auto point : points) {
    linear[i] *= 0.0254;
    double theta =
        fmod_positive(90 - chassis.getPose().theta, 360) * DEG_TO_RAD;
    double cos_theta = cos(theta);
    double sin_theta = sin(theta);

    Eigen::Matrix<double, 3, 3> rotation{
        {cos_theta, sin_theta, 0}, {-sin_theta, cos_theta, 0}, {0, 0, 1}};
    Matrixd<3, 1> locale{(points[i].first - chassis.getPose().x) * 0.0254,
                         (points[i].second - chassis.getPose().y) * 0.0254,
                         heading[i] - theta};
    Matrixd<3, 1> error = locale * rotation;
    while (error[2] > M_PI) {
      error[2] -= 2 * M_PI;
    }
    while (error[2] < -M_PI) {
      error[2] += 2 * M_PI;
    }
    double k = 2.0 * zeta * sqrt(pow(angular[i], 2) + b * pow(linear[i], 2));
    double v = linear[i] * cos(error[2]) + k * error[0];
    double w =
        angular[i] + k * error[2] + b * linear[i] * sinc(error[2]) * error[1];
    double left = v - 0.254 * w;
    double right = v + 0.254 * w;
    drivetrain.leftMotors->move_velocity(39.9701 * left * 60 * (36.0 / 48) /
                                         2.75 * M_PI);
    drivetrain.rightMotors->move_velocity(39.9701 * right * 60 * (36.0 / 48) /
                                          2.75 * M_PI);
    i += 1;
    pros::delay(10);
  }
  drivetrain.leftMotors->move(0);
  drivetrain.rightMotors->move(0);
}*/

#endif // LTV_HPP