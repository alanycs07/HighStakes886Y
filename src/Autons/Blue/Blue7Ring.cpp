#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void Blue7Ring(){
    chassis.setPose(64.8, 11.4, 165.3);
    chassis.swingToPoint(26, 22, DriveSide::RIGHT, 1000, {.forwards = false});
    chassis.moveToPoint(26, 22, 1000, {.forwards = false});
    chassis.waitUntilDone();
    pros::delay(100);
    goalClamp.set_value(true);
}