#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET (BlueNegativeGoalCurve_txt);
ASSET (BlueNegativeRingStackCurve_txt);

void Blue7Ring(){
    armMacro = true;
    chassis.setPose(61.5, 15.6, 163.8);
    armTarget = wallPos;
    pros::delay(620);
    /*
    chassis.swingToPoint(-26, -22, DriveSide::RIGHT, 600, {.forwards = false, .earlyExitRange = 10});
    armTarget = restingPos;
    chassis.moveToPoint(-26, -22, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntilDone();
    */
    chassis.follow(BlueNegativeGoalCurve_txt, 10, 2000, false);
    armTarget = restingPos;
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    pros::delay(100);
    chassis.turnToHeading(305, 700);
    // chassis.waitUntilDone();
    // sortingColor = true;
    // chassis.follow(BlueNegativeRingStackCurve_txt, 10, 1500);

}