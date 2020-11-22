// Program used to test the USB Joystick object on the 
// Arduino Leonardo or Arduino Micro.
//
// Matthew Heironimus
// 2015-03-28 - Original Version
// 2015-11-18 - Updated to use the new Joystick library 
//              written for Arduino IDE Version 1.6.6 and
//              above.
// 2016-05-13   Updated to use new dynamic Joystick library
//              that can be customized.
//------------------------------------------------------------

#include "Joystick.h"

// Create Joystick
// Joystick_ Joystick;
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,     // Report ID           (JOYSTICK_DEFAULT_REPORT_ID)
  JOYSTICK_TYPE_JOYSTICK,         // Joystick type       (JOYSTICK_TYPE_MULTI_AXIS)
  
  0,                             // button count        (JOYSTICK_DEFAULT_BUTTON_COUNT)
  0,                              // hat switch count    (JOYSTICK_DEFAULT_HATSWITCH_COUNT)

  true,                           // include X-Axis      (true)
  true,                           // include Y-Axis      (true)
  false,                          // include Z-Axis      (true)

  false,                          // include Rx-Axis     (true)
  false,                          // include Ry-Axis     (true)
  false,                          // include Rz+Axis     (true)
  
  true,                           // include rudder      (true)
  false,                           // include throttle    (true)
  
  false,                          // include accelerator (true)
  false,                          // include brake       (true)
  false                           // include steering    (true)
);


void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  // Set Range Values
  // Joystick.setXAxisRange(-127, 127);
  // Joystick.setYAxisRange(-127, 127);
  // Joystick.setZAxisRange(-127, 127);

  // Joystick.setRxAxisRange(0, 360);
  // Joystick.setRyAxisRange(360, 0);
  // Joystick.setRzAxisRange(0, 720);

  Joystick.setRudderRange(0, 1023);
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
  //Joystick.setThrottleRange(0, 1024);

  // Joystick.setAcceleratorRange(-127, 127);
	// Joystick.setBrakeRange(-127, 127);
	// Joystick.setSteeringRange(-127, 127);
    
  
  Joystick.begin(false);

  // Joystick.setXAxis(0);
  // Joystick.setYAxis(0);
  // Joystick.setZAxis(0);

  // Joystick.setRxAxis(180);
  // Joystick.setRyAxis(180);
  // Joystick.setRzAxis(360);

  Joystick.setRudder(512);
  Joystick.setXAxis(0);
  Joystick.setYAxis(0);
  
  // Joystick.setAccelerator(0);
	// Joystick.setBrake(0);
	// Joystick.setSteering(0);

  Joystick.sendState();
}

int rudderOffset = 0;
bool firstLoop = true;

void loop() {
  if (firstLoop) {
    for (int i=0; i<5; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
    firstLoop = false;

    rudderOffset = (int)analogRead(A0) - 511;
  }

  int rudder = (int)analogRead(A0) - rudderOffset;
  double brakeL = 1.22 * (double)analogRead(A1);
  double brakeR = 1.22 * (double)analogRead(A2);

  Joystick.setRudder(rudder);

 
  

  Joystick.setXAxis((int)brakeL);
  Joystick.setYAxis((int)brakeR);
  

  Joystick.sendState();

  delay(1);

}
