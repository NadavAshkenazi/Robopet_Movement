// C++ code
//
/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/
#include <Console.h>
#include <Servo.h>
int incomingByte = 0;
int pos = 0;
char c = '0';

Servo servo_9;

void setup()
{
  servo_9.attach(9, 500, 2500);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
//   Bridge.begin();
//
//  Console.begin();

  // Wait for Console port to connect
//
//  while (!Console);

//  Console.println("Hi, what's your name?");
}

void loop()
{
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
//  for (pos = 0; pos <= 180; pos += 1) {
//    // tell servo to go to position in variable 'pos'
//    servo_9.write(pos);
//    // wait 15 ms for servo to reach the position
//    delay(15); // Wait for 15 millisecond(s)
//  }
//  for (pos = 180; pos >= 0; pos -= 1) {
//    // tell servo to go to position in variable 'pos'
//    servo_9.write(pos);
//    // wait 15 ms for servo to reach the position
//    delay(15); // Wait for 15 millisecond(s)
    if(Serial.available() > 0)  {
      int incomingData= Serial.read(); // can be -1 if read error
      switch(incomingData) { 
        case '1':
          //handle '1'
          servo_9.write(0);
          Serial.print('1');
          break;
        case '2':
          //hanle '2'
          servo_9.write(90);
          Serial.print('2');
          break;
        case '3':
          //hanle '2'
          servo_9.write(180);
          Serial.print('3');
          break;
        case '4':
          //hanle '2'
          servo_9.write(200);
          Serial.print('4');
          break;

        default:
        // handle unwanted input 
        break;
      }
   }
}
   
