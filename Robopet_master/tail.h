//
// Created by Nadavash on 03/06/2021.
//

#ifndef UNTITLED_TAIL_H
#define UNTITLED_TAIL_H

#include <Adafruit_PWMServoDriver.h>


void tail_shake(Adafruit_PWMServoDriver pwm);
void tail_moveEnd(Adafruit_PWMServoDriver pwm, int angle);
void tail_moveStart(Adafruit_PWMServoDriver pwm, int angle);
void tail_endDown(Adafruit_PWMServoDriver pwm, int angle);

#endif //UNTITLED_TAIL_H
