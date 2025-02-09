#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET (BlueNegGoalCurve_txt);
ASSET (BlueNegativeRingStackCurve_txt);

void Blue7Ring(){
    armMacro = true;
    // ejectRing = red;
    chassis.setPose(61, 14, 165.3);
    armTarget = wallPos;
    pros::delay(620);
    chassis.follow(BlueNegGoalCurve_txt, 9, 1200, false);
    armTarget = restingPos;
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    //middle ring grab
    chassis.turnToHeading(310,500);
    chassis.waitUntilDone();
    sortingColor = true;
    chassis.moveToPoint(9.5, 44, 900, {.maxSpeed = 80}); //first ring
    //chassis.follow(RedNegativeRingStackCurve_txt, 10, 1500);
    chassis.turnToHeading(350, 400);
    chassis.moveToPoint(10.5, 55, 600, {.maxSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(11, 45, 700, {.forwards = false});
    chassis.turnToPoint(23, 50, 600);
    chassis.moveToPoint(23, 50, 700);
    chassis.waitUntilDone();
    pros::delay(100);
    // chassis.turnToHeading(120, 400);
    chassis.moveToPose(58, 62, 50, 1000, {.lead = 0.3, .minSpeed = 70});
    chassis.moveToPoint(70, 65, 1300, {.maxSpeed = 90});
    chassis.waitUntilDone();
    pros::delay(300);
    chassis.moveToPoint(58, 60, 600, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(400);
    chassis.moveToPoint(70, 65, 900, {.maxSpeed = 60});
    intakeRaise.set_value(true);
    chassis.waitUntilDone();
    intakeRaise.set_value(false);
    pros::delay(100);
    chassis.moveToPoint(57.5, 56, 600, {.forwards = false, .minSpeed = 60});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.turnToPoint(44, 0, 600);
    chassis.moveToPoint(44, 0, 800, {.maxSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPoint(44, -50, 1000, {.minSpeed = 85});

    clampExtended = true;
}