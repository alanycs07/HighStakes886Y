#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

void new_skills() {
arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  ejectColor = noColor;
  autoStarted = true;
  sortingColor = true;
  armTarget = restingPos;
  chassis.setPose(0, 0, 0);

  armTarget = restingPos;
  chassis.moveToPose(0, 2.5, 0, 300, {.maxSpeed = 40}); //move forward to get alliance stake
  chassis.waitUntil(0.01);
  sortingColor = true;  //intakes to get alliance stake
  chassis.waitUntilDone();
  pros::delay(50);
  chassis.moveToPoint(-26.2, 38.8, 1100, {.maxSpeed = 100});  //first ring
  chassis.turnToPoint(-26, 18, 500, {.forwards = false}); //aim for the goal
  sortingColor = false;
  intake.move(0);
  chassis.moveToPoint(-26, 18, 1000, {.forwards = false, .maxSpeed = 60});  //backs up to the goal
  chassis.waitUntilDone();
  goalClamp.set_value(true);  //clamps goal
  
  chassis.turnToPoint(-59.5, 113.5, 500); //turn to top left ring 
  runAntiJam = true;
  sortingColor = true;
  chassis.moveToPoint(-59.5, 113.5, 1600, {.minSpeed = 80}); //goes there and intake 2 rings

  chassis.waitUntilDone();
  pros::delay(100);
  chassis.moveToPoint(-50, 94, 1100, {.forwards = false});  //drive back
  chassis.turnToPoint(-53.5, 7, 950); //turn to bottom 3 rings
  chassis.moveToPoint(-53.5, 7, 2000, {.maxSpeed = 90}); //move there
  chassis.waitUntilDone();
  pros::delay(300);
  chassis.turnToPoint(-65, 16, 800); //turn to last ring to fill the goal
  chassis.waitUntilDone();
  pros::delay(300);
  chassis.moveToPoint(-65, 16, 1000);
  chassis.turnToHeading(20, 700);
  armMacro = true;
  armTarget = loadingPos;
  chassis.moveToPoint(-67, 7.5, 800, {.forwards = false}); 
  sortingColor = false;
  intake.move_velocity(-12000);
  pros::delay(300);
  goalClamp.set_value(false); // put goal down
  intake.move_velocity(0);
  chassis.moveToPoint(-66.5, 60, 1200, {.maxSpeed = 95}); // going to wall ring
  armTarget = raisedPos;
  pros::delay(100);
  sortingColor = true;
  chassis.waitUntilDone();
  pros::delay(400);
  sortingColor = false;
  intake.move(0);
  chassis.turnToPoint(-80, 62.4, 700); //turn to wall
  chassis.moveToPoint(-80, 62.4, 3000, {.maxSpeed = 30});  
  chassis.waitUntil(2); //goes to wall
  armTarget = wallPos;
  pros::delay(600);
  armTarget = loadingPos;
  pros::delay(500);
  sortingColor = true;
  pros::delay(900);
  sortingColor = false;
  intake.move(0);
  armTarget = wallPos;
  pros::delay(600);
  
  chassis.moveToPoint(-57, 66, 800, {.forwards = false}); //drive back from wall
  armTarget = restingPos;
  chassis.turnToPoint(-56.6, 110, 900); //aim for top 1 rings
  chassis.moveToPoint(-56.6, 110, 1500, {.maxSpeed = 110});
  sortingColor = true;
  chassis.waitUntilDone();
  double reading = 0;
  for(int i = 0; i < 5; i++){
    reading += leftDistance.get();
    pros::delay(10);
  }
  reading = reading/5 * 0.0393701;
  sortingColor = false;
  intake.move(0);
  chassis.setPose(-70+reading+6.15, 110, 0);
  chassis.turnToPoint(-35, 112, 700);
  chassis.moveToPoint(-35, 112, 700);
  doinker.set_value(true);
  chassis.swingToPoint(-62, 121, DriveSide::LEFT, 1500);
  chassis.moveToPoint(-70, 121, 1500);

  //chassis.turnToHeading(67, 800);

  
  

  
    
}