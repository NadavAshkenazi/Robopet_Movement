String incoming = "";   // for incoming serial string data

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
    if (incoming == "demo") {
      //demo routine  
      Serial.println("you started the demo routine");
    } 
    else if (incoming=="sort") {
      //sorteer routine
      Serial.println("you started the sort routine");
    }     
    else {
      //junk
      Serial.println("something else");
      Serial.println(incoming);
      incoming = "";
    } 
    Serial.flush(); 
  }  
}
