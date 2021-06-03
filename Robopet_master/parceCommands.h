//
// Created by Nadavash on 18/05/2021.
//

#ifndef UNTITLED_PARCECOMMANDS_H
#define UNTITLED_PARCECOMMANDS_H

#include "Arduino.h"

void splitCommand(String incoming, String* command);
void flushCommand(String* command);

#endif //UNTITLED_PARCECOMMANDS_H
