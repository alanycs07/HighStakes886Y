#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET (BlueNegGoalCurve_txt);
ASSET (BlueNegativeRingStackCurve_txt);

void Blue7Ring(){
    chassis.setPose(0,0,0);
    goalClamp.set_value(true);
    pros::delay(200);
    //chassis.moveToPoint(0, 24, 100000);
    chassis.turnToHeading(90, 10000);
    /*
    runAntiJam = true;
    armMacro = true;
    // ejectRing = red;
    chassis.setPose(61, 14, 165.3);
    // armTarget = wallPos;
    // pros::delay(550);
    chassis.follow(BlueNegGoalCurve_txt, 9, 1300, false);
    // armTarget = restingPos;
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    //middle ring grab
    chassis.turnToHeading(310,500);
    chassis.waitUntilDone();
    runAntiJam = true;
    sortingColor = true;
    chassis.moveToPoint(9.5, 43.5, 900, {.maxSpeed = 80}); //first ring
    //chassis.follow(RedNegativeRingStackCurve_txt, 10, 1500);
    chassis.turnToHeading(10, 400);
    chassis.moveToPoint(8.2, 58, 800, {.maxSpeed = 50});
    chassis.waitUntilDone();
    pros::delay(450);
    chassis.moveToPoint(11, 45, 700, {.forwards = false});
    chassis.turnToPoint(23, 50, 500);
    chassis.moveToPoint(23, 50, 700);
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(140, 400);
    //changes here
    chassis.moveToPoint(40, 42, 700);
    chassis.turnToPoint(70, 65, 400);
    //chassis.moveToPose(58, 60, 50, 1000, {.lead = 0.3, .minSpeed = 70});
    chassis.moveToPoint(65, 60, 1200, {.minSpeed = 60});
    runAntiJam = false;
    chassis.moveToPoint(80, 75, 1100, {.maxSpeed = 60});
    // chassis.moveToPoint(-61, 57, 600, {.forwards = false, .maxSpeed = 70});
    // chassis.waitUntilDone();
    // pros::delay(80);
    // chassis.moveToPoint(-80, 75, 800, {.maxSpeed = 60});
    // intakeRaise.set_value(true);
    // chassis.waitUntilDone();
    // intakeRaise.set_value(false);
    // pros::delay(100);
    runAntiJam = true;
    chassis.moveToPoint(57.5, 56, 600, {.forwards = false, .minSpeed = 60});
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToPoint(44, -10, 700);
    chassis.moveToPoint(44, -48, 1800);
    intakeRaise.set_value(true);
    chassis.waitUntil(55);
    intakeRaise.set_value(false);
    chassis.turnToPoint(70, -70, 700);
    chassis.waitUntilDone();
    doinkerExtended = true;


    clampExtended = true;
    */
}