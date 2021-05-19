//
// Created by Nadavash on 18/05/2021.
//

#include "robot.h"
#include "axis.h"
#include "robopet_UltraSonic.h"
#include "parceCommands.h"


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

void Robot::turnLeft() {
    Serial.println("=========================");
    Serial.println("---> robot->turn_Left");
    axis_turnLeft(pwm);
    Serial.println("=========================");
}

void Robot::turnStraight() {
    Serial.println("=========================");
    Serial.println("---> robot->turn_Right");
    axis_turnStraight(pwm);
    Serial.println("=========================");
}

void Robot::turnRight() {
    Serial.println("=========================");
    Serial.println("---> robot->turn_Right");
    axis_turnRight(pwm);
    Serial.println("=========================");
}

void Robot::turn(int angle) {
    Serial.println("=========================");
    Serial.print("---> robot->turn "); Serial.println(angle);
    axis_turn(pwm, angle);
    Serial.println("=========================");
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

long Robot::getDist() {
    return ultrasonicDistance_read(TRIGGER_PIN, ECHO_PIN);
}

void Robot::parceCommand() {
    if(Serial.available() > 0)  {
        // read the incoming:
      String command[] = {"0", "0", "0"};
      String incoming = Serial.readString();
      Serial.println(incoming);
      splitCommand(incoming, command); 
      if (command[0] == "stop"){
        this->stop();
      }
      else if (command[0] == "left"){
        this->turnLeft();
      }
      else if (command[0] == "right"){
        this->turnRight();
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
         Serial.print("distance is: ");Serial.println(this->getDist());
      }
      else {
        Serial.print("unknown data: ");Serial.println(incoming);
      }
      
    Serial.flush(); 
 }
}
