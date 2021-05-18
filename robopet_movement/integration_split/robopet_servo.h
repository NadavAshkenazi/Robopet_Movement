//
// Created by Nadavash on 18/05/2021.
//

#ifndef UNTITLED_ROBOPET_SERVO_H
#define UNTITLED_ROBOPET_SERVO_H

#include "Arduino.h"

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575

int servo_angleToPulse(int ang);

#endif //UNTITLED_ROBOPET_SERVO_H
