#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"
#include "pros/vision.h"

void colorSort(int sortedColor) {
    pros::vision_object_s_t red_stuff = vision_sensor.get_by_sig(0, 1);
    pros::vision_object_s_t blue_stuff = vision_sensor.get_by_sig(0, 2);

    int ejectCounter = 0;

    distance = sorterDistance.get_distance();

    if(ejectRing == false) {
        intake.move_velocity(12000);
    } else if (ejectRing == true) {
        if (distance < 30) {
            intake.move_velocity(-12000);
            ejectCounter = pros::millis();
            if (pros::millis() - ejectCounter >= 300) {
            ejectRing = false;
            }
        }
        else {
            intake.move_velocity(12000);
        }
    }

    // if (sortedColor == red) {
    //     if (red_stuff.height * red_stuff.width > 20000) {
    //         // ejectRing = true;
    //         intake.move_velocity(0);
    //         sortingColor = false;
    //     }
    // }

    // else if (sortedColor == blue) {
        if (blue_stuff.height * blue_stuff.width > 20000) {
            // ejectRing = true;
            intake.move_velocity(0);
            sortingColor = false;
        }
    // }  
    else {
        ejectRing = false;
        intake.move_velocity(12000);
    }

}

void changeSortedColor() {
    ejectColor += 1;
    if (ejectColor == 3) {
        ejectColor = 0;
    }
}

void ejectNextRing() {
    if (sortNextRing == true) {
        if (distance < 30) {
            intake.move_velocity(-12000);
            pros::delay(300);
            ejectRing = false;
        }
        else {
            intake.move_velocity(12000);
        }
    }
}