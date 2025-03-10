#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void allianceStakeAlign() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPose(0, 2.5, 0, 800, {.maxSpeed = 60});
}