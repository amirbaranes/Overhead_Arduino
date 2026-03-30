#include "HelperMethods.h"

// Potentiometers

void handlePotentiometer(
  int pin,
  int min, // 290
  int max, // 0
  const char* addresses[], // Array of addresses
  int addressCount,        // Number of addresses
  int &lastValue
) {
  int potValue = analogRead(pin);
  int mappedValue = map(potValue, 0, 692, min, max);

  const int noiseThreshold = 15;

  if (abs(mappedValue - lastValue) > noiseThreshold) {
    for (int i = 0; i < addressCount; ++i) { // Iterate over the addresses
      messenger.sendCmdStart(kSimCommand);
      messenger.sendCmdArg(addresses[i]);

    int val = mappedValue;

    if (val < 30)
    {
      val = max;
    }

    if (val > (min - 20))
    {
      val = min;
    }

      messenger.sendCmdArg(mappedValue);
      messenger.sendCmdEnd();
    }

    lastValue = mappedValue;
  }
}

void handlePotentiometer2(
  int pin,
  int min,
  int max,
  const char* address,
  int &lastValue
) {
  int potValue = analogRead(pin);
  int mappedValue = map(potValue, 0, 1023, min, max);

  const int noiseThreshold = 5;

  if (abs(mappedValue - lastValue) > noiseThreshold) {
    messenger.sendCmdStart(kSimCommand);
    messenger.sendCmdArg(address);
    messenger.sendCmdArg(mappedValue);
    messenger.sendCmdEnd();

    lastValue = mappedValue;
  }
}
