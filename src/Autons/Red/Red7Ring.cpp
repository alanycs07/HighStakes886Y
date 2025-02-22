#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET(RedNegGoalCurve_txt);
ASSET(RedNegativeRingStackCurve_txt);

void Red7Ring(){
    runAntiJam = true;
    //armMacro = true;
    chassis.setPose(-61, 14, 194.7);
    //armTarget = wallPos;
    //pros::delay(620);
    chassis.follow(RedNegGoalCurve_txt, 9, 1300, false);
    //armTarget = restingPos;
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    //middle ring grab
    chassis.turnToHeading(50,500);
    chassis.waitUntilDone();
    // sortingColor = true;
    // intake.move_velocity(12000);
    runAntiJam = true;
    sortingColor = true;
    chassis.moveToPoint(-10, 46, 900, {.maxSpeed = 80}); //first ring
    //chassis.follow(RedNegativeRingStackCurve_txt, 10, 1500);
    chassis.turnToHeading(10, 400);
    chassis.moveToPoint(-8.4, 58, 800, {.maxSpeed = 50});
    chassis.waitUntilDone();
    pros::delay(450);
    chassis.moveToPoint(-11, 45, 700, {.forwards = false});
    chassis.turnToPoint(-23, 50, 500);
    chassis.moveToPoint(-23, 50, 700);
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToHeading(-140, 400);
    //changes here
    chassis.moveToPoint(-40, 42, 700);
    chassis.turnToPoint(-70, 65, 400);
    //chassis.moveToPose(58, 60, 50, 1000, {.lead = 0.3, .minSpeed = 70});
    chassis.moveToPoint(-65, 60, 1200, {.minSpeed = 60});
    runAntiJam = false;
    chassis.moveToPoint(-80, 75, 1100, {.maxSpeed = 60});
    // chassis.moveToPoint(-61, 57, 600, {.forwards = false, .maxSpeed = 70});
    // chassis.waitUntilDone();
    // pros::delay(80);
    // chassis.moveToPoint(-80, 75, 800, {.maxSpeed = 60});
    // intakeRaise.set_value(true);
    // chassis.waitUntilDone();
    // intakeRaise.set_value(false);
    // pros::delay(100);
    chassis.moveToPoint(-57.5, 56, 600, {.forwards = false, .minSpeed = 60});
    runAntiJam = true;
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToPoint(-44, -10, 700);
    chassis.moveToPoint(-44, -48, 1800);
    intakeRaise.set_value(true);
    chassis.waitUntil(55);
    intakeRaise.set_value(false);
    chassis.turnToPoint(-70, -70, 700);
    chassis.waitUntilDone();
    doinkerExtended = true;

    //chassis.turnToPoint(-44, 50, 600);
    //chassis.moveToPoint(44, -50, 1000, {.minSpeed = 85});

    clampExtended = true;
} 