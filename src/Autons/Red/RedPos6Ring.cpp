#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void RedPos6Ring() {
    autoStarted = true;
    armMacro = true;
    armTarget = restingPos;
    useAutoIntake = false;
    spinUntilDetected = false;
    sortingColor = false;
    chassis.setPose(-55, -23.5, 270);
    chassis.moveToPose(-27, -23.5, 270, 1200, {.forwards = false, .minSpeed = 50});
    chassis.waitUntilDone();
    pros::delay(100);
    goalClamp.set_value(true);
    pros::delay(100);
    chassis.turnToPoint(-11.5, -9, 1000, {.maxSpeed = 90});
    intake.move_velocity(12000);
    chassis.moveToPoint(-11.5, -9, 1000, {.maxSpeed = 85});
    chassis.waitUntil(1);
    intake.move_velocity(0);
    chassis.waitUntilDone();
    intake.move_velocity(-12000);
    doinker.set_value(true);
    pros::delay(200);
    intake.move_velocity(0);
    // chassis.turnToPoint(-8.2,-9.6, 300);
    // chassis.moveToPoint(-8.2, -9.6, 1200, {.maxSpeed = 50});
    // chassis.swingToPoint(-8.2, -9.6, DriveSide::RIGHT, 1000);
    chassis.moveToPose(-7.6, -7.5, 70, 1000);
    chassis.waitUntilDone();
    leftDoinker.set_value(true);
}