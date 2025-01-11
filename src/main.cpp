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
 bool spinIntake = false;

 void intakeUntilLoaded() {
    intake1.move_voltage(12000);
    intake2.move_voltage(-12000);
    if (intakeDistance.get_distance() < 30) {
      spinIntake = false;
      intake1.move_voltage(0);
      intake2.move_voltage(0);
  }
 }

//////////////////////////////////////////////////////////
// ARM PID
//////////////////////////////////////////////////////////

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
  pros::lcd::initialize(); // initialize brain screen
  pros::lcd::register_btn0_cb(on_left_button);
  pros::lcd::register_btn1_cb(on_center_button);
  pros::lcd::register_btn2_cb(on_right_button);
  chassis.calibrate(); // calibrate sensors
  // intakeRaise.set_value(1);
  armRotation.reset();
  // print position to brain screen
  pros::Task screen_task([&]() {
    while (true) {
      // print robot location to the brain screen
      pros::lcd::print(0, "X: %f", chassis.getPose().x);         // x
      pros::lcd::print(1, "Y: %f", chassis.getPose().y);         // y
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
      pros::lcd::print(3, "Angle: %ld", armRotation.get_angle());
      // delay to save resources
      pros::delay(40);
      
    }
  });
  pros::Task intakeTask([&]() {
    while(spinIntake == true) {
        intakeUntilLoaded();
    pros::delay(20);
    }
  });
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

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.setPose(-53.25, -11.5, 300);
  spinIntake = false;
  chassis.moveToPose(-64, -5.5, 300, 700);
  chassis.waitUntilDone();
  arm.move_voltage(-12000);
  pros::delay(700);
  // chassis.follow(clampGoalCurve_txt, 4, 2000, false);
  // chassis.moveToPose(-31, -21, 290, 1500, {.forwards = false, .minSpeed = 40});
  chassis.moveToPoint(-28.5, -22.5, 2000, {.forwards = false, .maxSpeed = 70});
  chassis.waitUntil(8);
  arm.move_voltage(12000);
  chassis.waitUntilDone();
  arm.move_voltage(0);
  chassis.waitUntilDone();
  goalClamp.set_value(true);
  chassis.turnToPoint(-41, -15, 400);
  chassis.moveToPoint(-41, -15, 700);
  chassis.waitUntilDone();
  rightDoinker.set_value(true);
  pros::delay(500);
  chassis.moveToPoint(-23.5, -23, 800, {.forwards = false});
  chassis.turnToPoint(-20, -47, 800, {.maxSpeed = 60});
  chassis.waitUntilDone();
  rightDoinker.set_value(false);
  pros::delay(100);
  chassis.turnToPoint(-27, -53, 800);
  chassis.waitUntilDone();
  intake1.move_voltage(12000);
  intake2.move_voltage(-12000);
  chassis.moveToPoint(-27, -53, 1000);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.turnToPoint(-65, -65, 500);
  // chassis.moveToPoint(-51.5, -61.5, 1000);
  chassis.moveToPoint(-70, -70, 2500, {.maxSpeed = 80});
  // pros::delay(400);
  chassis.moveToPoint(-41, -59, 1000, {.forwards = false});
  chassis.turnToPoint(-17, -23, 1000);
  chassis.moveToPoint(-17, -23, 1000, {.maxSpeed = 60});
  chassis.waitUntilDone();
  // arm.move_voltage(-12000);
  // pros::delay(700);
  // arm.move_voltage(0);
  // chassis.waitUntil(10);
  // armPiston.set_value(true);

