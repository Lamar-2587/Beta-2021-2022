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
#include <cmath>
#include "math.h"
#define pi 3.14159265

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
int total;
int fwdconversion = 28; //28 degrees travels 1 inch
int strafeconversion = 62; //62 degrees strafes 1 inch
double trnconversion = 17.5; //17.5 degrees turns some amount of degrees idk

//Resets drivetrain
void reset () {
  leftback.resetPosition();
  rightback.resetPosition();
  rightfront.resetPosition();
  leftfront.resetPosition();
  return;
}

//stops drivetrain
void end () {
  leftback.stop();
  rightback.stop();
  rightfront.stop();
  leftfront.stop();
  return;
}

void kill () {
  leftback.stop(hold);
  rightback.stop(hold);
  rightfront.stop(hold);
  leftfront.stop(hold);
  return;
}

//grab function false is clamp down, true is let go
void grab (bool up) {
  clamp.resetPosition();
  if (up == false){
    clamp.setVelocity(100, percent);
    clamp.rotateFor(-360, degrees, false);   
  } else {
    clamp.setVelocity(100, percent);
    clamp.rotateFor(360, degrees, false);   
  }
  clamp.setBrake(hold);
}

//False is up, true is down.
void lifty (bool up) {
  lift.resetPosition();
  if (up == false){
    lift.setVelocity(100, percent);
    lift.rotateFor(1200, degrees, false);
  } 
  else {
    lift.setVelocity(100, percent);
    lift.rotateFor(-1200, degrees, false);
  }
}
//Takes average of all drivetrain motors' rotational values
//Used in situations going straight foward or backward
int fwdaverage () {
  total = ((leftback.position(degrees) + rightback.position(degrees) + rightfront.position(degrees) + leftfront.position(degrees)) / 4);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(total);
  return total;
}

//
int saverage () {
  total = ((-leftback.position(degrees) + rightback.position(degrees) + -rightfront.position(degrees) + leftfront.position(degrees)) / 4);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(total);
  return total;
}



void front (bool way, double number, int speed) {
  reset();
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);
  if (way == true) {

    double target = number * fwdconversion;
    leftback.spin(forward);
    rightback.spin(forward);
    leftfront.spin(forward);
    rightfront.spin(forward);
    int current;
    while (true) {
      current = fwdaverage();
      if (current >= target) {
        break;
      }
    }
    end();

  } else if (way == false) {

    double target = number * -fwdconversion;
    leftback.spin(reverse);
    rightback.spin(reverse);
    leftfront.spin(reverse);
    rightfront.spin(reverse);
    int current;
    while (true) {
      current = fwdaverage();
      if (current <= target) {
        break;
      }
    }
    end();

  }
  wait(.5, seconds);
  return;
}

void frontgrab (double number, int speed = 80) {
  reset();
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);

  double target = (number * -fwdconversion) + (5 * fwdconversion);
  leftback.spin(reverse);
  rightback.spin(reverse);
  leftfront.spin(reverse);
  rightfront.spin(reverse);
  int current;
  while (true) {
    current = fwdaverage();
    if (current <= target) {
      break;
    }
  }
  grab(false);
  while (true) {
    current = fwdaverage();
    if (current <= (number * -fwdconversion)) {
      break;
    }
    break;
  }
  end(); 
  return;
}



void strafe (bool way, double number, int speed) {
  reset();
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);
  if (way == true) {

    double target = number * strafeconversion;
    leftback.spin(reverse);
    rightback.spin(forward);
    leftfront.spin(forward);
    rightfront.spin(reverse);
    int current;
    while (true) {
      current = saverage();
      if (current >= target) {
        break;
      }
    }
    end();

  } else if (way == false) {

    double target = number * -strafeconversion;
    leftback.spin(forward);
    rightback.spin(reverse);
    leftfront.spin(reverse);
    rightfront.spin(forward);
    int current;
    while (true) {
      current = saverage();
      if (current <= target) {
        break;
      }
    }
    end();

  }
  wait(.5, seconds);
  return;
}

