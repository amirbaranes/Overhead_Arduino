#include "HelperMethods.h"

// Potentiometers

void handlePotentiometer(
  int pin,
  int min,                  // 290
  int max,                  // 0
  const char* addresses[],  // Array of addresses
  int addressCount,         // Number of addresses
  int& lastValue) {
  int potValue = analogRead(pin);
  int mappedValue = map(potValue, 0, 692, min, max);

  const int noiseThreshold = 15;

  if (abs(mappedValue - lastValue) > noiseThreshold) {
    for (int i = 0; i < addressCount; ++i) {  // Iterate over the addresses
      messenger.sendCmdStart(kSimCommand);
      messenger.sendCmdArg(addresses[i]);

      int val = mappedValue;

      if (val < 30) {
        val = max;
      }

      if (val > (min - 20)) {
        val = min;
      }

      messenger.sendCmdArg(mappedValue);
      messenger.sendCmdEnd();
    }

    lastValue = mappedValue;
  }
}

void handlePotentiometer2(int pin, int min, int max, const char* address, int& lastValue) {
  int potValue = analogRead(pin);

  int mappedValue = map(potValue, 0, 1024, min, max);

  int noiseThreshold = 5;
  int diffValue = mappedValue - lastValue;
  if (diffValue < 0) {
    diffValue = diffValue * -1;
  }

  if (diffValue > noiseThreshold) {
    messenger.sendCmdStart(kSimCommand);
    messenger.sendCmdArg(address);
    messenger.sendCmdArg(mappedValue);
    messenger.sendCmdEnd();


    lastValue = mappedValue;
  }
}

const char* airTempSelectorPosition0 = "BUTTON_80";
const char* airTempSelectorPosition1 = "BUTTON_81";
const char* airTempSelectorPosition2 = "BUTTON_82";
const char* airTempSelectorPosition3 = "BUTTON_83";
const char* airTempSelectorPosition4 = "BUTTON_84";
const char* airTempSelectorPosition5 = "BUTTON_85";
const char* airTempSelectorPosition6 = "BUTTON_86";

int lastTempButtonId = 0;
void handlePotentiometerTempSelector(int pin, int& lastValue) {
  int potValue = analogRead(pin);

  // Serial.println(potValue);
  int noiseThreshold = 5;
  int diffValue = potValue - lastValue;
  if (diffValue < 0) {
    diffValue = diffValue * -1;
  }

  if (diffValue <= noiseThreshold) {
    return;
  }

  int mappedValue = map(potValue, 0, 1024, 7, 0);

  if (lastTempButtonId == mappedValue) {
    return;
  }

  char* buttonId;
  switch (mappedValue) {

    case 1:
      buttonId = airTempSelectorPosition0;
      break;
    case 2:
      buttonId = airTempSelectorPosition1;
      break;
    case 3:
      buttonId = airTempSelectorPosition2;
      break;
    case 4:
      buttonId = airTempSelectorPosition3;
      break;
    case 5:
      buttonId = airTempSelectorPosition4;
      break;
    case 6:
      buttonId = airTempSelectorPosition5;
      break;
    case 7:
      buttonId = airTempSelectorPosition6;
      break;
  }



  messenger.sendCmdStart(kCommand);
  messenger.sendCmdArg(F("EMULATE"));
  messenger.sendCmdArg(F(DEVICE_ADDRESS));
  messenger.sendCmdArg(buttonId);
  messenger.sendCmdArg("PRESS");
  messenger.sendCmdEnd();

  lastValue = potValue;
  lastTempButtonId = mappedValue;
}
