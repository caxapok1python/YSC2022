#include <Servo.h>
// Pins
#define LOW_SERVO 8
#define MIDDLE_SERVO 9
#define HIGH_SERVO 10
#define CAP A13


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

// go to zero position
void man2zero(){
  midServo.write(0); // strighten middle servo
  delay(700); // long delay
  lowServo.write(0); // strighten low servo
  delay(500); // delay for low servo position
}

// go to position you want
void man2Pos(const short int pos[3]){
  man2zero(); // return man to zero position
  lowServo.write(pos[0]); // low servo to target position
  delay(700); // long delay
  midServo.write(pos[1]); // middle servo to target position
  delay(700); // delay for all
}

// setup manipulator
void setupMan(){
  highServo.attach(LOW_SERVO);
  lowServo.attach(MIDDLE_SERVO);
  midServo.attach(HIGH_SERVO);
  pinMode(CAP, INPUT_PULLUP);
  man2Pos(defaultPos);
}

// compress|decompress high servo 
void manCatch(bool flag){
  if (flag) highServo.write(catchBanka);
  else highServo.write(highServoRange[0]);
  delay(500);
}

// check tumblers and run functions (manipulator main loop)
void controlMan(){
  // low tumbler
  if (lowTumbler > tumblerRange[1]){ // low tumbler up
    man2Pos(defaultPos);
    delay(50);
    return;
  }
  if (lowTumbler < tumblerRange[0]){ // low tumbler down
    man2Pos(workPos);
    delay(50);
    return;
  }

  // middle tumbler
  if (midTumbler < tumblerRange[0]){ // middle tumbler up
    man2Pos(upPos);
    delay(50);
    return;
  }
  if (midTumbler > tumblerRange[1]){ // middle tumbler down
    return;
  }

  // mode tumbler
  if (midTumbler < tumblerRange[0]){ // mode tumbler up
    man2Pos(upPos);
    delay(50);
    return;
  }
  if (midTumbler > tumblerRange[1]){ // mode tumbler down
    return;
  }

  // high tumbler
  if (highTumbler < tumblerRange[0]) { // high tumbler up 
    manCatch(false);
    return;
  }
  if (highTumbler > tumblerRange[1]) { // high tumbler down
    manCatch(true);
    return;
  }
}

// manual manipulator control
void manualMan(){

  return;
}

// read manipulator cap button
void readCap(){
  capState = !digitalRead(CAP);
}

// test man positions only ( declarate after setupMan() ) 
void testMan(){
  man2zero();
  delay(1000 * 1000); // delay (1000 * 1000 about 16 min)
}
