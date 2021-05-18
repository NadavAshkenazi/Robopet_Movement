#include "parceCommands.h"
String incoming = "";   // for incoming serial string data

String command[] = {"0", "0", "0"};

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming:
    incoming = Serial.readString();
    // say what you got:
    Serial.println(incoming); 
    splitCommand(incoming, command);
    if (command[0] == "demo") {
      //demo routine  
      Serial.println("you started the demo routine");
      for (int i = 0; i< 3; i++){
        Serial.println(command[i]);
      }
      char buf1[command[1].length()+1];
      command[1].toCharArray(buf1, command[1].length()+1);
      char buf2[command[2].length()+1];
      command[2].toCharArray(buf2, command[2].length()+1);
      Serial.println(atoi(buf1) + atoi(buf2));
    } 
    else if (incoming=="sort") {
      //sorteer routine
      Serial.println("you started the sort routine");
    }     
    else {
      //junk
      Serial.println("something else");
//      Serial.println(incoming);
      splitCommand(incoming, command);
      for (int i = 0; i<3; i++){
        Serial.print("command");Serial.print(i);Serial.print(" ---> ");Serial.println(command[i]);
      }
      incoming = "";
    } 
    Serial.flush(); 
  }
}
