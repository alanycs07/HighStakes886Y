// #include "autons.hpp"
// #include "lemlibglobals.hpp"
// #include "globals.hpp"

// void redPositive6Ring() {
//     chassis.setPose(-51.6, -13.3, 15.5);
//     armMacro = false;
//     intakeRaise.set_value(true);
//     useAutoIntake = true;
//     spinUntilDetected = true;
//     pros::delay(100);
//     // sortingColor = true;
//     chassis.moveToPose(-49, -5, 15.5, 800);
//     chassis.waitUntilDone();
//     // pros::delay(200);
//     intakeRaise.set_value(false);
//     chassis.turnToPoint(-28, -22, 700, {.forwards = false});
//     chassis.moveToPoint(-28, -22, 1200, {.forwards = false, .maxSpeed = 80});
//     chassis.waitUntil(8);
//     useAutoIntake = false;
//     spinUntilDetected = false;
//     intake.move_velocity(0);
//     chassis.waitUntilDone();
//     pros::delay(100);
//     goalClamp.set_value(true);
//     pros::delay(100);
//     chassis.turnToPoint(-10, -8, 700);
//     chassis.moveToPoint(-10, -8, 1000, {.maxSpeed = 60});
//     chassis.waitUntilDone();
//     pros::delay(100);
//     doinker.set_value(true);
//     pros::delay(200);
//     chassis.moveToPoint(-24.5, -19.5, 800, {.forwards = false});
//     chassis.waitUntilDone();
//     doinker.set_value(false);
//     pros::delay(100);
//     chassis.turnToPoint(-15, -16, 500);
//     chassis.waitUntilDone();
//     sortingColor = true;
//     chassis.moveToPoint(-15, -16, 800, {.maxSpeed = 80});
//     chassis.waitUntilDone();
//     pros::delay(300);
//     chassis.moveToPoint(-28, -29, 800, {.forwards = false});

//     chassis.turnToPoint(-47, -27.5, 800);
//     chassis.moveToPoint(-47, -27.5, 800);
//     chassis.turnToPoint(-26, -47, 800);
//     chassis.moveToPoint(-26, -47, 1000);
//     chassis.turnToPoint(-47, -52.8, 800);
//     chassis.waitUntilDone();
//     sortingColor = false;
//     intake.move_velocity(-12000);
//     chassis.moveToPoint(-55, -52.8, 800);
//     chassis.moveToPoint(-55, -55, 800, {.forwards = false});
//     chassis.turnToPoint(-65, -72, 700);
//     chassis.waitUntilDone();
//     intake.move_velocity(0);
//     sortingColor = true;
//     chassis.moveToPoint(-65, -72, 1400, {.maxSpeed = 60});
//     chassis.moveToPoint(-55, -55, 800, {.forwards = false});
//     chassis.turnToPoint(-65, -72, 800, {.forwards = false});
//     chassis.moveToPoint(-60, -65, 800, {.forwards = false});
//     chassis.waitUntilDone();
//     goalClamp.set_value(false);
//     chassis.moveToPoint(-55, -55, 800);
//     chassis.turnToHeading(270, 800);
//     chassis.moveToPoint(-15, -55, 1000, {.forwards = false});
//     // chassis.turnToPoint(-65, -65, 900);
//     // chassis.waitUntilDone();
//     // sortingColor = false;
//     // sortNextRing = true;
//     // chassis.moveToPoint(-55, -55, 800);
//     // chassis.moveToPoint(-70, -70, 1200, {.maxSpeed = 50});
//     // chassis.waitUntil(4);
//     // sortNextRing = false;
//     // sortingColor = true;
//     // chassis.moveToPoint(-55, -55, 700, {.forwards = false, .maxSpeed = 55});
//     // chassis.waitUntilDone();
//     // intakeRaise.set_value(true);
//     // chassis.moveToPoint(-70, -70, 1500, {.maxSpeed = 40});
//     // chassis.waitUntilDone();
//     // intakeRaise.set_value(false);
//     // chassis.moveToPoint(-55, -55, 800 , {.forwards = false});
//     // chassis.turnToPoint(-47, -23.75, 700);
//     // chassis.moveToPoint(-47, -23.75, 900);
//     // chassis.turnToPoint(-23.5, -47, 800);
//     // chassis.moveToPoint(-23.5, -47, 1000);
//     // chassis.turnToPoint(-65, -65, 800, {.forwards = false});
//     // chassis.moveToPoint(-65, -65, 800, {.forwards = false});
// }