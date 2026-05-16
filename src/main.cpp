#include <Arduino.h>

int meinePins[] = {23, 22, 21, 19, 18, 5, 4, 0, 2, 15};
int anzahlPins = sizeof(meinePins) / sizeof(meinePins[0]);

const int buttonHelligKeitPin = 13;
const int buttonBreitePin = 12;

int breite = 1;
int stufe = 0;
int pwmStates[] = {20, 68, 170, 255};
void setup()
{

  for (int i = 0; i < anzahlPins; i++)
  {
    pinMode(meinePins[i], OUTPUT);
  }

  pinMode(buttonHelligKeitPin, INPUT_PULLUP);
  pinMode(buttonBreitePin, INPUT_PULLUP);
}

void loop()
{
  for (int i = 0; i < anzahlPins; i++)
  {
    for (int j = 0; j < breite; j++)
    {
      analogWrite(meinePins[(i + j) % anzahlPins], pwmStates[stufe]);
    }

    for (int w = 0; w < 50; w++)
    {
      delay(10);
      if (digitalRead(buttonHelligKeitPin) == LOW)
      {
        stufe++;
        if (stufe > 4)
        {
          stufe = 0;
        }
      }
      if (digitalRead(buttonBreitePin) == LOW)
      {
        breite++;
        if (breite > anzahlPins)
        {
          breite = 1;
        }

        for (int k = 0; k < anzahlPins; k++)
        {
          analogWrite(meinePins[k], 0);
        }

        delay(100);
        return; // bei return springt es wieder an den anfang
      }
    }
    for (int j = 0; j < breite; j++)
    {
      analogWrite(meinePins[(i + j) % anzahlPins], 0); // zb: j = 1 -> (9 + 1) % 10 = 0 (Erste LED geht an)
    }
  }
}
