#include "main.h"
#include "autons.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlibglobals.hpp"
#include "liblvgl/llemu.hpp"
#include "mathfunc.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"

ASSET(clampGoalCurve_txt);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
//  void intakeUntilLoaded() {
//     intake1.move_voltage(12000);
//     intake2.move_voltage(-12000);
//     if (intakeDistance.get_distance() < 30) {
//       spinIntake = false;
//       intake1.move_voltage(0);
//       intake2.move_voltage(0);
//   }
//  }

//////////////////////////////////////////////////////////
// ARM PID
//////////////////////////////////////////////////////////
// bool spinIntake = false;
void on_left_button() {
  autonColor = (autonColor + 1) % 3;
  if (autonColor == 0) {
    pros::lcd::set_text(4, "Sorting Color: Blue");
  } else if (autonColor == 1){
    pros::lcd::set_text(4, "Sorting Color: Red");
  } else {
    pros::lcd::set_text(4, "Sorting Color: No Sorting");
  }
}

void on_center_button() {
  startingPos = (startingPos + 1) % 5;
  if (startingPos == 0) {
    pros::lcd::set_text(5, "Starting Position: Red Positive");
  } else if (startingPos == 1) {
    pros::lcd::set_text(5, "Starting Position: Red Negative");
  } else if (startingPos == 2) {
    pros::lcd::set_text(5, "Starting Position: Blue Positive");
  } else if (startingPos == 3) {
    pros::lcd::set_text(5, "Starting Position: Blue Negative");
  } else {
    pros::lcd::set_text(5, "Starting Position: Skills");
  } 
}

void on_right_button() {
  path = (path + 1) % 4;

  //POSITIVE
  if (path == 0 && (startingPos == 0 || startingPos == 2)) {
    pros::lcd::set_text(6, "Autonomous Running: SIG AWP");
  } else if (path == 1 && (startingPos == 0 || startingPos == 2)) {
    pros::lcd::set_text(6, "Autonomous Running: Positive 4 Ring");
  } else if (path == 2 && (startingPos == 0 || startingPos == 2)) {
    pros::lcd::set_text(6, "Autonomous Running: N/A");
  } else if (path == 3 && (startingPos == 0 || startingPos == 2)) {
    pros::lcd::set_text(6, "Autonomous Running: N/A");
  }
  //NEGATIVE
  else if ((path == 0) && (startingPos == 1 || startingPos == 3)) {
    pros::lcd::set_text(6, "Autonomous Running: Negative 7 Ring");
  } else if (path == 1 && (startingPos == 1 || startingPos == 3)) {
    pros::lcd::set_text(6, "Autonomous Running: N/A");
  } else if (path == 2 && (startingPos == 1 || startingPos == 3)) {
    pros::lcd::set_text(6, "Autonomous Running: N/A");
  }
  //MISC
  else if (path == 0 && startingPos == 4) {
    pros::lcd::set_text(6, "Autonomous Running: Skills");
  } else if (path == 1 && startingPos == 4) {
    pros::lcd::set_text(6, "Autonomous Running: No Autonomous");
  } else if (path == 2 && startingPos == 4) {
    pros::lcd::set_text(6, "Autonomous Running: Leave Line");
  }
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  spinUntilDetected = false;
  int previous_state = 0;

  bool sortingColorMem;
  bool useAutoIntakeMem;
  bool spinUntilDetectedMem;
  pros::lcd::initialize(); // initialize brain screen
  pros::lcd::register_btn0_cb(on_left_button);
  pros::lcd::register_btn1_cb(on_center_button);
  pros::lcd::register_btn2_cb(on_right_button);
  chassis.calibrate(); // calibrate sensors
  // intakeRaise.set_value(1);
  // armRotation.reset();
  // print position to brain screen
  pros::Task screen_task([&]() {
    while (true) {
      // print robot location to the brain screen
      pros::lcd::print(0, "X: %f", chassis.getPose().x);         // x
      pros::lcd::print(1, "Y: %f", chassis.getPose().y);         // y
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
      pros::lcd::print(3, "Arm Position: %ld", armRotation.get_position());
      // pros::lcd::print(4, "Voltage: %ld", intake.get_voltage());
      // pros::lcd::print(5, "Current Draw: %ld", intake.get_current_draw());
      // pros::lcd::print(6, "Actual Velocity: %ld", intake.get_actual_velocity());

    if (sortingColor == true) {
      if (ejectColor == red) {
        colorSort(red);
      }
      else if (ejectColor == blue) {
        colorSort(blue);
      }
      else {
        colorSort(noColor);
      }
    }
    if (useAutoIntake == true) {
      loadRing();
    }

    if (armMacro == true) {
      Macro();
    }

    ejectNextRing();

if (autoStarted == true) {
  if(intake.get_current_draw() > 2000 && intake.get_actual_velocity() < 100 && intake.get_actual_velocity() > 0){
      if(!stopIntake){
        current_peak += 1;
      }
    }else{
      current_peak = 0;
    }

    if(current_peak > 4 && !stopIntake && !armMacro){
      intake.move(-127);
      // if(intake.get_voltage() > 5000){previous_state = 127;}
      // else if(intake.get_voltage() < -5000){previous_state = -127;}
      // else{previous_state = 0;}
      stopIntake = true;
      sortingColor = false;
      useAutoIntake = false;
      spinUntilDetected = false;
      sortingColorMem = sortingColor;
      useAutoIntakeMem = useAutoIntake;
      spinUntilDetectedMem = spinUntilDetected;
      outtakeStartTime = pros::millis();
      current_peak = 0;
    }

    if(stopIntake){
      if(pros::millis() - outtakeStartTime >= 150){
        sortingColor = sortingColorMem;
        useAutoIntake = useAutoIntakeMem;
        spinUntilDetected = spinUntilDetectedMem;
        stopIntake = false;
      }
    }
}


// if (intake.get_actual_velocity() >= 0 && intake.get_actual_velocity() < 100 && abs(intake.get_current_draw()) > 2000  && !stopIntake){
//       intake.move(-127);
//       stopIntake = true;
//       sortingColor = false;
//       outakeTime = 0;
//     }
//     if(stopIntake){
//       outakeTime += 25;
//     } 
//     if(stopIntake && outakeTime > 300){
//       stopIntake = false;
//       intake.move(0);
//     }
   

      // delay to save resources
      pros::delay(25);
      
    }
  });

  pros::lcd::set_text(4, "Sorting Color: Blue");
  pros::lcd::set_text(5, "Starting Position: Red Positive");
  pros::lcd::set_text(6, "Autonomous Running: Sig AWP");

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  
}




