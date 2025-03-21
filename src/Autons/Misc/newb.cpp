#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlibglobals.hpp"
#include "globals.hpp"

// void new_skills() {
// arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//   //ejectColor = blue;
//   autoStarted = true;
//   sortingColor = true;
//   armTarget = restingPos;
//   runAntiJam = false;
//   chassis.setPose(0, 0, 0);

//   armTarget = restingPos;
//   chassis.moveToPoint(0, 3.5, 500); //move forward to get alliance stake
//   chassis.waitUntilDone();
//   pros::delay(50);
//   sortingColor = true;  //intakes to get alliance stake
//   chassis.waitUntilDone();
//   pros::delay(100);
//   chassis.moveToPoint(-26.2, 38.8, 1100, {.maxSpeed = 100});  //first ring
//   chassis.turnToPoint(-25.8, 18, 500, {.forwards = false}); //aim for the goal
//   sortingColor = false;
//   intake.move(0);
//   chassis.moveToPoint(-25.35, 18, 1000, {.forwards = false, .maxSpeed = 60});  //backs up to the goal
//   chassis.waitUntilDone();
//   goalClamp.set_value(true);  //clamps goal
  
//   chassis.turnToPoint(-59.3, 113.5, 500); //turn to top left ring 
//   sortingColor = true;
//   chassis.moveToPoint(-59.3, 113.5, 3000, {.minSpeed = 60}); //goes there and intake 2 rings
//   chassis.waitUntilDone();
//   pros::delay(400);
//   chassis.moveToPoint(-48, 93, 1100, {.forwards = false});  //drive back
//   chassis.turnToPoint(-50.4, 7, 850, {.maxSpeed = 90}); //turn to bottom 3 rings
//   chassis.moveToPoint(-50.4, 35, 1400, {.maxSpeed = 90}); //move there
//   chassis.waitUntilDone();
//   pros::delay(100);
//   chassis.moveToPoint(-50.4, 7, 1200, {.maxSpeed = 50}); //move there
//   // chassis.waitUntilDone();
//   // double reading = 0;
//   // for(int i = 0; i < 5; i++){
//   //   reading += rightDistance.get();
//   //   pros::delay(10);
//   // }
//   // reading = reading/5 * 0.0393701;
//   // chassis.setPose(-70+reading+6.15, chassis.getPose().y, chassis.getPose().theta);
//   // pros::delay(500);
//   chassis.turnToPoint(-64, 18, 800); //turn to last ring to fill the goal
//   chassis.moveToPoint(-64, 18, 800);
//   chassis.waitUntil(2);
//   armMacro = true;
//   armTarget = loadingPos;
//   chassis.waitUntilDone();
//   pros::delay(300);
//   chassis.turnToHeading(20, 400);
//   chassis.moveToPoint(-67, 7.5, 800, {.forwards = false}); 
//   sortingColor = false;
//   intake.move_velocity(0);
//   goalClamp.set_value(false); // put goal down
//   chassis.moveToPoint(-50, 66, 1700, {.maxSpeed = 100}); // going to wall ring
//   chassis.turnToPoint(-80, 66, 700); //turn to wall
//   chassis.moveToPoint(-80, 66, 1200, {.maxSpeed = 60});  
//   armTarget = raisedPos;
//   pros::delay(100);
//   sortingColor = true;
//   pros::delay(800);
//   sortingColor = false;
//   intake.move(0);
//   chassis.moveToPoint(-80, 65, 2000, {.maxSpeed = 10});  
//   armTarget = wallPos;
//   pros::delay(600);
//   armTarget = loadingPos;
//   pros::delay(500);
//   useAutoIntake = false;
//   spinUntilDetected = false;
//   sortingColor = true;
//   pros::delay(900);
//   sortingColor = false;
//   intake.move(0);
//   armTarget = wallPos;
//   pros::delay(700);
//   armTarget = restingPos;
//   chassis.moveToPoint(-61, 66, 800, {.forwards = false}); //drive back from wall
//   chassis.turnToPoint(-55.5, 111, 700); //aim for top 1 rings
  
