//
// Created by Nadavash on 18/05/2021.
//

/* ========= Axis Functions ========== */
#include "axis.h"

void axis_turnRight(Adafruit_PWMServoDriver pwm){
    pwm.setPWM(AXIS_PIN, 0, servo_angleToPulse(HARD_RIGHT));
    Serial.print("Axis set to ");Serial.println(HARD_RIGHT);
}

void axis_turnStraight(Adafruit_PWMServoDriver pwm){
    pwm.setPWM(AXIS_PIN, 0, servo_angleToPulse(STRAIGHT));
    Serial.print("Axis set to ");Serial.println(STRAIGHT);
}

void axis_turnLeft(Adafruit_PWMServoDriver pwm){
    pwm.setPWM(AXIS_PIN, 0, servo_angleToPulse(HARD_LEFT));
    Serial.print("Axis set to ");Serial.println(HARD_LEFT);
}

void axis_turn(Adafruit_PWMServoDriver pwm, int angle){
    if (angle < HARD_LEFT){
       angle = HARD_LEFT;
       Serial.print("Invalid angle, setting to ");Serial.println(HARD_LEFT);
    }
    else if (angle > HARD_RIGHT){
      angle = HARD_RIGHT;
      Serial.print("Invalid angle, setting to ");Serial.println(HARD_RIGHT);
    }
    pwm.setPWM(AXIS_PIN, 0, servo_angleToPulse(angle));
    Serial.print("Axis set to ");Serial.println(angle);
}
