//
// Created by Nadavash on 18/05/2021.
//

#include "robot.h"
#include "axis.h"
#include "robopet_UltraSonic.h"
#include "parceCommands.h"

#define SEC 1000


void Robot::motorsTurnLeftForward() {
    motorL.motor_setSpeed(0);
    motorR.motor_Forward();
}

void Robot::motorsTurnRightForward() {
    motorL.motor_Forward();
    motorR.motor_setSpeed(0);
}

void Robot::motorsTurnLeftBackward() {
    motorL.motor_Backward();
    motorR.motor_setSpeed(0);
}

void Robot::motorsTurnRightBackward() {
    motorL.motor_setSpeed(0);
    motorR.motor_Backward();
}

void Robot::setSpeed(int speed) {
    motorL.motor_setSpeed(speed);
    motorR.motor_setSpeed(speed);
}

int Robot::getSpeed() {
    return MAX(motorL.motor_getSpeed(), motorR.motor_getSpeed());
}

void Robot::driveForward() {
    Serial.println("=========================");
    Serial.println("---> robot->drive_forwards");
//    axis_turnStraight(pwm);
    motorL.motor_Forward();
    motorR.motor_Forward();
    Serial.println("=========================");
}

void Robot::driveBackward() {
    Serial.println("=========================");
    Serial.println("---> robot->drive_backwards");
//    axis_turnStraight(pwm);
    motorL.motor_Backward();
    motorR.motor_Backward();
    Serial.println("=========================");
}

void Robot::turn(int angle) {
    Serial.println("=========================");
    Serial.print("---> robot->turn "); Serial.println(angle);
    axis_turn(pwm, angle);
    Serial.println("=========================");
}

void Robot::turnLeft() {
   this->turn(HARD_LEFT);
}

void Robot::turnStraight() {
   this->turn(STRAIGHT);
}

void Robot::turnRight() {
   this->turn(HARD_RIGHT);
}



void Robot::stop() {
    Serial.println("=========================");
    Serial.println("---> robot->stop");
    motorL.motor_setSpeed(0);
    motorR.motor_setSpeed(0);
    Serial.println("Robot stopped");
    Serial.println("=========================");
}

void Robot::scan() {
 //    camera_scan(pwm);
      Serial.println("=========================");
    Serial.println("---> robot->scan");
    camera.scan();
    Serial.println("=========================");
}

void Robot::cam_setX(int angle) {
    Serial.println("=========================");
    Serial.println("---> robot->cam_setX");
    camera.setAngleX(angle);
    Serial.println("=========================");
}

void Robot::cam_setY(int angle) {
    Serial.println("=========================");
    Serial.println("---> robot->cam_setX");
    camera.setAngleY(angle);
    Serial.println("=========================");
}

long Robot::getDist(int direction) {
  if (direction == BACK)
     return ultrasonicDistance_read(BACK_TRIGGER_PIN, BACK_ECHO_PIN);
  else if (direction == FRONT)
     return ultrasonicDistance_read(FRONT_TRIGGER_PIN, FRONT_ECHO_PIN);
}


void Robot::spinLeftBackward(int quarters){
    int speed = this->getSpeed();
    this->stop();
    this->driveBackward();
    this->setSpeed(255);
    delay(100);
    this->turnLeft();
    this->motorsTurnLeftBackward();
    delay(SEC*quarters);
    this->setSpeed(speed);
    this->turnStraight();
}

void Robot::spinLeftForward(int quarters){
    int speed = this->getSpeed();
    this->stop();
    this->driveForward();
    this->setSpeed(255);
    delay(100);
    this->turnLeft();
    this->motorsTurnLeftForward();
    delay(SEC*quarters);
    this->setSpeed(speed);
    this->turnStraight();
}

void Robot::spinRightBackward(int quarters){
    int speed = this->getSpeed();
    this->stop();
    this->driveBackward();
    this->setSpeed(255);
    delay(100);
    this->turnRight();
    this->motorsTurnRightBackward();
    delay(SEC*quarters);
    this->setSpeed(speed);
    this->turnStraight();
}

void Robot::spinRightForward(int quarters){
    int speed = this->getSpeed();
    this->stop();
    this->driveForward();
    this->setSpeed(255);
    delay(100);
    this->turnRight();
    this->motorsTurnRightForward();
    delay(SEC*quarters);
    this->setSpeed(speed);
    this->turnStraight();
}











void Robot::parceCommand() {
    if(Serial.available() > 0)  {
        // read the incoming:
      String command[] = {"0", "0", "0", "0"};
      String incoming = Serial.readString();
      Serial.println(incoming);
      splitCommand(incoming, command); 
      if (command[0] == "stop"){
        this->stop();
      }
      else if (command[0] == "left"){
        this->turnLeft();
//        if (command[1] == "--hard")
//          this->motorsLeft();
      }
      else if (command[0] == "right"){
        this->turnRight();
//        if (command[1] == "--hard")
//          this->motorsRight();
      }
      else if (command[0] == "straight"){
        this->turnStraight();
      }
      else if (command[0] == "forward"){
        this->driveForward();
      }
      else if (command[0] == "backward"){
        this->driveBackward();
      }
      else if (command[0] == "scan"){
        this->scan();
      }
      else if (command[0] == "speed"){
       char buf[command[1].length()+1];
       command[1].toCharArray(buf, command[1].length()+1);
       this->setSpeed(atoi(buf));
      }
      else if (command[0] == "turn"){
       char buf[command[1].length()+1];
       command[1].toCharArray(buf, command[1].length()+1);
       this->turn(atoi(buf));
      }
      else if (command[0] == "cam_setX"){
       char buf[command[1].length()+1];
       command[1].toCharArray(buf, command[1].length()+1);
       this->cam_setX(atoi(buf));
      }
      else if (command[0] == "cam_setY"){
       char buf[command[1].length()+1];
       command[1].toCharArray(buf, command[1].length()+1);
       this->cam_setY(atoi(buf));
      }
      else if (command[0] == "dist"){
        if (command[1] == "--front"){
          Serial.print("distance is: ");Serial.println(this->getDist(FRONT));
        }
        else if (command[1] == "--back"){
          Serial.print("distance is: ");Serial.println(this->getDist(BACK));
        }
      }
      else {
        Serial.print("unknown data: ");Serial.println(incoming);
      }
      
    Serial.flush(); 
 }
}
