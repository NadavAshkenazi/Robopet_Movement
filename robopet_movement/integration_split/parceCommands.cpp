//
// Created by Nadavash on 18/05/2021.
//

#include "parceCommands.h"

void splitCommand(String incoming, String* command){
//    Serial.println("in split");
    String temp = "";
    int wordIndex = 0;
    for (int i = 0; i< incoming.length(); i++){
//        Serial.println(incoming[i]);
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
//        Serial.print("command is: ");Serial.println(command[wordIndex]);
    }
    temp = "";
}

void flushCommand(String* command){
    for (int i = 0; i<4; i++){
        command[i] = "0";
    }
}
