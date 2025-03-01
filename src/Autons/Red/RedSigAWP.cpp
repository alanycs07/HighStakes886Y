#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void RedSigAWP () {
    armMacro = true;
    chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-61.5, -11.6, 343.8);
    armTarget = wallPos;
    pros::delay(600);
    chassis.turnToPoint(-29, -23, 1000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 7});
    chassis.waitUntilDone();
    armTarget = restingPos;
    chassis.moveToPoint(-29, -23, 1300, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    pros::delay(100);
    chassis.turnToPoint(-12.5, -10.5, 900, {.maxSpeed = 90});
    chassis.moveToPoint(-12.5, -10.5, 1300, {.maxSpeed = 75});
    chassis.waitUntilDone();
    doinker.set_value(true);
    pros::delay(100);
    chassis.moveToPose(-6, -9.25, 72, 600);
    chassis.waitUntilDone();
    leftDoinker.set_value(true);
    pros::delay(200);
    chassis.moveToPoint(-46, -23.5, 1000, {.forwards = false});
    chassis.turnToPoint(0, -55, 800);
    chassis.waitUntilDone();
    leftDoinker.set_value(false);
    doinker.set_value(false);
    chassis.turnToPoint(-38.5, -26, 400);
    chassis.waitUntilDone();
    sortingColor = true;
    // runAntiJam = true;
    chassis.moveToPoint(-38.5, -26, 600);
    chassis.turnToPoint(-37, -37, 800);
    chassis.moveToPoint(-37, -37, 800);
    // chassis.turnToPoint(-62, -70, 800);
    // chassis.moveToPoint(-70, -70, 1800, {.maxSpeed = 70});
    // chassis.moveToPoint(-52, -52, 800, {.forwards = false});
    // chassis.turnToHeading(150, 800);
    // chassis.swingToHeading(37, DriveSide::LEFT, 800);
    // chassis.waitUntilDone();
    // sortingColor = false;
    chassis.turnToPoint(-22, -48, 1100);
    chassis.waitUntilDone();
    pros::delay(200);
    sortingColor = false;
    goalClamp.set_value(false);
    leftDoinker.set_value(true);
    chassis.moveToPoint(-22, -48, 900);
    // useAutoIntake = true;
    // spinUntilDetected = true;
    intake.move_velocity(12000);
    chassis.waitUntil(6);
    // intake.move_velocity(0);
    pros::delay(300);
    intake.move_velocity(0);
    chassis.turnToPoint(-8, -46.5, 900, {.forwards = false});
    chassis.waitUntilDone();
    leftDoinker.set_value(false);
    chassis.moveToPoint(-8, -46.5, 1200, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    pros::delay(200);
    goalClamp.set_value(true);
    chassis.waitUntilDone();
    useAutoIntake = false;
    spinUntilDetected = false;
    // sortingColor = true;
    intake.move_velocity(12000);
    pros::delay(300);
    chassis.swingToPoint(-12, -20, DriveSide::RIGHT, 1000);
    armTarget = wallPos;
    chassis.moveToPoint(-12, -20, 1000);
    intake.move_velocity(0);

    clampExtended = true;



    // // chassis.turnToHeading(-47, 500);    
    // chassis.turnToPoint(-46, -2, 550);
    // // arm.move_voltage(-12000);
    // armTarget = restingPos;
    // chassis.waitUntilDone();
    // pros::delay(100);

    // chassis.moveToPoint(-47, -2, 700, {.maxSpeed = 40});
    // intakeRaise.set_value(true);
    // useAutoIntake = true;
    // spinUntilDetected = true;
    // chassis.waitUntilDone();
    // intakeRaise.set_value(false);
    // pros::delay(300);
    // chassis.turnToPoint(-23, -30, 600,{.forwards = false});
    // chassis.moveToPoint(-23, -30, 1200, {.forwards = false, .maxSpeed = 80});
    // chassis.waitUntilDone();
    // pros::delay(80);
    // goalClamp.set_value(true);
    // useAutoIntake = false;
    // spinUntilDetected = false;
    // chassis.turnToPoint(-9.5, -15, 600); //turn to middle 4 rings
    // intake.move_velocity(0);
    // chassis.moveToPoint(-9.5, -15, 700);
    // chassis.waitUntilDone();
    // doinker.set_value(true);
    // pros::delay(100);
    // chassis.moveToPoint(-29, -30, 1000, {.forwards = false, .maxSpeed = 100});
    // chassis.waitUntilDone();
    // doinker.set_value(false);
    // pros::delay(100);
    // chassis.turnToPoint(-18, -29, 400);
    // chassis.waitUntilDone();
    // sortingColor = true;
    // chassis.moveToPoint(-15, -29, 700);
    // chassis.waitUntilDone();
    // pros::delay(300);
    
    // chassis.moveToPoint(-40, -30, 1200, {.forwards = false, .minSpeed = 90});
    // chassis.waitUntilDone();
    // pros::delay(200);
    // goalClamp.set_value(false);
    // chassis.turnToPoint(-27, -50, 600);
    // chassis.moveToPoint(-27, -50, 900);
    // useAutoIntake = true;
    // spinUntilDetected = true;
    // chassis.waitUntilDone();
    // pros::delay(250);
    // chassis.turnToPoint(-9, -51, 900, {.forwards = false});
    // chassis.moveToPoint(-9.4, -51, 900, {.forwards = false, .maxSpeed = 50});
    // chassis.waitUntilDone();
    // goalClamp.set_value(true);
    // useAutoIntake = false;
    // spinUntilDetected = false;
    // sortingColor = true;
    // chassis.moveToPose(-18, -18, 18, 1200, {.minSpeed = 80});
    // chassis.moveToPoint(-18, -18, 1000);


    // clampExtended = true;

}   