void frontarm (bool up) {
  goalarm.setVelocity(100, percent);
  if (up == true) { 
    goalarm.spin(forward);
    while (true) {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(potG.angle(degrees));
      if (potG.angle(degrees) <= 30) {
        break;
      }
      wait(.05, sec);
    }   
  } else if (up == false) {
    goalarm.spin(reverse);
    while (true) {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(potG.angle(degrees));
      if (potG.angle(degrees) >= 93) {
        break;
      }
      wait(.05, sec);
    }   
  }
  goalarm.stop();
  goalarm.setBrake(hold); 
}

int taverage () {
  total = ((leftback.position(degrees) + -rightback.position(degrees) + -rightfront.position(degrees) + leftfront.position(degrees)) / 4);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(total);
  return total;
}

void rotate (bool way, double number, int speed) {
  reset();
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);
  if (way == true) {

    double target = number * trnconversion;
    leftback.spin(forward);
    rightback.spin(reverse);
    leftfront.spin(forward);
    rightfront.spin(reverse);
    int current;
    while (true) {
      current = taverage();
      if (current >= target) {
        break;
      }
    }
    end();

  } else if (way == false) {

    double target = number * -trnconversion;
    leftback.spin(reverse);
    rightback.spin(forward);
    leftfront.spin(reverse);
    rightfront.spin(forward);
    int current;
    while (true) {
      current = taverage();
      if (current <= target) {
        break;
      }
    }
    end();

  }
  wait(.5, seconds);
  return;
}

void rotate2 (bool way, int target, int speed) {
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);
  
  int hdegrees;

  if (way == true) {
    hdegrees = inertia.rotation(degrees) + target;
    leftback.spin(forward);
    rightback.spin(reverse);
    leftfront.spin(forward);
    rightfront.spin(reverse);
    waitUntil(inertia.rotation(degrees) >= hdegrees);
    end();

  } else if (way == false) {
    hdegrees = inertia.rotation(degrees) - target;
    leftback.spin(reverse);
    rightback.spin(forward);
    leftfront.spin(reverse);
    rightfront.spin(forward);
    waitUntil(inertia.rotation(degrees) <= hdegrees);
    end();
  }
  wait(.5, seconds);  
}

void rotate3 (bool way, int head, int speed){
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);
  
  

  if (way==false) {
    leftback.spin(reverse);
    rightback.spin(forward);
    leftfront.spin(reverse);
    rightfront.spin(forward);

    while (true) {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print(sin((inertia.rotation(degrees)*pi/180)));
      if (sin((inertia.rotation(degrees)*pi/180)) > (sin((head)*pi/180) - .01) && sin((inertia.rotation(degrees)*pi/180)) < (sin((head)*pi/180)+.01)) {
        break;
      }
    }
      kill();
    }
    if (way==true) {
      leftback.spin(forward);
      rightback.spin(reverse);
      leftfront.spin(forward);
      rightfront.spin(reverse);

      while (true) {
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print(sin((inertia.rotation(degrees)*pi/180)));
        if (sin((inertia.rotation(degrees)*pi/180)) > (sin((head)*pi/180) - .01) && sin((inertia.rotation(degrees)*pi/180)) < (sin((head)*pi/180)+.01)) {
          break;
        }
      }
        kill();
    }
    wait(.5, seconds);
  }


void forwardtillbump (int speed) {
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);

  leftback.spin(forward);
  rightback.spin(forward);
  leftfront.spin(forward);
  rightfront.spin(forward);

  waitUntil(goallimit.pressing());

  end();
  wait(.5, seconds);
}

double targetangle;
double magnitude;
double FrBl;
double FlBr;

double backleft;
double backright;
double frontleft;
double frontright;

double scale;


void moveto (double x, double y, double turnval) {
  
  targetangle = atan2(y,x);
  
  magnitude = sqrt(x*x + y*y) / 100;
  
  FrBl = sin(targetangle - pi/4) * magnitude * 1.4142131;
  FlBr = sin(targetangle + pi/4) * magnitude * 1.4142131;

  backleft = FrBl + turnval / 100;
  backright = FlBr - turnval / 100;
  frontleft = FlBr + turnval / 100;
  frontright = FrBl - turnval / 100;

  scale = std::max(std::max(fabs(backleft) , fabs(backright)) , std::max(fabs(frontleft) , fabs(frontright)));

  if (scale < 1) {
    scale = 1;
  }

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Scale: %f", scale);

  backleft = (backleft / scale) * 100;
  backright = (backright / scale) * 100;
  frontleft = (frontleft / scale) * 100;
  frontright = (frontright / scale) * 100;

  leftfront.setVelocity(frontleft, percent);
  leftback.setVelocity(backleft, percent);
  rightfront.setVelocity(frontright, percent);
  rightback.setVelocity(backright, percent);

  leftfront.spin(forward);
  leftback.spin(forward);
  rightfront.spin(forward);
  rightback.spin(forward);

  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("backleft: %f", backleft);

  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("backright: %f", backright);

  Brain.Screen.setCursor(4, 1);
  Brain.Screen.print("frontleft: %f", frontleft);

  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("frontright: %f", frontright);


}

