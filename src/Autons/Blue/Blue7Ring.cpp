#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET (BlueNegGoalCurve_txt);
ASSET (BlueNegativeRingStackCurve_txt);

void Blue7Ring(){
    runAntiJam = false;
    armMacro = true;
    // ejectRing = red;
    chassis.setPose(61, 14, 165.3);
    armTarget = wallPos;
    pros::delay(550);
    chassis.follow(BlueNegGoalCurve_txt, 9, 1200, false);
    armTarget = restingPos;
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    //middle ring grab
    chassis.turnToHeading(310,500);
    chassis.waitUntilDone();
    sortingColor = true;
    chassis.moveToPoint(10, 45, 900, {.maxSpeed = 80}); //first ring
    //chassis.follow(RedNegativeRingStackCurve_txt, 10, 1500);
    chassis.turnToHeading(350, 400);
    chassis.moveToPoint(8.7, 57, 600, {.maxSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(450);
    chassis.moveToPoint(11, 45, 700, {.forwards = false});
    chassis.turnToPoint(23, 50, 600);
    chassis.moveToPoint(23, 50, 700);
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(140, 400);
    //changes here
    chassis.moveToPoint(40, 42, 700);
    chassis.turnToPoint(70, 65, 400);
    //chassis.moveToPose(58, 60, 50, 1000, {.lead = 0.3, .minSpeed = 70});
    chassis.moveToPoint(65, 60, 1100, {.minSpeed = 70}); //into corner
    chassis.moveToPoint(75, 70, 1500, {.maxSpeed = 60});
    chassis.moveToPoint(61, 57, 600, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(80);
    chassis.moveToPoint(75, 70, 900, {.maxSpeed = 60});
    intakeRaise.set_value(true);
    chassis.waitUntilDone();
    intakeRaise.set_value(false);
    pros::delay(100);
    chassis.moveToPoint(57.5, 56, 600, {.forwards = false, .minSpeed = 60});
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToPoint(44, -10, 800);
    chassis.moveToPoint(44, -10, 1000, {.maxSpeed = 100});
    //chassis.turnToPoint(44, 50, 600);
    //chassis.moveToPoint(44, -50, 1000, {.minSpeed = 85});

    clampExtended = true;
}