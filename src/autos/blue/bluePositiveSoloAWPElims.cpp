#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void bluePositiveSoloAWPElims() {
  autoStarted = true;
  chassis.setPose(57.5, -14, 45);
  armTarget = loadingPos;
  pros::delay(500);
  conveyor.move_velocity(-12000);
  chassis.moveToPose(61.5, -10, 45, 700);
  chassis.waitUntilDone();
  conveyor.move_velocity(0);
  pros::delay(100);
  armTarget = allianceStakePos;
  pros::delay(400);
  chassis.moveToPoint(57.5, -14, 500, {.forwards = false});
  chassis.turnToPoint(50, 0, 500, {.maxSpeed = 60});
  chassis.waitUntilDone();
  intake.move_velocity(-12000);
  armTarget = armRaisedPos;
  chassis.moveToPoint(50, 0, 500, {.maxSpeed = 60});
  chassis.waitUntilDone();
  // pros::delay(300);
  intakeRaise.set_value(true);
  // armTarget = 12000;
  pros::delay(500);
  chassis.moveToPoint(52, -7, 700, {.forwards = false, .maxSpeed = 60});
  chassis.turnToPoint(27, -21.5, 700, {.forwards = false});
  chassis.moveToPoint(38, -15, 400, {.forwards = false});
  chassis.moveToPoint(27, -21.5, 700, {.forwards = false, .maxSpeed = 50});
  chassis.waitUntilDone();
  pros::delay(200);
  goalClamp.set_value(true);
  pros::delay(200);
  chassis.turnToPoint(24, -41, 1000, {.maxSpeed = 60});
  chassis.waitUntilDone();
  conveyor.move_velocity(-12000);
  chassis.moveToPoint(24, -41, 1000);
  chassis.moveToPoint(24, -35, 500, {.forwards = false});
  chassis.turnToPoint(58, -35, 500);
  chassis.moveToPoint(58, -35, 700);
  chassis.waitUntil(10);
  conveyor.move_velocity(0);
  intake.move_velocity(0);
  chassis.turnToPoint(70, -65, 400);
  chassis.moveToPoint(70, -65, 1000, {.maxSpeed = 70});
  chassis.waitUntil(10);
  intake.move_velocity(-12000);
  chassis.waitUntilDone();
  conveyor.move_velocity(-12000);

  isExtended1 = true;
}
