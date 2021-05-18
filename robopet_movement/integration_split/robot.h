//
// Created by Nadavash on 18/05/2021.
//

#ifndef UNTITLED_ROBOT_H
#define UNTITLED_ROBOT_H
#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>
#include "motor.h"
#include "pins.h"

class Robot {
    Motor motorL;
    Motor motorR;
    Adafruit_PWMServoDriver pwm;
public:
    Robot() : motorL(Motor(MOTOR1_PIN1, MOTOR1_PIN2, ENA, "Left")),
              motorR(Motor(MOTOR2_PIN1, MOTOR2_PIN2, ENB, "Right")),
              pwm(Adafruit_PWMServoDriver()) {};

    void setSpeed(int speed);
    int getSpeed();
    void driveForward();
    void driveBackward();
    void turnLeft();
    void turnRight();
    void turnStraight();
    void turn(int angle);
    void stop();
    void scan();
};

#endif //UNTITLED_ROBOT_H
