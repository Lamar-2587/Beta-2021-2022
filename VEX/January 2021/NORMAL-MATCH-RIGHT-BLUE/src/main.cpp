/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftback             motor         11              
// rightback            motor         20              
// leftfront            motor         1               
// rightfront           motor         10              
// goalarm              motor         19              
// chain                motor         6               
// lift                 motor         5               
// clamp                motor         8               
// remote          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



void front (int speed, bool near, int far) {
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.spin(forward);
  rightfront.spin(forward);
  leftback.spin(forward);
  rightback.spin(forward);
  if (near == false) {
    while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print(distancer.distance(mm));
    if (distancer.distance(mm) >= far) {
      break; 
    }
    wait(.05, sec);
    }
  }
  if (near == true) {
    while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print(distancer.distance(mm));
    if (distancer.distance(mm) <= far) {
      break; 
    }
    wait(.05, sec);
    }
  }
  leftfront.stop();
  rightfront.stop();
  leftback.stop();
  rightback.stop();
  rightfront.setBrake(hold);
  rightback.setBrake(hold);
  leftfront.setBrake(hold);
  leftback.setBrake(hold); 
  return;
}


void grab (bool up) {
  if (up == false){
    clamp.setVelocity(100, percent);
    clamp.rotateFor(-360, degrees, false);   
  } else {
    clamp.setVelocity(100, percent);
    clamp.rotateFor(360, degrees, false);   
  }
}



void pause () {
  rightfront.setBrake(hold);
  rightback.setBrake(hold);
  leftfront.setBrake(hold);
  leftback.setBrake(hold); 
}


void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //int backspace = 344;
  //int frontspace = 101;
  Brain.Screen.print("this is autonomous");
  //front(-50, false, 1370);
  leftback.setVelocity(-100, percent);
  rightback.setVelocity(-100, percent);
  leftfront.setVelocity(-100, percent);
  rightfront.setVelocity(-100, percent);
  leftfront.spin(forward);
  rightfront.spin(forward);
  leftback.spin(forward);
  rightback.spin(forward);
    while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print(distancer.distance(mm));
    if (distancer.distance(mm) >= 1000) {
      break; 
    }
    wait(.05, sec);
    }
  grab(false);
    while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print(distancer.distance(mm));
    if (distancer.distance(mm) >= 1370) {
      break; 
    }
    wait(.05, sec);
    }  
  leftfront.stop();
  rightfront.stop();
  leftback.stop();
  rightback.stop();
  rightfront.setBrake(hold);
  rightback.setBrake(hold);
  leftfront.setBrake(hold);
  leftback.setBrake(hold); 
  front(100, true, 600);
  leftback.setVelocity(-20, percent);
  rightback.setVelocity(-20, percent);
  leftfront.setVelocity(-20, percent);
  rightfront.setVelocity(-20, percent);
  leftfront.spin(forward);
  rightfront.spin(reverse);
  leftback.spin(forward);
  rightback.spin(reverse);
  while (true) {
    colour.takeSnapshot(colour__BLUEGOAL);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print(colour.objectCount);    
    if (colour.largestObject.centerX > 110 && colour.largestObject.centerX < 130) {
      break;
    }
    wait(.05, sec);
  }
  leftfront.stop();
  rightfront.stop();
  leftback.stop();
  rightback.stop();
  rightfront.setBrake(hold);
  rightback.setBrake(hold);
  leftfront.setBrake(hold);
  leftback.setBrake(hold);
  goalarm.setVelocity(100, percent);
  goalarm.spin(reverse);
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(frontencoder.position(degrees));
    if (frontencoder.position(degrees) >= 56) {
      break;
    }
    wait(.05, sec);
  }
  goalarm.stop();
  goalarm.setBrake(hold);


  leftback.setVelocity(40, percent);
  rightback.setVelocity(40, percent);
  leftfront.setVelocity(40, percent);
  rightfront.setVelocity(40, percent);
  leftfront.spin(forward);
  rightfront.spin(forward);
  leftback.spin(forward);
  rightback.spin(forward);
  while (true) {
    if (goallimit.pressing()) {
      break; 
    }
    wait(.05, sec);
  }
  leftfront.stop();
  rightfront.stop();
  leftback.stop();
  rightback.stop();
  rightfront.setBrake(brake);
  rightback.setBrake(brake);
  leftfront.setBrake(brake);
  leftback.setBrake(brake);

  goalarm.spin(forward);
  frontencoder.resetRotation();
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(frontencoder.position(degrees));
    if (frontencoder.position(degrees) <= -56) {
      break;
    }
    wait(.05, sec);
  }
  goalarm.stop();
  goalarm.setBrake(hold);

  rightfront.setBrake(coast);
  rightback.setBrake(coast);
  leftfront.setBrake(coast);
  leftback.setBrake(coast);

  
  chain.setVelocity(100, percent);
  chain.spin(forward);

  Brain.Screen.print("DONE!!");

  
  return;

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
int front;
int rotate;
int strafe;


