#include <CmdMessenger.h>
#include <Encoder.h>
#include "HelperMethods.h"
#include "ComponentDefenition.h"
#include <LedControl.h>
#include <Servo.h>
#include <NoDelay.h>


const unsigned long BigDelayInterval = 50;   // in ms
const unsigned long SmallDelayInterval = 1;  // in ms
unsigned long lastBigDelayTime = 0;
unsigned long lastSmallDelayTime = 0;

bool demoMode = false;
int screenIntensity = 0;


// 7-Segment Displays (MAX7219 / LedControl)
LedControl adf2Active = LedControl(pin2, pin3, pin4, 1);
LedControl adf2Stndby = LedControl(pin5, pin6, pin7, 1);
LedControl adf1Active = LedControl(pin27, pin28, pin29, 1);
LedControl adf1Stndby = LedControl(pin30, pin31, pin32, 1);

const int displayBrightness = 1;
noDelay displayDemo(500);

// ADF1 Dual Encoder - objects declared before loop()
Encoder adf1EncoderInner(pin35, pin34);
Encoder adf1EncoderOuter(pin36, pin37);
long adf1OldPositionInner = -9999;
long adf1OldPositionOuter = -9999;

// Servo
Servo aileronServo;
int aileronServoAngle = 0;
int aileronServoMiddleAngle = 0;
int aileronServoMinimumAngle = 0;
int aileronServoMaximumAngle = 180;
noDelay aileronServoDemo(1000);
int aileronServoDemoCurrentValue = aileronServoMinimumAngle;


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // ADF 1 button
  pinMode(pin33, INPUT_PULLUP);  // ADF 1 TFR

  // ADF1 dual encoder - pins handled by Encoder library

  // ADF1 digit button
  pinMode(pin38, INPUT_PULLUP);

  // ADF / ANT / Tone switches
  pinMode(pin39, INPUT_PULLUP);  // ADF
  pinMode(pin40, INPUT_PULLUP);  // ANT
  pinMode(pin41, INPUT_PULLUP);  // Tone OFF
  pinMode(pin42, INPUT_PULLUP);  // Tone ON

  // AILERON buttons
  pinMode(pin43, INPUT_PULLUP);  // wing Left
  pinMode(pin44, INPUT_PULLUP);  // wing right
  pinMode(pin45, INPUT_PULLUP);  // wing Left 2
  pinMode(pin46, INPUT_PULLUP);  // wing right 2
  pinMode(pin47, INPUT_PULLUP);  // nose left
  pinMode(pin48, INPUT_PULLUP);  // nose right

  // AILERON servo - handled by Servo.attach()

  // Stab trim switches
  pinMode(pin50, INPUT_PULLUP);  // ovrd
  pinMode(pin51, INPUT_PULLUP);  // norm

  // Cabin door LED
  pinMode(pin52, OUTPUT);

  resetServos();
  initializeScreens();
  clearLeds();

  attachCommandCallbacks();

  initializeServos();
}

void resetServos() {
  aileronServo.attach(pin49);
  aileronServo.write(0);
}

void initializeServos() {
  delay(1000);
  aileronServo.write(aileronServoMiddleAngle);
}

void initializeScreens() {
  adf2Active.shutdown(0, false);
  adf2Active.setIntensity(0, screenIntensity);
  adf2Active.clearDisplay(0);

  adf2Stndby.shutdown(0, false);
  adf2Stndby.setIntensity(0, screenIntensity);
  adf2Stndby.clearDisplay(0);

  adf1Active.shutdown(0, false);
  adf1Active.setIntensity(0, screenIntensity);
  adf1Active.clearDisplay(0);

  adf1Stndby.shutdown(0, false);
  adf1Stndby.setIntensity(0, screenIntensity);
  adf1Stndby.clearDisplay(0);
}

void clearLeds() {
  updateLedValue(pin52, 0, lastStatePin52);  // Cabin door led
}

////////////////////////////
// Loop
////////////////////////////

void loop() {
  messenger.feedinSerialData();

    handleDualEncoderRotaryV2(adf1EncoderInner, adf1EncoderOuter,
      adf1OldPositionInner, adf1OldPositionOuter,
      buttonId34, buttonId35, buttonId36, buttonId37);  // ADF1 dual encoder

  if (demoMode == true) {
    testDisplay();
    onAileronServoDemo();
    onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    // ADF 1
    handleMomentaryButton(pin33, lastStatePin33, buttonId33);  // ADF 1 TFR

    handleMomentaryButton(pin38, lastStatePin38, buttonId38);  // ADF1 digit button

    // ADF / ANT / Tone switches
    handleOnOffSwitch(pin39, lastStatePin39, buttonId39);  // ADF
    handleOnOffSwitch(pin40, lastStatePin40, buttonId40);  // ANT
    handleOnOffSwitch(pin41, lastStatePin41, buttonId41);  // Tone OFF
    handleOnOffSwitch(pin42, lastStatePin42, buttonId42);  // Tone ON

    // AILERON buttons
    handleMomentaryButton(pin43, lastStatePin43, buttonId43);  // wing Left
    handleMomentaryButton(pin44, lastStatePin44, buttonId44);  // wing right
    handleMomentaryButton(pin45, lastStatePin45, buttonId45);  // wing Left 2
    handleMomentaryButton(pin46, lastStatePin46, buttonId46);  // wing right 2
    handleMomentaryButton(pin47, lastStatePin47, buttonId47);  // nose left
    handleMomentaryButton(pin48, lastStatePin48, buttonId48);  // nose right

    // Stab trim switches
    handleOnOffSwitch(pin50, lastStatePin50, buttonId50);  // ovrd
    handleOnOffSwitch(pin51, lastStatePin51, buttonId51);  // norm
  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;

    handlePotentiometer2(pinA0, pinA0PotMin, pinA0PotMax, pinA0PotAddress, pinA0PotLastVal);  // Flood Bright
  }
}


