/*
 Name:		Counter.ino
 Created:	9/19/2017 11:25:05 PM
 Author:	cmcarthur
*/

int ledPin[] = { 6,7,8,9 };

// the setup function runs once when you press reset or power the board
void setup() {
	for (int i = 0; i<4; i++)
	{
		pinMode(ledPin[i], OUTPUT);
	}
}

// the loop function runs over and over again until power down or reset
void loop()
{
	for (byte counter = 0; counter <= 15; counter++)
	{
		displayBinary(counter);
		delay(500);
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
