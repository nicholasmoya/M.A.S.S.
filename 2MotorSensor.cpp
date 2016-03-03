#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>

#include "motor/DCMotor.h"

using namespace std;
using namespace exploringBB;

#define LDR_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"

int readAnalog(int number)
{
    stringstream ss;
    ss << LDR_PATH << number << "_raw";
    fstream fs;
    fs.open(ss.str().c_str(),fstream::in);
    fs >> number;
    fs.close();

    return number;
}

int main(){
    DCMotor dcm1(new PWM("pwm_test_P9_42.16"), 116); //will export GPIO116
    DCMotor dcm2(new PWM("pwm_test_P9_22.17"), 115); //will export GPIO115
    dcm1.setDirection(DCMotor::CLOCKWISE);
  
    dcm2.setDirection(DCMotor::CLOCKWISE);
    dcm2.setSpeedPercent(50.0f);   //make it clear that a float is passed
    dcm1.go();
    dcm2.go();

    int counter = 0;
    float distanceThreshold = 25.0;
    float maxPID = 20; // max possible value of the sum of control variables
    float kp = 1;
    float kd = 1; // the gains of proportional and derivative control 

    float error1, error2;
    float lastError1 = 0;
    float lastError2 = 0;
    float P1, D1, P2, D2; // proportional and derivative control variables
    float motorSpeed1, motorSpeed2; // the corrected motor speed as a percentage of max motor speed

    int value0;
    int value1;
    int value2;

    float distance0;
    float distance1;
    float distance2;

    while(1) {
        distance0 = 35.3112f*exp(-0.0006672f*(float)value0);  // calculate distance from sensor 0
        distance1 = 35.3112f*exp(-0.0006672f*(float)value1);  // calculate distance from sensor 1
        distance2 = 35.3112f*exp(-0.0006672f*(float)value2);  // calculate distance from sensor 2
        value0 = readAnalog(0);  // assign value from ADC 0 pin
        value1 = readAnalog(1);  // assign value from ADC 1 pin
        value2 = readAnalog(2);  // assign value from ADC 2 pin

        // cout << "The distance from the front sensor is: " << distance0 << " cm" << "value = " << value0;  // display distance0

        // Back up if sensor 0 detects an object

        /*
        if (counter > 0)
            counter -= 1;
        else {
            counter = 10;            
            cout << "\n Shaka Zulu" << '\r' << endl;  // display warning if neccessry
            dcm1.setDirection(DCMotor::ANTICLOCKWISE);
            dcm2.setDirection(DCMotor::ANTICLOCKWISE);
            dcm1.setSpeedPercent(65.0f);   //make it clear that a float is passed
            dcm2.setSpeedPercent(50.0f);   //make it clear that a float is passed
            dcm1.go();
            dcm2.go();
            usleep(5000000);
            dcm1.stop();
            dcm2.stop();
        }

        cout << "The distance from the first sensor is: " << distance1 << " cm";  // display distance1

        */ 

        if ((distance1 <= distanceThreshold) && (distance2 >= distanceThreshold)) {
            dcm1.setSpeedPercent(50.0f);   //make it clear that a float is passed

            cout << "Correcting the distance from the left sensor" << '\r' << endl;  
            cout << "Distance from sensor is: " << distance1 << '\r' << endl;  
        
            error1 = distance1 - distanceThreshold;
            P1 = kp*error1;
            D1 = kd*(error1 - lastError1);
            cout << "Error 1: " << error1 << '\r' << endl;  
            lastError1 = error1;

            motorSpeed2 = 100.0 - 50.0*(maxPID + P1 + D1)/maxPID;

            cout << "P1" << P1 << '\r' << endl;  
            cout << "D1" << D1 << '\r' << endl;  
            cout << "Motor Speed 2: " << motorSpeed2 << '\r' << endl;  
            
            dcm2.setSpeedPercent(motorSpeed2);

            int value1 = readAnalog(1);  // assign value from ADC 1 pin
            float distance1 = 35.3112f*exp(-0.0006672f*(float)value1);  // calculate distance from sensor 1

        }

        /*
        else if ((distance2 <= distanceThreshold) && (distance1 >= distanceThreshold)) {
            dcm2.setSpeedPercent(50.0f);   //make it clear that a float is passed

            cout << "Correcting the distance from the right sensor" << '\r' << endl;  
            cout << "Distance from sensor is: " << distance2 << '\r' << endl;  
        
            error2 = distance2 - distanceThreshold;
            P2 = kp*error2;
            D2 = kd*(error2 - lastError2);
            lastError2 = error2;

            motorSpeed1 = 100.0 - 50.0*(maxPID + P2 + D2)/maxPID;

            cout << "P2" << P2 << '\r' << endl;  
            cout << "D2" << D2 << '\r' << endl;  
            cout << "Error 2: " << error2 << '\r' << endl;  
            cout << "Motor Speed 1: " << motorSpeed1 << '\r' << endl;  
            
            dcm1.setSpeedPercent(motorSpeed1);

            int value2 = readAnalog(2);  // assign value from ADC 1 pin
            float distance2 = 35.3112f*exp(-0.0006672f*(float)value2);  // calculate distance from sensor 1

            counter = 0;
        }
        else if ((distance1 >= distanceThreshold) && (distance2 >= distanceThreshold)) {
            dcm1.setSpeedPercent(50.0f);   //make it clear that a float is passed
            dcm2.setSpeedPercent(50.0f);   //make it clear that a float is passed
        }
        else if ((distance1 <= distanceThreshold) && (distance2 <= distanceThreshold)) {
            dcm1.setSpeedPercent(100.0f);   //make it clear that a float is passed
            dcm2.setSpeedPercent(100.0f);   //make it clear that a float is passed
        }
        */

        usleep(50000);
    }
    return 0;
}
