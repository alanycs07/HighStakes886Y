#include "globals.hpp"
#include "pros/rotation.hpp"
#include "pros/adi.hpp"

// MOTORS //
pros::Rotation armRotation(21);
// pros::Distance intakeDistance(21);
pros::adi::DigitalOut intakeRaise(4);
pros::adi::DigitalOut doinker(2);
pros::adi::DigitalOut leftDoinker(3);
pros::adi::DigitalOut goalClamp(1);
pros::Optical colorSensor(16);
pros::adi::Button limitSwitch(5);
pros::Distance sorterDistance(1);
pros::Controller controller(pros::E_CONTROLLER_MASTER);
// ARM PID //
bool armMacro = false;
double armPosition;
double armkP = 0.4;
double armkI = 0.01;
double armkD = 0.1;
double previous_error = 0;
double target;
double error;
double integral;
double armVoltage;
int armTarget;
double derivative;
double measuredAngle;


//COLOR SORT
int ejectColor;
int noColor = 0;
int red = 1;
int blue = 2;
bool sortingColor;
bool ejectRing = false;
bool sortNextRing = false;
double hue;
double distance;
// OTHER AUTO INFO //
bool autoStarted = true;
bool spinUntilDetected = true;
bool useAutoIntake = false;


//ARM MACRO
double loadingPos = 22000;
double restingPos = 11000;
double wallPos = 72000;
//MO AUTO SELECTOR
//color 
int autonColor = 0;
//path
int path = 0;
//starting pos
int startingPos = 0; 

//piston
  bool clampExtended = false;
  bool doinkerExtended = false;
  bool rushClampExtended = false;
  bool intakeRaiseExtended = false;



