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
LedControl xpdrDisplay = LedControl(pin31, pin32, pin33, 1);

const int displayBrightness = 1;
noDelay displayDemo(500);

// VHF2 Dual Encoder
Encoder vhf2EncoderInner(pin10, pin11);
Encoder vhf2EncoderOuter(pin12, pin13);
long vhf2NewPositionInner = 0;
long vhf2OldPositionInner = -9999;
long vhf2NewPositionOuter = 0;
long vhf2OldPositionOuter = -9999;

// NAV2 Dual Encoder
Encoder nav2EncoderInner(pin22, pin23);
Encoder nav2EncoderOuter(pin24, pin25);
long nav2NewPositionInner = 0;
long nav2OldPositionInner = -9999;
long nav2NewPositionOuter = 0;
long nav2OldPositionOuter = -9999;

// XPDR Dual Encoder 1 (first + second digit)
Encoder xpdrEncoder1Inner(pin34, pin35);
Encoder xpdrEncoder1Outer(pin36, pin37);
long xpdr1NewPositionInner = 0;
long xpdr1OldPositionInner = -9999;
long xpdr1NewPositionOuter = 0;
long xpdr1OldPositionOuter = -9999;

// XPDR Dual Encoder 2 (third + fourth digit)
Encoder xpdrEncoder2Inner(pin38, pin39);
Encoder xpdrEncoder2Outer(pin40, pin41);
long xpdr2NewPositionInner = 0;
long xpdr2OldPositionInner = -9999;
long xpdr2NewPositionOuter = 0;
long xpdr2OldPositionOuter = -9999;


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // Check if the dual encoder handle it better
  //  // VHF 2 encoders
  // pinMode(pin10, INPUT_PULLUP);  // VHF 2 high CLK
  // pinMode(pin11, INPUT_PULLUP);  // VHF 2 high DT
  // pinMode(pin12, INPUT_PULLUP);  // VHF 2 low CLK
  // pinMode(pin13, INPUT_PULLUP);  // VHF 2 low DT

  // VHF 2 buttons
  pinMode(pin8, INPUT_PULLUP);   // VHF 2 TFR
  pinMode(pin9, INPUT_PULLUP);   // VHF 2 com test

  // VHF 2 dual encoder - pins handled by Encoder library

  // Check if the dual encoder handle it better
  //   // NAV 2 encoders
  // pinMode(pin22, INPUT_PULLUP);  // NAV 2 high CLK
  // pinMode(pin23, INPUT_PULLUP);  // NAV 2 high DT
  // pinMode(pin24, INPUT_PULLUP);  // NAV 2 low CLK
  // pinMode(pin25, INPUT_PULLUP);  // NAV 2 low DT

  // NAV 2 buttons
  pinMode(pin20, INPUT_PULLUP);  // NAV 2 TFR
  pinMode(pin21, INPUT_PULLUP);  // NAV 2 com test

  // NAV 2 dual encoder - pins handled by Encoder library

  // XPDR mode - 6 POS ROTARY
  pinMode(pin26, INPUT_PULLUP);
  pinMode(pin27, INPUT_PULLUP);
  pinMode(pin28, INPUT_PULLUP);
  pinMode(pin29, INPUT_PULLUP);
  pinMode(pin30, INPUT_PULLUP);
  pinMode(pin47, INPUT_PULLUP);

  // XPDR dual encoders - pins handled by Encoder library

  // XPDR switches
  pinMode(pin42, INPUT_PULLUP);  // XPDR 1
  pinMode(pin43, INPUT_PULLUP);  // XPDR 2

  // Alt Source switches
  pinMode(pin44, INPUT_PULLUP);  // Alt Source 1
  pinMode(pin45, INPUT_PULLUP);  // Alt Source 2

  // Ident button
  pinMode(pin46, INPUT_PULLUP);  // Ident

  // XPDR test LED
  pinMode(pin48, OUTPUT);

  // SELCAL buttons
  pinMode(pin49, INPUT_PULLUP);  // SELCAL 1
  pinMode(pin50, INPUT_PULLUP);  // SELCAL 2
  pinMode(pin51, INPUT_PULLUP);  // SELCAL 3
  pinMode(pin52, INPUT_PULLUP);  // SELCAL 4
  pinMode(pin53, INPUT_PULLUP);  // SELCAL 5

  // SELCAL LEDs
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);
  pinMode(pinA3, OUTPUT);
  pinMode(pinA4, OUTPUT);
  pinMode(pinA5, OUTPUT);

  initializeScreens();
  clearLeds();

  attachCommandCallbacks();
}

