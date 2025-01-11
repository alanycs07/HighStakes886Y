#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "main.h"

// MOTORS //
extern pros::Rotation armRotation;
extern pros::Distance intakeDistance;
extern pros::adi::DigitalOut leftDoinker;
extern pros::adi::DigitalOut rightDoinker;
extern pros::adi::DigitalOut armRetractPiston;
extern pros::adi::DigitalOut armPiston;
extern pros::adi::DigitalOut goalClamp;
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

// OTHER AUTO INFO //
extern bool autoStarted;


// AUTO SELECTOR // 
// red = false, blue = true
extern bool color;
// for auto selector
extern int current;
// random other stuff like # of rings 
extern int misc;

extern int autonColor;
extern int path;
extern int startingPos;

//piston
  extern bool clampExtended;
  extern bool armExtended;
  extern bool rightDoinkerExtended;
  extern bool leftDoinkerExtended;
#endif