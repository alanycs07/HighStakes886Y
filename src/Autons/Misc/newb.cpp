#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void new_skills() {
arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  ejectColor = blue;
  autoStarted = true;
  sortingColor = true;
  armTarget = restingPos;
  chassis.setPose(0, 0, 0);

  armTarget = restingPos;
  chassis.moveToPoint(0, 2.5, 300, {.maxSpeed = 40}); //move forward to get alliance stake
  chassis.waitUntil(0.01);
  sortingColor = true;  //intakes to get alliance stake
  chassis.waitUntilDone();
  pros::delay(50);
  chassis.moveToPoint(-26.2, 38.8, 1100, {.maxSpeed = 100});  //first ring
  chassis.turnToPoint(-25.8, 18, 500, {.forwards = false}); //aim for the goal
  sortingColor = false;
  intake.move(0);
  chassis.moveToPoint(-25.35, 18, 1000, {.forwards = false, .maxSpeed = 60});  //backs up to the goal
  chassis.waitUntilDone();
  goalClamp.set_value(true);  //clamps goal
  
  chassis.turnToPoint(-59.3, 113.5, 500); //turn to top left ring 
  sortingColor = true;
  chassis.moveToPoint(-59.3, 113.5, 3000, {.minSpeed = 60}); //goes there and intake 2 rings
  chassis.waitUntilDone();
  pros::delay(400);
  chassis.moveToPoint(-48, 93, 1100, {.forwards = false});  //drive back
  chassis.turnToPoint(-50.4, 7, 850, {.maxSpeed = 90}); //turn to bottom 3 rings
  chassis.moveToPoint(-50.4, 35, 1400, {.maxSpeed = 90}); //move there
  chassis.waitUntilDone();
  pros::delay(100);
  chassis.moveToPoint(-50.4, 7, 1500, {.maxSpeed = 50}); //move there
  chassis.waitUntilDone();
  pros::delay(700);
  double reading = 0;
  chassis.turnToPoint(-65, 19, 800); //turn to last ring to fill the goal
  chassis.moveToPoint(-65, 19, 800);
  chassis.waitUntil(2);
  armMacro = true;
  armTarget = loadingPos;
  chassis.turnToHeading(20, 400);
  chassis.moveToPoint(-67, 7.5, 800, {.forwards = false}); 
  sortingColor = false;
  intake.move_velocity(-12000);
  pros::delay(300);
  goalClamp.set_value(false); // put goal down
  chassis.moveToPoint(-50, 63.5, 1700, {.maxSpeed = 100});
  intake.move_velocity(0); // going to wall ring
  chassis.turnToPoint(-80, 63.5, 700); //turn to wall
  chassis.moveToPoint(-80, 63.5, 1200, {.maxSpeed = 60});  
  armTarget = raisedPos;
  pros::delay(100);
  sortingColor = true;
  pros::delay(800);
  sortingColor = false;
  intake.move(0);
  chassis.waitUntilDone();//goes to wall
  armTarget = wallPos;
  pros::delay(600);
  armTarget = loadingPos;
  pros::delay(500);
  useAutoIntake = false;
  spinUntilDetected = false;
  sortingColor = true;
  pros::delay(900);
  sortingColor = false;
  intake.move(0);
  armTarget = wallPos;
  pros::delay(700);
  armTarget = restingPos;
  chassis.moveToPoint(-61, 66, 800, {.forwards = false}); //drive back from wall
  chassis.turnToPoint(-55.7, 110, 700); //aim for top 1 rings
  
  chassis.moveToPoint(-55.7, 110, 1000, {.maxSpeed = 110});
  sortingColor = true;
  chassis.turnToHeading(0, 300);
  chassis.waitUntilDone();
  reading = 0;
  for(int i = 0; i < 5; i++){
    reading += leftDistance.get();
    pros::delay(10);
  }
  reading = reading/5 * 0.0393701;
  pros::delay(600);
  sortingColor = false;
  intake.move(0);
  chassis.setPose(-70+reading+6.15, 110, 0);
  chassis.turnToPoint(-31.5, 114.5, 700);
  chassis.moveToPoint(-31.5, 114.5, 700);
  doinker.set_value(true);
  chassis.swingToPoint(-62, 121, DriveSide::LEFT, 1500);
  chassis.moveToPoint(-65, 125, 1400);
  doinker.set_value(false);
  chassis.swingToHeading(-90, DriveSide::RIGHT, 350);
  chassis.waitUntilDone();
  reading = 0;
  for(int i = 0; i < 5; i++){
    reading += rightDistance.get();
    pros::delay(10);
  }
  reading = reading/5 * 0.0393701;
  chassis.setPose(chassis.getPose().x, 140-reading-6.15, chassis.getPose().theta);
  chassis.moveToPoint(-4.3, 133, 2000, {.forwards = false, .maxSpeed = 90});
  chassis.waitUntilDone();
  pros::delay(300);
  chassis.turnToPoint(-5, 145, 900, {.forwards = false});
  chassis.moveToPoint(-5, 145, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.moveToPoint(-5, 142.5, 300, {.maxSpeed = 40}); //move forward to get alliance stake
  chassis.waitUntil(0.01);
  sortingColor = true;  //intakes to get alliance stake
  chassis.waitUntilDone();
  pros::delay(200);
  chassis.moveToPoint(-20, 125, 1000);  
  sortingColor = false;
  intake.move(0);
  chassis.turnToPoint(2, 117, 500, {.forwards = false}); //aim for the goal
  chassis.moveToPoint(2, 117, 1000, {.forwards = false});
  chassis.waitUntilDone();
  goalClamp.set_value(true);  //clamps goal
  chassis.moveToPoint(-30, 102, 1000);
  chassis.turnToPoint(54.5, 24, 900);
  chassis.moveToPoint(54.5, 24, 3000); //move diagonally down
  sortingColor = true;
  chassis.waitUntil(65);
  sortingColor = true;
  chassis.turnToPoint(58, 8, 700);
  chassis.moveToPoint(58, 8, 1000);
  chassis.turnToPoint(75, 25, 900);
  chassis.moveToPoint(75, 25, 1000);
  chassis.waitUntilDone();
  pros::delay(700);
  chassis.moveToPoint(76, 9, 1500, {.forwards = false});
  sortingColor = false;
  intake.move(0);
  chassis.waitUntilDone();
  goalClamp.set_value(false);
  pros::delay(50);
  chassis.moveToPoint(58, 19, 800);
  chassis.turnToPoint(33.5,21, 800, {.forwards = false});
  chassis.moveToPoint(33.5, 20, 1200, {.forwards = false});
  chassis.waitUntilDone();
  goalClamp.set_value(true);
  chassis.moveToPoint(56, 61.5, 1200);
  sortingColor = true;
  chassis.turnToPoint(80, 65.8, 900); //turn to wall
  chassis.moveToPoint(80, 65.8, 1000, {.maxSpeed = 60});
  armTarget = raisedPos;
  pros::delay(100);
  sortingColor = true;
  pros::delay(400);
  sortingColor = false;
  intake.move(0);
  chassis.waitUntilDone();//goes to wall
  armTarget = wallPos;
  pros::delay(600);
  armTarget = loadingPos;
  pros::delay(500);
  useAutoIntake = false;
  spinUntilDetected = false;
  sortingColor = true;
  pros::delay(900);
  sortingColor = false;
  intake.move(0);
  armTarget = wallPos;
  pros::delay(700);
  chassis.moveToPoint(60, 65.5, 800, {.forwards = false}); //drive back from wall

  armTarget = restingPos;
  chassis.turnToPoint(67, 91, 800);
  sortingColor = true;
  chassis.moveToPoint(67, 91, 1200);
  chassis.turnToPoint(48, 94, 800);
  chassis.moveToPoint(48, 94, 1200);
  chassis.moveToPoint(70, 95, 1200, {.forwards = false});
  chassis.turnToPoint(68, 128, 800);
  chassis.moveToPoint(68, 128, 1200);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.turnToPoint(75, 131, 800, {.forwards = false});
  chassis.moveToPoint(75, 131, 1200, {.forwards = false});
  sortingColor = false;
  intake.move(0);
  chassis.waitUntilDone();
  goalClamp.set_value(false);



  

  //chassis.turnToHeading(67, 800);

  
  

  
    
}