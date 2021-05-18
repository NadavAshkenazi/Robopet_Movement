//
// Created by Nadavash on 18/05/2021.
//
#include "motor.h"

void Motor::motor_setSpeed(int speed) {
    motor_speed = speed;
    analogWrite(enable, motor_speed);
    Serial.print(name);Serial.print(" motor set to ");Serial.println(motor_speed);
}

int Motor::motor_getSpeed() {
    return motor_speed;
}

void Motor::motor_Forward() {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    Serial.print(name);Serial.println(" motor forward");
}

void Motor::motor_Backward() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    Serial.print(name);Serial.println(" motor backward");
}
