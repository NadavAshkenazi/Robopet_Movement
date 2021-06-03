//
// Created by Nadavash on 18/05/2021.
//

#include "robot.h"
#include "axis.h"
#include "robopet_UltraSonic.h"
#include "tail.h"
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
    Serial.println("---> robot->drive_forwards");
//    axis_turnStraight(pwm);
    motorL.motor_Forward();
    motorR.motor_Forward();
}

void Robot::driveBackward() {
    Serial.println("---> robot->drive_backwards");
//    axis_turnStraight(pwm);
    motorL.motor_Backward();
    motorR.motor_Backward();
}

void Robot::turn(int angle) {
    Serial.print("---> robot->turn "); Serial.println(angle);
    axis_turn(pwm, angle);
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
    Serial.println("---> robot->stop");
    motorL.motor_setSpeed(0);
    motorR.motor_setSpeed(0);
    Serial.println("Robot stopped");
}

void Robot::scan() {
 //    camera_scan(pwm);
    Serial.println("---> robot->scan");
    camera.scan();
}

void Robot::cam_setX(int angle) {
    Serial.println("---> robot->cam_setX");
    camera.setAngleX(angle);
}

void Robot::cam_setY(int angle) {
    Serial.println("---> robot->cam_setX");
    camera.setAngleY(angle);
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
    Serial.print("waiting "); Serial.println(SEC*quarters);
    delay(SEC*quarters);
    this->stop();
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
    Serial.print("waiting "); Serial.println(SEC*quarters);
    delay(SEC*quarters);
    this->stop();
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
    Serial.print("waiting "); Serial.println(SEC*quarters);
    delay(SEC*quarters);
    this->stop();
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
    Serial.print("waiting "); Serial.println(SEC*quarters);
    delay(SEC*quarters);
    this->stop();
    this->setSpeed(speed);
    this->turnStraight();
}

void Robot::shakeTail(){
      tail_shake(pwm);
    }

 void Robot::getState(){
  if (this->state == "Idle"){
    Serial.print("Robopet State: Idle");
  }
  else if (this->state == "Happy"){
    Serial.print("Robopet State: Happy");
  }
  else if (this->state == "Friendly"){
     Serial.print("Robopet State: Friendly");
  }
  else if (this->state == "Hostile"){
     Serial.print("Robopet State: Hostile");
  }
  return this->state;
 }
 void Robot::setState(String state){
    if (this->state == "Idle"){
    Serial.print("Robopet State set to Idle");
    }
    else if (this->state == "Happy"){
      Serial.print("Robopet State set to Happy");
    }
    else if (this->state == "Friendly"){
       Serial.print("Robopet State set to Friendly");
    }
    else if (this->state == "Hostile"){
       Serial.print("Robopet State set to Hostile");
    }
    else{
      Serial.print("Undefined State");
      return;
    }
  this->state = state;
 }
 
 void Robot::behave(){
//  if (this->state == "Idle"){
//    Serial.print("Robopet State: Idle");
//  }
  if (this->state == "Happy"){
    this->shakeTail();
  }
  else if (this->state == "Friendly"){
    this->shakeTail();
  }
//  else if (this->state == "Hostile"){
//     Serial.print("Robopet State: Hostile");
//  }
 }

void Robot::robopet_listen(){
  if(Serial.available() > 0)  {
        // read the incoming:
      String incoming = Serial.readString();
      Serial.println(incoming);
      this->nextCommand = incoming;
      Serial.flush(); 
  }
}
void Robot::parceCommand() { 
      String command[] = {"0", "0", "0", "0"};
      splitCommand(this->nextCommand, command); 
      if (command[0] == "Empty"){
        return;
      }
      else if (command[0] == "stop"){
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
     
      else if (command[0] == "spin"){        
       char buf[command[3].length()+1];
       command[3].toCharArray(buf, command[3].length()+1);  
       if (command[1] == "--left"){
          if (command[2] == "--front")
             spinLeftForward(atoi(buf));
          else if (command[2] == "--back")
             spinLeftBackward(atoi(buf));
       }
       else if (command[1] == "--right"){
          if (command[2] == "--front")
             spinRightForward(atoi(buf));
          else if (command[2] == "--back")
             spinRightBackward(atoi(buf));
       }
      }
      else if (command[0] == "shakeTail"){
        this->shakeTail();
      }
      else if (command[0] == "setState"){
         if (command[1] == "Idle"){
            this->setState("Idle");
          }
         else if (command[1] == "Happy"){
            this->setState("Happy");
          }
         else if (command[1] == "Friendly"){
            this->setState("Friendly");
          }
         else if (command[1] == "Hostile"){
            this->setState("Hostile");
          }
        else if (command[1] == "--back"){
          Serial.print("distance is: ");Serial.println(this->getDist(BACK));
        }
      }
      else {
        Serial.print("unknown data: ");Serial.println(this->nextCommand);
      }
      this->nextCommand = "Empty";
}
