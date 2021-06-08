
// C++ code
//
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "pins.h"
#include "robot.h"
#include "robopet_UltraSonic.h"


#define WAIT 1000



Robot robot = Robot();


                               
void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  //PCA9685 setups
  robot.pwm.begin();
  robot.pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //L298 setups
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  pinMode(ENA_PIN, OUTPUT); 
  pinMode(ENB_PIN, OUTPUT);

  //robot setup
  robot.setSpeed(150);
  robot.turnStraight();
  robot.cam_setX(90);
  robot.cam_setY(45);
  delay(WAIT);
  Serial.println("Robopet ON");


}
void loop()
{
//  robot.setSpeed(200);
//  delay(WAIT);
//  robot.turnLeft();
//  delay(WAIT);
//  robot.driveBackward();
//  delay(WAIT);
//  robot.turnRight();
//  delay(WAIT);
//  robot.driveForward();
//  robot.stop();
//  delay(WAIT);
//  if(robot.getDist(FRONT) <= 50){
//    Serial.print("distance is: ");Serial.println(robot.getDist(FRONT));
//    robot.spinLeftBackward(2);
//  }
//  if(robot.getDist(BACK) <= 50){
//    Serial.print("distance is: ");Serial.println(robot.getDist(BACK));
//    int speed = robot.getSpeed();
//    robot.spinLeftForward(2);
//  }
   robot.parceCommand();
   robot.behave();
//   Serial.print("distance is: ");Serial.println(ultrasonicDistance_read(13, 12));
//   robot.shakeTail();
}




   
