#include "GyverPID.h"

#define DT 30
#define PODEZD_K_BANKE 50  // max 255

// regulator coefs
#define kp = 1.0;
#define ki = 1.0;
#define kd = 1.0;

// autopilot directions
#define FORWARD 1
#define BACKWARD 0


GyverPID regulator(0, 0, 0, DT);

// Automotive banka
void autoCatch(){
  man2Pos(workPos);
  readCap();
  while (!capState){
    manualPower(LEFT, PODEZD_K_BANKE);
    manualPower(RIGHT, PODEZD_K_BANKE);
    readCap();
  }
  manualPower(LEFT, 0);
  manualPower(RIGHT, 0);
  manCatch(true);
  delay(500);
  man2Pos(defaultPos);
  delay(1000);
}

// check button and run automatic funcs
void checkAutomotive(){
  if (modeTumbler > tumblerRange[1]){
    autoCatch();
    delay(100);
  }

  if (buttonLeft){  // pressed left button
    buttonLeft = false;
    delay(50);
    loopRPI(); 
  }
}

//auto drive 
void autopilot(const short int direction, const short int speed){
  if (direction == FORWARD){ // drive forward
    return;
  }
  // drive backward
  ;
}
