#include "Arduino.h"
// pid regulator
#include "GyverPID.h"

#define DT 30
#define PODEZD_K_BANKE 40  // max 255

// regulator coefs
#define kp = 1.0;
#define ki = 1.0;
#define kd = 1.0;

// autopilot directions
#define FORWARD 1
#define BACKWARD 0

// reset pin
#define RST 12


GyverPID regulator(0, 0, 0, DT);

// Automotive banka
void autoCatch(){
  man2Pos(defaultPos);
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
  man2Pos(workPos);
  delay(1000);
}

void time_banka(){
  // подготовка
  manCatch(false);  // разжимаем клешню
  manualPower(LEFT, 0); // остановка левой стороны
  manualPower(RIGHT, 0); // остновка правой стороны
  delay(1000); // ждем не понятно чего
  manualPower(LEFT, PODEZD_K_BANKE); // поехали левым мотором
  manualPower(RIGHT, PODEZD_K_BANKE); // плехали правым мотором
  delay(1500); // ждем отъезда
  manualPower(LEFT, 0); // остановка левой стороны
  manualPower(RIGHT, 0); // остновка правой стороны
  manCatch(true); // зажимаем клешню
  delay(200); // ожидание между 
  man2Pos(workPos); // поднимаем манипулятор
  manualPower(LEFT, -1 * PODEZD_K_BANKE); // отъчезжаем левым мотором
  manualPower(RIGHT, -1 * PODEZD_K_BANKE); // отъезжаем правым мотором
  delay(1000); 
  manualPower(LEFT, 0); // остановка левой стороны
  manualPower(RIGHT, 0); // остновка правой стороны
}

// check button and run automatic funcs
void checkAutomotive(){
  if (modeTumbler > tumblerRange[1]){
    time_banka();
    delay(100);
  }

  if (midTumbler > tumblerRange[1]){  // pressed left button
    delay(50);
    // control Arduino from Raspberry PI
    runRPI(); 
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

