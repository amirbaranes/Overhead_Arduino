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
LedControl vhf2Active = LedControl(pin2, pin3, pin4, 1);
LedControl vhf2Stndby = LedControl(pin5, pin6, pin7, 1);
LedControl nav2Active = LedControl(pin14, pin15, pin16, 1);
LedControl nav2Stndby = LedControl(pin17, pin18, pin19, 1);

const int displayBrightness = 1;
noDelay displayDemo(500);


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // VHF2 buttons
  pinMode(pin8, INPUT_PULLUP);   // VHF2 TFR
  pinMode(pin9, INPUT_PULLUP);   // VHF2 test

  // VHF2 encoders
  pinMode(pin10, INPUT_PULLUP);  // VHF2 high CLK
  pinMode(pin11, INPUT_PULLUP);  // VHF2 high DT
  pinMode(pin12, INPUT_PULLUP);  // VHF2 low CLK
  pinMode(pin13, INPUT_PULLUP);  // VHF2 low DT

  // NAV2 buttons
  pinMode(pin20, INPUT_PULLUP);  // NAV2 TFR
  pinMode(pin21, INPUT_PULLUP);  // NAV2 test

  // NAV2 encoders
  pinMode(pin22, INPUT_PULLUP);  // NAV2 high CLK
  pinMode(pin23, INPUT_PULLUP);  // NAV2 high DT
  pinMode(pin24, INPUT_PULLUP);  // NAV2 low CLK
  pinMode(pin25, INPUT_PULLUP);  // NAV2 low DT

  // CargoFire LEDs (OUTPUT)
  pinMode(pin26, OUTPUT);   // CargoFire ext fwd
  pinMode(pin27, OUTPUT);   // CargoFire ext aft
  pinMode(pin35, OUTPUT);   // CargoFire detector fault
  pinMode(pin36, OUTPUT);   // CargoFire fwd arm yellow
  pinMode(pin37, OUTPUT);   // CargoFire fwd arm red
  pinMode(pin39, OUTPUT);   // CargoFire aft arm yellow
  pinMode(pin40, OUTPUT);   // CargoFire aft arm red
  pinMode(pin45, OUTPUT);   // CargoFire discharg1
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
  pinMode(pin48, INPUT_PULLUP);
  pinMode(pin49, INPUT_PULLUP);

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
  // VHF2 Active
  vhf2Active.shutdown(0, false);
  vhf2Active.setIntensity(0, screenIntensity);
  vhf2Active.clearDisplay(0);

  // VHF2 Standby
  vhf2Stndby.shutdown(0, false);
  vhf2Stndby.setIntensity(0, screenIntensity);
  vhf2Stndby.clearDisplay(0);

  // NAV2 Active
  nav2Active.shutdown(0, false);
  nav2Active.setIntensity(0, screenIntensity);
  nav2Active.clearDisplay(0);

  // NAV2 Standby
  nav2Stndby.shutdown(0, false);
  nav2Stndby.setIntensity(0, screenIntensity);
  nav2Stndby.clearDisplay(0);

   //showNumberOnDisplay(nav2Stndby,"300.66",5);
   //showNumberOnDisplay(nav2Active,"300.88",5);
}

