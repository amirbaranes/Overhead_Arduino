#include <CmdMessenger.h>
#include <Encoder.h>
#include "HelperMethods.h"
#include "ComponentDefenition.h"
#include <LedControl.h>
#include <NoDelay.h>


const unsigned long BigDelayInterval = 50;   // in ms
const unsigned long SmallDelayInterval = 1;  // in ms
unsigned long lastBigDelayTime = 0;
unsigned long lastSmallDelayTime = 0;

bool demoMode = false;
int screenIntensity = 0;


// ADD DISPLAY / SERVO / COMPONENT OBJECTS HERE


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // ADD PIN MODES HERE

  // initializeScreens();
  clearLeds();

  attachCommandCallbacks();
}

// void initializeScreens() {
//   // ADD DISPLAY INITIALIZATIONS HERE
// }

void clearLeds() {
  // ADD LED CLEARS HERE
}

////////////////////////////
// Loop
////////////////////////////

void loop() {
  messenger.feedinSerialData();

  if (demoMode == true) {
    // testDisplay();
    // onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    // ADD COMPONENT HANDLERS HERE (buttons, switches, rotaries, encoders)
  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;

    // ADD FAST-POLLING HANDLERS HERE (potentiometers)
  }
}


////////////////////////////
// Demo
////////////////////////////

// void testDisplay() {
// }

// void onAnnounciatorsDemo() {
// }


////////////////////////////
// Messenger Callbacks
////////////////////////////

void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;
}

// ADD CALLBACKS HERE


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  // ADD CALLBACK ATTACHMENTS HERE
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("Pedestal_P4");
    messenger.sendCmdEnd();

  } else if (strcmp(request, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();

  } else if (strcmp(request, "CONFIG") == 0) {

    // ADD CONFIG REGISTRATIONS HERE

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}
