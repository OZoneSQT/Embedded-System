/*
 Name:      Counter.ino
 Created:   9/19/2017 11:25:05 PM
 Author:    cmcarthur
*/

// the setup function runs once when you press reset or power the board
void setup() {
   Serial.begin(115200);

   //while (!Serial) { } // wait for connection

   int serial_max_write = Serial.availableForWrite();

   Serial.println("input a message, i'll echo");
}

// the loop function runs over and over again until power down or reset
void loop()
{
   while (Serial.available() > 0) {
      // read the incoming byte:
      int incomingByte = Serial.read();

      // say what you got:
      Serial.print("I received: ");
      Serial.write(incomingByte);
      Serial.println();
   }
}
