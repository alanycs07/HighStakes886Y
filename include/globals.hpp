#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "main.h"

// MOTORS //
extern pros::Rotation armRotation;
extern pros::Distance intakeDistance;
extern pros::adi::DigitalOut intakeRaise;
extern pros::adi::DigitalOut doinker;
extern pros::adi::DigitalOut leftDoinker;
extern pros::adi::DigitalOut goalClamp;

extern pros::Optical colorSensor;
extern pros::adi::Button limitSwitch;
extern pros::Distance sorterDistance;
extern pros::Vision vision_sensor;
extern pros::Distance leftDistance;
extern pros::Distance rightDistance;
extern pros::Distance intakeDistance;
extern pros::Controller controller;

// ARM PID //
extern bool armMacro;
extern double armPosition;
extern double armkP;
extern double armkI;
extern double armkD;
extern double previous_error;
extern double target;
extern double error;
extern double integral;
extern double armVoltage;
extern int armTarget;
extern double derivative;
extern double measuredAngle;

//COLOR SORT
extern int ejectColor;
extern int noColor;
extern int red;
extern int blue;
extern bool sortingColor;
extern bool ejectRing;
extern bool sortNextRing;
extern int detected_amount;
extern double intake_Distance;

extern double hue;
extern double distance;

//ARM STUFF
extern double loadingPos;
extern double restingPos;
extern double wallPos;
extern double raisedPos;

// OTHER AUTO INFO //
extern bool autoStarted;
extern bool spinUntilDetected;
extern bool useAutoIntake;
extern bool stopIntake;
extern int outakeTime;
extern int current_peak;
extern int outtakeStartTime;


extern int autonColor;
extern int path;
extern int startingPos;

extern bool runAntiJam;

//piston
  extern bool clampExtended;
  extern bool doinkerExtended;
  extern bool rushClampExtended;
  extern bool intakeRaiseExtended;
#endif