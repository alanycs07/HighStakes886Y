#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

ASSET(asset2_txt);
ASSET(RedNegativeRingStackCurve_txt);

void Red7Ring(){
    armMacro = true;
    chassis.setPose(-61, 14, 194.7);
    armTarget = wallPos;
    pros::delay(620);
    chassis.follow(asset2_txt, 10, 1800, false);
    armTarget = restingPos;
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    //middle ring grab
    chassis.turnToHeading(55, 800);
    chassis.waitUntilDone();
    sortingColor = true;
    chassis.moveToPose(-10, 62, 0, 1500, {.minSpeed = 40});
    //chassis.follow(RedNegativeRingStackCurve_txt, 10, 1500);

}