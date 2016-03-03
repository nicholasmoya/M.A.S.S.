/* A DC Motor Example
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include <iostream>
#include "motor/DCMotor.h"
using namespace std;
using namespace exploringBB;

int main(){
   cout << "Starting EBB DC Motor Example" << endl;
   DCMotor dcm1(new PWM("pwm_test_P9_42.16"), 116); //will export GPIO116
   DCMotor dcm2(new PWM("pwm_test_P9_22.17"), 115); //will export GPIO116
   dcm1.setDirection(DCMotor::ANTICLOCKWISE);
   dcm2.setDirection(DCMotor::CLOCKWISE);
   dcm1.setSpeedPercent(50.0f);   //make it clear that a float is passed
   dcm2.setSpeedPercent(00.0f);   //make it clear that a float is passed
   dcm1.go();
   dcm2.go();
   /*
   cout << "Rotating Anti-clockwise at 50% speed" << endl;
   usleep(5000000);    //sleep for 5 seconds
   dcm1.reverseDirection();
   dcm2.reverseDirection();
   cout << "Rotating clockwise at 50% speed" << endl;
   usleep(5000000);
   dcm1.setSpeedPercent(00.0f);
   dcm2.setSpeedPercent(70.0f);
   cout << "Rotating clockwise at 100% speed" << endl;
   usleep(5000000);
   */

   dcm1.stop();
   dcm2.stop();
   cout << "End of EBB DC Motor Example" << endl;
}
