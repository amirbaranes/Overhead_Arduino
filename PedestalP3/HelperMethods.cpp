
#include "HelperMethods.h"


// HANDLERS IMPLEMENTATION...

////////////////////////////
// Send Functions
////////////////////////////

void sendButtonState(const char* buttonId, const char* action) {
  messenger.sendCmdStart(kCommand);
  messenger.sendCmdArg(F("EMULATE"));
  messenger.sendCmdArg(F(DEVICE_ADDRESS));
  messenger.sendCmdArg(buttonId);
  messenger.sendCmdArg(action);
  messenger.sendCmdEnd();

  Serial.println("");
}

void testAnnounciatorBlink(int pin) {
  digitalWrite(pin, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(250);               // wait for a second
  digitalWrite(pin, LOW);   // turn the LED off by making the voltage LOW
}

void updateLedValue(int pin, int value, int& lastPinValue) {
  if (value > 0) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
  lastPinValue = value;
}

void updateMax7219Display(LedControl display, long number) {
  int ones = 0;
  int tens = 0;
  int hundreds = 0;
  int thousands = 0;
  int tenThousands = 0;
  long numberDivide = number;
  long numberCopy = number;
  bool isNegative = false;
  int lastDigit = 0;

  display.clearDisplay(0);

  if (numberCopy < 0) {
    isNegative = true;
    numberCopy = numberCopy * -1;
    numberDivide = numberCopy;
  }


  ones = numberDivide % 10;
  Serial.print(ones);
   Serial.println();
  display.setDigit(0, 0, ones, false);
  lastDigit++;

  if (numberCopy > 9) {
    numberDivide = numberDivide / 10;
    tens = numberDivide % 10;
    display.setDigit(0, 1, tens, false);
    lastDigit++;
  }

  if (numberCopy > 99) {
    numberDivide = numberDivide / 10;
    hundreds = numberDivide % 10;
    display.setDigit(0, 2, hundreds, false);
    lastDigit++;
  }

  if (numberCopy > 999) {
    numberDivide = numberDivide / 10;
    thousands = numberDivide % 10;
    display.setDigit(0, 3, thousands, false);
    lastDigit++;
  }

  if (numberCopy > 9999) {
    numberDivide = numberDivide / 10;
    tenThousands = numberDivide % 10;
    display.setDigit(0, 4, tenThousands, false);
    lastDigit++;
  }

  if (isNegative == true) {
    display.setChar(0, lastDigit, '-', false);
  }
}
