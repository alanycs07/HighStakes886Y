#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET(asset1_txt);

void RedPos4Ring(){
    armMacro = true;
    chassis.setPose(-61.5, -15.6, 343.8);
    armTarget = wallPos;
    pros::delay(620);
    /*
    chassis.swingToPoint(-26, -22, DriveSide::RIGHT, 600, {.forwards = false, .earlyExitRange = 10});
    armTarget = restingPos;
    chassis.moveToPoint(-26, -22, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntilDone();
    */
    chassis.follow(asset1_txt, 10, 2000, false);
    armTarget = restingPos;
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    //middle ring grab
    chassis.turnToPoint(-9.8, -11, 900);
    chassis.moveToPoint(-9.8, -11, 1000);
    chassis.waitUntilDone();
    doinker.set_value(true);
    pros::delay(180);
    //ring stack setup
    chassis.moveToPoint(-30, -20, 1000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToPoint(-15, -47, 500);
    chassis.waitUntilDone();
    doinker.set_value(false);
    //intake stack
    chassis.moveToPoint(-25, -52, 1400, {.maxSpeed = 70});
    sortingColor = true;
    chassis.waitUntilDone();
    pros::delay(150);
    //corner rings
    chassis.turnToPoint(-55, -60, 650);
    chassis.moveToPoint(-55, -60, 800);
    chassis.turnToPoint(-61, -65, 300);
    chassis.moveToPoint(-70, -75, 600, {.maxSpeed = 60});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(-58, -61, 600, {.forwards = false}); //backup
    chassis.waitUntilDone();
    pros::delay(200);
    intakeRaise.set_value(true);
    chassis.moveToPoint(-70, -75, 1000, {.maxSpeed = 60});
    chassis.waitUntilDone();
    intakeRaise.set_value(false);
    chassis.moveToPoint(-56, -59, 1000, {.forwards = false}); 
    sortingColor = false;
    chassis.waitUntilDone();
    doinker.set_value(true);
    pros::delay(100);
    // chassis.moveToPoint(-56.5, -61, 1000); 
    chassis.turnToHeading(100, 400);
    chassis.turnToHeading(45, 400);
    chassis.waitUntilDone();
    chassis.moveToPoint(-70, -70, 500, {.forwards = false}); 
    sortingColor = false;
    goalClamp.set_value(false);
    chassis.waitUntilDone();
    intake.move_velocity(-12000);
    doinker.set_value(false);
    chassis.moveToPoint(-20, -20, 1200, {.maxSpeed = 80}); 
    intake.move_velocity(0);
    
}