
// C++ code
//
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define WAIT 5000

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

//axis consts 
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)
#define HARD_LEFT 60
#define HARD_RIGHT 115
#define STRAIGHT 90

//motors consts
#define MOTOR_OFF 0
#define MOTOR_MAX_SPEED 255
#define MOTOR_INIT_SPEED 100



//camera consts 
#define MIN_X_ANGLE 20
#define MAX_X_ANGLE 180
#define MIN_Y_ANGLE 20
#define MAX_Y_ANGLE 90

//PCA9685:
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // PCA9685 interface with the default address 0x40
int axisPin = 0;
int cameraXPin = 14;
int cameraYPin = 15;

//pins
int motor1pin1 = 2;
int motor1pin2 = 3;
int ENA = 9;

int motor2pin1 = 4;
int motor2pin2 = 5;
int ENB = 10;

//motorSpeed

int motorSpeedL = 0;
int motorSpeedR = 0;


int incomingByte = 0;

/* ========= UltraSonicFuncrions ========== */
int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

/*
 * gets angle in degree and returns the pulse width
 */
int servo_angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}
/* ========= Camera functcions Functions ========== */

void camera_scan(){
  for( int angle =20; angle<181; angle +=20){
    delay(500);
    pwm.setPWM(14, 0, servo_angleToPulse(angle) );
    for( int angle =20; angle<91; angle +=20){
      delay(500);
      pwm.setPWM(15, 0, servo_angleToPulse(angle) );
    }
  }

  delay(1000);
}


/* ========= Axis Functions ========== */

void axis_turnRight(){
  pwm.setPWM(axisPin, 0, servo_angleToPulse(HARD_RIGHT));
  Serial.print("Axis set to ");Serial.print(HARD_RIGHT);
}

void axis_turnStraight(){
  pwm.setPWM(axisPin, 0, servo_angleToPulse(STRAIGHT));Serial.print("\n");
  Serial.print("Axis set to ");Serial.print(STRAIGHT);Serial.print("\n");
}

void axis_turnLeft(){
  pwm.setPWM(axisPin, 0, servo_angleToPulse(HARD_LEFT));Serial.print("\n");
  Serial.print("Axis set to ");Serial.print(HARD_LEFT);Serial.print("\n");
}

/* ========= Motor Functions ========== */

void motor_setLSpeed(int speed){
  motorSpeedL = speed;
  analogWrite(ENA, motorSpeedL); //ENA pin
  Serial.print("Left motor set to ");Serial.print(motorSpeedL);Serial.print("\n");
}

int motor_getLSpeed(){
  return motorSpeedL;
}

void motor_setRSpeed(int speed){
  motorSpeedR = speed;
  analogWrite(ENB, motorSpeedR); //ENA pin
  Serial.print("Right motor set to ");Serial.print(motorSpeedR);Serial.print("\n");
}

int motor_getRSpeed(){
  return motorSpeedR;
}

int motor_setOverallSpeed(int speed){
  motor_setLSpeed(speed);
  motor_setRSpeed(speed);
}

void motor_lForward(){
 digitalWrite(motor1pin1, HIGH);
 digitalWrite(motor1pin2, LOW);
 Serial.print("Left motor forward\n");
}

void motor_rForward(){
 digitalWrite(motor2pin1, HIGH);
 digitalWrite(motor2pin2, LOW);
 Serial.print("Right motor forward\n");
}

void motor_lBackward(){
 digitalWrite(motor1pin1, LOW);
 digitalWrite(motor1pin2, HIGH);
 Serial.print("Left motor backward\n");
}

void motor_rBackward(){
 digitalWrite(motor2pin1, LOW);
 digitalWrite(motor2pin2, HIGH);
 Serial.print("Right motor backward\n");
}

void motor_turnLeft(){
 motor_lForward();
 motor_rBackward();
}


void motor_turnRight(){
 motor_lBackward();
 motor_rForward();
}

void motor_straight(){
 motor_lForward();
 motor_rForward();
}