void initializeScreens() {
  vhf2Active.shutdown(0, false);
  vhf2Active.setIntensity(0, screenIntensity);
  vhf2Active.clearDisplay(0);

  vhf2Stndby.shutdown(0, false);
  vhf2Stndby.setIntensity(0, screenIntensity);
  vhf2Stndby.clearDisplay(0);

  nav2Active.shutdown(0, false);
  nav2Active.setIntensity(0, screenIntensity);
  nav2Active.clearDisplay(0);

  nav2Stndby.shutdown(0, false);
  nav2Stndby.setIntensity(0, screenIntensity);
  nav2Stndby.clearDisplay(0);

  xpdrDisplay.shutdown(0, false);
  xpdrDisplay.setIntensity(0, screenIntensity);
  xpdrDisplay.clearDisplay(0);
}

void clearLeds() {
  updateLedValue(pin48, 0, lastStatePin48);   // XPDR test LED
  updateLedValue(pinA1, 0, lastStatePinA1);   // SELCAL 1 led
  updateLedValue(pinA2, 0, lastStatePinA2);   // SELCAL 2 led
  updateLedValue(pinA3, 0, lastStatePinA3);   // SELCAL 3 led
  updateLedValue(pinA4, 0, lastStatePinA4);   // SELCAL 4 led
  updateLedValue(pinA5, 0, lastStatePinA5);   // SELCAL 5 led
}

////////////////////////////
// Loop
////////////////////////////

