//
// Created by Nadavash on 18/05/2021.
//

#include "robopet_servo.h"


int servo_angleToPulse(int ang){
    int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max
    return pulse;
}