//  //RING RUSH
//  chassis.setPose(-49.75, 25.25, 64.85);
//  spinIntake = true;
//  leftDoinker.set_value(true);
// //  chassis.moveToPose(-15, 41.25, 64.85, 1500, {.minSpeed = 80});
//  chassis.moveToPoint(-8, 43.5, 1100);
//  spinIntake = true;
//  chassis.waitUntilDone();
//  chassis.moveToPoint(-39, 29.75, 1000, {.forwards = false});
//  chassis.waitUntil(15);
//  leftDoinker.set_value(false);
//  chassis.turnToPoint(-23.5, 23.5, 1000, {.forwards = false, .maxSpeed = 80});
//  chassis.waitUntilDone();
//  spinIntake = false;
//  chassis.moveToPoint(-23.5, 24.5, 1000, {.forwards = false});
//  chassis.waitUntilDone();
//  pros::delay(100);
//  goalClamp.set_value(true);
//  chassis.turnToPoint(-23.5, 50, 700);
//  chassis.waitUntilDone();
//  intake1.move_voltage(12000);
//  intake2.move_voltage(-12000);
//  chassis.moveToPoint(-23.5, 53, 1000, {.maxSpeed = 80});
//  chassis.waitUntilDone();
//  pros::delay(300);
//  chassis.turnToPoint(-54.5, 36, 1000);
//  chassis.moveToPoint(-54.5, 36, 1000, {.maxSpeed = 100});
//  chassis.waitUntilDone();
// //  pros::delay(200);
//  armPiston.set_value(true);
//  chassis.moveToPoint(-27, 45.5, 1000, {.forwards = false});
//  chassis.waitUntilDone();
//  intake1.move_voltage(0);
//  intake2.move_voltage(0);
//  chassis.turnToPoint(-7.5, 62.5, 600);
//  chassis.moveToPoint(-7.5, 62.5, 1000, {.maxSpeed = 75});
//  chassis.waitUntilDone();
//  arm.move_voltage(-12000);
//  pros::delay(900);
//  arm.move_voltage(0);
//  intake1.move_voltage(-12000);
//  intake2.move_voltage(12000);
//  arm.move_voltage(12000);
// //  chassis.moveToPoint(-55, 50, 1000, {.forwards = false});
//  chassis.moveToPoint(-27, 45.5, 1000, {.forwards = false});
//  chassis.waitUntilDone();
//  arm.move_voltage(0);
//  intake1.move_voltage(12000);
//  intake2.move_voltage(-12000);
//  chassis.turnToPoint(-70, 70, 700);
//  chassis.moveToPoint(-70, 70, 1500, {.maxSpeed = 80});
  

//POS WALL
  // chassis.setPose(-53.25, -11.5, 300);
  // spinIntake = false;
  // chassis.moveToPose(-64, -5.5, 300, 700);
  // chassis.waitUntilDone();
  // arm.move_voltage(-12000);
  // pros::delay(700);
  // chassis.moveToPoint(-28.5, -22.5, 2000, {.forwards = false, .maxSpeed = 70});
  // chassis.waitUntil(8);
  // arm.move_voltage(12000);
  // chassis.waitUntilDone();
  // arm.move_voltage(0);
  // armPiston.set_value(true);
  // chassis.turnToPoint(-52.5, 7, 1000);
  // chassis.moveToPoint(-52.5, 7, 1000, {.maxSpeed = 90});
  // pros::delay(200);
  // chassis.moveToPoint(-23.5, -23, 800, {.forwards = false});
  // chassis.turnToPoint(-23.5, -51, 700);
  // chassis.moveToPoint(-23.5, -51, 1000);
  // chassis.turnToPoint(-7.5, -62.5, 600);
  // chassis.moveToPoint(-7.5, -62.5, 1000, {.maxSpeed = 75});

  


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
  autoStarted = false;
  // bool isExtended1 = true; // remove for DRIVER SKILLS
  // arm.set_brake_mode(pros::MotorBrake::hold);
  spinIntake = false;
  // //BELOW FOR DRIVER SKILLS//
  while (true) {
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      intake1.move_voltage(12000);
      intake2.move_voltage(-12000);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake1.move_voltage(-12000);
      intake2.move_voltage(12000);
    }
    else {
      intake1.move_voltage(0);
      intake2.move_voltage(0);
    }


    if(rightY > 25) {
      arm.move_voltage(-12000);
      armRetractPiston.set_value(true);
    } 
    else if (rightY < -25) {
      arm.move_voltage(12000);
      armRetractPiston.set_value(false);
    }
    else {
      arm.move_voltage(0);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      armPiston.set_value(false);
    }
    else if (rightX > 50) {
      armPiston.set_value(true);
      // armRetractPiston.set_value(false);
    }
    
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      clampExtended = !clampExtended;
      goalClamp.set_value(clampExtended);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      rightDoinkerExtended = !rightDoinkerExtended;
      rightDoinker.set_value(rightDoinkerExtended);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      leftDoinkerExtended = !leftDoinkerExtended;
      leftDoinker.set_value(leftDoinkerExtended);
    }
    chassis.arcade(leftY, leftX);
    pros::delay(25); // Run for 20 ms then update
  }
}