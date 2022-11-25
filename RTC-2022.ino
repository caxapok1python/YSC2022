// Include
#include "Arduino.h" // basic library
#include "reset.h" // rescure reset 
#include "joystick.h" // joystick library
#include "motors.h" // motors driver library
#include "manipulator.h" // manipulator library
#include "gyro.h" // gyto library (no code)
#include "rpi.h" // rpi library (no code)
#include "automotive.h" // automatisation library

/*
┌─────────────────────────────────────────────────────────────┐
│                            SETUP                            │
└─────────────────────────────────────────────────────────────┘
*/
void setup() {
  setupRescure(); // setup sercure reset pin

  // debug
  // setup serial
  Serial.begin(115200);
  delay(10);
  
  // setup components
  // firmata serail 57600 baud
  setupJoystick(); // joystick
  
  setupMotors(); // motors: setup drivers
  setupMan(); // manipulator

  setupGyro(); // gyro & acceleration
}


/*
┌─────────────────────────────────────────────────────────────┐
│                            LOOP                             │
└─────────────────────────────────────────────────────────────┘
*/
void loop() {
  // testMan(); // debug

  // calibrateSticks(); // debug

  // read joystick
  readTumblers(); // tumblers
  readSticks(); // sticks
  readJoyButton(); // button

  // control robot components
  controlMotors(); // motors
  controlMan(); // manipulator

  // automotive
  checkAutomotive(); // check start for automotive

}
