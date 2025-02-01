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
    pros::lcd::set_text(4, "Color: Red");
  } else if (autonColor == 1){
    pros::lcd::set_text(4, "Color: Blue");
  } else {
    pros::lcd::set_text(4, "Color: MISC");
  }
}

void on_center_button() {
  startingPos = (startingPos + 1) % 3;
  if (startingPos == 0) {
    pros::lcd::set_text(5, "Starting Position: Positive");
  } else if (startingPos == 1) {
    pros::lcd::set_text(5, "Starting Position: Negative");
  } else {
    pros::lcd::set_text(5, "Starting Position: Skills");
  }
}

void on_right_button() {
  path = (path + 1) % 4;

  //POSITIVE
  if (path == 0 && startingPos == 0) {
    pros::lcd::set_text(6, "Autonomous Running: 3 + 1 AWP");
  } else if (path == 1 && startingPos == 0) {
    pros::lcd::set_text(6, "Autonomous Running: 3 + 1 Elims");
  } else if (path == 2 && startingPos == 0) {
    pros::lcd::set_text(6, "Autonomous Running: Rush Fast");
  } else if (path == 3 && startingPos == 0) {
    pros::lcd::set_text(6, "Autonomous Running: Rush Slow");
  }
  //NEGATIVE
  else if (path == 0 && startingPos == 1) {
    pros::lcd::set_text(6, "Autonomous Running: 5 Ring AWP");
  } else if (path == 1 && startingPos == 1) {
    pros::lcd::set_text(6, "Autonomous Running: 5 + 1 Elims");
  } else if (path == 2 && startingPos == 1) {
    pros::lcd::set_text(6, "Autonomous Running: 6 Ring Elims");
  }
  //MISC
  else if (path == 0 && startingPos == 2) {
    pros::lcd::set_text(6, "Autonomous Running: Skills");
  } else if (path == 1 && startingPos == 2) {
    pros::lcd::set_text(6, "Autonomous Running: No Autonomous");
  } else if (path == 2 && startingPos == 2) {
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
      pros::lcd::print(4, "Sorting Color: %ld", colorSensor.get_proximity());
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
      // delay to save resources
      pros::delay(20);
      
    }
  });
  // pros::Task intakeTask([&]() {
  //   while(spinIntake == true) {
  //       // intakeUntilLoaded();
  //   pros::delay(20);
  //   }
  // });

  // pros::Task Macro([&]() {
  //   while (true) {
  //     if (armMacro == true) {
  //       // measuredAngle = armRotation.get_position();
  //       // error = angleWrap(armTarget, measuredAngle); // 7250 = target
  //       // derivative = (error - previous_error);
  //       // if (fabs(error) < 0.5 || fabs(error + derivative) < 0.5) {
  //       //   arm.move_voltage(0);
  //       //   // break;
  //       // }
  //       // if (sign(error) != sign(previous_error)) {
  //       //   integral += error;
  //       // } else {
  //       //   integral = 0;
  //       // }
  //       // arm.move_voltage(error * armkP + integral * armkI + derivative * armkD);
  //       // previous_error = error;
  //       // pros::delay(25);
  //     }
  //   }
  // );
  pros::lcd::set_text(4, "Color: Red");
  pros::lcd::set_text(5, "Starting Position: Positive");
  pros::lcd::set_text(6, "Autonomous Running: 3 + 1 AWP");
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
void competition_initialize() {}


