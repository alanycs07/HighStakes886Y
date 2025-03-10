#include "autons.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

template <typename T> int sign(T val) { return (T(0) < val) - (val < T(0)); }

void Macro() {
    measuredAngle = (armRotation.get_position());
    error = armTarget - measuredAngle;
    derivative = (error - previous_error);
    if (fabs(error) < 0.5 || fabs(error + derivative) < 0.5) {
        arm.move_voltage(0);

    }
    if (sign(error) != sign(previous_error)) {
          integral += error;
    } else {  
        integral = 0;
    }
    arm.move_voltage(error * armkP + integral * armkI + derivative * armkD * -1);
    previous_error = error;
}