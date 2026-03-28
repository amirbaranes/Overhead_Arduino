#include "HelperMethods.h"

// Switches

void handleOnOffSwitch(int switchPin, int& lastState, const char* buttonId) {
  int currentState = digitalRead(switchPin);

  if (currentState != lastState) {
    lastState = currentState;
    if (currentState == LOW) {
      sendButtonState(buttonId, "PRESS");
    } else {
      sendButtonState(buttonId, "RELEASE");
    }
  }
}

void handleOnOffOnSwitch(int switchPin1, int switchPin2, int& lastState1, int& lastState2, const char* buttonId1, const char* buttonId2) {
  int currentState1 = digitalRead(switchPin1);
  int currentState2 = digitalRead(switchPin2);

  if (currentState1 != lastState1) {
    lastState1 = currentState1;
    if (currentState1 == LOW && currentState2 == HIGH) {
      sendButtonState(buttonId1, "PRESS");
    } else if (currentState1 == HIGH && currentState2 == HIGH) {
      sendButtonState(buttonId1, "RELEASE");
    }
  }

  if (currentState2 != lastState2) {
    lastState2 = currentState2;
    if (currentState2 == LOW && currentState1 == HIGH) {
      sendButtonState(buttonId2, "PRESS");
    } else if (currentState1 == HIGH && currentState2 == HIGH) {
      sendButtonState(buttonId2, "RELEASE");
    }
  }
}
