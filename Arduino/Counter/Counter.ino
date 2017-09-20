/*
 Name:		Counter.ino
 Created:	9/19/2017 11:25:05 PM
 Author:	cmcarthur
*/

/*
 Attributions: 
 http://www.multiwingspan.co.uk/arduino.php?page=led5 -- binary counter
 http://www.multiwingspan.co.uk/arduino.php?page=led4 -- button state change
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

// globals to be used in loop
byte g_iCounter = 0;
int g_bIsPressed = 0;

// the loop function runs over and over again until power down or reset
void loop()
{
	int bButtonState = digitalRead(buttonPin);
	if (bButtonState == HIGH && !g_bIsPressed) {
		displayBinary(++g_iCounter);
		Serial.println(g_iCounter);
		delay(50);
	}
	g_bIsPressed = bButtonState;
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