void loop() {
  messenger.feedinSerialData();

  // VHF 2 dual encoder (outside BigDelay for responsiveness)
  handleDualEncoderRotary(vhf2EncoderInner, vhf2EncoderOuter,
    vhf2NewPositionInner, vhf2OldPositionInner, vhf2NewPositionOuter, vhf2OldPositionOuter,
    buttonId10, buttonId11, buttonId12, buttonId13, false);

  // NAV 2 dual encoder
  handleDualEncoderRotary(nav2EncoderInner, nav2EncoderOuter,
    nav2NewPositionInner, nav2OldPositionInner, nav2NewPositionOuter, nav2OldPositionOuter,
    buttonId22, buttonId23, buttonId24, buttonId25, false);

  // XPDR dual encoder 1 (first + second digit)
  handleDualEncoderRotaryXpndr(xpdrEncoder1Inner, xpdrEncoder1Outer,
    xpdr1NewPositionInner, xpdr1OldPositionInner, xpdr1NewPositionOuter, xpdr1OldPositionOuter,
    buttonId34, buttonId35, buttonId36, buttonId37, false);

  // XPDR dual encoder 2 (third + fourth digit)
  handleDualEncoderRotaryXpndr(xpdrEncoder2Inner, xpdrEncoder2Outer,
    xpdr2NewPositionInner, xpdr2OldPositionInner, xpdr2NewPositionOuter, xpdr2OldPositionOuter,
    buttonId38, buttonId39, buttonId40, buttonId41, false);

  if (demoMode == true) {
    testDisplay();
    onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    // Check if the dual encoder handle it better
    // // VHF 2 encoders
    // handleRotaryEncoder(pin10, pin11, lastStatePin10, buttonId10, buttonId11);  // VHF 2 high digit
    // handleRotaryEncoder(pin12, pin13, lastStatePin12, buttonId12, buttonId13);  // VHF 2 low digit

    // VHF 2 buttons
    handleMomentaryButton(pin8, lastStatePin8, buttonId8);     // VHF 2 TFR
    handleMomentaryButton(pin9, lastStatePin9, buttonId9);     // VHF 2 com test

    // Check if the dual encoder handle it better
    // // NAV 2 encoders
    // handleRotaryEncoder(pin22, pin23, lastStatePin22, buttonId22, buttonId23);  // NAV 2 high digit
    // handleRotaryEncoder(pin24, pin25, lastStatePin24, buttonId24, buttonId25);  // NAV 2 low digit

    // NAV 2 buttons
    handleMomentaryButton(pin20, lastStatePin20, buttonId20);  // NAV 2 TFR
    handleMomentaryButton(pin21, lastStatePin21, buttonId21);  // NAV 2 com test

    // XPDR mode - 5 POS ROTARY
    handle6PositionRotary(pin26, pin27, pin28, pin29, pin30, pin47, xpdrModeLastState,
      buttonId26, buttonId27, buttonId28, buttonId29, buttonId30, buttonId47);

    // XPDR encoders
    // XPDR encoders now handled as dual encoders outside BigDelay block

    // XPDR switches
    handleOnOffSwitch(pin42, lastStatePin42, buttonId42);  // XPDR 1
    handleOnOffSwitch(pin43, lastStatePin43, buttonId43);  // XPDR 2

    // Alt Source switches
    handleOnOffSwitch(pin44, lastStatePin44, buttonId44);  // Alt Source 1
    handleOnOffSwitch(pin45, lastStatePin45, buttonId45);  // Alt Source 2

    // Ident / XPDR test buttons
    handleMomentaryButton(pin46, lastStatePin46, buttonId46);  // Ident
    // pin47 now used for XPDR mode rotary position 6

    // SELCAL buttons
    handleMomentaryButton(pin49, lastStatePin49, buttonId49);  // SELCAL 1
    handleMomentaryButton(pin50, lastStatePin50, buttonId50);  // SELCAL 2
    handleMomentaryButton(pin51, lastStatePin51, buttonId51);  // SELCAL 3
    handleMomentaryButton(pin52, lastStatePin52, buttonId52);  // SELCAL 4
    handleMomentaryButton(pin53, lastStatePin53, buttonId53);  // SELCAL 5
  }
}


////////////////////////////
// Demo
////////////////////////////

void testDisplay() {
  if (displayDemo.update()) {
    // Generate random VHF frequencies xxx.xxx (118.000 - 136.999)
    char vhfBuf[10];
    sprintf(vhfBuf, "%d.%03d", random(118, 137), random(0, 1000));
    showNumberOnDisplay(vhf2Active, vhfBuf, 6);

    sprintf(vhfBuf, "%d.%03d", random(118, 137), random(0, 1000));
    showNumberOnDisplay(vhf2Stndby, vhfBuf, 6);

    // Generate random NAV frequencies xxx.xx (108.00 - 117.99)
    char navBuf[10];
    sprintf(navBuf, "%d.%02d", random(108, 118), random(0, 100));
    showNumberOnDisplay(nav2Active, navBuf, 5);

    sprintf(navBuf, "%d.%02d", random(108, 118), random(0, 100));
    showNumberOnDisplay(nav2Stndby, navBuf, 5);

    // Generate random XPDR code (0000 - 7777, octal digits only)
    char xpdrBuf[6];
    sprintf(xpdrBuf, "%d%d%d%d", random(0, 8), random(0, 8), random(0, 8), random(0, 8));
    showNumberOnDisplay(xpdrDisplay, xpdrBuf, 4);
  }
}

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin48);   // XPDR test LED
  testAnnounciatorBlink(pinA1);   // SELCAL 1 led
  testAnnounciatorBlink(pinA2);   // SELCAL 2 led
  testAnnounciatorBlink(pinA3);   // SELCAL 3 led
  testAnnounciatorBlink(pinA4);   // SELCAL 4 led
  testAnnounciatorBlink(pinA5);   // SELCAL 5 led
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
  double val = messenger.readDoubleArg();
  char buf[10];
  dtostrf(val, 7, 3, buf);
  showNumberOnDisplay(vhf2Active, buf, 6);
}

