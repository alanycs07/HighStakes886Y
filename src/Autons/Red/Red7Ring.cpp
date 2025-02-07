#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET(RedNegGoalCurve_txt);
ASSET(RedNegativeRingStackCurve_txt);

void Red7Ring(){
    armMacro = true;
    chassis.setPose(-61, 14, 194.7);
    armTarget = wallPos;
    pros::delay(620);
    chassis.follow(RedNegGoalCurve_txt, 9, 1200, false);
    armTarget = restingPos;
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    //middle ring grab
    chassis.turnToHeading(50,500);
    chassis.waitUntilDone();
    sortingColor = true;
    chassis.moveToPoint(-10.5, 45.5, 900, {.maxSpeed = 80}); //first ring
    //chassis.follow(RedNegativeRingStackCurve_txt, 10, 1500);
    chassis.turnToHeading(10, 400);
    chassis.moveToPoint(-9, 54.5, 600, {.maxSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(450);
    chassis.moveToPoint(-11, 45, 700, {.forwards = false});
    chassis.turnToPoint(-23, 50, 500);
    chassis.moveToPoint(-23, 50, 700);
    chassis.turnToHeading(250, 400);
    chassis.moveToPose(-58, 60, 310, 1000, {.lead = 0.3, .minSpeed = 70});
    chassis.moveToPoint(-70, 65, 900, {.maxSpeed = 60});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPoint(-58, 60, 600, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(450);
    chassis.moveToPoint(-70, 65, 900, {.maxSpeed = 60});
    intakeRaise.set_value(true);
    chassis.waitUntilDone();
    intakeRaise.set_value(false);
    pros::delay(100);
    chassis.moveToPoint(-57.5, 56, 600, {.forwards = false, .minSpeed = 60});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.turnToPoint(-44, 0, 600);
    chassis.moveToPoint(-44, 0, 800, {.maxSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPoint(-44, -50, 1000, {.minSpeed = 85});

    
} 