//   chassis.moveToPoint(-55.5, 111, 1000, {.maxSpeed = 110});
//   sortingColor = true;
//   chassis.turnToPoint(-31.5, 114.5, 600);
//   chassis.moveToPoint(-31.5, 114.5, 700);
//   doinker.set_value(true);
//   chassis.swingToPoint(-62, 121, DriveSide::LEFT, 1200);
//   chassis.moveToPoint(-65, 125, 1100);
//   doinker.set_value(false);
//   chassis.swingToHeading(-90, DriveSide::RIGHT, 500);
//   chassis.waitUntilDone();
//   double reading = 0;
//   for(int i = 0; i < 5; i++){
//     reading += rightDistance.get();
//     pros::delay(10);
//   }
//   reading = reading/5 * 0.0393701;
//   chassis.setPose(chassis.getPose().x, 140-reading-6.15, chassis.getPose().theta);
//   pros::delay(100);
//   chassis.moveToPoint(-5.5, 131.2, 2000, {.forwards = false, .maxSpeed = 90});
//   chassis.waitUntilDone();
//   pros::delay(300);
//   chassis.turnToPoint(-5.9, 145, 800, {.forwards = false});
//   chassis.moveToPoint(-5.9, 145, 800, {.forwards = false, .maxSpeed = 80});
//   chassis.moveToPoint(-5.9, 134, 500, {.maxSpeed = 40}); //move forward to get alliance stake
//   chassis.waitUntil(0.2);
//   sortingColor = true;  //intakes to get alliance stake
//   chassis.waitUntilDone();
//   pros::delay(500);
//   chassis.moveToPoint(-35, 125, 1000);  
//   sortingColor = false;
//   intake.move(0);
//   chassis.turnToPoint(2, 114.5, 500, {.forwards = false}); //aim for the goal
//   chassis.moveToPoint(2, 114.5, 1000, {.forwards = false});
//   chassis.waitUntilDone();
//   goalClamp.set_value(true);  //clamps goal
//   chassis.moveToPoint(-30, 102, 1000);
//   chassis.turnToPoint(58, 23, 700);
//   chassis.moveToPoint(55, 23, 3000); //move diagonally down
//   sortingColor = true;
//   chassis.turnToPoint(58, 8, 700);
//   chassis.moveToPoint(58, 8, 1000);
//   chassis.turnToPoint(75, 25, 900);
//   chassis.moveToPoint(75, 25, 1000);
//   chassis.waitUntilDone();
//   pros::delay(700);
//   chassis.moveToPoint(76, 9, 800, {.forwards = false});
//   sortingColor = false;
//   intake.move(0);
//   chassis.waitUntilDone();
//   goalClamp.set_value(false);
//   pros::delay(50);
//   chassis.moveToPoint(65, 20, 800);
//   chassis.turnToPoint(37,20, 800, {.forwards = false});
//   chassis.moveToPoint(37, 20, 1200, {.forwards = false});
//   chassis.waitUntilDone();
//   goalClamp.set_value(true);
//   chassis.turnToHeading(90, 500);
//   // chassis.waitUntilDone();
//   // reading = 0;
//   // for(int i = 0; i < 5; i++){
//   //   reading += rightDistance.get();
//   //   pros::delay(10);
//   // }
//   // reading = reading/5 * 0.0393701;
//   // pros::delay(300);
//   // chassis.setPose(chassis.getPose().x, 0+reading+6.15, chassis.getPose().theta);
//   chassis.moveToPoint(57, 69, 1200);
//   sortingColor = true;
//   chassis.turnToPoint(80, 74, 900); //turn to wall
//   chassis.moveToPoint(80, 74, 1000, {.maxSpeed = 60});
//   armTarget = raisedPos;
//   pros::delay(100);
//   sortingColor = true;
//   pros::delay(400);
//   sortingColor = false;
//   intake.move(0);
//   chassis.moveToPoint(80, 74, 2000, {.maxSpeed = 10});
//   armTarget = wallPos;
//   pros::delay(600);
//   armTarget = loadingPos;
//   pros::delay(500);
//   useAutoIntake = false;
//   spinUntilDetected = false;
//   sortingColor = true;
//   pros::delay(900);
//   sortingColor = false;
//   intake.move(0);
//   armTarget = wallPos;
//   pros::delay(700);
//   chassis.moveToPoint(60, 70, 800, {.forwards = false}); //drive back from wall

//   armTarget = restingPos;
//   chassis.turnToPoint(64, 95, 800);
//   sortingColor = true;
//   chassis.moveToPoint(64, 95, 1200);
//   chassis.turnToPoint(45, 97, 800);
//   chassis.moveToPoint(45, 97, 1200);
//   chassis.moveToPoint(63, 97, 1200, {.forwards = false});
//   chassis.turnToPoint(63, 132, 800);
//   chassis.moveToPoint(63, 132, 1200);
//   chassis.waitUntilDone();
//   pros::delay(500);
//   chassis.turnToPoint(75, 134, 800, {.forwards = false});
//   chassis.moveToPoint(75, 134, 1200, {.forwards = false});
//   sortingColor = false;
//   intake.move(0);
//   chassis.waitUntilDone();
//   goalClamp.set_value(false);



  

