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

//camera consts
#define MIN_X_ANGLE 20
#define MAX_X_ANGLE 180
#define MIN_Y_ANGLE 20
#define MAX_Y_ANGLE 90
#define CAMERA_STEP 20

void camera_scan(Adafruit_PWMServoDriver pwm);

#endif //UNTITLED_CAMERA_H
