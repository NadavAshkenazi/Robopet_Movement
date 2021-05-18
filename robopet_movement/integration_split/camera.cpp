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

void Camera::setAngleX(int angle){
  angleX = angle;
  pwm.setPWM(cameraXPin, 0, servo_angleToPulse(angleX));
  Serial.print("camera x set to ");Serial.println(angleX);
}

void Camera::getAngleX(){
  return angleX;
}

void Camera::setAngleY(int angle){
  angleY = angle;
  pwm.setPWM(cameraYPin, 0, servo_angleToPulse(angleY));
  Serial.print("camera y set to ");Serial.println(angleY);
}

void Camera::getAngleY(){
  return angleY;
}

void Camera::scan(){
      for( int x = MIN_X_ANGLE; x <= MAX_X_ANGLE; x +=CAMERA_STEP){
        delay(500);
        setAngleX(x);
        for( int y = MIN_Y_ANGLE; y <= MAX_Y_ANGLE; y +=CAMERA_STEP){
            delay(500);
            setAngleY(y);        
        }
      }
      delay(1000);
}