//   //chassis.turnToHeading(67, 800);

  
  

  
    
// }

void new_skills() {
  arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
  ejectColor = noColor;
  autoStarted = true;
  sortingColor = true;
  armTarget = restingPos;
  runAntiJam = true;
  chassis.setPose(0, 0, 0);

  armTarget = restingPos;
  chassis.moveToPoint(0, 3.5, 500); //move forward to get alliance stake
  chassis.waitUntilDone();
  pros::delay(50);
  sortingColor = true;  //intakes to get alliance stake
  chassis.waitUntilDone();
  pros::delay(100);
  chassis.moveToPoint(-26.4, 40.6, 1100, {.maxSpeed = 100});  //first ring
  chassis.turnToPoint(-25.7, 18, 400, {.forwards = false}); //aim for the goal
  sortingColor = false;
  intake.move(0);
  chassis.moveToPoint(-25.3, 18.2, 800, {.forwards = false, .maxSpeed = 60});  //backs up to the goal
  chassis.waitUntilDone();
  goalClamp.set_value(true);  //clamps goal
  chassis.turnToPoint(-44, 91, 500);
  
  chassis.moveToPoint(-44, 91, 1000, {.minSpeed = 50}); 
  sortingColor = true;
  chassis.moveToPoint(-56.7, 111.5, 3000, {.minSpeed = 50}); //goes there and intake 2 rings
  
  chassis.waitUntilDone();
  pros::delay(400);
  chassis.moveToPoint(-48, 93, 1000, {.forwards = false});  //drive back
  chassis.turnToPoint(-50.5, 7, 1200, {.maxSpeed = 90}); //turn to bottom 3 rings
  chassis.moveToPoint(-50.5, 35, 1400, {.maxSpeed = 90}); //move there
  chassis.waitUntilDone();
  pros::delay(100);
  chassis.moveToPoint(-50.5, 0, 1250, {.maxSpeed = 50}); //move there
  chassis.waitUntilDone();
  double reading = 0;
  for(int i = 0; i < 5; i++){
    reading += rightDistance.get();
    pros::delay(10);
  }
  reading = reading/5 * 0.0393701;
  chassis.setPose(-70+reading+6.15, chassis.getPose().y, chassis.getPose().theta);
  pros::delay(500);
  chassis.turnToPoint(-63.2, 19.2, 1000); //turn to last ring to fill the goal
  chassis.moveToPoint(-63.2, 19.2, 800);
  chassis.waitUntil(2);
  armMacro = true;
  armTarget = loadingPos;
  chassis.waitUntilDone();
  pros::delay(300);
  chassis.turnToHeading(20, 400);
  chassis.moveToPoint(-67, 7.5, 800, {.forwards = false, .maxSpeed = 40}); 
  goalClamp.set_value(false); // put goal down
  chassis.moveToPoint(-49.5, 63.8, 1500, {.maxSpeed = 100}); // going to wall ring
  
  chassis.waitUntil(10);
  sortingColor = false;
  intake.move_velocity(0);
  chassis.turnToPoint(-78, 63.7, 700); //turn to wall
  chassis.moveToPoint(-78, 63.7, 1200, {.maxSpeed = 60});  
  armTarget = raisedPos;
  pros::delay(100);
  sortingColor = true;
  pros::delay(620);
  sortingColor = false;
  intake.move(0);
  chassis.moveToPoint(-78, 63.5, 2000, {.maxSpeed = 10});  
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
  pros::delay(900);
  armTarget = restingPos;
  chassis.moveToPoint(-51, 63.5, 900, {.forwards = false}); //drive back from wall
  
  chassis.turnToPoint(-50.5, 109.4, 800); //aim for top 1 rings
  chassis.moveToPoint(-50.5, 109.4, 1200, {.maxSpeed = 90});
  sortingColor = true;
  chassis.waitUntilDone();
  pros::delay(350);
  sortingColor = false;
  intake.move(0);
  chassis.turnToPoint(-31.5, 114, 800);
  
  chassis.moveToPoint(-31.5, 114, 700);
  doinker.set_value(true);
  chassis.swingToPoint(-62, 122, DriveSide::LEFT, 1200);
  chassis.moveToPoint(-65, 133, 1500);
  leftDoinker.set_value(true);
  doinker.set_value(false);
  // chassis.waitUntilDone();
  // reading = 0;
  // for(int i = 0; i < 5; i++){
  //   reading += rightDistance.get();
  //   pros::delay(10);
  // }
  // reading = reading/5 * 0.0393701;
  // chassis.setPose(chassis.getPose().x, 140-reading-6.15, chassis.getPose().theta);
  // pros::delay(100);
  // chassis.moveToPoint(-6, 130.5, 2000, {.forwards = false, .maxSpeed = 90});
  // chassis.waitUntilDone();
  // pros::delay(300);
  // chassis.turnToPoint(-6, 145, 900, {.forwards = false});
  // chassis.moveToPoint(-6, 145, 1000, {.forwards = false, .maxSpeed = 80});
  // chassis.moveToPoint(-6, 134.8, 500); //move forward to get alliance stake
  // chassis.waitUntilDone();
  // pros::delay(50);
  // sortingColor = true;  //intakes to get alliance stake
  // chassis.waitUntilDone();
  // pros::delay(200);
  //   chassis.moveToPoint(-35, 125, 1000);  
  //   sortingColor = false;
  //   intake.move(0);
    chassis.turnToPoint(1.5, 111, 500, {.forwards = false}); //aim for the goal
    chassis.moveToPoint(1.5, 111, 1700, {.forwards = false, .maxSpeed = 80});
    leftDoinker.set_value(false);
    chassis.waitUntilDone();
    goalClamp.set_value(true);  //clamps goal
    chassis.moveToPoint(-39.5, 89, 1200, {.maxSpeed = 90});
    sortingColor = true;
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.turnToPoint(40, 14, 800);
    chassis.moveToPoint(40, 14, 3000); //move diagonally down
  
    chassis.waitUntil(35);
    sortingColor = false;
    intake.move(0);
    chassis.waitUntil(58);
    sortingColor = true;
    chassis.turnToPoint(41, -2, 700);// getting 2 rings 
    chassis.moveToPoint(41, -2, 1000);
    pros::delay(400);
    chassis.turnToPoint(63.2, 14, 900); // last ring to fill the goal
    chassis.moveToPoint(63.2, 14, 1000);
    chassis.waitUntilDone();
    pros::delay(700);
    chassis.moveToPoint(67, 2, 1200, {.forwards = false}); // put goal down at this coord
    sortingColor = false;
    intake.move(0);
    chassis.waitUntilDone();
    goalClamp.set_value(false);
    pros::delay(50);
    chassis.moveToPoint(58, 13.5, 800);
    chassis.turnToPoint(26,12.7, 800, {.forwards = false});
    chassis.moveToPoint(26, 12.7, 1400, {.forwards = false, .maxSpeed = 70}); //back up to last goal
    chassis.waitUntilDone();
    goalClamp.set_value(true);
    chassis.moveToPoint(31, 13.8, 600, {.minSpeed = 30}); //dont change this
    chassis.moveToPoint(52.5, 61.2, 1500);
    sortingColor = true;
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.turnToPoint(80, 61, 900); //turn to wall
    chassis.moveToPoint(80, 61, 1000, {.maxSpeed = 60});
   
    armTarget = loadingPos;
    pros::delay(500);
    useAutoIntake = false;
    spinUntilDetected = false;
    sortingColor = true;
    pros::delay(1200);
    sortingColor = false;
    intake.move(0);
    armTarget = wallPos;
    pros::delay(700);
    chassis.moveToPoint(50, 61, 800, {.forwards = false}); //drive back from wall
  
    armTarget = restingPos;
    chassis.turnToPoint(53, 85, 800); //ring 1 right top
    sortingColor = true;
    chassis.moveToPoint(53, 85, 1200);
    chassis.turnToPoint(31, 88.5, 800); //ring 2 
    chassis.moveToPoint(31, 88.5, 1200);
    chassis.moveToPoint(57, 88, 1200, {.forwards = false}); //back up
    chassis.turnToPoint(57, 128, 800);
    chassis.moveToPoint(57, 128, 1200, {.maxSpeed = 60}); //get 2 rings
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.turnToPoint(75, 131, 800, {.forwards = false}); //drop goal
    chassis.moveToPoint(75, 131, 600, {.forwards = false});
    sortingColor = false;
    intake.move(0);
    chassis.waitUntilDone();
    goalClamp.set_value(false);
    chassis.moveToPoint(73, 110, 700);
    armTarget = wallPos;
    chassis.moveToPoint(-16, 60, 1600, {.forwards = false, .minSpeed = 110}); // hang
    chassis.waitUntilDone();
    armTarget = loadingPos;

    
}