int threshold = 10;
int backthreshold = -10;

bool goalarmstopped = true;
bool chainstopped = true;
bool liftstopped = true;
bool clampstopped = true;

bool toggleEnabled = false; 
bool buttonPressed = false; 


goalarm.setVelocity(100, percent);
  chain.setVelocity(100, percent);
  lift.setVelocity(100, percent);
  clamp.setVelocity(100, percent);


  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    front = remote.Axis3.position();
    rotate = remote.Axis4.position();
    strafe = remote.Axis1.position();

    if (front <= threshold && front >= backthreshold) {
      front = 0;
    }

    if (rotate <= threshold && rotate >= backthreshold) {
      rotate = 0;
    }

    if (strafe <= threshold && strafe >= backthreshold) {
      strafe = 0;
    }

    leftback.setVelocity(front + rotate - strafe, percent);
    leftback.spin(forward);

    rightback.setVelocity(front - rotate + strafe, percent);
    rightback.spin(forward);

    leftfront.setVelocity(front + rotate + strafe, percent);
    leftfront.spin(forward);

    rightfront.setVelocity(front - rotate - strafe, percent);
    rightfront.spin(forward);

    if (remote.ButtonL1.pressing()) {
      /*if (!up) {
        goalarm.spinFor(forward, 440, degrees);
        goalarm.setBrake(hold);
        up = true;
      }*/
     goalarm.spin(forward);
     goalarmstopped = false;
    } else if (remote.ButtonL2.pressing()) {
      /*if (up) {
        goalarm.spinFor(reverse, 440, degrees);
        goalarm.setBrake(hold);
        up = false;
      }*/
     goalarm.spin(reverse);
     goalarmstopped = false;
    } else if (!goalarmstopped) {
     goalarm.stop();
     goalarmstopped = true;
    }


    bool buttonX = remote.ButtonX.pressing();
    if (buttonX && !buttonPressed){
      buttonPressed = true; 
      toggleEnabled = !toggleEnabled;
    }
    else if (!buttonX) buttonPressed = false;

    if(toggleEnabled){
      chain.spin(forward);
    }
    else{
      chain.stop();
    }
/*
    if (remote.ButtonX.pressing()) {
     chain.spin(forward);
     chainstopped = false;
    } else if (remote.ButtonB.pressing()) {
     chain.spin(reverse);
     chainstopped = false;
    } else if (!chainstopped) {
     chain.stop();
     chainstopped = true;
    }
*/
    if (remote.ButtonR1.pressing()) {
     lift.spin(forward);
     liftstopped = false;
    } else if (remote.ButtonR2.pressing()) {
     lift.spin(reverse);
     liftstopped = false;
    } else if (!liftstopped) {
     lift.stop();
     lift.setBrake(hold);
     liftstopped = true;
    }

    if (remote.ButtonUp.pressing()) {
      /*if (!up) {
        goalarm.spinFor(forward, 440, degrees);
        goalarm.setBrake(hold);
        up = true;
      }*/
     clamp.spin(forward);
     clampstopped = false;
    } else if (remote.ButtonDown.pressing()) {
      /*if (up) {
        goalarm.spinFor(reverse, 440, degrees);
        goalarm.setBrake(hold);
        up = false;
      }*/
     clamp.spin(reverse);
     clampstopped = false;
    } else if (!clampstopped) {
     clamp.stop();
     clamp.setBrake(hold);
     clampstopped = true;
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
