#include "HelperMethods.h"

// Encoders

void handleDualEncoderRotary(
  Encoder& encoderObjectInner, Encoder& encoderObjectOuter,
  long& newPosition1Inner, long& oldPosition1Inner, long& newPosition1Outer, long& oldPosition1Outer,
  const char* buttonId1, const char* buttonId2,
  const char* buttonId3, const char* buttonId4, bool fastTuneSupport) {
  const int detentSteps = 4;  // Adjust based on your encoder's configuration

  static unsigned long lastDetentTimeInner = 0;  // Static variable for inner encoder
  static unsigned long lastDetentTimeOuter = 0;  // Static variable for outer encoder
  static unsigned long fastTurnThreshold = 20;   // Threshold in milliseconds

  newPosition1Inner = encoderObjectInner.read();
  newPosition1Outer = encoderObjectOuter.read();

  unsigned long currentMillis = millis();

  if ((newPosition1Inner / detentSteps) > (oldPosition1Inner / detentSteps)) {
    unsigned long timeDiff = currentMillis - lastDetentTimeInner;
    lastDetentTimeInner = currentMillis;
    oldPosition1Inner = newPosition1Inner;

    if (timeDiff < fastTurnThreshold && fastTuneSupport) {
      for (int i = 0; i < 20; i++) {
        sendButtonState(buttonId1, "PRESS");
        sendButtonState(buttonId2, "RELEASE");
      }
    } else {
      sendButtonState(buttonId1, "PRESS");
      sendButtonState(buttonId2, "RELEASE");
    }
  }
  if ((newPosition1Outer / detentSteps) > (oldPosition1Outer / detentSteps)) {
    unsigned long timeDiff = currentMillis - lastDetentTimeInner;
    lastDetentTimeInner = currentMillis;
    oldPosition1Outer = newPosition1Outer;


    if (timeDiff < fastTurnThreshold  && fastTuneSupport) {
      for (int i = 0; i < 20; i++) {
        sendButtonState(buttonId3, "PRESS");
        sendButtonState(buttonId4, "RELEASE");
      }
    } else {
      sendButtonState(buttonId3, "PRESS");
      sendButtonState(buttonId4, "RELEASE");
    }
  }

  if ((newPosition1Inner / detentSteps) < (oldPosition1Inner / detentSteps)) {
    unsigned long timeDiff = currentMillis - lastDetentTimeInner;
    lastDetentTimeInner = currentMillis;
    oldPosition1Inner = newPosition1Inner;

    if (timeDiff < fastTurnThreshold  && fastTuneSupport) {
      for (int i = 0; i < 20; i++) {
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "PRESS");
      }
    } else {
      sendButtonState(buttonId1, "RELEASE");
      sendButtonState(buttonId2, "PRESS");
    }
  }
  if ((newPosition1Outer / detentSteps) < (oldPosition1Outer / detentSteps)) {
    unsigned long timeDiff = currentMillis - lastDetentTimeInner;
    lastDetentTimeInner = currentMillis;
    oldPosition1Outer = newPosition1Outer;

    if (timeDiff < fastTurnThreshold  && fastTuneSupport) {
      for (int i = 0; i < 20; i++) {
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "PRESS");
      }
    } else {
      sendButtonState(buttonId3, "RELEASE");
      sendButtonState(buttonId4, "PRESS");
    }
  }
}

void handleRotaryEncoder(
  int clkPin, int dtPin,
  int& lastStateCLK,
  const char* buttonIdCW,
  const char* buttonIdCCW) {
  int currentStateCLK = digitalRead(clkPin);
  if (currentStateCLK != lastStateCLK) {
    if (digitalRead(dtPin) != currentStateCLK) {
      sendButtonState(buttonIdCW, "PRESS");
      sendButtonState(buttonIdCCW, "RELEASE");
    } else {
      sendButtonState(buttonIdCCW, "PRESS");
      sendButtonState(buttonIdCW, "RELEASE");
    }
  }
  lastStateCLK = currentStateCLK;
}

void handleRotaryEncoder2(
int clkPin, int dtPin,
  int &lastState,
  const char* buttonIdCW,
  const char* buttonIdCCW
) {
  // Read the current state of the CLK and DT pins
  int currentStateCLK = digitalRead(clkPin);
  int currentStateDT = digitalRead(dtPin);

  // Combine CLK and DT into a single state (2-bit number)
  int currentState = (currentStateCLK << 1) | currentStateDT;

  // Check if the state has changed
  if (currentState != lastState) {
    // Detect direction based on the state transition
    if ((lastState == 0b00 && currentState == 0b01) ||
        (lastState == 0b01 && currentState == 0b11) ||
        (lastState == 0b11 && currentState == 0b10) ||
        (lastState == 0b10 && currentState == 0b00)) {
      // Clockwise rotation
      sendButtonState(buttonIdCCW, "PRESS");
      sendButtonState(buttonIdCW, "RELEASE");
    } else if ((lastState == 0b00 && currentState == 0b10) ||
               (lastState == 0b10 && currentState == 0b11) ||
               (lastState == 0b11 && currentState == 0b01) ||
               (lastState == 0b01 && currentState == 0b00)) {
      // Counterclockwise rotation

            sendButtonState(buttonIdCW, "PRESS");
      sendButtonState(buttonIdCCW, "RELEASE");
    }
    // Update the last state
    lastState = currentState;
  }
}

void handleRotaryEncoderWithButton(
  int clkPin, int dtPin,
  int &lastStateCLK,
  const char* buttonIdCW,
  const char* buttonIdCCW
) {
  int currentStateCLK = digitalRead(clkPin);
  if (currentStateCLK != lastStateCLK) {
    if (digitalRead(dtPin) != currentStateCLK) {
      sendButtonState(buttonIdCW, "PRESS");
      sendButtonState(buttonIdCCW, "RELEASE");
    } else {
      sendButtonState(buttonIdCCW, "PRESS");
      sendButtonState(buttonIdCW, "RELEASE");
    }
  }
  lastStateCLK = currentStateCLK;
}

void handleDualEncoderRotaryV2(Encoder& innerEncoder, Encoder& outerEncoder, long& oldPositionInner, long& oldPositionOuter, const char* buttonIdInnerCW, const char* buttonIdInnerCCW, const char* buttonIdOuterCW, const char* buttonIdOuterCCW) {
  long innerValue = innerEncoder.read();
  if (innerValue != oldPositionInner) {
    if (innerValue > oldPositionInner) {
      sendButtonState(buttonIdInnerCW, "PRESS");
    } else {
      sendButtonState(buttonIdInnerCCW, "PRESS");
    }
    oldPositionInner = innerValue;
  }

  long outerValue = outerEncoder.read();
  if (outerValue != oldPositionOuter) {
    if (outerValue > oldPositionOuter) {
      sendButtonState(buttonIdOuterCW, "PRESS");
    } else {
      sendButtonState(buttonIdOuterCCW, "PRESS");
    }
    oldPositionOuter = outerValue;
  }
}
