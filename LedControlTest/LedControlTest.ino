#include <LedControl.h>

// LedControl(DataIn/DIO, CLK, CS/LOAD, number of devices)
// TODO: Change these pins to match your wiring
LedControl display = LedControl(2, 3, 4, 1);

int counter = 100;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 500;  // 0.5 sec

void setup() {
  Serial.begin(115200);

  display.shutdown(0, false);
  display.setIntensity(0, 1);
  display.clearDisplay(0);

  Serial.println("LedControl Test - counting 100 to 999");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    // Display the number digit by digit
    int ones = counter % 10;
    int tens = (counter / 10) % 10;
    int hundreds = (counter / 100) % 10;

    display.setDigit(0, 0, ones, false);
    display.setDigit(0, 1, tens, false);
    display.setDigit(0, 2, hundreds, false);

    Serial.println(counter);

    counter++;
    if (counter > 999) {
      counter = 100;
    }
  }
}
