#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor frontleft = motor(PORT8, ratio6_1, false);
motor backleft = motor(PORT11, ratio6_1, false);
motor backright = motor(PORT9, ratio6_1, true);
motor frontright = motor(PORT10, ratio6_1, true);
controller Controller1 = controller(primary);
motor boostright = motor(PORT20, ratio6_1, true);
motor boostleft = motor(PORT12, ratio6_1, false);
digital_out clamp = digital_out(Brain.ThreeWirePort.F);
inertial intertia = inertial(PORT1);
encoder righttracker = encoder(Brain.ThreeWirePort.A);
encoder lefttracker = encoder(Brain.ThreeWirePort.G);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}