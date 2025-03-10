#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void BlueNegativeQuals(){
  armMacro = true;
  armTarget = restingPos;
  chassis.setPose(-55, 23.5, 270);
  chassis.moveToPose(-27, 23.5, 270, 1000, {.forwards = false});
  chassis.waitUntilDone();
  goalClamp.set_value(true);
  pros::delay(500);
  chassis.turnToPoint(-9, 39, 1000);
  pros::delay(300);
  sortingColor = true;
  chassis.moveToPoint(-9, 39, 1000);
  chassis.turnToPoint(-6, 47, 1000);
  chassis.moveToPoint(-6, 47, 1000);
  pros::delay(500);
  chassis.moveToPoint(-12, 33, 1000, {.forwards = false});
  chassis.turnToPoint(-20, 42.5, 1000);
  chassis.moveToPoint(-20, 42.5, 1000);
  chassis.turnToHeading(270, 1000);
  chassis.moveToPose(-65, 65, 315, 2000, {.minSpeed = 60});
  chassis.waitUntilDone();
  pros::delay(200);
  chassis.moveToPoint(-65, 65, 1200, {.maxSpeed = 30});
  chassis.turnToHeading(180, 500);
  //QUALS - 5 RING + BAR TOUCH//
  chassis.turnToPoint(-23.5, 0, 1000);
  chassis.moveToPoint(-33.5, 15.6, 1000);
  chassis.waitUntilDone();
  sortingColor = false;
  chassis.moveToPoint(-23.5, 0, 3000, {.maxSpeed = 40});
  armTarget = wallPos;

  // // ELIMS ONLY BELOW - 6 RING//
  // chassis.turnToPoint(-51, 10, 500);
  // chassis.waitUntilDone();
  // intakeRaise.set_value(false);
  // chassis.moveToPoint(-51, 10, 1500, {.maxSpeed = 72});
  // chassis.waitUntilDone();
  // pros::delay(200);
  // intakeRaise.set_value(true);
  // pros::delay(700);
  // chassis.moveToPoint(-58, 19, 1000, {.forwards = false});
  // chassis.waitUntilDone();
  // pros::delay(500);
  // conveyor.move_velocity(0);
  clampExtended = true;
}