void turncolour (bool way, bool side, int speed, std::string type) {
  leftback.setVelocity(speed, percent);
  rightback.setVelocity(speed, percent);
  rightfront.setVelocity(speed, percent);
  leftfront.setVelocity(speed, percent);

  if (way == true) {
    leftback.spin(forward);
    rightback.spin(reverse);
    leftfront.spin(forward);
    rightfront.spin(reverse);
  } else if (way == false) {
    leftback.spin(reverse);
    rightback.spin(forward);
    leftfront.spin(reverse);
    rightfront.spin(forward);
  }
  
  if (side == true) {
    if (type == "b") {
      while (true) {
        colour.takeSnapshot(colour__BLUEGOAL);
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1); 
        Brain.Screen.print(colour.objectCount);    
        if (colour.largestObject.centerX > 167 && colour.largestObject.centerX < 187) {
          break;
        }
      }
    } else if (type == "r") {
      while (true) {
        colour.takeSnapshot(colour__REDGOAL);
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1); 
        Brain.Screen.print(colour.objectCount);    
        if (colour.largestObject.centerX > 167 && colour.largestObject.centerX < 187) {
          break;
        }
      }
    } else if (type == "y") {
      while (true) {
        colour.takeSnapshot(colour__YELLOWGOAL);
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1); 
        Brain.Screen.print(colour.objectCount);
        Brain.Screen.setCursor(2, 1); 
        Brain.Screen.print(colour.largestObject.centerX);    
        if (colour.largestObject.centerX > 140 && colour.largestObject.centerX < 160) {
          break;
        }
      }  
    }
  } else if (side == false) {
    if (type == "b") {
      while (true) {
        colourb.takeSnapshot(colourb__BLUEGOAL);
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1); 
        Brain.Screen.print(colourb.objectCount);    
        if (colourb.largestObject.centerX > 167 && colourb.largestObject.centerX < 187) {
          break;
        }
      }
    } else if (type == "r") {
      while (true) {
        colourb.takeSnapshot(colourb__REDGOAL);
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1); 
        Brain.Screen.print(colourb.objectCount);
        Brain.Screen.setCursor(2, 1); 
        Brain.Screen.print(colourb.largestObject.centerX);    
        if (colourb.largestObject.centerX > 140 && colourb.largestObject.centerX < 155) {
          break;
        }
      }
    } else if (type == "y") {
      while (true) {
        colourb.takeSnapshot(colourb__YELLOWGOAL);
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1); 
        Brain.Screen.print(colourb.objectCount);
        Brain.Screen.setCursor(2, 1); 
        Brain.Screen.print(colourb.largestObject.centerX);    
        if (colourb.largestObject.centerX > 157 && colourb.largestObject.centerX < 177) {
          break;
        }
      }  
    }
  }
  
  kill();
  wait(.5, seconds);
}

void deploy () {
  Brain.Screen.print("Event has occurred");
  chain.resetPosition();
  chain.setVelocity(100, percent);
  chain.spinFor(-420, degrees, true);
  chain.stop();
  chain.spinFor(1000, degrees, false);
}

