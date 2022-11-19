#include <Servo.h>
// Pins
#define LOW_SERVO 8
#define MIDDLE_SERVO 9
#define HIGH_SERVO 10
#define CAP A10


const short int lowServoRange[3] = {0, 80, 40};
const short int midServoRange[3] = {0, 90, 45};
const short int highServoRange[3] = {5, 70, 35};
const short int catchBanka = 60;

const short int defaultPos[2] = {0, 80}; // 1
const short int zeroPos[2] = {0, 0};
const short int workPos[2] = {80, 0}; // 2
const short int upPos[2] = {10, 20}; // 3

bool manMode = false;
bool catchFlag = false;
bool capState = false;

short int lowServoPos, midServoPos, highServoPos;


Servo lowServo;
Servo midServo;
Servo highServo;


void man2zero(){
  lowServo.write(0);
  delay(300);
  midServo.write(0);
  delay(500);
  return;
}

void man2Pos(const short int pos[3]){
  man2zero();
  lowServo.write(pos[0]);
  delay(300);
  midServo.write(pos[1]);
  delay(500);
}

void setupMan(){
  highServo.attach(LOW_SERVO);
  lowServo.attach(MIDDLE_SERVO);
  midServo.attach(HIGH_SERVO);
  pinMode(CAP, INPUT_PULLUP);
  man2Pos(defaultPos);
}

void checkManMode(){
  if (modeTumbler <= tumblerRange[0]){
    manMode = !manMode;
    delay(50);
    return;
  }
}

//void stickControl(const short int serv){
//  if (serv == HIGH_SERVO){
//    return;
//  }
//  short int l = map(leftStick, stickRange[0], stickRange[1], lowServoRange[1], lowServoRange[0]);
//  short int m = map(rightStick, stickRange[0], stickRange[1], midServoRange[1], midServoRange[0]);
//  
//  lowServo.write(l);
//  midServo.write(m);
//}

void manCatch(bool flag){
  if (flag) highServo.write(catchBanka);
  else highServo.write(highServoRange[0]);
  delay(500);
}

void controlMan(){
  if (lowTumbler > tumblerRange[1]){
    man2Pos(workPos);
    delay(50);
    return;
  }
  if (lowTumbler < tumblerRange[0]){
    man2Pos(defaultPos);
    delay(50);
    return;
  }
  if (midTumbler < tumblerRange[0]){
    man2Pos(upPos);
    delay(50);
    return;
  }
  if (highTumbler > tumblerRange[1]) {
    manCatch(true);
    return;
  }
  if (highTumbler < tumblerRange[0]) {
    manCatch(false);
    return;
  }
}

void _controlMan(){
  setPower(LEFT, stickRange[2]);
  setPower(RIGHT, stickRange[2]);
  return;
}

void readCap(){
  capState = !digitalRead(CAP);
}
