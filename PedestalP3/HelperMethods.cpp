
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
  delay(1000);               // wait for a second
  digitalWrite(pin, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 
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

// Cache for last displayed values per display (up to 8 displays, 8 digits each)
struct DisplayCache {
  LedControl* disp;
  int digits[8];
  bool dp[8];
  int numDigits;
};

static DisplayCache displayCaches[8];
static int displayCacheCount = 0;

DisplayCache* getDisplayCache(LedControl &disp, int deviceDigits) {
  for (int i = 0; i < displayCacheCount; i++) {
    if (displayCaches[i].disp == &disp) return &displayCaches[i];
  }
  // New display - initialize cache
  if (displayCacheCount < 8) {
    DisplayCache* cache = &displayCaches[displayCacheCount++];
    cache->disp = &disp;
    cache->numDigits = deviceDigits;
    for (int i = 0; i < 8; i++) {
      cache->digits[i] = -1;
      cache->dp[i] = false;
    }
    return cache;
  }
  return NULL;
}

void showNumberOnDisplay(LedControl &disp, const char* value, int deviceDigits) {
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

  // Build new display state
  int padding = deviceDigits - digitCount;
  int newDigits[8];
  bool newDp[8];

  for (int pos = 0; pos < deviceDigits; pos++) {
    int idx = pos - padding;
    newDigits[pos] = (idx >= 0 && idx < digitCount) ? digits[idx] : 0;
    newDp[pos] = (decimalAfterDigit >= 0 && idx == decimalAfterDigit);
  }

  // Get cache and only update changed digits
  DisplayCache* cache = getDisplayCache(disp, deviceDigits);

  for (int pos = 0; pos < deviceDigits; pos++) {
    if (cache == NULL || newDigits[pos] != cache->digits[pos] || newDp[pos] != cache->dp[pos]) {
      disp.setDigit(0, pos, newDigits[pos], newDp[pos]);
      if (cache) {
        cache->digits[pos] = newDigits[pos];
        cache->dp[pos] = newDp[pos];
      }
    }
  }
}
