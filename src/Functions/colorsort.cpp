#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void colorSort(int sortedColor) {
    colorSensor.set_led_pwm(100);
    hue = colorSensor.get_hue();
    distance = sorterDistance.get_distance();

    if(ejectRing == false) {
        intake.move_velocity(12000);
    } else if (ejectRing == true) {
        if (distance < 30) {
            intake.move_velocity(-12000);
            pros::delay(300);
            ejectRing = false;
        }
        else {
            intake.move_velocity(12000);
        }
    }

    if (sortedColor == red) {
        if ((hue > 355) || (hue < 15)) {
            ejectRing = true;
        }
    }

    else if (sortedColor == blue) {
        if ((hue > 200) && ( hue < 230)) {
            ejectRing = true;
        }
    }  
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