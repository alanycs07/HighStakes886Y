#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void loadRing() {
    colorSensor.set_led_pwm(100);
    hue = colorSensor.get_hue();
    if (spinUntilDetected == true) {
        intake.move_velocity(12000);
        if (((hue > 355) || (hue < 15)) || ((hue > 200) && ( hue < 230))) {
            spinUntilDetected = false;
        }
    } else if (spinUntilDetected == false) {
        intake.move_velocity(0);
    }
}

