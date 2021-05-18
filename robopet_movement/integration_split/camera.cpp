//
// Created by Nadavash on 18/05/2021.
//

/* ========= Camera functcions Functions ========== */
#include "camera.h"

void camera_scan(Adafruit_PWMServoDriver pwm){
    for( int angle = MIN_X_ANGLE; angle <= MAX_X_ANGLE; angle +=CAMERA_STEP){
        delay(500);
        pwm.setPWM(14, 0, servo_angleToPulse(angle) );
        for( int angle = MIN_Y_ANGLE; angle <= MAX_Y_ANGLE; angle +=CAMERA_STEP){
            delay(500);
            pwm.setPWM(15, 0, servo_angleToPulse(angle) );
        }
    }

    delay(1000);
}