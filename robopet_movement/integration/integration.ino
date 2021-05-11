
// C++ code
//
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define WAIT 1000

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
#define MOTOR_INIT_SPEED 50



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

/*
 * gets angle in degree and returns the pulse width
 */
int servo_angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}

/* ========= Axis Functions ========== */

void axis_turnRight(){
  pwm.setPWM(axisPin, 0, servo_angleToPulse(HARD_RIGHT));
  Serial.print("Axis set to ");Serial.print(HARD_RIGHT);
  delay(WAIT);
}

void axis_turnStraight(){
  pwm.setPWM(axisPin, 0, servo_angleToPulse(STRAIGHT));
  Serial.print("Axis set to ");Serial.print(STRAIGHT);
  delay(WAIT);
}

void axis_turnLeft(){
  pwm.setPWM(axisPin, 0, servo_angleToPulse(HARD_LEFT));
  Serial.print("Axis set to ");Serial.print(HARD_LEFT);
  delay(WAIT);
}

/* ========= Motor Functions ========== */

void motor_setLSpeed(int speed){
  motorSpeedL = speed;
  analogWrite(ENA, motorSpeedL); //ENA pin
  Serial.print("Left motor set to ");Serial.print(motorSpeedL);
}

int motor_getLSpeed(){
  return motorSpeedL;
}

void motor_setRSpeed(int speed){
  motorSpeedR = speed;
  analogWrite(ENB, motorSpeedR); //ENA pin
  Serial.print("Right motor set to ");Serial.print(motorSpeedR);
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
 Serial.print("Left motor forward");
}

void motor_rForward(){
 digitalWrite(motor2pin1, HIGH);
 digitalWrite(motor2pin2, LOW);
 Serial.print("Right motor forward");
}

void motor_lBackward(){
 digitalWrite(motor1pin1, LOW);
 digitalWrite(motor1pin2, HIGH);
 Serial.print("Left motor backward");
}

void motor_rBackward(){
 digitalWrite(motor2pin1, LOW);
 digitalWrite(motor2pin2, HIGH);
 Serial.print("Right motor backward");
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
 motor_lForward();
 motor_rForward();
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

void robot_driveForwards(){
  axis_turnStraight();
  motor_motor_straight();
}

void robot_driveReverse(){
  axis_turnStraight();
  motor_reverse();
}

void robot_turnLeft(){
  axis_turnLeft();
  motor_turnLeft();
}

void robot_turnRight(){
  axis_turnRight();
  motor_turnRight();
}

void robot_stop(){
  for (int i = MAX(motorSpeedL,motorSpeedR); i >= MOTOR_OFF; i--){
    robot_setSpeed(i);
  }
  Serial.print("Robot stopped");
}

void robot_drive(){
  if (MAX(motorSpeedL,motorSpeedR) <= MOTOR_OFF){
    robot_setSpeed(MOTOR_INIT_SPEED);
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
  motor_setOverallSpeed(100);
  
  motor_lBackward();
  motor_rBackward();
  delay(WAIT);
  
  axis_turnStraight();
  axis_turnRight();
  axis_turnLeft();

  motor_lForward();
  motor_rForward();
  delay(WAIT);

  axis_turnStraight();
  axis_turnRight();
  axis_turnLeft();

  
//    if(Serial.available() > 0)  {
//      int incomingData= Serial.read(); // can be -1 if read error
//      switch(incomingData) { 
//        case '0':
//          //handle '1'
//          servo_9.write(1);
//          Serial.print("0/n");
//          break;
//        case '1':
//          //handle '1'
//          servo_9.write(60);
//          Serial.print("1/n");
//          break;
//        case '2':
//          //hanle '2'
//          servo_9.write(90);
//          Serial.print("2/n");
//          break;
//        case '3':
//          //hanle '3'
//          servo_9.write(115);
//          Serial.print("3/n");
//          break;
//        case '4':
//          //hanle '4'
//          servo_9.write(180);
//          Serial.print("4/n");
//          break;
//        case '5':
//          //hanle '5'
//          servo_9.write(0);
//          for (int pos = 0; pos <= 180; pos+=5){
//              servo_9.write(pos);
//              delay(500);
//              if(Serial.available() > 0){
//                int incomingData = Serial.read();
//                if (incomingData == '0') break;
//              }
//          }
//          Serial.print("5/n");
//          break;
//
//        default:
//        // handle unwanted input 
//        break;
//      }
//   }
}



   