void clearLeds() {
  updateLedValue(pin26, 0, lastStatePin26);  // CargoFire ext fwd
  updateLedValue(pin27, 0, lastStatePin27);  // CargoFire ext aft
  updateLedValue(pin35, 0, lastStatePin35);  // CargoFire detector fault
  updateLedValue(pin36, 0, lastStatePin36);  // CargoFire fwd arm yellow
  updateLedValue(pin37, 0, lastStatePin37);  // CargoFire fwd arm red
  updateLedValue(pin39, 0, lastStatePin39);  // CargoFire aft arm yellow
  updateLedValue(pin40, 0, lastStatePin40);  // CargoFire aft arm red
  updateLedValue(pin45, 0, lastStatePin45);  // CargoFire discharg1
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

    // VHF2 buttons
    handleMomentaryButton(pin8, lastStatePin8, buttonId8);     // VHF2 TFR
    handleMomentaryButton(pin9, lastStatePin9, buttonId9);     // VHF2 test

    // VHF2 encoders
    handleRotaryEncoder(pin10, pin11, lastStatePin10, buttonId10, buttonId11);  // VHF2 high digit
    handleRotaryEncoder(pin12, pin13, lastStatePin12, buttonId12, buttonId13);  // VHF2 low digit

    // NAV2 buttons
    handleMomentaryButton(pin20, lastStatePin20, buttonId20);  // NAV2 TFR
    handleMomentaryButton(pin21, lastStatePin21, buttonId21);  // NAV2 test

    // NAV2 encoders
    handleRotaryEncoder(pin22, pin23, lastStatePin22, buttonId22, buttonId23);  // NAV2 high digit
    handleRotaryEncoder(pin24, pin25, lastStatePin24, buttonId24, buttonId25);  // NAV2 low digit

    // CargoFire buttons
    handleMomentaryButton(pin28, lastStatePin28, buttonId28);  // CargoFire test
    handleMomentaryButton(pin38, lastStatePin38, buttonId38);  // CargoFire fwd arm
    handleMomentaryButton(pin41, lastStatePin41, buttonId41);  // CargoFire aft arm
    handleMomentaryButton(pin42, lastStatePin42, buttonId42);  // CargoFire discharge

    // CargoFire det fwd - 3 POS ROTARY
    handle3PositionRotary(pin29, pin30, pin31, CargoFireDetFwdLastState, buttonId29, buttonId30, buttonId31);

    // CargoFire det aft - 3 POS ROTARY
    handle3PositionRotary(pin32, pin33, pin34, CargoFireDetAftLastState, buttonId32, buttonId33, buttonId34);

    // WX radar mode - 3 POS ROTARY
    handle3PositionRotary(pin48, pin49, pin51, wxRadarModeLastState, buttonId48, buttonId49, buttonId51);

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
    // Generate random VHF frequencies xxx.xxx (118.000 - 136.999)
    char vhfBuf[10];
    int vhfInt = random(118, 137);
    int vhfDec = random(0, 1000);
    sprintf(vhfBuf, "%d.%03d", vhfInt, vhfDec);
    showNumberOnDisplay(vhf2Active, vhfBuf, 6);

    sprintf(vhfBuf, "%d.%03d", random(118, 137), random(0, 1000));
    showNumberOnDisplay(vhf2Stndby, vhfBuf, 6);

    // Generate random NAV frequencies xxx.xx (108.00 - 117.99)
    char navBuf[10];
    sprintf(navBuf, "%d.%02d", random(108, 118), random(0, 100));
    showNumberOnDisplay(nav2Active, navBuf, 5);

    sprintf(navBuf, "%d.%02d", random(108, 118), random(0, 100));
    showNumberOnDisplay(nav2Stndby, navBuf, 5);
  }
}

void onAnnounciatorsDemo() {
   testAnnounciatorBlink(pin26);   // CargoFire ext fwd.  / CargoFire ext aft
   testAnnounciatorBlink(pin27);   // CargoFire ext aft. / CargoFire ext fwd
   testAnnounciatorBlink(pin35);   // CargoFire detector fault / CargoFire fwd arm yellow
   testAnnounciatorBlink(pin36);   // CargoFire fwd arm yellow // CargoFire detector fault
   testAnnounciatorBlink(pin37);   // CargoFire fwd arm red / CargoFire aft arm yellow
   testAnnounciatorBlink(pin39);   // CargoFire aft arm yellow / CargoFire fwd arm red 
   testAnnounciatorBlink(pin40);   // CargoFire aft arm red / CargoFire discharg1
   testAnnounciatorBlink(pin45);   // CargoFire discharg1 / CargoFire discharg1
   testAnnounciatorBlink(pin44);   // CargoFire discharg2 / CargoFire aft arm red
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

void onNav2ActiveChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(nav2Active, reversed);
}

void onNav2StndbyChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }
  updateMax7219Display(nav2Stndby, reversed);
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
  updateLedValue(pin45, val, lastStatePin45);
}

void onCargoFireDischarg2Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin44, val, lastStatePin44);
}


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  // Displays
  messenger.attach(K_VHF2_ACTIVE, onVhf2ActiveChange);
  messenger.attach(K_VHF2_STNDBY, onVhf2StndbyChange);
  messenger.attach(K_NAV2_ACTIVE, onNav2ActiveChange);
  messenger.attach(K_NAV2_STNDBY, onNav2StndbyChange);

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
    messenger.sendCmdArg(K_VHF2_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P1/K_VHF2_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_VHF2_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_VHF2_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P1/K_VHF2_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_VHF2_STNDBY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_NAV2_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P1/K_NAV2_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_NAV2_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_NAV2_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P1/K_NAV2_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_NAV2_STNDBY"));
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
