//
// Created by Nadavash on 18/05/2021.
//

#ifndef UNTITLED_AXIS_H
#define UNTITLED_AXIS_H

#include "Arduino.h"
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "robopet_servo.h"
#include "pins.h"

//axis consts
#define HARD_LEFT 60
#define STRAIGHT 90
#define HARD_RIGHT 120



void axis_turnRight(Adafruit_PWMServoDriver pwm, bool debug=false);
void axis_turnStraight(Adafruit_PWMServoDriver pwm, bool debug=false);
void axis_turnLeft(Adafruit_PWMServoDriver pwm, bool debug=false);
void axis_turn(Adafruit_PWMServoDriver pwm, int angle, bool debug=false);
#endif //UNTITLED_AXIS_H
