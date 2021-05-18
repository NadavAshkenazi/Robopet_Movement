
// C++ code
//
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "parceCommands.h"
#include "camera.h"
#include "robopet_servo.h"
#include "pins.h"
#include "axis.h"
#include "robopet_UltraSonic.h"
#include "motor.h"

String incoming = "";   // for incoming serial string data
String command[] = {"0", "0", "0"};

#define WAIT 1000

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


//motors consts
#define MOTOR_OFF 0
#define MOTOR_MAX_SPEED 255
#define MOTOR_INIT_SPEED 100


//PCA9685:
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // PCA9685 interface with the default address 0x40
Motor motorL = Motor(MOTOR1_PIN1, MOTOR1_PIN2, ENA, "Left");
Motor motorR = Motor(MOTOR2_PIN1, MOTOR2_PIN2, ENB, "Right");

//motorSpeed

int motorSpeedL = 0;
int motorSpeedR = 0;


/* ========= Motor Functions ========== */

//void motor_setLSpeed(int speed){
//  motorSpeedL = speed;
//  analogWrite(ENA, motorSpeedL); //ENA pin
//  Serial.print("Left motor set to ");Serial.println(motorSpeedL);
//}
//
//int motor_getLSpeed(){
//  return motorSpeedL;
//}

//void motor_setRSpeed(int speed){
//  motorSpeedR = speed;
//  analogWrite(ENB, motorSpeedR); //ENA pin
//  Serial.print("Right motor set to ");Serial.println(motorSpeedR);
//}
//
//int motor_getRSpeed(){
//  return motorSpeedR;
//}
//
int motor_setOverallSpeed(int speed){
  motorL.motor_setSpeed(speed);
  motorR.motor_setSpeed(speed);
}
//
//void motor_lForward(){
// digitalWrite(MOTOR1_PIN1, HIGH);
// digitalWrite(MOTOR1_PIN2, LOW);
// Serial.println("Left motor forward");
//}
//
//void motor_rForward(){
// digitalWrite(MOTOR2_PIN1, HIGH);
// digitalWrite(MOTOR2_PIN2, LOW);
// Serial.println("Right motor forward");
//}
//
//void motor_lBackward(){
// digitalWrite(MOTOR1_PIN1, LOW);
// digitalWrite(MOTOR1_PIN2, HIGH);
// Serial.println("Left motor backward");
//}
//
//void motor_rBackward(){
// digitalWrite(MOTOR2_PIN1, LOW);
// digitalWrite(MOTOR2_PIN2, HIGH);
// Serial.println("Right motor backward");
//}

void motor_turnLeft(){
// motor_lForward();
// motor_rBackward();
  motorL.motor_Forward();
  motorR.motor_Backward();
}


void motor_turnRight(){
// motor_lBackward();
// motor_rForward();
  motorL.motor_Backward();
  motorR.motor_Forward();
}

void motor_straight(){
// motor_lForward();
// motor_rForward();
  motorL.motor_Forward();
  motorR.motor_Forward();
}

void motor_reverse(){
// motor_lBackward();
// motor_rBackward();
  motorL.motor_Backward();
  motorR.motor_Backward();
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
  return MAX(motorL.motor_getSpeed(), motorR.motor_getSpeed());
}

void robot_driveForwards(){
  Serial.println("=========================");
  Serial.print("---> robot->drive_forwards");
  Serial.println("backward");
  axis_turnStraight(pwm);
  motor_straight();
  Serial.println("=========================");
}

void robot_driveReverse(){
  Serial.println("=========================");
  Serial.println("---> robot->drive_Reverse");
  axis_turnStraight(pwm);
  motor_reverse();
  Serial.println("=========================");
}

void robot_turnLeft(){
  Serial.println("=========================");
  Serial.println("---> robot->turn_Left");
  axis_turnLeft(pwm);
//  motor_turnLeft();
  Serial.println("=========================");
}

void robot_turnRight(){
  Serial.println("=========================");
  Serial.println("---> robot->turn_Right");
  axis_turnRight(pwm);
//  motor_turnRight();
  Serial.println("=========================");
}

void robot_stop(){
  Serial.println("=========================");
  Serial.println("---> robot->stop");
//  for (int i = MAX(motorSpeedL,motorSpeedR); i >= MOTOR_OFF; i--){
//    robot_setSpeed(i);
//    delay(10);
//  }
  robot_setSpeed(MOTOR_OFF);
  Serial.println("Robot stopped");
  Serial.println("=========================");
}

void robot_drive(){
  robot_setSpeed(MOTOR_INIT_SPEED);
  robot_driveForwards();
}

void robot_parceCommand(){
  if(Serial.available() > 0)  {
        // read the incoming:
      incoming = Serial.readString();
      Serial.println(incoming);
      splitCommand(incoming, command); 
      if (command[0] == "drive"){
        robot_drive();
      }
      else if (command[0] == "drive"){
        robot_drive();
      }
      else if (command[0] == "stop"){
        robot_stop();
      }
      else if (command[0] == "left"){
        robot_turnLeft();
      }
      else if (command[0] == "right"){
        robot_turnRight();
      }
      else if (command[0] == "forward"){
        robot_driveForwards();
      }
      else if (command[0] == "reverse"){
        robot_driveReverse();
      }
      else if (command[0] == "scan"){
        camera_scan(pwm);
      }
//      else {
//        Serial.print("unknown data: ");Serial.println(incoming);
//      }
      
    Serial.flush(); 
    flushCommand(command);
//    Serial.println("done");
 }
}

void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  //PCA9685 setups
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //L298 setups
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);

  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);
}
void loop()
{
  robot_drive();
  delay(WAIT);
  robot_setSpeed(200);
  delay(WAIT);
  robot_turnLeft();
  delay(WAIT);
  robot_driveReverse();
  delay(WAIT);
  robot_turnRight();
  delay(WAIT);
  robot_driveForwards();
  robot_stop();
  delay(WAIT);
//  Serial.println("in loop");
//  cm = 0.01723 * ultrasonicDistance_read(8, 7);
//  if(cm >= 20){
//    robot_parceCommand();
//  }
//  else {
//    if (robot_getSpeed() != 0){
//        robot_stop();
//        Serial.print("cm = ");Serial.print(cm);Serial.print("\n");
//    }
//  }
    robot_parceCommand();
//    Serial.println("distance is: ");Serial.println(ultrasonicDistance_read(8, 7));
}



   
