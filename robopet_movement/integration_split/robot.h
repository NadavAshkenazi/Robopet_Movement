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
  public:
    Motor motorL;
    Motor motorR;
    Adafruit_PWMServoDriver pwm;
    Camera camera;
    Robot() : motorL(Motor(MOTOR1_PIN1, MOTOR1_PIN2, ENA_PIN, "Left")),
              motorR(Motor(MOTOR2_PIN1, MOTOR2_PIN2, ENB_PIN, "Right")),
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
    void cam_setX(int angle);
    void cam_setY(int angle);
    long getDist();
    void parceCommand();
};

#endif //UNTITLED_ROBOT_H
