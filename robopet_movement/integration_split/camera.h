//
// Created by Nadavash on 18/05/2021.
//

#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

#include "Arduino.h"
#include "robopet_servo.h"
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>



void camera_scan(Adafruit_PWMServoDriver pwm);

class Camera {
public:
        int cameraXPin;
        int cameraYPin;
        int angleX;
        int angleY;
        Adafruit_PWMServoDriver pwm;

        Camera(int cameraXPin, int cameraYPin, Adafruit_PWMServoDriver pwm) : cameraXPin(cameraXPin), cameraYPin(cameraYPin),
                angleX(90), angleY(90), pwm(pwm) {};

        void setAngleX(int angle);
        void getAngleX();
        void setAngleY(int angle);
        void getAngleY();
        void scan();
};
#endif //UNTITLED_CAMERA_H
