#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void loadRing() {
    // colorSensor.set_led_pwm(100);
    // hue = colorSensor.get_hue();
    // if (spinUntilDetected == true) {
    //     intake.move_velocity(12000);
    //     if (((hue > 355) || (hue < 15)) || ((hue > 200) && ( hue < 230))) {
    //         spinUntilDetected = false;
    //     }
    // } else if (spinUntilDetected == false) {
    //     intake.move_velocity(0);
    // }

    pros::vision_object_s_t red_stuff = vision_sensor.get_by_sig(0, 1);
    pros::vision_object_s_t blue_stuff = vision_sensor.get_by_sig(0, 2);
    intake_Distance = intakeDistance.get_distance();

    intake.move_velocity(12000);
    if (spinUntilDetected == true) {
    // if ((red_stuff.height * red_stuff.width > 4000) || (blue_stuff.height * blue_stuff.width > 4000)) {
    //     spinUntilDetected = false;
    // }
    
        if (intake_Distance < 20) {
            spinUntilDetected = false;
            intake.move_velocity(0);
        }
    } else if (spinUntilDetected == false) {
        intake.move_velocity(0);
    }
}

