
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
#include "robot.h"

String incoming = "";   // for incoming serial string data
String command[] = {"0", "0", "0"};

#define WAIT 1000


//PCA9685:
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // PCA9685 interface with the default address 0x40
Robot robot = Robot();



void robot_parceCommand(){
  if(Serial.available() > 0)  {
        // read the incoming:
      incoming = Serial.readString();
      Serial.println(incoming);
      splitCommand(incoming, command); 
      if (command[0] == "stop"){
        robot.stop();
      }
      else if (command[0] == "left"){
        robot.turnLeft();
      }
      else if (command[0] == "right"){
        robot.turnRight();
      }
      else if (command[0] == "forward"){
        robot.driveForward();
      }
      else if (command[0] == "backward"){
        robot.driveBackward();
      }
      else if (command[0] == "scan"){
        robot.scan();
      }
      else if (command[0] == "speed"){
       char buf[command[1].length()+1];
       command[1].toCharArray(buf, command[1].length()+1);
       robot.setSpeed(atoi(buf));
      }
      else if (command[0] == "turn"){
       char buf[command[1].length()+1];
       command[1].toCharArray(buf, command[1].length()+1);
       robot.turn(atoi(buf));
      }
      else {
        Serial.print("unknown data: ");Serial.println(incoming);
      }
      
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
  robot.setSpeed(255);
  delay(WAIT);
  robot.driveForward();
  delay(WAIT);
  robot.turnLeft();
  delay(WAIT);
  robot.driveBackward();
  delay(WAIT);
  robot.turnRight();
  delay(WAIT);
  robot.driveForward();
  robot.stop();
  delay(WAIT);
  Serial.println("in loop");
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



   
