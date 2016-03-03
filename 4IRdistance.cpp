/* 
IR Distance Sensor Code

This code reads three analog volage values from the 0 ADC pin, 1 ADC pin, and the 2 ADC pin.
It then calculates the distances the sensors are from an object using the least-squares
equation written into the code and derived from physical measurements. Each distance is then
Displayed along with a warning if the sensor is too close to an object.

*/

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>

using namespace std;

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

int main(int argc, char* argv[])
{
	cout << "Starting the IR distance sensor program:" << endl;
	while(1) 
	{
	  // int value0 = readAnalog(0);  // assign value from ADC 0 pin
    int value1 = readAnalog(1);  // assign value from ADC 1 pin
    int value2 = readAnalog(2);  // assign value from ADC 2 pin
		// float distance0 = 35.3112f*exp(-0.0006672f*(float)value0);  // calculate distance from sensor 0
    float distance1 = 35.3112f*exp(-0.0006672f*(float)value1);  // calculate distance from sensor 1
    float distance2 = 35.3112f*exp(-0.0006672f*(float)value2);  // calculate distance from sensor 2
    
    if ((distance1 <= 10) && (distance2 >= 10)) {
        cout << "Loosey goosey" << endl;
        int value1 = readAnalog(1);  // assign value from ADC 1 pin
        float distance1 = 35.3112f*exp(-0.0006672f*(float)value1);  // calculate distance from sensor 1
        
    }
    else if ((distance1 >= 10) && (distance2 <= 10)) {
        cout << "Shaka Zulu" << endl;
        int value2 = readAnalog(2);  // assign value from ADC 1 pin
        float distance2 = 35.3112f*exp(-0.0006672f*(float)value2);  // calculate distance from sensor 1
    }
    else if ((distance1 >= 10) && (distance2 >= 10)) {
        cout << "Shaka" << endl;
        // int value2 = readAnalog(2);  // assign value from ADC 1 pin
        // float distance2 = 35.3112f*exp(-0.0006672f*(float)value2);  // calculate distance from sensor 1
    }
    else if ((distance1 <= 10) && (distance2 <= 10)) {
        cout << "Zulu" << endl;
        // int value2 = readAnalog(2);  // assign value from ADC 1 pin
        // float distance2 = 35.3112f*exp(-0.0006672f*(float)value2);  // calculate distance from sensor 1
    }

    /* 
	 cout << "The distance from the  first sensor is: " << distance0 << " cm";  // display distance0
	 cout << '\t' << "This distance is ";
		if (distance0 <= 10)
			cout << "too close!" << '\r' << endl;  // display warning if neccessry
		else
			cout << "acceptable" << '\r' << endl;
		
   cout << "The distance from the second sensor is: " << distance1 << " cm";  // display distance1
	cout << '\t' << "This distance is ";
		if (distance1 <= 10)
			cout << "too close!" << '\r' << endl;  // display warning if neccessry
		else
			cout << "acceptable" << '\r' << endl;
      
   cout << "The distance from the  third sensor is: " << distance2 << " cm";  // display distance2
	cout << '\t' << "This distance is ";
		if (distance2 <= 10)
			cout << "too close!" << '\r' << endl;  // display warning if neccessry
		else
			cout << "acceptable" << '\r' << endl;

  cout << "===================================================================================" << endl;
 
    */

		usleep(100000); //this will run for 100 seconds
	}
	return 0;
}
