
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

void updateMax7219Display(LedControl display, long number, int decimalPlaces) {
  display.clearDisplay(0);

  bool isNegative = false;
  long v = number;

  if (v < 0) {
    isNegative = true;
    v = -v;
  }

  // Count how many digits the number has
  int numDigits = 0;
  long temp = v;
  do {
    numDigits++;
    temp /= 10;
  } while (temp > 0);

  // Write digits left to right, with decimal point
  for (int i = 0; i < numDigits; i++) {
    bool dp = (decimalPlaces > 0 && i == decimalPlaces);
    display.setDigit(0, (numDigits - 1) - i, v % 10, dp);
    v /= 10;
  }

  if (isNegative) {
    display.setChar(0, numDigits, '-', false);
  }
}

void showNumberOnDisplay(LedControl &disp, const char* value, int deviceDigits) {
  disp.clearDisplay(0);

  // Extract digits and find decimal point position
  int digits[16];
  int digitCount = 0;
  int decimalAfterDigit = -1;

  for (int i = 0; value[i]; i++) {
    if (value[i] == '.') {
      decimalAfterDigit = digitCount - 1;
    } else if (value[i] >= '0' && value[i] <= '9') {
      digits[digitCount++] = value[i] - '0';
    }
  }

  // Write to display with leading zeros (position 0 = leftmost)
  int padding = deviceDigits - digitCount;

  for (int pos = 0; pos < deviceDigits; pos++) {
    int idx = pos - padding;
    int d = (idx >= 0 && idx < digitCount) ? digits[idx] : 0;
    bool dp = (decimalAfterDigit >= 0 && idx == decimalAfterDigit);
    disp.setDigit(0, pos, d, dp);
  }
}
