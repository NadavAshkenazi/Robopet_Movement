//
// Created by Nadavash on 18/05/2021.
//

/* ========= Camera functcions Functions ========== */
#include "camera.h"

//camera consts
#define MIN_X_ANGLE 20
#define MAX_X_ANGLE 180
#define MIN_Y_ANGLE 20
#define MAX_Y_ANGLE 90
#define CAMERA_STEP 10

//void camera_scan(Adafruit_PWMServoDriver pwm){
//    for( int angle = MIN_X_ANGLE; angle <= MAX_X_ANGLE; angle +=CAMERA_STEP){
//        delay(500);
//        pwm.setPWM(14, 0, servo_angleToPulse(angle) );
//        for( int angle = MIN_Y_ANGLE; angle <= MAX_Y_ANGLE; angle +=CAMERA_STEP){
//            delay(500);
//            pwm.setPWM(15, 0, servo_angleToPulse(angle) );
//        }
//    }
//    delay(1000);
//    
//}

void Camera::setAngleX(int angle){
  if (angle > MAX_X_ANGLE)
    angle = MAX_X_ANGLE;
  else if (angle < MIN_X_ANGLE)
    angle = MIN_X_ANGLE;
  angleX = angle;
  pwm.setPWM(cameraXPin, 0, servo_angleToPulse(angleX));
  Serial.print("camera x set to ");Serial.println(angleX);
}

void Camera::getAngleX(){
  return angleX;
}

void Camera::setAngleY(int angle){
  if (angle > MAX_Y_ANGLE)
    angle = MAX_Y_ANGLE;
  else if (angle < MIN_Y_ANGLE)
    angle = MIN_Y_ANGLE;
  angleY = angle;
  pwm.setPWM(cameraYPin, 0, servo_angleToPulse(angleY));
  Serial.print("camera y set to ");Serial.println(angleY);
}

void Camera::getAngleY(){
  return angleY;
}

void Camera::scan(){
//    for( int x = MIN_X_ANGLE; x <= MAX_X_ANGLE; x +=CAMERA_STEP){
//      delay(100);
//      setAngleX(x);
//      for( int y = MIN_Y_ANGLE; y <= MAX_Y_ANGLE; y +=CAMERA_STEP){
//          delay(100);
//          setAngleY(y);        
//      }
//    }
//    delay(1000);
    bool toBreak = false;
    for( int y = MIN_Y_ANGLE; y <= MAX_Y_ANGLE; y +=CAMERA_STEP){
      if (toBreak)
        break;
      delay(50);
      setAngleY(y);
      for( int x = MIN_X_ANGLE; x <= MAX_X_ANGLE; x +=CAMERA_STEP){
        if (toBreak)
          break;
          delay(75);
          setAngleX(x);
          if(Serial.available() > 0)  {
            // read the incoming:
             String incoming = Serial.readString();
             Serial.println(incoming);
             if (incoming == "cam_stop"){
                toBreak = true;
                break;
             }
          }
      }

      if (!toBreak){
        y +=CAMERA_STEP;
        setAngleY(y);
      }
      for( int x = MAX_X_ANGLE; x >= MIN_X_ANGLE; x -=CAMERA_STEP){
          if (toBreak)
            break;
          delay(75);
          setAngleX(x);
          if(Serial.available() > 0)  {
            // read the incoming:
             String incoming = Serial.readString();
             Serial.println(incoming);
             if (incoming == "cam_stop"){
                toBreak = true;
                break;
             }
          }          
      }
    }
    delay(1000);
}
