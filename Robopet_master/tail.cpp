
//
// Created by Nadavash on 03/06/2021.
//

#include "tail.h"
#include "pins.h"
#include "Arduino.h"
#include "robopet_servo.h"
#include <Wire.h>



#define TAIL_DELAY 100

void tail_moveStart(Adafruit_PWMServoDriver pwm, int angle){
    pwm.setPWM(TAIL_START_PIN, 0, servo_angleToPulse(angle));

}
void tail_moveEnd(Adafruit_PWMServoDriver pwm, int angle){
    pwm.setPWM(TAIL_END_PIN, 0, servo_angleToPulse(angle));
}

void tail_shake(Adafruit_PWMServoDriver pwm){
    for (int i = 0; i <= 3; i++){
        tail_moveStart(pwm, 60);
        delay(TAIL_DELAY);
        tail_moveEnd(pwm, 180);
        delay(TAIL_DELAY);
        tail_moveStart(pwm, 100);
        delay(TAIL_DELAY);
        tail_moveEnd(pwm, 90);
        delay(TAIL_DELAY);
    }
    tail_moveEnd(pwm, 130);


}
