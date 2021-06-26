//
// Created by Nadavash on 18/05/2021.
//

/* ========= Axis Functions ========== */
#include "axis.h"

void axis_turnRight(Adafruit_PWMServoDriver pwm, bool debug=false){
    pwm.setPWM(AXIS_PIN, 0, servo_angleToPulse(HARD_RIGHT));
    if (debug == true){
            Serial.print("Axis set to ");Serial.println(HARD_RIGHT);
    }
}

void axis_turnStraight(Adafruit_PWMServoDriver pwm, bool debug=false){
    pwm.setPWM(AXIS_PIN, 0, servo_angleToPulse(STRAIGHT));
    if (debug == true){
      Serial.print("Axis set to ");Serial.println(STRAIGHT);
    }
}

void axis_turnLeft(Adafruit_PWMServoDriver pwm, bool debug=false){
    pwm.setPWM(AXIS_PIN, 0, servo_angleToPulse(HARD_LEFT));
    if (debug == true){
      Serial.print("Axis set to ");Serial.println(HARD_LEFT);
    }
}

void axis_turn(Adafruit_PWMServoDriver pwm, int angle, bool debug=false){
    if (angle < HARD_LEFT){
       angle = HARD_LEFT;
       Serial.print("Invalid angle, setting to ");Serial.println(HARD_LEFT);
    }
    else if (angle > HARD_RIGHT){
      angle = HARD_RIGHT;
      Serial.print("Invalid angle, setting to ");Serial.println(HARD_RIGHT);
    }
//    pwm.setPWM(AXIS_PIN, 4096,0);
//    delay(1000);
    pwm.setPWM(AXIS_PIN, 0, servo_angleToPulse(angle));
//    delay(1000);
//    pwm.setPWM(AXIS_PIN, 0,4096);
//    delay(500);
    if (debug == true){
      Serial.print("Axis set to ");Serial.println(angle);
    }
}
