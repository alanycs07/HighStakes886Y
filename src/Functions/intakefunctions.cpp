#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void loadRing() {
    pros::vision_object_s_t red_stuff = vision_sensor.get_by_sig(0, 1);
    pros::vision_object_s_t blue_stuff = vision_sensor.get_by_sig(0, 2);
    if (spinUntilDetected == true) {
        intake.move_velocity(12000);
        if (red_stuff.height * red_stuff.width > 100000000 || blue_stuff.height * blue_stuff.width > 100000000) {
            spinUntilDetected = false;
        }
    } else if (spinUntilDetected == false) {
        intake.move_velocity(0);
    }
}

