#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void new_skills() {
arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  ejectColor = blue;
  autoStarted = true;
  armMacro = true;
  armTarget = restingPos;
  chassis.setPose(0, 0, 0);

  armTarget = restingPos;
  sortingColor = true;
  chassis.moveToPose(0, 2.5, 0, 300, {.maxSpeed = 40});
  chassis.waitUntilDone();
  pros::delay(50);
  chassis.moveToPoint(-26.2, 38.8, 1100, {.maxSpeed = 100});
  useAutoIntake = true;
  spinUntilDetected = true;
  chassis.turnToPoint(-26, 19, 500, {.forwards = false});
  chassis.moveToPoint(-26, 19, 800, {.forwards = false, .maxSpeed = 50});
  chassis.waitUntilDone();
  pros::delay(150);
  goalClamp.set_value(true);
  useAutoIntake = false;
  spinUntilDetected = false;
  runAntiJam = true;
  sortingColor = true;
  chassis.turnToPoint(-60, 114, 800);
  chassis.moveToPoint(-60.7, 114, 2000, {.minSpeed = 80});
  chassis.moveToPoint(-51, 90, 900, {.forwards = false});
  chassis.turnToPoint(-52.2, 7, 900);
  chassis.moveToPoint(-52.2, 35, 1000);
  chassis.moveToPoint(-52.2, 7, 1500, {.maxSpeed = 60});
  chassis.turnToPoint(-65, 16, 800);
  chassis.waitUntilDone();
  chassis.moveToPoint(-65, 16, 1000);
  armTarget = loadingPos;
  chassis.turnToHeading(20, 700);
  sortingColor = false;
  chassis.moveToPoint(-67, 7.5, 800, {.forwards = false});
  goalClamp.set_value(false);
  chassis.moveToPoint(-66.5, 65, 1500);
  chassis.turnToPoint(-71, 65, 1000);
  chassis.moveToPoint(-71, 65, 800);

  
    
}