void onVhf2StndbyChange() {
  double val = messenger.readDoubleArg();
  char buf[10];
  dtostrf(val, 7, 3, buf);
  showNumberOnDisplay(vhf2Stndby, buf, 6);
}

void onNav2ActiveChange() {
  double val = messenger.readDoubleArg();
  char buf[10];
  dtostrf(val, 6, 2, buf);
  showNumberOnDisplay(nav2Active, buf, 5);
}

void onNav2StndbyChange() {
  double val = messenger.readDoubleArg();
  char buf[10];
  dtostrf(val, 6, 2, buf);
  showNumberOnDisplay(nav2Stndby, buf, 5);
}

void onXpdrChange() {
  int val = messenger.readInt32Arg();
  char buf[5];
  sprintf(buf, "%04d", val);
  showNumberOnDisplay(xpdrDisplay, buf, 4);
}

// LED callbacks
void onXpdrTestLedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin48, val, lastStatePin48);
}

void onSelcal1LedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA1, val, lastStatePinA1);
}

void onSelcal2LedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA2, val, lastStatePinA2);
}

void onSelcal3LedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA3, val, lastStatePinA3);
}

void onSelcal4LedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA4, val, lastStatePinA4);
}

void onSelcal5LedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA5, val, lastStatePinA5);
}


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  // Displays
  messenger.attach(K_VHF2_ACTIVE, onVhf2ActiveChange);
  messenger.attach(K_VHF2_STNDBY, onVhf2StndbyChange);
  messenger.attach(K_NAV2_ACTIVE, onNav2ActiveChange);
  messenger.attach(K_NAV2_STNDBY, onNav2StndbyChange);
  messenger.attach(K_XPDR, onXpdrChange);

  // LEDs
  messenger.attach(K_XPDR_TEST_LED, onXpdrTestLedChange);
  messenger.attach(K_SELCAL_1_LED, onSelcal1LedChange);
  messenger.attach(K_SELCAL_2_LED, onSelcal2LedChange);
  messenger.attach(K_SELCAL_3_LED, onSelcal3LedChange);
  messenger.attach(K_SELCAL_4_LED, onSelcal4LedChange);
  messenger.attach(K_SELCAL_5_LED, onSelcal5LedChange);
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("Pedestal_P2");
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
    messenger.sendCmdArg(F("Pedestal_P2/K_VHF2_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_VHF2_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_VHF2_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P2/K_VHF2_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_VHF2_STNDBY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_NAV2_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P2/K_NAV2_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_NAV2_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_NAV2_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P2/K_NAV2_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_NAV2_STNDBY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_XPDR);
    messenger.sendCmdArg(F("Pedestal_P2/K_XPDR"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_XPDR"));
    messenger.sendCmdEnd();

    // === LED Annunciators ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_XPDR_TEST_LED);
    messenger.sendCmdArg(F("Pedestal_P2/K_XPDR_TEST_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_XPDR_TEST_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_SELCAL_1_LED);
    messenger.sendCmdArg(F("Pedestal_P2/K_SELCAL_1_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_SELCAL_1_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_SELCAL_2_LED);
    messenger.sendCmdArg(F("Pedestal_P2/K_SELCAL_2_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_SELCAL_2_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_SELCAL_3_LED);
    messenger.sendCmdArg(F("Pedestal_P2/K_SELCAL_3_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_SELCAL_3_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_SELCAL_4_LED);
    messenger.sendCmdArg(F("Pedestal_P2/K_SELCAL_4_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_SELCAL_4_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_SELCAL_5_LED);
    messenger.sendCmdArg(F("Pedestal_P2/K_SELCAL_5_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_SELCAL_5_LED"));
    messenger.sendCmdEnd();

    // ADD MORE CONFIG REGISTRATIONS HERE

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}