////////////////////////////
// Demo
////////////////////////////

void testDisplay() {
  if (displayDemo.update()) {
   // Generate random ADF frequencies (190 - 1799 kHz, no decimal)
    char adfBuf[6];
    sprintf(adfBuf, "%d", random(190, 1800));
    showNumberOnDisplay(adf2Active, adfBuf, 5);

    sprintf(adfBuf, "%d", random(190, 1800));
    showNumberOnDisplay(adf2Stndby, adfBuf, 5);

    sprintf(adfBuf, "%d", random(190, 1800));
    showNumberOnDisplay(adf1Active, adfBuf, 5);

    sprintf(adfBuf, "%d", random(190, 1800));
    showNumberOnDisplay(adf1Stndby, adfBuf, 5);

//         adf2Active.setDigit(0, 0, 1, false);
//     adf2Active.setDigit(0, 1, 1, false);
//     adf2Active.setDigit(0, 2, 1, false);

// //adf2 active
//     adf2Stndby.setDigit(0, 0, 1, false);
//     adf2Stndby.setDigit(0, 1, 1, false);
//     adf2Stndby.setDigit(0, 2, 1, false);

//     adf1Active.setDigit(0, 0, 1, false);
//     adf1Active.setDigit(0, 1, 1, false);
//     adf1Active.setDigit(0, 2, 1, false);

// //adf1Stndby
//     adf1Stndby.setDigit(0, 0, 1, false);
//     adf1Stndby.setDigit(0, 1, 1, false);
//     adf1Stndby.setDigit(0, 2, 1, false);
  }
}

void onAileronServoDemo() {
  if (aileronServoDemo.update()) {
    if (aileronServoDemoCurrentValue == aileronServoMaximumAngle) {
      aileronServoDemoCurrentValue = aileronServoMinimumAngle;
    }
    aileronServo.write(aileronServoDemoCurrentValue);
    aileronServoDemoCurrentValue++;
  }
}

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin52);  // Cabin door led
}


////////////////////////////
// Messenger Callbacks
////////////////////////////

void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;
}

// Display callbacks
void onAdf2ActiveChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(adf2Active, reversed);
}

void onAdf2StndbyChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(adf2Stndby, reversed);
}

void onAdf1ActiveChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(adf1Active, reversed);
}

void onAdf1StndbyChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(adf1Stndby, reversed);
}

// Servo callback
void onAileronServoChange() {
  double val = messenger.readDoubleArg();
  double value = val / (double)100;
  double percentagePosition = (aileronServoMaximumAngle - aileronServoMinimumAngle) * value;
  int finalValue = aileronServoMinimumAngle + percentagePosition;
  aileronServo.write(finalValue);
}

// LED callback
void onCabinDoorLedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin52, val, lastStatePin52);
}


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  // Displays
  messenger.attach(K_ADF2_ACTIVE, onAdf2ActiveChange);
  messenger.attach(K_ADF2_STNDBY, onAdf2StndbyChange);
  messenger.attach(K_ADF1_ACTIVE, onAdf1ActiveChange);
  messenger.attach(K_ADF1_STNDBY, onAdf1StndbyChange);

  // Servo
  messenger.attach(K_AILERON_SERVO, onAileronServoChange);

  // LED
  messenger.attach(K_CABIN_DOOR_LED, onCabinDoorLedChange);
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("Pedestal_P3");
    messenger.sendCmdEnd();

  } else if (strcmp(request, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();

  } else if (strcmp(request, "CONFIG") == 0) {

    // === 7-Segment Displays ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_ADF2_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P3/K_ADF2_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_ADF2_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_ADF2_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P3/K_ADF2_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_ADF2_STNDBY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_ADF1_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P3/K_ADF1_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_ADF1_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_ADF1_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P3/K_ADF1_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_ADF1_STNDBY"));
    messenger.sendCmdEnd();

    // === Servo ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AILERON_SERVO);
    messenger.sendCmdArg(F("Pedestal_P3/K_AILERON_SERVO"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AILERON_SERVO"));
    messenger.sendCmdEnd();

    // === LED ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CABIN_DOOR_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_CABIN_DOOR_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CABIN_DOOR_LED"));
    messenger.sendCmdEnd();

    // ADD MORE CONFIG REGISTRATIONS HERE

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}
