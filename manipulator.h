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
const short int upPos[2] = {0,30}; // 3

bool manMode = false;
bool catchFlag = false;
bool capState = false;

short int lowServoPos = 1, midServoPos = 1, highServoPos = 1;


Servo lowServo;
Servo midServo;
Servo highServo;

// go to zero position
void man2zero(){
  midServo.write(0); // strighten middle servo
  delay(300); // long delay
  lowServo.write(0); // strighten low servo
  delay(300); // delay for low servo position
}

// go to position you want
void man2Pos(const short int pos[3]){
  manualPower(LEFT, 0); // остановка левой стороны
  manualPower(RIGHT, 0); // остновка правой стороны
  man2zero(); // return man to zero position
  // lowServoPos = pos[0];
  // midServoPos = pos[1];
  lowServo.write(pos[0]); // low servo to target position
  // delay(300); // long delay
  midServo.write(pos[1]); // middle servo to target position
}

// compress|decompress high servo 
void manCatch(bool flag){
  if (flag) highServo.write(catchBanka);
  else highServo.write(highServoRange[0]);
  // delay(500);
}

// setup manipulator
void setupMan(){
  highServo.attach(LOW_SERVO);
  lowServo.attach(MIDDLE_SERVO);
  midServo.attach(HIGH_SERVO);
  pinMode(CAP, INPUT_PULLUP);
  man2Pos(workPos);
  manCatch(false);
}

// manual manipulator control
void manualMan(){
  manualPower(LEFT, 0); // остановка левой стороны
  manualPower(RIGHT, 0); // остновка правой стороны
  lowServo.write(lowServoPos);
  delay(200);
  midServo.write(midServoPos);
  delay(200);

  while (true){
    readTumblers();
    // mode tumbler
    if (modeTumbler < 1300){ // mode tumbler up
      delay(50);
      break;
    }
    if (modeTumbler > 1500){
      // lowServoPos = 0;
      // highServoPos = 0;
      // lowServo.write(lowServoPos);
      // delay(200);
      // midServo.write(midServoPos);
      // delay(200);    
      resetFunc();      
    }

    // low tumbler
    if(lowTumbler < tumblerRange[0] and lowServoPos > lowServoRange[0]){ // low tumbler down
      lowServoPos--;
    }
    if (lowTumbler > tumblerRange[1] and lowServoPos < lowServoRange[1]){ // low tumbler up
      lowServoPos++;
    }

    // middle tumbler
    if (midTumbler > tumblerRange[1] and lowServoPos > midServoRange[0]){ // middle tumbler up
      midServoPos++;
    }
    if (midTumbler < tumblerRange[0] and lowServoPos < midServoRange[1]){ // middle tumbler down
      midServoPos--;
    }
    
    midServo.write(lowServoPos);
    lowServo.write(midServoPos);
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
  const short int tmpPos[2] = {midServoPos, lowServoPos};
  man2Pos(tmpPos);
  midServo.write(lowServoPos);
  lowServo.write(midServoPos);  
}

// check tumblers and run functions (manipulator main loop)
void controlMan(){
  // low tumbler
  if (lowTumbler > tumblerRange[1]){ // low tumbler down
    delay(50);
    man2Pos(defaultPos);
    return;
  }
  if (lowTumbler < tumblerRange[0]){ // low tumbler up
    delay(50);
    man2Pos(workPos);
    return;
  }

  // middle tumbler
  if (midTumbler < tumblerRange[0]){ // middle tumbler up
    delay(50);
    man2Pos(upPos);
    return;
  }
  
  // mode tumbler
  if (modeTumbler < tumblerRange[0]){ // mode tumbler up
    delay(500);
    manualMan();
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

// read manipulator cap button
void readCap(){
  capState = pulseIn(CAP, 1);
}

// test man positions only ( declarate after setupMan() ) 
void testMan(){
  while (1){
    readCap();
    Serial.println(capState);    
  }
  delay(1000 * 1000); // delay (1000 * 1000 about 16 min)
}
