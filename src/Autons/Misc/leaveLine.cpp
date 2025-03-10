#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void leaveLine() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPose(0, 24, 0, 2000);
}