//
// Created by Nadavash on 18/05/2021.
//

#include "robot.h"
#include "axis.h"
#include "camera.h"


void Robot::setSpeed(int speed) {
    motorL.motor_setSpeed(speed);
    motorR.motor_setSpeed(speed);
}

int Robot::getSpeed() {
    return MAX(motorL.motor_getSpeed(), motorR.motor_getSpeed());
}

void Robot::driveForward() {
    Serial.println("=========================");
    Serial.print("---> robot->drive_forwards");
//    axis_turnStraight(pwm);
    motorL.motor_Forward();
    motorR.motor_Forward();
    Serial.println("=========================");
}

void Robot::driveBackward() {
    Serial.println("=========================");
    Serial.print("---> robot->drive_backwards");
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
    camera_scan(pwm);
}
