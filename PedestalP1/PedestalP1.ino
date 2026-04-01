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


// 7-Segment Displays (MAX7219 / LedControl)
// LedControl(DataIn/DIO, CLK, CS/LOAD, number of devices)
LedControl vhf1Active = LedControl(pin2, pin3, pin4, 1);
LedControl vhf1Stndby = LedControl(pin5, pin6, pin7, 1);
LedControl vhf2Active = LedControl(pin14, pin15, pin16, 1);
LedControl vhf2Stndby = LedControl(pin17, pin18, pin19, 1);

const int displayBrightness = 1;
noDelay displayDemo(1000);
int displayDemoValue = 123;


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // VHF1 buttons
  pinMode(pin8, INPUT_PULLUP);   // VHF1 TFR
  pinMode(pin9, INPUT_PULLUP);   // VHF1 test

  // VHF1 encoders
  pinMode(pin10, INPUT_PULLUP);  // VHF1 high CLK
  pinMode(pin11, INPUT_PULLUP);  // VHF1 high DT
  pinMode(pin12, INPUT_PULLUP);  // VHF1 low CLK
  pinMode(pin13, INPUT_PULLUP);  // VHF1 low DT

  // NAV1 buttons
  pinMode(pin20, INPUT_PULLUP);  // NAV1 TFR
  pinMode(pin21, INPUT_PULLUP);  // NAV1 test

  // NAV1 encoders
  pinMode(pin22, INPUT_PULLUP);  // NAV1 high CLK
  pinMode(pin23, INPUT_PULLUP);  // NAV1 high DT
  pinMode(pin24, INPUT_PULLUP);  // NAV1 low CLK
  pinMode(pin25, INPUT_PULLUP);  // NAV1 low DT

  // CargoFire LEDs (OUTPUT)
  pinMode(pin26, OUTPUT);   // CargoFire ext fwd
  pinMode(pin27, OUTPUT);   // CargoFire ext aft
  pinMode(pin35, OUTPUT);   // CargoFire detector fault
  pinMode(pin36, OUTPUT);   // CargoFire fwd arm yellow
  pinMode(pin37, OUTPUT);   // CargoFire fwd arm red
  pinMode(pin39, OUTPUT);   // CargoFire aft arm yellow
  pinMode(pin40, OUTPUT);   // CargoFire aft arm red
  pinMode(pin43, OUTPUT);   // CargoFire discharg1
  pinMode(pin44, OUTPUT);   // CargoFire discharg2

  // CargoFire buttons
  pinMode(pin28, INPUT_PULLUP);  // CargoFire test
  pinMode(pin38, INPUT_PULLUP);  // CargoFire fwd arm
  pinMode(pin41, INPUT_PULLUP);  // CargoFire aft arm
  pinMode(pin42, INPUT_PULLUP);  // CargoFire discharge

  // CargoFire det fwd - 3 POS ROTARY
  pinMode(pin29, INPUT_PULLUP);
  pinMode(pin30, INPUT_PULLUP);

  // CargoFire det aft - 3 POS ROTARY
  pinMode(pin32, INPUT_PULLUP);
  pinMode(pin33, INPUT_PULLUP);

  // WX radar mode - 3 POS ROTARY
  pinMode(pin47, INPUT_PULLUP);
  pinMode(pin48, INPUT_PULLUP);

  // pinA0, pinA1 - analog, no pinMode needed for potentiometers

  // CargoFire extra buttons
  pinMode(pinA8, INPUT_PULLUP);   // CargoFire fwd arm button2
  pinMode(pinA9, INPUT_PULLUP);   // CargoFire aft arm button2
  pinMode(pinA10, INPUT_PULLUP);  // CargoFire discharg2

  initializeScreens();
  clearLeds();

  attachCommandCallbacks();
}

void initializeScreens() {
  // VHF1 Active
  vhf1Active.shutdown(0, false);
  vhf1Active.setIntensity(0, screenIntensity);
  vhf1Active.clearDisplay(0);

  // VHF1 Standby
  vhf1Stndby.shutdown(0, false);
  vhf1Stndby.setIntensity(0, screenIntensity);
  vhf1Stndby.clearDisplay(0);

  // NAV1 Active
  vhf2Active.shutdown(0, false);
  vhf2Active.setIntensity(0, screenIntensity);
  vhf2Active.clearDisplay(0);

  // NAV1 Standby
  vhf2Stndby.shutdown(0, false);
  vhf2Stndby.setIntensity(0, screenIntensity);
  vhf2Stndby.clearDisplay(0);
}

