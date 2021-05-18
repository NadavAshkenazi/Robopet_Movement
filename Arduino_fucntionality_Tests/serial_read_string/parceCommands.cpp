//
// Created by Nadavash on 18/05/2021.
//

#include "parceCommands.h"

void splitCommand(String incoming, String* command){
    String temp = "";
    int wordIndex = 0;
    for (int i = 0; i< incoming.length(); i++){
        Serial.println(incoming[i]);
        if(incoming[i] == ' '){
            command[wordIndex] = temp;
            temp = "";
            wordIndex+=1;
        }
        else{
            temp = temp + incoming[i];
        }
    }
    if (wordIndex < 3){
        command[wordIndex] = temp;
    }
    temp = "";
}

void flushCommand(String* command){
    for (int i = 0; i<3; i++){
        command[i] = "0";
    }
}