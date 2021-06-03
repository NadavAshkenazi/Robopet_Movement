// C++ code
//
/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(14, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  // turn the LED off by making the voltage LOW
  digitalWrite(14, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(15, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  // turn the LED off by making the voltage LOW
  digitalWrite(15, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(16, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  // turn the LED off by making the voltage LOW
  digitalWrite(16, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
} 