//    fwd-back:
//    28 degrees = 1 inch
//
//    strafe:
//    62 degrees = 1 inch
void autonomous(void) {
  int defaultspeed = 70;
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //Initialize inertial sensor
  inertia.startCalibration();
  wait(2, seconds);

  ///*

  //Grab goal in front with front arm
  frontarm(false);
  forwardtillbump(40);
  frontarm(true);
  

  //potential for using match load rings here
  deploy();

  //Go back a bit and strafe a bit left
  front(false, 1, defaultspeed);
  strafe(false, 5, defaultspeed);


  rotate3(true, 75, 50); //96.1417757 degrees precisely
  front(false, 8, defaultspeed);
  turncolour(true, false, 5, "y");
  
  //inertial move till collision or move for certian rotations guarantee meeting of the yellow mobile goal
  frontgrab(47, 80);
  
  //turn towards lower platform
  rotate2(true, 31, 50);

  //move forward 57.378 inches
  front(false, 40, defaultspeed);



  //lift the lift
  lifty(false);
  wait(1, seconds);

  //come to the platform
  front(false, 13, defaultspeed);

  //turn back
  rotate2(false, 30, 50);
  wait(.5, seconds);

  //strafe to level platform
  strafe(true, 10, defaultspeed);

  //re-orient 
  //rotate3(false, 90, 5);

  //grab lets go of goal to balance the goal
  grab(true);

  //rotate to align with blue goal
  rotate3(false, -10, 40);
  
  wait(.5, seconds);



  lifty(true); //move back 4 bar down
  turncolour(true, false, 7, "b"); //turn until blue is seen in the range it should be in
  front(false, 33, defaultspeed); //go to blue goal; stop before getting there though
  frontarm(false); //drop red one from front goal
  turncolour(false, false, 7, "b");
  turncolour(true, false, 7, "b");
  front(false, 12, defaultspeed); // resume trip to blue goal
  
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  
  grab(false); //clamp down blue
  frontarm(true);//pull arm back up as to not block vision sensor

  rotate2(true, 30, 5); //rotate towards yellow central goal

  turncolour(true, true, 3, "y"); //finish rotating with help of color

  frontarm(false); //put arm down for yellow goal

  front(true, 60, defaultspeed); //go until yellow goal hits button

  rotate2(true, 3, 80); //rotate to desired tall yellow deposit

  front(true, 75, defaultspeed);//deposit tall yellow

  front(false, 35, 80);//move back to start balancing blue

  rotate3(false, -90, 50);

  lifty(false);
  
  strafe(false, 15, 80);

  front(false, 25, 80);

  grab(true);

  /////////////////////////////////////////////////

  front(true, 5, 50);

  lifty(true);

  rotate2(true, 73, 30);

  turncolour(true, true, 5, "r");

  frontarm(false);
///////////////////////////////////////
//collide with red goal
  forwardtillbump(30);
  kill();
  wait(0.5, seconds);
  forwardtillbump(40);

  frontarm(true);

  rotate2(true, 40, 20);

  turncolour(true, false, 5, "y");

  front(false, 25, 30);

  grab(false);
  wait(.5, seconds);
  
  rotate3(true, 90, 30);

  lifty(false);
  
  strafe(true, 20, 80);

  rotate3(false, 90, 30);

  wait(1, seconds);

  front(false, 45, 50);

  grab(true);

  front(true, 20, 50);

  lifty(true);

  rotate3(false, 30, 30);

  turncolour(false, false, 5, "r");

  front(false, 50, 30);
  
  ///

  grab(false);

  wait(.5, seconds);

  front(true, 20, 50);

  lifty(false);

  wait(.7, seconds);

  rotate2(true, 90, 50);

  front(false, 10, 30);

  grab(true);

  front(true, 10, 50);


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

bool toggleEnabledb = false; 
bool buttonPressedb = false; 




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

    /*leftback.setVelocity(front + rotate - strafe, percent);
    leftback.spin(forward);

    rightback.setVelocity(front - rotate + strafe, percent);
    rightback.spin(forward);

    leftfront.setVelocity(front + rotate + strafe, percent);
    leftfront.spin(forward);

    rightfront.setVelocity(front - rotate - strafe, percent);
    rightfront.spin(forward);*/



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
    } else if (remote.ButtonB.pressing()) {
      chain.stop();
      chain.spin(reverse);
    }
    else{
      chain.stop();
    }

    /*bool buttonB = remote.ButtonB.pressing();
    if (buttonB && !buttonPressedb){
      buttonPressedb = true; 
      toggleEnabledb = !toggleEnabledb;
    }
    else if (!buttonB) buttonPressedb = false;

    if(toggleEnabledb){
      deploy ();
    }*/

    //remote.ButtonB.released(deploy);



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

    moveto(strafe, front, rotate);
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

