/*
 Name:		Counter.ino
 Created:	9/19/2017 11:25:05 PM
 Author:	cmcarthur
*/

int ledPin[] = { 6,7,8,9 };
int buttonPin = 4;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	for (int i = 0; i<4; i++)
	{
		pinMode(ledPin[i], OUTPUT);
	}
	pinMode(buttonPin, OUTPUT);
}

// the loop function runs over and over again until power down or reset
byte counter = 0;
void loop()
{
	int val = digitalRead(buttonPin);
	if (val == HIGH) {
		displayBinary(++counter);
		Serial.println(counter);
		delay(250);
	}
}

void displayBinary(byte numToShow)
{
	for (int i = 0; i<4; i++)
	{
		if (bitRead(numToShow, i) == 1)
		{
			digitalWrite(ledPin[i], HIGH);
		}
		else
		{
			digitalWrite(ledPin[i], LOW);
		}
	}

}
