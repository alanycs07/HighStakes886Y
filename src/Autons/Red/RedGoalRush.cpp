#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void RedRush() {
    armMacro = true;
    armTarget = 30000;
    //RUSH
    chassis.setPose(-52, -61.5, 65.8);
    doinker.set_value(true);
    // spinUntilDetected = true;
    useAutoIntake = true;
    spinUntilDetected = true;
    chassis.moveToPose(-19 , -47, 65.8, 1200, {.lead=0.2, .minSpeed = 100});
    chassis.waitUntilDone();
    pros::delay(100);
    leftDoinker.set_value(true);
    //DRIVE BACK
    chassis.moveToPose(-47.5, -59.5, 65.8, 5000, {.forwards = false, .minSpeed = 60});
    chassis.waitUntil(5);
    //drop rushed goal
    leftDoinker.set_value(false);
    chassis.turnToPoint(-47.5, -36, 900);
    chassis.waitUntil(6);
    useAutoIntake = false;
    spinUntilDetected = false;
    intake.move_velocity(0);
    doinker.set_value(false);
    //wall stakes align
    chassis.moveToPoint(-46, -36, 1300, {.maxSpeed = 90});
    chassis.turnToPoint(-7.5, -60.5, 1000);
    chassis.moveToPoint(-7.5, -60.5, 1700, {.maxSpeed = 75});
    chassis.waitUntilDone();
    armTarget = wallPos;
    pros::delay(900);
    // armTarget = restingPos;
    //clamp next goal
    chassis.moveToPose(-25, -28, 180, 1300, {.forwards = false, .minSpeed = 50});
    chassis.waitUntil(10);
    armTarget = restingPos;
    chassis.moveToPoint(-25, -28, 400, {.forwards = false});
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    pros::delay(100);
    //corner rings
    sortingColor = true;
    chassis.turnToPoint(-70, -75, 500);
    chassis.moveToPoint(-70, -75, 1600, {.maxSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(200);
    // chassis.moveToPoint(-50, -50, 800, {.forwards = false});
    // chassis.waitUntilDone();
    // intakeRaise.set_value(true);
    // chassis.moveToPoint(-70, -70, 1000, {.maxSpeed = 80});
    // chassis.waitUntilDone();
    // intakeRaise.set_value(false);
    // pros::delay(200);
    chassis.moveToPoint(-50, -50, 800, {.forwards = false});
    chassis.waitUntilDone();
    pros::delay(400);
    chassis.turnToPoint(0, -46, 800);
    chassis.waitUntilDone();
    //setup for drivers
    goalClamp.set_value(false);
    chassis.moveToPoint(-15, -49, 1000);
    chassis.turnToHeading(270, 1000);


    // chassis.waitUntil(25);
    // rushClamp.set_value(false);
    // chassis.waitUntilDone();
    // doinker.set_value(false);
    // pros::delay(400);
    // chassis.turnToPoint(-28, -27.5, 1000, {.forwards = false, .maxSpeed = 90});
    // chassis.moveToPoint(-28, -27.5, 1000, {.forwards = false, .maxSpeed = 70});
    // chassis.waitUntilDone();
    // pros::delay(150);
    // goalClamp.set_value(true);

}