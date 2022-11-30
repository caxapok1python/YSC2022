// right motor pins
#define RIGHT_A 2
#define RIGHT_B 4
#define RIGHT_PWM 6

// left motor pins
#define LEFT_A 3
#define LEFT_B 7
#define LEFT_PWM 5

// sides
#define LEFT true
#define RIGHT false

// setup pins
void setupMotors(){
  pinMode(LEFT_A, OUTPUT);
  pinMode(LEFT_B, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_A, OUTPUT);
  pinMode(RIGHT_B, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  digitalWrite(LEFT_A, LOW);
  digitalWrite(LEFT_B, LOW);
  analogWrite(LEFT_PWM, 0);
  digitalWrite(RIGHT_A, LOW);
  digitalWrite(RIGHT_B, LOW);
  analogWrite(RIGHT_PWM, 0);
  
  Serial.println(leftStick);
  while (leftStick < 500){
    readSticks();
    digitalWrite(LEFT_A, LOW);
    digitalWrite(LEFT_B, LOW);
    analogWrite(LEFT_PWM, 0);
    digitalWrite(RIGHT_A, LOW);
    digitalWrite(RIGHT_B, LOW);
    analogWrite(RIGHT_PWM, 0);
  }
  Serial.println(leftStick);
}

// convert joysick value to pwm forward
short int forwardPwm(const short int val){
  return map(val, stickRange[2], stickRange[1], 255, 0);
}

// convert joysick value to pwm backward
short int backwardPwm(const short int val){
  return map(val, stickRange[0], stickRange[2], 255, 0);
}

// setup power manualy (0 <= power <= 255)
void manualPower(bool left, const short int power){
  // forward
  if (power > 0){ 
    if (left){ // left
      digitalWrite(LEFT_A, HIGH);
      digitalWrite(LEFT_B, HIGH);
      analogWrite(LEFT_PWM, power);
      return;
    } 
    // right
    digitalWrite(RIGHT_A, HIGH);
    digitalWrite(RIGHT_B, HIGH);
    analogWrite(RIGHT_PWM, power);
    return;
  }
  // backward
  if (left){ // left
      digitalWrite(LEFT_A, HIGH);
      digitalWrite(LEFT_B, LOW);
      analogWrite(LEFT_PWM, power);
      return;
    }
    // right
    digitalWrite(RIGHT_A, HIGH);
    digitalWrite(RIGHT_B, LOW);
    analogWrite(RIGHT_PWM, power);
    return;
}

// convert joystick value to motor signal
void setPower(bool left, const short int value){
  // if value in center range stop motor
  if (value <= stickRange[2] + centerRange && value >= stickRange[2] - centerRange){
    if (left){ // left
      digitalWrite(LEFT_A, LOW);
      digitalWrite(LEFT_B, LOW);
      analogWrite(LEFT_PWM, 0);
      return;
    }
    digitalWrite(RIGHT_A, LOW);
    digitalWrite(RIGHT_B, LOW);
    analogWrite(RIGHT_PWM, 0);
    return;
    
  }
  if (value > stickRange[2]){
    // forward
    const short int pwm = forwardPwm(value);
//    Serial.println(pwm); // debug
    if (left){
      digitalWrite(LEFT_A, HIGH);
      digitalWrite(LEFT_B, HIGH);
      analogWrite(LEFT_PWM, pwm);
      return;
    }
    digitalWrite(RIGHT_A, HIGH);
    digitalWrite(RIGHT_B, HIGH);
    analogWrite(RIGHT_PWM, pwm);
    return;
  }
  else{
    // backward
    const short int pwm = backwardPwm(value);
//    Serial.print(-pwm); // debug
    if (left){
      digitalWrite(LEFT_A, HIGH);
      digitalWrite(LEFT_B, LOW);
      analogWrite(LEFT_PWM, pwm);
      return;
    }
    else{
      digitalWrite(RIGHT_A, HIGH);
      digitalWrite(RIGHT_B, LOW);
      analogWrite(RIGHT_PWM, pwm);
      return;
    }
  }
}

// control left and right motors both
void controlMotors(){
  setPower(LEFT, leftStick);
  setPower(RIGHT, rightStick);
}