void motor_reverse(){
 motor_lBackward();
 motor_rBackward();
}


/* ========= Robot movement Functions ========== */

void robot_setSpeed(int speed){
  if(speed >= MOTOR_MAX_SPEED){
    motor_setOverallSpeed(MOTOR_MAX_SPEED);
  }
  else if (speed <= MOTOR_OFF){
    motor_setOverallSpeed(MOTOR_OFF);
  }
  else{
    motor_setOverallSpeed(speed);
  }
}

int robot_getSpeed(){
  return MAX(motor_getLSpeed(), motor_getRSpeed());
}

void robot_driveForwards(){
  Serial.print("=========================\n");
  Serial.print("---> robot->drive_forwards\n");
  Serial.print("backward\n");
  axis_turnStraight();
  motor_straight();
  Serial.print("=========================\n");
}

void robot_driveReverse(){
  Serial.print("=========================\n");
  Serial.print("---> robot->drive_Reverse\n");
  axis_turnStraight();
  motor_reverse();
  Serial.print("=========================\n");
}

void robot_turnLeft(){
  Serial.print("=========================\n");
  Serial.print("---> robot->turn_Left\n");
  axis_turnLeft();
//  motor_turnLeft();
  Serial.print("=========================\n");
}

void robot_turnRight(){
  Serial.print("=========================\n");
  Serial.print("---> robot->turn_Right\n");
  axis_turnRight();
//  motor_turnRight();
  Serial.print("=========================\n");
}

void robot_stop(){
  Serial.print("=========================\n");
  Serial.print("---> robot->stop\n");
//  for (int i = MAX(motorSpeedL,motorSpeedR); i >= MOTOR_OFF; i--){
//    robot_setSpeed(i);
//    delay(10);
//  }
  robot_setSpeed(MOTOR_OFF);
  Serial.print("Robot stopped\n");
  Serial.print("=========================\n");
}

void robot_drive(){
  robot_setSpeed(MOTOR_INIT_SPEED);
  robot_driveForwards();
}

void robot_parceCommand(){
if(Serial.available() > 0)  {
    int incomingData= Serial.read(); // can be -1 if read error
    switch(incomingData) { 
      case 'D':
        //handle 'D'
        robot_drive();
        break;
      case 'S':
        //handle 'S'
        robot_stop();
        break;
      case 'L':
        //hanle 'L'
        robot_turnLeft();
        break;
      case 'R':
        //hanle 'R'
        robot_turnRight();
        break;
      case 'F':
        //hanle 'F'
        robot_driveForwards();
        break;
      case 'B':
        //hanle 'B'
        robot_driveReverse();
        break;
      case 'C':
        //hanle 'C'
        camera_scan();
        break;
      
//      case '5':
//        //hanle '5'
//        servo_9.write(0);
//        for (int pos = 0; pos <= 180; pos+=5){
//            servo_9.write(pos);
//            delay(500);
//            if(Serial.available() > 0){
//              int incomingData = Serial.read();
//              if (incomingData == '0') break;
//            }
//        }
//        Serial.print("5/n");
//        break;

      default:
        Serial.print("unknown data: ");Serial.print(incomingData);Serial.print("\n");
      break;
    }
 }
}

void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  //PCA9685 setups
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //L298 setups
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);
}
void loop()
{
//  robot_drive();
//  delay(WAIT);
//  robot_setSpeed(100);
//  delay(WAIT);
//  robot_turnLeft();
//  delay(WAIT);
//  robot_driveReverse();
//  delay(WAIT);
//  robot_turnRight();
//  delay(WAIT);
//  robot_driveForwards();
//  robot_stop();
//  delay(WAIT);
  cm = 0.01723 * readUltrasonicDistance(8, 7);
  if(cm >= 20){
    robot_parceCommand();
  }
  else {
    if (robot_getSpeed() != 0){
        robot_stop();
        Serial.print("cm = ");Serial.print(cm);Serial.print("\n");
    }
  }
}



   
