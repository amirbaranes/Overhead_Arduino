
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
}

void testAnnounciatorBlink(int pin){
    digitalWrite(pin, HIGH);  // turn the LED on (HIGH is the voltage level)
 // delay(250);                      // wait for a second
  //digitalWrite(pin, LOW);   // turn the LED off by making the voltage LOW 
}

void updateLedValue(int pin, int value , int& lastPinValue) {
  if (value > 0) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
  lastPinValue = value;
}