void clearLeds() {
  updateLedValue(pin26, 0, lastStatePin26);  // CargoFire ext fwd
  updateLedValue(pin27, 0, lastStatePin27);  // CargoFire ext aft
  updateLedValue(pin35, 0, lastStatePin35);  // CargoFire detector fault
  updateLedValue(pin36, 0, lastStatePin36);  // CargoFire fwd arm yellow
  updateLedValue(pin37, 0, lastStatePin37);  // CargoFire fwd arm red
  updateLedValue(pin39, 0, lastStatePin39);  // CargoFire aft arm yellow
  updateLedValue(pin40, 0, lastStatePin40);  // CargoFire aft arm red
  updateLedValue(pin43, 0, lastStatePin43);  // CargoFire discharg1
  updateLedValue(pin44, 0, lastStatePin44);  // CargoFire discharg2
}

////////////////////////////
// Loop
////////////////////////////

void loop() {
  messenger.feedinSerialData();

  if (demoMode == true) {
    testDisplay();
    onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    // VHF1 buttons
    handleMomentaryButton(pin8, lastStatePin8, buttonId8);     // VHF1 TFR
    handleMomentaryButton(pin9, lastStatePin9, buttonId9);     // VHF1 test

    // VHF1 encoders
    handleRotaryEncoder(pin10, pin11, lastStatePin10, buttonId10, buttonId11);  // VHF1 high digit
    handleRotaryEncoder(pin12, pin13, lastStatePin12, buttonId12, buttonId13);  // VHF1 low digit

    // NAV1 buttons
    handleMomentaryButton(pin20, lastStatePin20, buttonId20);  // NAV1 TFR
    handleMomentaryButton(pin21, lastStatePin21, buttonId21);  // NAV1 test

    // NAV1 encoders
    handleRotaryEncoder(pin22, pin23, lastStatePin22, buttonId22, buttonId23);  // NAV1 high digit
    handleRotaryEncoder(pin24, pin25, lastStatePin24, buttonId24, buttonId25);  // NAV1 low digit

    // CargoFire buttons
    handleMomentaryButton(pin28, lastStatePin28, buttonId28);  // CargoFire test
    handleMomentaryButton(pin38, lastStatePin38, buttonId38);  // CargoFire fwd arm
    handleMomentaryButton(pin41, lastStatePin41, buttonId41);  // CargoFire aft arm
    handleMomentaryButton(pin42, lastStatePin42, buttonId42);  // CargoFire discharge

    // CargoFire det fwd - 3 POS ROTARY
    handle3PositionRotary(pin29, pin30, CargoFireDetFwdLastState, buttonId29, buttonId30, buttonId31);

    // CargoFire det aft - 3 POS ROTARY
    handle3PositionRotary(pin32, pin33, CargoFireDetAftLastState, buttonId32, buttonId33, buttonId34);

    // WX radar mode - 3 POS ROTARY
    handle3PositionRotary(pin47, pin48, wxRadarModeLastState, buttonId47, buttonId48, buttonId49);

    // CargoFire extra buttons
    handleMomentaryButton(pinA8, lastStatePinA8, buttonIdA8);    // CargoFire fwd arm button2
    handleMomentaryButton(pinA9, lastStatePinA9, buttonIdA9);    // CargoFire aft arm button2
    handleMomentaryButton(pinA10, lastStatePinA10, buttonIdA10); // CargoFire discharg2
  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;

    // WX radar potentiometers
    handlePotentiometer2(pinA0, pinA0PotMin, pinA0PotMax, pinA0PotAddress, pinA0PotLastVal);  // wx radar tilt
    handlePotentiometer2(pinA1, pinA1PotMin, pinA1PotMax, pinA1PotAddress, pinA1PotLastVal);  // wx radar tilt 2
  }
}


////////////////////////////
// Demo
////////////////////////////

void testDisplay() {
  if (displayDemo.update()) {
    if (displayDemoValue == 999) {
      displayDemoValue = 123;
    }

    vhf1Active.setDigit(0, 0, 1, false);
    vhf1Active.setDigit(0, 1, 1, false);
    vhf1Active.setDigit(0, 2, 1, false);

    vhf1Stndby.setDigit(0, 0, 1, false);
    vhf1Stndby.setDigit(0, 1, 1, false);
    vhf1Stndby.setDigit(0, 2, 1, false);

    vhf2Active.setDigit(0, 0, 1, false);
    vhf2Active.setDigit(0, 1, 1, false);
    vhf2Active.setDigit(0, 2, 1, false);

    vhf2Stndby.setDigit(0, 0, 1, false);
    vhf2Stndby.setDigit(0, 1, 1, false);
    vhf2Stndby.setDigit(0, 2, 1, false);

    displayDemoValue++;
  }
}

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin26);   // CargoFire ext fwd
  testAnnounciatorBlink(pin27);   // CargoFire ext aft
  testAnnounciatorBlink(pin35);   // CargoFire detector fault
  testAnnounciatorBlink(pin36);   // CargoFire fwd arm yellow
  testAnnounciatorBlink(pin37);   // CargoFire fwd arm red
  testAnnounciatorBlink(pin39);   // CargoFire aft arm yellow
  testAnnounciatorBlink(pin40);   // CargoFire aft arm red
  testAnnounciatorBlink(pin43);   // CargoFire discharg1
  testAnnounciatorBlink(pin44);   // CargoFire discharg2
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
void onVhf1ActiveChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(vhf1Active, reversed);
}

