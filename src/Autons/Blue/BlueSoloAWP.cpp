#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void BluePositiveAWP () {
  chassis.setPose(58.6, -11.3, 68.5);
  armMacro = true;
  armTarget = wallPos;
  pros::delay(700);
  chassis.moveToPoint(29, -23.5, 1500, {.forwards = false, .maxSpeed = 90});
  chassis.waitUntilDone();
  armTarget = restingPos;
  goalClamp.set_value(true);
  pros::delay(100);
  chassis.turnToPoint(30, -47, 700);
  chassis.waitUntilDone();
  sortingColor = true;
  chassis.moveToPoint(30, -47, 1000); //intake first stack
  chassis.moveToPoint(30, -32, 1000, {.forwards = false});
  chassis.turnToPoint(75, -68, 750);
  // chassis.moveToPoint(-47, -47, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(75, -68, 2000, {.maxSpeed = 90});
  //chassis.waitUntilDone();
  //intake.move_velocity(-12000);
  //pros::delay(500);
  //sortingColor = true;
  //pros::delay(300);
  chassis.moveToPoint(50, -50, 700, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  intakeRaise.set_value(true); // intake 2nd stack ring
  pros::delay(200);
  chassis.moveToPoint(75, -70, 1500, {.maxSpeed = 45});
  chassis.waitUntilDone();
  intakeRaise.set_value(false);
  chassis.moveToPoint(50, -60, 900, {.forwards = false});
  chassis.turnToPoint(54, -2.5, 800);
  chassis.moveToPoint(54, -2.5, 2000, {.maxSpeed = 70});
  chassis.waitUntil(5);
  intakeRaise.set_value(true);
  chassis.waitUntilDone();
  intakeRaise.set_value(false);
  pros::delay(600);
  // chassis.moveToPoint(50, -50, 1200, {.forwards = false, .maxSpeed = 80});
  chassis.moveToPoint(-50, -12, 1200, {.forwards = false});
  chassis.waitUntilDone();
  sortingColor = false;
  // goalClamp.set_value(false);
  // intake.move_velocity(-12000);
  // chassis.moveToPoint(19, -22, 1000, {.maxSpeed = 85});
  // chassis.waitUntil(5);
  // intake.move_velocity(0);
  // armTarget = wallPos;
}