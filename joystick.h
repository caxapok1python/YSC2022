// Sticks
#define LEFT_STICK A2
#define RIGHT_STICK A4

// MEGA2560 PINS ONLY
// Buttons
#define LEFT_BUTTON A7
//#define RIGHT_BUTTON A9
// Tumblers
#define LOW_TUMBLER A8
#define MIDDLE_TUMBLER A9
#define HIGH_TUMBLER A5
#define MODE_TUMBLER A3

// tumbler values
// low tumbler (up > tumblerRange[1]; down < tumblerRange[0])
// middle tumbler (up < tumblerRange[0]; down > tumblerRange[1])
// high tumbler (up > tumblerRange[1]; down < tumblerRange[0])
// mode tumbler (up < tumblerRange[0]; down > tumblerRange[1])

// constant joystick ranges
const short int stickRange[3] = {980, 1995, 1475}; // stick range (min, max, medium)
const short int centerRange = 60; // anti noise protection in medium position of stick
const short int tumblerRange[3] = {1200, 1980}; // tumbler range (min deadline, max deadline)
const short int buttonRange = 1800; // button deadpoint

// setup default position of sticks
short int leftStick = stickRange[2]; 
short int rightStick = stickRange[2]; 

// setup default position of tumblers
short int lowTumbler, midTumbler, highTumbler, modeTumbler = tumblerRange[2]; 

// setup default button position
bool buttonLeft = false;


// setup joysick pins
void setupJoystick(){
  pinMode(LEFT_STICK, INPUT);
  pinMode(RIGHT_STICK, INPUT);
  pinMode(LOW_TUMBLER, INPUT);
  pinMode(MIDDLE_TUMBLER, INPUT);
  pinMode(HIGH_TUMBLER, INPUT);
  pinMode(MODE_TUMBLER, INPUT);
  pinMode(LEFT_BUTTON, INPUT);
}

// void calibateSticks(){
//   // start
//   for (short int timer = 0; timer <=  1000 * 2; timer++){
//     leftJoy[0] = min(leftJoyData[0], analogRead(LEFT_JOY));
//     rightJoyData[0] = min(rightJoyData[0], analogRead(RIGHT_JOY));
//   }
//   // change
//   for (short int timer = 0; timer <=  1000 * 2; timer++){
//     leftJoyData[1] = max(leftJoyData[1], analogRead(LEFT_JOY));
//     rightJoyData[1] = max(rightJoyData[1], analogRead(RIGHT_JOY));
//   }
//   leftJoyData[2] = (leftJoyData[0]+leftJoyData[1])/2;
//   rightJoyData[2] = (rightJoyData[0]+rightJoyData[1])/2;
// }

// read sticks
void readSticks(){
  leftStick = pulseIn(LEFT_STICK, 1);
  rightStick = pulseIn(RIGHT_STICK, 1);
}

// read tumblers
void readMode(){
  modeTumbler = pulseIn(MODE_TUMBLER, 1); 
}
void readLow(){
  lowTumbler = pulseIn(LOW_TUMBLER, 1);
}
void readMid(){
  midTumbler = pulseIn(MIDDLE_TUMBLER, 1); 
}
void readHigh(){
  highTumbler = pulseIn(HIGH_TUMBLER, 1);
}
void readTumblers(){ // all
  lowTumbler = pulseIn(LOW_TUMBLER, 1); 
  midTumbler = pulseIn(MIDDLE_TUMBLER, 1); 
  highTumbler = pulseIn(HIGH_TUMBLER, 1);
  modeTumbler = pulseIn(MODE_TUMBLER, 1); 
}

// read button
void readJoyButton(){
  if (pulseIn(LEFT_BUTTON, 1) > buttonRange) buttonLeft = true;
  else buttonLeft = false;
}

// 
void debugJoystick(){
  if (setupped){
    return;
  }
  // if not setupped raspberry do debug
  // stup serial
  Serial.begin(115200);
  delay(10);

  Serial.print("A0:");
  Serial.print(analogRead(A0));
  Serial.print(" | ");

  Serial.print("A1:");
  Serial.print(analogRead(A1));
  Serial.print(" | ");

  Serial.print("A2:");
  Serial.print(analogRead(A2));
  Serial.print(" | ");

  Serial.print("A3:");
  Serial.print(analogRead(A3));
  Serial.print(" | ");

  Serial.print("A4:");
  Serial.print(analogRead(A4));
  Serial.print(" | ");

  Serial.print("A5:");
  Serial.print(analogRead(A5));
  Serial.print(" | ");

  Serial.print("A6:");
  Serial.print(analogRead(A6));
  Serial.print(" | ");

  Serial.print("A7:");
  Serial.print(analogRead(A7));
  Serial.print(" | ");

  Serial.print("A8:");
  Serial.print(analogRead(A8));
  Serial.print(" | ");

  Serial.print("A9:");
  Serial.print(analogRead(A9));
  Serial.print(" | ");

  // Serial.print("A10:");
  // Serial.print(analogRead(A10));
  // Serial.print(" | ");

  // Serial.print("A11:");
  // Serial.print(analogRead(A11));
  // Serial.print(" | ");

  Serial.println();
}
