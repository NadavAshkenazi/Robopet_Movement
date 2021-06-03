

// C++ code
//
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "pins.h"
#include "robot.h"
#include "robopet_UltraSonic.h"
#include <TimedAction.h>


#define WAIT 1000

Robot robot = Robot();

void parce(){
  robot.parceCommand();
}

void beh(){
  robot.behave();
}



TimedAction parceCommand = TimedAction(300,parce);
TimedAction behave = TimedAction(100,beh);
                               
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
  delay(WAIT);
  Serial.print("Robopet ON");


}
void loop()
{
  robot.robopet_listen();
  parceCommand.check();
  behave.check();
}




   
