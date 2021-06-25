
//
// Created by Nadavash on 03/06/2021.
//

#include "tail.h"
#include "pins.h"
#include "Arduino.h"
#include "robopet_servo.h"
#include <Wire.h>

#define MIN_ANGLE 50
#define MAX_ANGLE 120

#define TAIL_DELAY 200

void tail_moveStart(Adafruit_PWMServoDriver pwm, int angle){
  if (angle < MIN_ANGLE) angle = MIN_ANGLE;
  else if (angle > MAX_ANGLE) angle = MAX_ANGLE;
    pwm.setPWM(TAIL_START_PIN, 0, servo_angleToPulse(angle));

}
void tail_moveEnd(Adafruit_PWMServoDriver pwm, int angle){
    pwm.setPWM(TAIL_END_PIN, 0, servo_angleToPulse(angle));
}

void tail_shake(Adafruit_PWMServoDriver pwm){
    for (int i = 0; i <= 3; i++){
//        tail_moveStart(pwm, 60);
//        delay(TAIL_DELAY);
        for( int x = 0; x <= 180; x +=60){
            delay(100);
            tail_moveEnd(pwm, x);
        }
        for( int x =180; x >= 0; x -=60){
            delay(100);
            tail_moveEnd(pwm, x);
        }
            tail_moveEnd(pwm, 90);
    }
//    tail_moveEnd(pwm, 130);


}
