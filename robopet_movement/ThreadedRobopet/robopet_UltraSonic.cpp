//
// Created by Nadavash on 18/05/2021.
//

#include "robopet_UltraSonic.h"

/* ========= UltraSonicFuncrions ========== */
long ultrasonicDistance_read(int triggerPin, int echoPin){
    pinMode(triggerPin, OUTPUT);  // Clear the trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    // Reads the echo pin, and returns the sound wave travel time in microseconds
    long dist = pulseIn(echoPin, HIGH);
    long distInCm = 0.01723 * dist;
    return distInCm;
}