void onVhf1StndbyChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(vhf1Stndby, reversed);
}

void onVhf2ActiveChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(vhf2Active, reversed);
}

void onVhf2StndbyChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(vhf2Stndby, reversed);
}

// LED callbacks
void onCargoFireExtFwdChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin26, val, lastStatePin26);
}

void onCargoFireExtAftChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin27, val, lastStatePin27);
}

void onCargoFireDetectorFaultChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin35, val, lastStatePin35);
}

void onCargoFireFwdArmYellowChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin36, val, lastStatePin36);
}

void onCargoFireFwdArmRedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin37, val, lastStatePin37);
}

void onCargoFireAftArmYellowChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin39, val, lastStatePin39);
}

void onCargoFireAftArmRedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin40, val, lastStatePin40);
}

void onCargoFireDischarg1Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin43, val, lastStatePin43);
}

void onCargoFireDischarg2Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin44, val, lastStatePin44);
}


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  // Displays
  messenger.attach(K_VHF1_ACTIVE, onVhf1ActiveChange);
  messenger.attach(K_VHF1_STNDBY, onVhf1StndbyChange);
  messenger.attach(K_NAV1_ACTIVE, onVhf2ActiveChange);
  messenger.attach(K_NAV1_STNDBY, onVhf2StndbyChange);

  // LEDs
  messenger.attach(K_CARGO_FIRE_EXT_FWD, onCargoFireExtFwdChange);
  messenger.attach(K_CARGO_FIRE_EXT_AFT, onCargoFireExtAftChange);
  messenger.attach(K_CARGO_FIRE_DETECTOR_FAULT, onCargoFireDetectorFaultChange);
  messenger.attach(K_CARGO_FIRE_FWD_ARM_YELLOW, onCargoFireFwdArmYellowChange);
  messenger.attach(K_CARGO_FIRE_FWD_ARM_RED, onCargoFireFwdArmRedChange);
  messenger.attach(K_CARGO_FIRE_AFT_ARM_YELLOW, onCargoFireAftArmYellowChange);
  messenger.attach(K_CARGO_FIRE_AFT_ARM_RED, onCargoFireAftArmRedChange);
  messenger.attach(K_CARGO_FIRE_DISCHARG1, onCargoFireDischarg1Change);
  messenger.attach(K_CARGO_FIRE_DISCHARG2, onCargoFireDischarg2Change);
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("Pedestal_P1");
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
    messenger.sendCmdArg(K_VHF1_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P1/K_VHF1_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_VHF1_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_VHF1_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P1/K_VHF1_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_VHF1_STNDBY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_NAV1_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P1/K_NAV1_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_NAV1_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_NAV1_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P1/K_NAV1_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_NAV1_STNDBY"));
    messenger.sendCmdEnd();

    // === LED Annunciators ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_EXT_FWD);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_EXT_FWD"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_EXT_FWD"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_EXT_AFT);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_EXT_AFT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_EXT_AFT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_DETECTOR_FAULT);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_DETECTOR_FAULT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_DETECTOR_FAULT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_FWD_ARM_YELLOW);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_FWD_ARM_YELLOW"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_FWD_ARM_YELLOW"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_FWD_ARM_RED);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_FWD_ARM_RED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_FWD_ARM_RED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_AFT_ARM_YELLOW);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_AFT_ARM_YELLOW"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_AFT_ARM_YELLOW"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_AFT_ARM_RED);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_AFT_ARM_RED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_AFT_ARM_RED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_DISCHARG1);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_DISCHARG1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_DISCHARG1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CARGO_FIRE_DISCHARG2);
    messenger.sendCmdArg(F("Pedestal_P1/K_CARGO_FIRE_DISCHARG2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CARGO_FIRE_DISCHARG2"));
    messenger.sendCmdEnd();

    // ADD MORE CONFIG REGISTRATIONS HERE

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}
