//
// Created by Nadavash on 18/05/2021.
//

#include "parceCommands.h"

void splitCommand(String incoming, String* command){
    String temp = "";
    int wordIndex = 0;
    int i = 0;
    while (incoming[i] == ' ' || incoming[i] == '\n'){
      i++;
    }
    for (; i< incoming.length(); i++){
        if(incoming[i] == ' '){
            command[wordIndex] = temp;
            Serial.print("command is: ");Serial.println(command[wordIndex]);
            temp = "";
            wordIndex+=1;
        }
        else{
            temp = temp + incoming[i];
        }
    }
    if (wordIndex < 4){
        command[wordIndex] = temp;
        Serial.print("command is: ");Serial.println(command[wordIndex]);
    }
    temp = "";
    Serial.println("full command is: ");
    Serial.println(command[0]);
    Serial.println(command[1]);
    Serial.println(command[2]);
    Serial.println(command[3]);
}

void flushCommand(String* command){
    for (int i = 0; i<4; i++){
        command[i] = "0";
    }
}
