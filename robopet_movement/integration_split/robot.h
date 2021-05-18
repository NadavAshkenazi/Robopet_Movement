//
// Created by Nadavash on 18/05/2021.
//

#ifndef UNTITLED_ROBOT_H
#define UNTITLED_ROBOT_H
#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>
#include "motor.h"
#include "camera.h"
#include "pins.h"


class Robot {
    Motor motorL;
    Motor motorR;
    Adafruit_PWMServoDriver pwm;
    Camera camera;
public:
    Robot() : motorL(Motor(MOTOR1_PIN1, MOTOR1_PIN2, ENA, "Left")),
              motorR(Motor(MOTOR2_PIN1, MOTOR2_PIN2, ENB, "Right")),
              pwm(Adafruit_PWMServoDriver()),camera(Camera(CAMERAX_PIN,CAMERAY_PIN, pwm))  {};

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
