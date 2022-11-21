// Include
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
  
  // setup components
  // firmata serail 57600 baud
  setupJoystick(); // joystick
  
  setupRPI(); // raspberry pi: firmata setup(long time ± 10sec)
  setupMotors(); // motors: setup drivers
  setupMan(); // manipulator

  setupGyro(); // gyro & acceleraton
  
}


/*
┌─────────────────────────────────────────────────────────────┐
│                            LOOP                             │
└─────────────────────────────────────────────────────────────┘
*/
void loop() {
  // read joystick
  readTumblers(); // tumblers
  readSticks(); // sticks
  readJoyButton(); // button

  // control robot components
  controlMotors(); // motors
  controlMan(); // maipulator

  // automative
  checkAutomotive(); // check start for automotive

}
