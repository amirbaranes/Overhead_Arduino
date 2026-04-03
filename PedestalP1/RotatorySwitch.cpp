#include "HelperMethods.h"

// Rotaries

void handle2PositionRotary(int pin1, int& lastState, const char* buttonId1, const char* buttonId2) {
  int state1 = digitalRead(pin1);
  int currentState;
  if (state1 == LOW) {
    currentState = 0;  // Position 1
  } else if (state1 == HIGH) {
    currentState = 1;  // Position 2
  } else {
    return;
  }
  if (currentState != lastState) {
    lastState = currentState;
    switch (currentState) {
      case 0:
        sendButtonState(buttonId1, "PRESS");
        sendButtonState(buttonId2, "RELEASE");
        break;
      case 1:
        sendButtonState(buttonId2, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        break;
    }
  }
}

void handle3PositionRotary(int pin1, int pin2, int pin3, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3) {
  int state1 = digitalRead(pin1);
  int state2 = digitalRead(pin2);
  int state3 = digitalRead(pin3);

  int currentState = -1;
  if (state1 == LOW && state2 == HIGH && state3 == HIGH) {
    currentState = 0;  // Position 1
  } else if (state1 == HIGH && state2 == LOW && state3 == HIGH) {
    currentState = 1;  // Position 2
  } else if (state1 == HIGH && state2 == HIGH && state3 == LOW) {
    currentState = 2;  // Position 3
  }

  if (currentState == -1) {
    return;
  }

  if (currentState != lastState) {
    lastState = currentState;
    switch (currentState) {
      case 0:
        sendButtonState(buttonId1, "PRESS");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        break;
      case 1:
        sendButtonState(buttonId2, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        break;
      case 2:
        sendButtonState(buttonId3, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        break;
    }
  }
}

void handle4PositionRotary(int pin1, int pin2, int pin3, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, int& candidateState, unsigned long& stateStartTime) {

  const unsigned long debounceTime = 200;  // Stability time threshold (100ms)

  // Read the current state of each pin
  int state1 = digitalRead(pin1);
  int state2 = digitalRead(pin2);
  int state3 = digitalRead(pin3);

  // Determine the current position based on pin readings
  int currentState = -1;
  if (state1 == LOW && state2 == HIGH && state3 == HIGH) {
    currentState = 0;
  } else if (state1 == HIGH && state2 == LOW && state3 == HIGH) {
    currentState = 1;
  } else if (state1 == HIGH && state2 == HIGH && state3 == LOW) {
    currentState = 2;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH) {
    currentState = 3;
  }

  // If the state is invalid, ignore it
  if (currentState == -1) {
    return;
  }

  // If the state changes, start timing the new candidate state
  if (currentState != candidateState) {
    candidateState = currentState;
    stateStartTime = millis();
  }

  // If the candidate state remains stable for the debounce time, confirm it as the new state
  if ((millis() - stateStartTime) >= debounceTime && currentState != lastState) {
    lastState = currentState;  // Update the last state
    // Process the confirmed state change
    switch (lastState) {
      case 0:
        sendButtonState(buttonId1, "PRESS");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        break;
      case 1:
        sendButtonState(buttonId2, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        break;
      case 2:
        sendButtonState(buttonId3, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        break;
      case 3:
        sendButtonState(buttonId4, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        break;
    }
  }
}

void handle5PositionRotary(int pin1, int pin2, int pin3, int pin4, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5) {
  // Read the current state of each pin
  int state1 = digitalRead(pin1);
  int state2 = digitalRead(pin2);
  int state3 = digitalRead(pin3);
  int state4 = digitalRead(pin4);

  // Determine the current position based on the states of pin1, pin2, pin3, and pin4
  int currentState;
  if (state1 == LOW && state2 == HIGH && state3 == HIGH && state4 == HIGH) {
    currentState = 0;  // Position 1
  } else if (state1 == HIGH && state2 == LOW && state3 == HIGH && state4 == HIGH) {
    currentState = 1;  // Position 2
  } else if (state1 == HIGH && state2 == HIGH && state3 == LOW && state4 == HIGH) {
    currentState = 2;  // Position 3
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == LOW) {
    currentState = 3;  // Position 4
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH) {
    currentState = 4;  // Position 5
  } else {
    Serial.println("Invalid state detected. Exiting function.");
    // Exit if the switch is in an unexpected state
    return;
  }

  // Check if the position has changed
  if (currentState != lastState) {

    lastState = currentState;

    // Send a signal based on the new position
    switch (currentState) {
      case 0:
        sendButtonState(buttonId1, "PRESS");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        break;
      case 1:
        sendButtonState(buttonId2, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        break;
      case 2:
        sendButtonState(buttonId3, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        break;
      case 3:
        sendButtonState(buttonId4, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        break;
      case 4:
        sendButtonState(buttonId5, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        break;
    }
  }
}

void handle6PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6) {
  static int candidateState = -1;           // State being considered
  static unsigned long stateStartTime = 0;  // Time when the candidate state started
  const unsigned long debounceTime = 200;   // Stability time threshold (100ms)

  // Read the current state of each pin
  int state1 = digitalRead(pin1);
  int state2 = digitalRead(pin2);
  int state3 = digitalRead(pin3);
  int state4 = digitalRead(pin4);
  int state5 = digitalRead(pin5);

  // Determine the current position based on pin readings
  int currentState = -1;
  if (state1 == LOW && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH) {
    currentState = 0;
  } else if (state1 == HIGH && state2 == LOW && state3 == HIGH && state4 == HIGH && state5 == HIGH) {
    currentState = 1;
  } else if (state1 == HIGH && state2 == HIGH && state3 == LOW && state4 == HIGH && state5 == HIGH) {
    currentState = 2;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == LOW && state5 == HIGH) {
    currentState = 3;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == LOW) {
    currentState = 4;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH) {
    currentState = 5;
  }

  // If the state is invalid, ignore it
  if (currentState == -1) {
    return;
  }

  // If the state changes, start timing the new candidate state
  if (currentState != candidateState) {
    candidateState = currentState;
    stateStartTime = millis();
  }

  // If the candidate state remains stable for the debounce time, confirm it as the new state
  if ((millis() - stateStartTime) >= debounceTime && currentState != lastState) {
    lastState = currentState;  // Update the last state

    // Process the confirmed state change
    switch (lastState) {
      case 0:
        sendButtonState(buttonId1, "PRESS");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        break;
      case 1:
        sendButtonState(buttonId2, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        break;
      case 2:
        sendButtonState(buttonId3, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        break;
      case 3:
        sendButtonState(buttonId4, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        break;
      case 4:
        sendButtonState(buttonId5, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        break;
      case 5:
        sendButtonState(buttonId6, "PRESS");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        break;
    }
  }
}

void handle7PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7) {
  static int candidateState = -1;           // State being considered
  static unsigned long stateStartTime = 0;  // Time when the candidate state started
  const unsigned long debounceTime = 200;   // Stability time threshold (100ms)

  // Read the current state of each pin
  int state1 = digitalRead(pin1);
  int state2 = digitalRead(pin2);
  int state3 = digitalRead(pin3);
  int state4 = digitalRead(pin4);
  int state5 = digitalRead(pin5);
  int state6 = digitalRead(pin6);

  // Determine the current position based on pin readings
  int currentState = -1;
  if (state1 == LOW && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == HIGH) {
    currentState = 0;
  } else if (state1 == HIGH && state2 == LOW && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == HIGH) {
    currentState = 1;
  } else if (state1 == HIGH && state2 == HIGH && state3 == LOW && state4 == HIGH && state5 == HIGH && state6 == HIGH) {
    currentState = 2;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == LOW && state5 == HIGH && state6 == HIGH) {
    currentState = 3;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == LOW && state6 == HIGH) {
    currentState = 4;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == LOW) {
    currentState = 5;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == HIGH) {
    currentState = 6;
  }

  // If the state is invalid, ignore it
  if (currentState == -1) {
    return;
  }

  // If the state changes, start timing the new candidate state
  if (currentState != candidateState) {
    candidateState = currentState;
    stateStartTime = millis();
  }

  // If the candidate state remains stable for the debounce time, confirm it as the new state
  if ((millis() - stateStartTime) >= debounceTime && currentState != lastState) {
    lastState = currentState;  // Update the last state

    // Process the confirmed state change
    switch (lastState) {
      case 0:
        sendButtonState(buttonId1, "PRESS");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        sendButtonState(buttonId7, "RELEASE");
        break;
      case 1:
        sendButtonState(buttonId2, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        sendButtonState(buttonId7, "RELEASE");
        break;
      case 2:
        sendButtonState(buttonId3, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        sendButtonState(buttonId7, "RELEASE");
        break;
      case 3:
        sendButtonState(buttonId4, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        sendButtonState(buttonId7, "RELEASE");
        break;
      case 4:
        sendButtonState(buttonId5, "PRESS");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId6, "RELEASE");
        sendButtonState(buttonId7, "RELEASE");
        break;
      case 5:
        sendButtonState(buttonId6, "PRESS");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        sendButtonState(buttonId7, "RELEASE");
        break;
      case 6:
        sendButtonState(buttonId7, "PRESS");
        sendButtonState(buttonId6, "RELEASE");
        sendButtonState(buttonId5, "RELEASE");
        sendButtonState(buttonId1, "RELEASE");
        sendButtonState(buttonId2, "RELEASE");
        sendButtonState(buttonId3, "RELEASE");
        sendButtonState(buttonId4, "RELEASE");
        break;
    }
  }
}

void handle8PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7, const char* buttonId8) {
  static int candidateState = -1;           // State being considered
  static unsigned long stateStartTime = 0;  // Time when the candidate state started
  const unsigned long debounceTime = 200;   // Stability time threshold (100ms)

  // Read the current state of each pin
  int state1 = digitalRead(pin1);
  int state2 = digitalRead(pin2);
  int state3 = digitalRead(pin3);
  int state4 = digitalRead(pin4);
  int state5 = digitalRead(pin5);
  int state6 = digitalRead(pin6);
  int state7 = digitalRead(pin7);

  // Determine the current position based on pin readings
  int currentState = -1;
  if (state1 == LOW && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == HIGH && state7 == HIGH) {
    currentState = 0;
  } else if (state1 == HIGH && state2 == LOW && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == HIGH && state7 == HIGH) {
    currentState = 1;
  } else if (state1 == HIGH && state2 == HIGH && state3 == LOW && state4 == HIGH && state5 == HIGH && state6 == HIGH && state7 == HIGH) {
    currentState = 2;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == LOW && state5 == HIGH && state6 == HIGH && state7 == HIGH) {
    currentState = 3;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == LOW && state6 == HIGH && state7 == HIGH) {
    currentState = 4;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == LOW && state7 == HIGH) {
    currentState = 5;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == HIGH && state7 == LOW) {
    currentState = 6;
  } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH && state4 == HIGH && state5 == HIGH && state6 == HIGH && state7 == HIGH) {
    currentState = 7;
  }

  // If the state is invalid, ignore it
  if (currentState == -1) {
    return;
  }

  // If the state changes, start timing the new candidate state
  if (currentState != candidateState) {
    candidateState = currentState;
    stateStartTime = millis();
  }

  // If the candidate state remains stable for the debounce time, confirm it as the new state
  if ((millis() - stateStartTime) >= debounceTime && currentState != lastState) {
    lastState = currentState;  // Update the last state

    // Process the confirmed state change
    switch (lastState) {
      case 0:
        sendButtonState(buttonId1, "PRESS");
      delay(200);
         sendButtonState(buttonId1, "PRESS");
        break;
      case 1:
        sendButtonState(buttonId2, "PRESS");
      delay(200);
         sendButtonState(buttonId2, "PRESS");
        break;
      case 2:
        sendButtonState(buttonId3, "PRESS");
      delay(200);
         sendButtonState(buttonId3, "PRESS");
        break;
      case 3:
        sendButtonState(buttonId4, "PRESS");
      delay(200);
         sendButtonState(buttonId4, "PRESS");
        break;
      case 4:
        sendButtonState(buttonId5, "PRESS");
      delay(200);
         sendButtonState(buttonId5, "PRESS");
        break;
      case 5:
        sendButtonState(buttonId6, "PRESS");
       delay(200);
         sendButtonState(buttonId6, "PRESS");
        break;
      case 6:
        sendButtonState(buttonId7, "PRESS");
      delay(200);
         sendButtonState(buttonId7, "PRESS");
        break;
      case 7:
        sendButtonState(buttonId8, "PRESS");
      delay(200);
         sendButtonState(buttonId8, "PRESS");
        break;
    }
  }
}
