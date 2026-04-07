// // DigitLedDisplay library: https://github.com/ozhantr/DigitLedDisplay
// #include <DigitLedDisplay.h>

// // DigitLedDisplay(DIO/Data, CS/LOAD, CLK)
// // TODO: Change these pins to match your wiring
// DigitLedDisplay display = DigitLedDisplay(2, 4, 3);

// const int deviceDigits = 5;  // TODO: Change to match your display (5, 6, 8, etc.)
// unsigned long lastUpdateTime = 0;
// const unsigned long updateInterval = 500;  // 0.5 sec

// void setup() {
//   Serial.begin(115200);

//   display.setDigitLimit(deviceDigits);
//   display.setBright(0);    // 0-15
//   display.printDigit(0);   // Clear display

//   Serial.println("DigitLedDisplay Test - random frequencies");
// }

// void loop() {
//   unsigned long currentTime = millis();

//   if (currentTime - lastUpdateTime >= updateInterval) {
//     lastUpdateTime = currentTime;

//     // Generate random frequency and display as integer
//     long freq = random(118000, 137000);
//     display.printDigit(freq);

//     Serial.println(freq);
//   }
// }






#include <LedControl.h>

// LedControl(DataIn/DIO, CLK, CS/LOAD, number of devices)
// TODO: Change these pins to match your wiring
LedControl display = LedControl(2, 3, 4, 1);

const int deviceDigits = 5;  // TODO: Change to match your display (5, 6, 8, etc.)
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 500;  // 0.5 sec

// Display cache for efficient updates
int lastDigits[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
bool lastDp[8] = {false, false, false, false, false, false, false, false};

void showNumberOnDisplay(const char* value) {
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

    if (d != lastDigits[pos] || dp != lastDp[pos]) {
      display.setDigit(0, pos, d, dp);
      lastDigits[pos] = d;
      lastDp[pos] = dp;
    }
  }
}

void setup() {
  Serial.begin(115200);

  display.shutdown(0, false);
  display.setIntensity(0, 1);
  display.clearDisplay(0);

  Serial.println("LedControl Test - random frequencies");
}

void loop() {
  unsigned long currentTime = millis();
  //   display.setDigit(0, 0, 8, false);
  // display.setDigit(0, 1, 8, false);
  // display.setDigit(0, 2, 5, false);
  // display.setDigit(0, 3, 2, false);
  // display.setDigit(0, 4, 3, false);


  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    // Generate random frequency xxx.xxx
    char buf[10];
    sprintf(buf, "%d.%03d", (int)random(118, 137), (int)random(0, 1000));
    showNumberOnDisplay(buf);

    Serial.println(buf);
  }
}