void autonomous() {
  // chassis.setPose(-50.75, -10.5, 291.5);
  // arm.move_velocity(12000);
  // pros::delay(800);
  // arm.move_velocity(-12000);
  // // // chassis.setPose(-57.5, -14, 315);
  // // // armTarget = loadingPos;
  // // // pros::delay(500);
  // // // conveyor.move_velocity(-12000);
  // // // chassis.moveToPose(-61.5, -10, 315, 700);
  // // // chassis.waitUntilDone();
  // // // conveyor.move_velocity(0);
  // // // pros::delay(100);
  // // // armTarget = allianceStakePos;
  // // // pros::delay(400);
  // // chassis.moveToPoint(-57.5, -14, 500, {.forwards = false});
  // // chassis.turnToPoint(-50, 0, 500, {.maxSpeed = 60});
  // // chassis.waitUntilDone();
  // // intake.move_velocity(-12000);
  // // chassis.moveToPoint(-50, 0, 500, {.maxSpeed = 60});
  // // chassis.waitUntilDone();
  // // // pros::delay(300);
  // // intakeRaise.set_value(true);
  // // // armTarget = 12000;
  // // pros::delay(500);
  // // chassis.moveToPoint(-52, -7, 700, {.forwards = false, .maxSpeed = 60});
  // // chassis.turnToPoint(-27, -21.5, 700, {.forwards = false});
  // // chassis.moveToPoint(-38, -15, 400, {.forwards = false});
  // // chassis.moveToPoint(-27, -21.5, 700, {.forwards = false, .maxSpeed = 50});
  // // chassis.waitUntilDone();
  // chassis.moveToPoint(-29, -20.5, 1500, {.forwards = false, .maxSpeed = 70});
  // chassis.waitUntilDone();
  // arm.move_velocity(0);
  // goalClamp.set_value(true);
  // pros::delay(200);
  // chassis.turnToPoint(-27, -41, 1000, {.maxSpeed = 60});
  // chassis.waitUntilDone();
  // intake.move_velocity(12000);
  // chassis.moveToPoint(-27, -41, 1000);
  // // chassis.moveToPoint(-27, -35, 500, {.forwards = false});
  // // chassis.turnToPoint(-58, -35, 500);
  // // chassis.moveToPoint(-58, -35, 700);
  // // chassis.waitUntil(10);
  // // intake.move_velocity(0);
  // // intake.move_velocity(0);
  // chassis.turnToPoint(-70, -65, 900);
  // chassis.moveToPoint(-70, -65, 2500, {.maxSpeed = 60});
  // chassis.waitUntil(10);
  // intake.move_velocity(12000);
  // // pros::delay(200);
  // chassis.moveToPoint(-58, -35, 1000, {.forwards = false});
  // chassis.turnToPoint(-28.5, 1, 1000);
  // chassis.waitUntilDone();
  // intake.move_velocity(0);
  // chassis.moveToPoint(-32, -9, 1000, {.minSpeed = 40});
  // chassis.waitUntilDone();
  // // chassis.moveToPoint(-28.5, 1, 2000, {.maxSpeed = 40});

  // // chassis.waitUntilDone();
  // // pros::delay(1000);
  // // goalClamp.set_value(false);
  // // pros::delay(200);
  // // conveyor.move_velocity(0);
  // // intake.move_velocity(0);
  // // chassis.moveToPoint(-24, -48, 500);
  // // chassis.turnToPoint(-10, -49, 500, {.forwards = false});
  // // chassis.moveToPoint(-10, -49, 1000, {.forwards = false, .maxSpeed = 50});
  // // chassis.waitUntilDone();
  // // pros::delay(200);
  // // goalClamp.set_value(true);
  // // pros::delay(200);
  // // chassis.turnToPoint(-63, -63, 200);
  // // chassis.moveToPoint(-63, -63, 2500, {.maxSpeed = 80});
  // // chassis.waitUntil(10);
  // // intake.move_velocity(-12000);
  // // chassis.waitUntilDone();
  // // // chassis.moveToPoint(-65, -65, 1000, {.maxSpeed = 40});
  // // conveyor.move_velocity(-12000);
  // // chassis.turnToHeading(180, 1000, {.maxSpeed = 40});
  // clampExtended = true;
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
  autoStarted = false;
  // bool isExtended1 = true; // remove for DRIVER SKILLS
  arm.set_brake_mode(pros::MotorBrake::hold);
  // //BELOW FOR DRIVER SKILLS//
  while (true) {
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int leftY = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int leftX = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      sortingColor = true;
      
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake.move_voltage(-12000);
      sortingColor = false;
    }
    else {
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
      rushClamp.set_value(rushClampExtended);
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