#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void RedPos6Ring() {
    ejectColor = red;


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
    chassis.turnToPoint(-12.5, -9, 800, {.maxSpeed = 90});
    intake.move_velocity(12000);
    chassis.moveToPoint(-12.5, -9, 900, {.maxSpeed = 85});
    chassis.waitUntil(1);
    intake.move_velocity(0);
    chassis.waitUntilDone();
    intake.move_velocity(-12000);
    doinker.set_value(true);
    pros::delay(100);
    intake.move_velocity(0);
    // chassis.turnToPoint(-8.2,-9.6, 300);
    // chassis.moveToPoint(-8.2, -9.6, 1200, {.maxSpeed = 50});
    // chassis.swingToPoint(-8.2, -9.6, DriveSide::RIGHT, 1000);
    chassis.moveToPose(-7.5, -7.25, 67, 400);
    chassis.waitUntilDone();
    leftDoinker.set_value(true);
    pros::delay(200);
    // chassis.turnToPoint(-15, -21, 800, {.forwards = false});
    chassis.moveToPoint(-37.5, -18, 800, {.forwards = false});
    chassis.turnToPoint(0, -35, 500);
    chassis.waitUntilDone();
    doinker.set_value(false);
    // leftDoinker.set_value(false);
    chassis.turnToPoint(-27, -17, 400); //left ring
    // chassis.waitUntil(3);
    leftDoinker.set_value(false);
    chassis.moveToPoint(-27, -17, 500);
    runAntiJam = true;
    sortingColor = true;
    // intake.move_velocity(12000);
    // chassis.swingToHeading(235, DriveSide::RIGHT, 1000);
    // chassis.moveToPoint(-34.5, -26, 500);
    // chassis.moveToPose(-24, -47, 180, 1000);
    chassis.moveToPoint(-37.5, -18, 500, {.forwards = false, .minSpeed = 30, .earlyExitRange = 3});//backup
    chassis.turnToPoint(-27.5, -27, 400 ); //right ring
    chassis.moveToPoint(-27.5, -27, 800, {.minSpeed = 30, .earlyExitRange = 4});
    // chassis.turnToPoint(-24, -46, 800);//middle stack
    chassis.moveToPoint(-24, -48, 800, {.minSpeed = 30, .earlyExitRange = 4});
    chassis.turnToPoint(-70, -70, 400);
    chassis.waitUntilDone();
    // chassis.moveToPoint(-70, -70, 2000, {.maxSpeed = 90});
    // chassis.moveToPose(-70, -75, 235, 2000, {.minSpeed = 30});
    runAntiJam = false;
    chassis.moveToPoint(-70, -70, 1500, {.maxSpeed = 100});
    // chassis.waitUntil(10);
    chassis.moveToPoint(-49.5, -60, 600, {.forwards = false});
    chassis.waitUntilDone();
    // intakeRaise.set_value(true);
    // pros::delay(100);

    //BELOW 5 RING SWEEP
    chassis.waitUntilDone();
    doinker.set_value(true);
    chassis.moveToPoint(-57, -55, 300);
    chassis.waitUntilDone();
    sortingColor = false;
    chassis.turnToHeading(100, 800);
    chassis.waitUntilDone();
    doinker.set_value(false);


    //BELOW 6 RING

    // runAntiJam = true;
    // chassis.moveToPoint(-70, -70, 800, {.maxSpeed = 90});
    // chassis.waitUntilDone();
    // intakeRaise.set_value(false);
    // chassis.moveToPoint(-49.5, -58, 600, {.forwards = false});
    // chassis.moveToPoint(-70, -70, 800, {.maxSpeed = 90});
    // chassis.moveToPoint(-49.5, -58, 600, {.forwards = false});


    //CONTINUE
    chassis.turnToPoint(-12, -18, 700);
    chassis.moveToPoint(-12, -18, 1000);
    chassis.waitUntil(8);
    goalClamp.set_value(false);
    sortingColor = false;
    armTarget = wallPos;




    // chassis.waitUntilDone();
    // doinker.set_value(true);
    // chassis.moveToPoint(-57, -55, 300);
    // chassis.waitUntilDone();
    // sortingColor = false;
    // chassis.turnToHeading(100, 800);
    // chassis.waitUntilDone();
    // doinker.set_value(false);
    // // chassis.moveToPose(-15, -47, 90, 1000, {.minSpeed = 70});
    // chassis.moveToPoint(-20, -47, 1000, {.maxSpeed = 70});
    // chassis.waitUntil(3);
    // goalClamp.set_value(false);


    

    // chassis.moveToPose(-43, -35, 90, 1000, {.forwards = false, .minSpeed = 35});
}