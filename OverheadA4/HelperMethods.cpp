
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

void testAnnounciatorBlink(int pin){
    digitalWrite(pin, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(250);                      // wait for a second
  digitalWrite(pin, LOW);   // turn the LED off by making the voltage LOW 
}

void updateLedValue(int pin, int value , int& lastPinValue) {
  if (value > 0) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
  lastPinValue = value;
}




double mapCustomSections(double pos, ServoSection* sections, int num_sections) {
    for (int i = 0; i < num_sections; i++) {
        if (pos >= sections[i].in_min && pos <= sections[i].in_max) {
            double in_range = sections[i].in_max - sections[i].in_min;
            if (in_range == 0) return (sections[i].out_min + sections[i].out_max) / 2.0;

            double ratio = (pos - sections[i].in_min) / in_range;
            return sections[i].out_min + ratio * (sections[i].out_max - sections[i].out_min);
        }
    }

    // Clamp if out of range
    if (pos < sections[0].in_min) return sections[0].out_min;
    if (pos > sections[num_sections - 1].in_max) return sections[num_sections - 1].out_max;

    return -1; // Should not reach here unless section config is malformed
}

double percentageDifference(double num1, double num2) {
    if (num1 == 0) {
        return 0;
    }
    double diff = fabs(num1 - num2);
    return (diff / fabs(num1)) * 100.0;
}


