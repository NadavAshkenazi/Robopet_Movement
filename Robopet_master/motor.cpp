//
// Created by Nadavash on 18/05/2021.
//
#include "motor.h"

void Motor::motor_setSpeed(int speed, bool debug=false) {
    if (speed > MOTOR_MAX_SPEED) speed = 255;
    if (speed < MOTOR_OFF) speed = 0;
    
    motor_speed = speed;
    analogWrite(enable, motor_speed);
    if (debug == true){
          Serial.print(name);Serial.print(" motor set to ");Serial.println(motor_speed);
    }
}

int Motor::motor_getSpeed() {
    return motor_speed;
}

void Motor::motor_Forward(bool debug=false) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    Serial.print(pin1);Serial.println(" - > pin 1");
    Serial.print(pin2);Serial.println(" - > pin 2");

    if (debug == true){ 
          Serial.print(name);Serial.println(" motor forward");
    }
}

void Motor::motor_Backward(bool debug=false) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    if (debug == true){
          Serial.print(name);Serial.println(" motor backward");
    }
}