void autonomous() {
//COLOR SORT//
  if (autonColor == 0) {
    //EJECT BLUE
    ejectColor = blue;
  }
  else if (autonColor == 1) {
    //EJECT RED
    ejectColor = red;
  }
  else {
    ejectColor = noColor;
  }

  if (startingPos == 0) {
    //RED POSITIVE
    if (path == 0) {
      // RedPositiveAWP();
      // redPositive6Ring();
      // BlueSigAWP();
      RedSigAWP();
      // Blue7Ring();
      //Red7Ring();
      //  RedPos4Ring();
    } else if (path == 1) {
      // RedRush();
      RedPos4Ring();
    } else if (path == 2) {
      
    }
   } else if (startingPos == 1) {
    //RED NEGATIVE
    if (path == 0) {
      Red7Ring();
    } else if (path == 1) {

    } else if (path == 2) {

    }
  } else if (startingPos == 2) {
    //BLUE POSITIVE
    if (path == 0) {
      BlueSigAWP();
    } else if (path == 1) {
      // BluePos4Ring();
    } else if (path == 2) {

    }
  } else if (startingPos == 3) {
    //BLUE NEGATIVE
    if (path == 0) {
      Blue7Ring();
    } else if (path == 1) {

    } else if (path == 2) {

    }
  } else {
    //SKILLS
    if (path == 0) {

    } else if (path == 1) {

    } else if (path == 2) {

    }
  }
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  ejectColor = noColor;
  useAutoIntake = false;
  spinUntilDetected = false;
  autoStarted = false;
  // bool isExtended1 = true; // remove for DRIVER SKILLS
  arm.set_brake_mode(pros::MotorBrake::hold);
  // //BELOW FOR DRIVER SKILLS//
  while (true) {
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int leftY = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int leftX = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !stopIntake) {
      sortingColor = true;
      
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake.move_voltage(-12000);
      sortingColor = false;
    }
    else if (!stopIntake){
      intake.move_voltage(0);
      sortingColor = false;
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      clampExtended = !clampExtended;
      goalClamp.set_value(clampExtended);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      doinkerExtended = !doinkerExtended;
      doinker.set_value(doinkerExtended);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      rushClampExtended = !rushClampExtended;
      leftDoinker.set_value(rushClampExtended);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      intakeRaiseExtended = !intakeRaiseExtended;
      intakeRaise.set_value(intakeRaiseExtended);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      changeSortedColor();
    }
    
    chassis.arcade(leftY, leftX);

//ARM BELOW
    
    if (rightY > 30) {
      armMacro = false;
      arm.move(rightY);
    } else if (rightY < -30) {
      armMacro = false;
      arm.move(rightY);
    }

    if (!armMacro && std::abs(rightY) < 30) {
      arm.move(0);
    }
    
    if (rightX > 70) {
      //loading
      armMacro = true;
      armTarget = loadingPos;
    }

    if (rightX < -70) {
      //alliance stake lineup
      armMacro = true;
      armTarget = 72000;
    }

    
    pros::delay(25); // Run for 20 ms then update
  }
}