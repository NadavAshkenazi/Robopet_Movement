//
// Created by Nadavash on 18/05/2021.
//

#ifndef UNTITLED_MOTOR_H
#define UNTITLED_MOTOR_H
#include "Arduino.h"

//motors consts
#define MOTOR_OFF 0
#define MOTOR_MAX_SPEED 255

class Motor {
public:
        int pin1;
        int pin2;
        int enable;
        int motor_speed;
        String name;

        Motor(int p1, int p2, int en, String name) : pin1(p1), pin2(p2),
        enable(en), motor_speed(0), name(name) {};

        void motor_setSpeed(int speed, bool debug=false);
        int motor_getSpeed();
        void motor_Forward(bool debug=false);
        void motor_Backward(bool debug=false);
};


#endif //UNTITLED_MOTOR_H
