// Include
#include "joystick.h" // joystick library
#include "motors.h" // motors driver library
#include "manipulator.h" // manipulator library
#include "gyro.h" // gyto library (no code)
#include "rpi.h" // rpi library (no code)
#include "automotive.h" // automatisation library

void setup() {
  Serial.begin(115200);
  delay(10);

  // setup compopents
  setupMotors(); // motors
  setupJoystick(); // joystick
  setupMan(); // manipulator
  setupRPI(); // raspberry pi
}

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
