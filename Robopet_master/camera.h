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
        int angleX;
        int angleY;
        Adafruit_PWMServoDriver pwm;
        Servo servo_headX;
        Servo servo_headY;
        Camera(Adafruit_PWMServoDriver pwm) :angleX(90), angleY(90), pwm(pwm) {};
        void CameraSetup();
        void setAngleX(int angle, bool debug=false);
        int getAngleX();
        void setAngleY(int angle, bool debug=false);
        int getAngleY();
        void scan(bool debug=false);
        void mouthSetAngle(int angle, bool debug=false);

};
#endif //UNTITLED_CAMERA_H
