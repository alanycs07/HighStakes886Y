
#include "motionprofile.hpp"

#include <iostream>
namespace mpLib {

CubicBezier::CubicBezier(const Point2D &p0, const Point2D &p1,
                         const Point2D &p2, const Point2D &p3) {
  this->p0 = p0;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  // this->P << p0.x, p1.x, p2.x, p3.x,
  //     p0.y, p1.y, p2.y, p3.y;
  this->P << p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y;

  this->coefficients << -1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0;
  this->derivativeCoef << -3, 9, -9, 3, 6, -12, 6, 0, -3, 3, 0, 0;
  this->second_derivative_coef << -6, 18, -18, 6, 6, -12, 6, 0;
}

Point2D CubicBezier::getPoint(double t) {
  Eigen::RowVector4d T;
  T << t * t * t, t * t, t, 1;
  auto result = (T * this->coefficients) * this->P;
  return Point2D(result(0), result(1));
}

Point2D CubicBezier::getDerivative(double t) {
  Eigen::RowVector3d T;
  T << t * t, t, 1;
  auto result = (T * this->derivativeCoef) * this->P;
  return Point2D(result(0), result(1));
}

Point2D CubicBezier::getSecondDerivative(double t) {
  Eigen::RowVector2d T;
  T << t, 1;
  auto result = (T * this->second_derivative_coef) * this->P;
  return Point2D(result(0), result(1));
}

double CubicBezier::getCurvature(double t) {
  Point2D d = this->getDerivative(t);
  Point2D dd = this->getSecondDerivative(t);
  double k = (d.x * dd.y - d.y * dd.x) / std::pow(d.x * d.x + d.y * d.y, 1.5);
  return k;
}

// double CubicBezier::getCurvature(Point2D d, Point2D dd) {
//   double denominator = d.x * d.x + d.y * d.y;
//   denominator *= denominator * denominator;
//   denominator = std::sqrt(denominator);
//   double k = (d.x * dd.y - d.y * dd.x) / denominator;
//   return k;
// }

Spline::Spline(std::initializer_list<virtualPath *> paths) : paths(paths) {}

Point2D Spline::getPoint(double t) {
  int index = int(t - 0.000001);
  if (index > this->paths.size() - 1) {
    index = this->paths.size() - 1;
    t = index + 1;
  }
  return this->paths.at(index)->getPoint(t - index);
}
Point2D Spline::getDerivative(double t) {
  int index = int(t - 0.000001);
  if (index > this->paths.size() - 1) {
    index = this->paths.size() - 1;
    t = index + 1;
  }
  return this->paths[index]->getDerivative(t - index);
}
Point2D Spline::getSecondDerivative(double t) {
  int index = int(t - 0.000001);
  if (index > this->paths.size() - 1) {
    index = this->paths.size() - 1;
    t = index + 1;
  }
  return this->paths[index]->getSecondDerivative(t - index);
}
double Spline::getCurvature(double t) {
  int index = int(t - 0.000001);
  if (index > this->paths.size() - 1) {
    index = this->paths.size() - 1;
    t = index + 1;
  }
  return this->paths[index]->getCurvature(t - index);
}

ProfilePoint::ProfilePoint(double x, double y, double theta, double curvature,
                           double t, double vel, double accel) {
  this->x = x;
  this->y = y;
  this->theta = theta;
  this->curvature = curvature;
  this->t = t;
  this->vel = vel;
  this->accel = accel;
}
ProfilePoint::ProfilePoint(double dist, double vel) {
  this->dist = dist;
  this->vel = vel;
}

Constraints::Constraints(double max_vel, double max_acc, double friction_coef,
                         double max_dec, double max_jerk, double track_width) {
  this->max_vel = max_vel;
  this->max_acc = max_acc;
  this->friction_coef = friction_coef;
  this->max_dec = max_dec;
  this->max_jerk = max_jerk;
  this->track_width = track_width;
}
double Constraints::maxSpeed(double curvature) {
  double max_turn_speed =
      ((2 * this->max_vel / this->track_width) * this->max_vel) /
      (fabs(curvature) * this->max_vel +
       (2 * this->max_vel / this->track_width));
  if (curvature == 0)
    return max_turn_speed;
  double max_slip_speed =
      sqrt(this->friction_coef * (1 / fabs(curvature)) * 9.81 * 39.3701);
  return std::min(max_slip_speed, max_turn_speed);
}

std::pair<double, double> Constraints::wheelSpeeds(double angularVel,
                                                   double vel) {
  double v_left = vel - angularVel * this->track_width / 2;
  double v_right = vel + angularVel * this->track_width / 2;
  return std::make_pair(v_left, v_right);
}

TrapezoidalProfile::TrapezoidalProfile(Constraints *constraints, double length,
                                       double start_vel, double end_vel) {
  this->constraints = constraints;
  this->length = length;
  this->start_vel = start_vel;
  this->end_vel = end_vel;
  double non_cruise_dist =
      constraints->max_vel * constraints->max_vel / (2 * constraints->max_acc) +
      constraints->max_vel * constraints->max_vel / (2 * constraints->max_dec);

  this->cruise_vel =
      non_cruise_dist < length
          ? constraints->max_vel
          : std::sqrt(2 *
                      (length * constraints->max_acc * constraints->max_dec) /
                      (constraints->max_acc + constraints->max_dec));

  this->accel_dist = (this->cruise_vel * this->cruise_vel -
                      this->start_vel * this->start_vel) /
                     (2 * constraints->max_acc);
  this->decel_dist =
      length + (end_vel * end_vel - this->cruise_vel * this->cruise_vel) /
                   (2 * constraints->max_dec);
}
double TrapezoidalProfile::get_vel_at_dist(double dist) {
  if (dist < 0) {
    dist = 0;
  }
  if (dist > this->length) {
    dist = this->length;
  }

  if (dist < this->accel_dist) {
    return std::sqrt(this->start_vel * this->start_vel +
                     2 * this->constraints->max_acc * dist);
  } else if (dist < this->decel_dist) {
    return this->cruise_vel;
  } else {
    return std::sqrt(this->cruise_vel * this->cruise_vel +
                     2 * -this->constraints->max_dec *
                         (dist - this->decel_dist));
  }
}

ProfileGenerator::ProfileGenerator() {}

void ProfileGenerator::generateProfile(virtualPath *path,
                                       Constraints *constraints, double dd) {

  this->constraints = constraints;
  this->dd = dd;
  this->profile.clear();
  double dist = this->dd;

  double vel = 0.00001;

  std::vector<ProfilePoint> forwardPass;

  forwardPass.push_back(ProfilePoint(0, 0));

  double t = 0;
  double curvature;
  double angular_vel;
  double angular_accel;
  double last_angular_vel;
  double max_accel;
  Point2D deriv;
  Point2D derivSecond;

  std::vector<double> cache;

  while (t <= path->getLength()) {
    deriv = path->getDerivative(t);
    derivSecond = path->getSecondDerivative(t);

    t += dd / sqrt(deriv.x * deriv.x + deriv.y * deriv.y);

    curvature = calcCurvature(deriv, derivSecond);
    cache.push_back(curvature);
    angular_vel = vel * curvature;
    angular_accel = (angular_vel - last_angular_vel) * (vel / dd);
    last_angular_vel = angular_vel;

    max_accel = this->constraints->max_acc -
                fabs(angular_accel * this->constraints->track_width / 2);
    vel = std::min(this->constraints->maxSpeed(curvature),
                   std::sqrt(vel * vel + 2 * max_accel * dd));
    dist += dd;
    auto profileOutput = ProfilePoint(dist, vel);

    Point2D pathPoint = path->getPoint(t);
    profileOutput.x = pathPoint.x;
    profileOutput.y = pathPoint.y;
    profileOutput.theta = 90 - (atan2(deriv.y, deriv.x) * 180.0 / M_PI);
    profileOutput.curvature = curvature;
    forwardPass.push_back(profileOutput);
  }

  vel = 0.00001;
  last_angular_vel = 0;
  angular_accel = 0;
  t = path->getLength();
  int i = 0;

  while (i < forwardPass.size()) {
    curvature = cache.back();
    cache.pop_back();

    angular_vel = vel * curvature;
    angular_accel = (angular_vel - last_angular_vel) * (vel / dd);
    last_angular_vel = angular_vel;

    max_accel = this->constraints->max_dec -
                fabs(angular_accel * this->constraints->track_width / 2);
    vel = std::min(this->constraints->maxSpeed(curvature),
                   std::sqrt(vel * vel + 2 * max_accel * dd));
    dist -= dd;

    auto profileOutput = forwardPass.at(forwardPass.size() - i - 1);
    if (vel < profileOutput.vel) {
      profileOutput.vel = vel;
    }
    this->profile.push_back(profileOutput);
    i++;
  }
  std::reverse(this->profile.begin(), this->profile.end());
  cache.clear();
  //? Removing this loop slows down code????
}

std::optional<ChassisSpeeds> ProfileGenerator::getProfilePoint(double d) {
  int index = int(d / this->dd);
  if (index >= this->profile.size()) {
    return std::nullopt;
  }
  double vel = this->profile[index].vel;
  double curvature = this->profile[index].curvature;
  double angular_vel = vel * curvature;
  double accel = this->profile[index].accel;
  return ChassisSpeeds(vel, angular_vel, accel,
                       Pose(this->profile[index].x, this->profile[index].y,
                            this->profile[index].theta));
}
} // namespace mpLib