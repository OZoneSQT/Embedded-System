/*
 Name:      Counter.ino
 Created:   9/19/2017 11:25:05 PM
 Author:    cmcarthur
*/

// the setup function runs once when you press reset or power the board
void setup() {
   Serial.begin(115200);
}

// the loop function runs over and over again until power down or reset
void loop()
{
   delay(500);
   Serial.println("Hello World");
}
