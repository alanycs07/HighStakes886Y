#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void RedSigAWP () {
    armMacro = true;
    chassis.setPose(-61.5, -15.6, 343.8);
    armTarget = wallPos;
    pros::delay(600);
    // chassis.turnToHeading(-47, 500);
    chassis.turnToPoint(-53, -2, 500);    
    armTarget = restingPos;
    pros::delay(700);
    arm.move_voltage(0);
    chassis.moveToPoint(-53, -2, 700);
    intakeRaise.set_value(true);
    useAutoIntake = true;
    spinUntilDetected = true;
    chassis.waitUntilDone();
    intakeRaise.set_value(false);
    pros::delay(350);
    chassis.turnToPoint(-27, -25, 600,{.forwards = false});
    chassis.moveToPoint(-27, -25, 1200, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(80);
    goalClamp.set_value(true);
    useAutoIntake = false;
    spinUntilDetected = false;
    chassis.turnToPoint(-12, -9, 600); //turn to middle 4 rings
    intake.move_velocity(0);
    chassis.moveToPoint(-11.7, -9, 1000);
    chassis.waitUntilDone();
    leftDoinker.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(-29, -25, 1000, {.forwards = false, .maxSpeed = 100});
    chassis.waitUntilDone();
    leftDoinker.set_value(false);
    pros::delay(100);
    chassis.turnToPoint(-19.5, -22.7, 200);
    chassis.waitUntilDone();
    sortingColor = true;
    chassis.moveToPoint(-16, -21, 700);
    chassis.waitUntilDone();
    pros::delay(300);
    
    chassis.moveToPoint(-40, -30, 1200, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    pros::delay(200);
    goalClamp.set_value(false);
    chassis.turnToPoint(-28.5, -48.5, 600);
    chassis.moveToPoint(-28.5, -48.5, 1000);
    useAutoIntake = true;
    spinUntilDetected = true;
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.turnToPoint(-11.5, -48, 700, {.forwards = false});
    chassis.moveToPoint(-11.5, -48, 1000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    useAutoIntake = false;
    spinUntilDetected = false;
    sortingColor = true;
    chassis.moveToPose(-20, -18, 20, 1200, {.minSpeed = 70});
    chassis.moveToPoint(-20, -18, 1000);


}   