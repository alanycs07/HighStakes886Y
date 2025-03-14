#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET (BlueNegGoalCurve_txt);
ASSET (BlueNegativeRingStackCurve_txt);

void Blue7Ring(){
    armMacro = true;
    chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(61.5, 11.6, 163.3);
    armTarget = wallPos;
    pros::delay(600);
    chassis.turnToPoint(25, 24, 1000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 7});
    chassis.waitUntilDone();
    armTarget = restingPos;
    chassis.moveToPoint(25, 24, 1500, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    pros::delay(100);  
    chassis.turnToPoint(11, 41, 800);
    chassis.waitUntilDone();
    // runAntiJam = true;
    // sortingColor = true;

    intake.move_velocity(12000);

    // chassis.moveToPoint(14.5, 40, 800, {.minSpeed = 30, .earlyExitRange = 6});
    // chassis.turnToPoint(9, 47, 400, {.minSpeed = 30, .earlyExitRange = 3});
    // chassis.moveToPoint(9, 47, 400, {.minSpeed = 20, .earlyExitRange = 3});

    chassis.moveToPoint(11, 41, 800);
    chassis.turnToPoint(8, 50, 800);
    chassis.moveToPoint(8, 50, 800);

    chassis.swingToPoint(26, 44, DriveSide::RIGHT, 800);
    // chassis.moveToPoint(26, 44, 1000);
    // chassis.moveToPoint(23, 47, 600, {.forwards = false});


    // chassis.turnToPoint(70, 68, 800);
    // chassis.moveToPoint(70, 68, 2000, {.maxSpeed = 80});

    chassis.turnToPoint(62, 65, 800);
    chassis.moveToPoint(62, 65, 2000, {.maxSpeed = 80});
    chassis.moveToPoint(52, 62, 600, {.forwards = false});
    chassis.waitUntilDone();
    intakeRaise.set_value(true);
    intake.move_velocity(0);
    pros::delay(200);
    sortingColor = true;

    chassis.moveToPoint(62, 65, 1000);
    chassis.waitUntilDone();
    intakeRaise.set_value(false);
    pros::delay(200);
    chassis.moveToPoint(52, 62, 500, {.forwards = false});
    // chassis.moveToPoint(70, 68, 1000, {.maxSpeed = 50});
    // chassis.waitUntilDone();
    // intakeRaise.set_value(false);
    // pros::delay(200);
    // chassis.moveToPoint(52, 62, 800, {.forwards = false});
    chassis.turnToPoint(48, 11.5, 800);
    chassis.moveToPoint(48, 11.5, 1000, {.minSpeed = 30, .earlyExitRange = 5});
    chassis.moveToPoint(46, 11.5, 1000, {.maxSpeed = 50});
    doinker.set_value(true);
    leftDoinker.set_value(true);
    chassis.waitUntilDone();
    doinker.set_value(false);
    // leftDoinker.set_value(false);
    // chassis.turnToPoint(55.5, -43.5, 300);
    // chassis.waitUntilDone();
    // sortingColor = false;
    // chassis.moveToPoint(55.5, -43.5, 800);
    // chassis.turnToPoint(70, -70, 800, {.forwards = false});


    // chassis.setPose(0,0,0);
    // goalClamp.set_value(true);
    // pros::delay(200);
    // //chassis.moveToPoint(0, 24, 100000);
    // chassis.turnToHeading(90, 10000);
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