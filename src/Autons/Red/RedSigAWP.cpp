#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void RedSigAWP () {
    armMacro = true;
    chassis.setPose(-61.5, -15.6, 343.8);
    armTarget = wallPos;
    pros::delay(600);
    // chassis.turnToHeading(-47, 500);    
    chassis.turnToPoint(-46, -2, 550);
    // arm.move_voltage(-12000);
    armTarget = restingPos;
    chassis.waitUntilDone();
    pros::delay(100);

    chassis.moveToPoint(-47, -2, 700, {.maxSpeed = 40});
    intakeRaise.set_value(true);
    useAutoIntake = true;
    spinUntilDetected = true;
    chassis.waitUntilDone();
    intakeRaise.set_value(false);
    pros::delay(300);
    chassis.turnToPoint(-23, -30, 600,{.forwards = false});
    chassis.moveToPoint(-23, -30, 1200, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(80);
    goalClamp.set_value(true);
    useAutoIntake = false;
    spinUntilDetected = false;
    chassis.turnToPoint(-9.5, -15, 600); //turn to middle 4 rings
    intake.move_velocity(0);
    chassis.moveToPoint(-9.5, -15, 700);
    chassis.waitUntilDone();
    doinker.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(-29, -30, 1000, {.forwards = false, .maxSpeed = 100});
    chassis.waitUntilDone();
    doinker.set_value(false);
    pros::delay(100);
    chassis.turnToPoint(-18, -29, 400);
    chassis.waitUntilDone();
    sortingColor = true;
    chassis.moveToPoint(-15, -29, 700);
    chassis.waitUntilDone();
    pros::delay(300);
    
    chassis.moveToPoint(-40, -30, 1200, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    pros::delay(200);
    goalClamp.set_value(false);
    chassis.turnToPoint(-28.5, -48.5, 600);
    chassis.moveToPoint(-27, -50, 900);
    useAutoIntake = true;
    spinUntilDetected = true;
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToPoint(-9, -51, 900, {.forwards = false});
    chassis.moveToPoint(-9.4, -51, 900, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    useAutoIntake = false;
    spinUntilDetected = false;
    sortingColor = true;
    chassis.moveToPose(-18, -18, 18, 1200, {.minSpeed = 80});
    chassis.moveToPoint(-18, -18, 1000);



}   