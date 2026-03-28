#include "HelperMethods.h"

// Buttons

void handleMomentaryButton(int buttonPin, int &lastState, const char* buttonId) {
  int currentState = digitalRead(buttonPin);

  if (currentState != lastState) {
    lastState = currentState;
    if (currentState == LOW) {
      sendButtonState(buttonId, "PRESS");
    } else {
      sendButtonState(buttonId, "RELEASE");
    }
  }
}
