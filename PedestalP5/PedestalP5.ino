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


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // OVHT DET 1 switches
  pinMode(pin2, INPUT_PULLUP);   // OVHT DET 1 A
  pinMode(pin3, INPUT_PULLUP);   // OVHT DET 1 B

  // Eng1 overheat LED
  pinMode(pin4, OUTPUT);

  // Fault inop / Ovht fire buttons
  pinMode(pin5, INPUT_PULLUP);   // Fault inop
  pinMode(pin6, INPUT_PULLUP);   // Ovht fire

  // DISCH1 LED
  pinMode(pin7, OUTPUT);

  // DISCH1 rotary (L/R/N)
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);
  pinMode(pin10, INPUT_PULLUP);

  // DISCH1 Pull switch / back button
  pinMode(pin11, INPUT_PULLUP);  // Pull
  pinMode(pin12, INPUT_PULLUP);  // back button

  // Wheel well / Fault / APU LEDs
  pinMode(pin13, OUTPUT);   // Wheel well
  pinMode(pin14, OUTPUT);   // Fault
  pinMode(pin15, OUTPUT);   // APU DET Inop
  pinMode(pin16, OUTPUT);   // APU Bottle disch
  pinMode(pin17, OUTPUT);   // DISCH APU

  // DISCH APU rotary (L/R/N)
  pinMode(pin18, INPUT_PULLUP);
  pinMode(pin19, INPUT_PULLUP);
  pinMode(pin20, INPUT_PULLUP);

  // DISCH APU Pull switch
  pinMode(pin21, INPUT_PULLUP);

  // DISCH APU handle LED
  pinMode(pin22, OUTPUT);

  // DISCH APU back button
  pinMode(pin23, INPUT_PULLUP);

  // OVHT DET 2 switches
  pinMode(pin24, INPUT_PULLUP);  // OVHT DET 2 A
  pinMode(pin25, INPUT_PULLUP);  // OVHT DET 2 B

  // Eng2 overheat LED
  pinMode(pin26, OUTPUT);

  // DISCH2 LED
  pinMode(pin27, OUTPUT);

  // DISCH2 rotary (L/R/N)
  pinMode(pin28, INPUT_PULLUP);
  pinMode(pin29, INPUT_PULLUP);
  pinMode(pin30, INPUT_PULLUP);

  // DISCH2 Pull switch / back button
  pinMode(pin31, INPUT_PULLUP);  // Pull
  pinMode(pin32, INPUT_PULLUP);  // back button

  // Bottle disch LEDs
  pinMode(pin33, OUTPUT);   // L bottle disch
  pinMode(pin34, OUTPUT);   // R bottle disch

  // Ext test buttons
  pinMode(pin35, INPUT_PULLUP);  // Ext test 1
  pinMode(pin36, INPUT_PULLUP);  // Ext test 2

  // Ext test LEDs
  pinMode(pin37, OUTPUT);   // Ext test L
  pinMode(pin38, OUTPUT);   // Ext test R
  pinMode(pin39, OUTPUT);   // Ext test APU

  clearLeds();

  attachCommandCallbacks();
}

void clearLeds() {
  updateLedValue(pin4, 0, lastStatePin4);     // Eng1 overheat
  updateLedValue(pin7, 0, lastStatePin7);     // DISCH1
  updateLedValue(pin13, 0, lastStatePin13);   // Wheel well
  updateLedValue(pin14, 0, lastStatePin14);   // Fault
  updateLedValue(pin15, 0, lastStatePin15);   // APU DET Inop
  updateLedValue(pin16, 0, lastStatePin16);   // APU Bottle disch
  updateLedValue(pin17, 0, lastStatePin17);   // DISCH APU
  updateLedValue(pin22, 0, lastStatePin22);   // DISCH APU handle
  updateLedValue(pin26, 0, lastStatePin26);   // Eng2 overheat
  updateLedValue(pin27, 0, lastStatePin27);   // DISCH2
  updateLedValue(pin33, 0, lastStatePin33);   // L bottle disch
  updateLedValue(pin34, 0, lastStatePin34);   // R bottle disch
  updateLedValue(pin37, 0, lastStatePin37);   // Ext test L
  updateLedValue(pin38, 0, lastStatePin38);   // Ext test R
  updateLedValue(pin39, 0, lastStatePin39);   // Ext test APU
}

////////////////////////////
// Loop
////////////////////////////

void loop() {
  messenger.feedinSerialData();

  if (demoMode == true) {
    onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    // OVHT DET 1 switches
    handleOnOffSwitch(pin2, lastStatePin2, buttonId2);   // OVHT DET 1 A
    handleOnOffSwitch(pin3, lastStatePin3, buttonId3);   // OVHT DET 1 B

    // Fault inop / Ovht fire buttons
    handleMomentaryButton(pin5, lastStatePin5, buttonId5);   // Fault inop
    handleMomentaryButton(pin6, lastStatePin6, buttonId6);   // Ovht fire

    // DISCH1 rotary (L/R/N)
    handle3PositionRotary(pin8, pin9, pin10, disch1RotaryLastState, buttonId8, buttonId9, buttonId10);

    // DISCH1 Pull switch / back button
    handleOnOffSwitch(pin11, lastStatePin11, buttonId11);    // Pull
    handleMomentaryButton(pin12, lastStatePin12, buttonId12);  // back button

    // DISCH APU rotary (L/R/N)
    handle3PositionRotary(pin18, pin19, pin20, dischApuRotaryLastState, buttonId18, buttonId19, buttonId20);

    // DISCH APU Pull switch / back button
    handleOnOffSwitch(pin21, lastStatePin21, buttonId21);      // Pull
    handleMomentaryButton(pin23, lastStatePin23, buttonId23);  // back button

    // OVHT DET 2 switches
    handleOnOffSwitch(pin24, lastStatePin24, buttonId24);  // OVHT DET 2 A
    handleOnOffSwitch(pin25, lastStatePin25, buttonId25);  // OVHT DET 2 B

    // DISCH2 rotary (L/R/N)
    handle3PositionRotary(pin28, pin29, pin30, disch2RotaryLastState, buttonId28, buttonId29, buttonId30);

    // DISCH2 Pull switch / back button
    handleOnOffSwitch(pin31, lastStatePin31, buttonId31);      // Pull
    handleMomentaryButton(pin32, lastStatePin32, buttonId32);  // back button

    // Ext test buttons
    handleMomentaryButton(pin35, lastStatePin35, buttonId35);  // Ext test 1
    handleMomentaryButton(pin36, lastStatePin36, buttonId36);  // Ext test 2
  }
}


////////////////////////////
// Demo
////////////////////////////

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin4);    // Eng1 overheat
  testAnnounciatorBlink(pin7);    // DISCH1
  testAnnounciatorBlink(pin13);   // Wheel well
  testAnnounciatorBlink(pin14);   // Fault
  testAnnounciatorBlink(pin15);   // APU DET Inop
  testAnnounciatorBlink(pin16);   // APU Bottle disch
  testAnnounciatorBlink(pin17);   // DISCH APU
  testAnnounciatorBlink(pin22);   // DISCH APU handle
  testAnnounciatorBlink(pin26);   // Eng2 overheat
  testAnnounciatorBlink(pin27);   // DISCH2
  testAnnounciatorBlink(pin33);   // L bottle disch
  testAnnounciatorBlink(pin34);   // R bottle disch
  testAnnounciatorBlink(pin37);   // Ext test L
  testAnnounciatorBlink(pin38);   // Ext test R
  testAnnounciatorBlink(pin39);   // Ext test APU
}


////////////////////////////
// Messenger Callbacks
////////////////////////////

void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;
}

// LED callbacks
void onEng1OverheatChange() { int val = messenger.readInt32Arg(); updateLedValue(pin4, val, lastStatePin4); }
void onDisch1LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin7, val, lastStatePin7); }
void onWheelWellChange() { int val = messenger.readInt32Arg(); updateLedValue(pin13, val, lastStatePin13); }
void onFaultChange() { int val = messenger.readInt32Arg(); updateLedValue(pin14, val, lastStatePin14); }
void onApuDetInopChange() { int val = messenger.readInt32Arg(); updateLedValue(pin15, val, lastStatePin15); }
void onApuBottleDischChange() { int val = messenger.readInt32Arg(); updateLedValue(pin16, val, lastStatePin16); }
void onDischApuLedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin17, val, lastStatePin17); }
void onDischApuHandleLedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin22, val, lastStatePin22); }
void onEng2OverheatChange() { int val = messenger.readInt32Arg(); updateLedValue(pin26, val, lastStatePin26); }
void onDisch2LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin27, val, lastStatePin27); }
void onLBottleDischChange() { int val = messenger.readInt32Arg(); updateLedValue(pin33, val, lastStatePin33); }
void onRBottleDischChange() { int val = messenger.readInt32Arg(); updateLedValue(pin34, val, lastStatePin34); }
void onExtTestLChange() { int val = messenger.readInt32Arg(); updateLedValue(pin37, val, lastStatePin37); }
void onExtTestRChange() { int val = messenger.readInt32Arg(); updateLedValue(pin38, val, lastStatePin38); }
void onExtTestApuChange() { int val = messenger.readInt32Arg(); updateLedValue(pin39, val, lastStatePin39); }


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  // LEDs
  messenger.attach(K_ENG1_OVERHEAT, onEng1OverheatChange);
  messenger.attach(K_DISCH1_LED, onDisch1LedChange);
  messenger.attach(K_WHEEL_WELL, onWheelWellChange);
  messenger.attach(K_FAULT, onFaultChange);
  messenger.attach(K_APU_DET_INOP, onApuDetInopChange);
  messenger.attach(K_APU_BOTTLE_DISCH, onApuBottleDischChange);
  messenger.attach(K_DISCH_APU_LED, onDischApuLedChange);
  messenger.attach(K_DISCH_APU_HANDLE_LED, onDischApuHandleLedChange);
  messenger.attach(K_ENG2_OVERHEAT, onEng2OverheatChange);
  messenger.attach(K_DISCH2_LED, onDisch2LedChange);
  messenger.attach(K_L_BOTTLE_DISCH, onLBottleDischChange);
  messenger.attach(K_R_BOTTLE_DISCH, onRBottleDischChange);
  messenger.attach(K_EXT_TEST_L, onExtTestLChange);
  messenger.attach(K_EXT_TEST_R, onExtTestRChange);
  messenger.attach(K_EXT_TEST_APU, onExtTestApuChange);
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("Pedestal_P5");
    messenger.sendCmdEnd();

  } else if (strcmp(request, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();

  } else if (strcmp(request, "CONFIG") == 0) {

    // === LEDs ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_ENG1_OVERHEAT);
    messenger.sendCmdArg(F("Pedestal_P5/K_ENG1_OVERHEAT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_ENG1_OVERHEAT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_DISCH1_LED);
    messenger.sendCmdArg(F("Pedestal_P5/K_DISCH1_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_DISCH1_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_WHEEL_WELL);
    messenger.sendCmdArg(F("Pedestal_P5/K_WHEEL_WELL"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_WHEEL_WELL"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_FAULT);
    messenger.sendCmdArg(F("Pedestal_P5/K_FAULT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_FAULT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_APU_DET_INOP);
    messenger.sendCmdArg(F("Pedestal_P5/K_APU_DET_INOP"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_APU_DET_INOP"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_APU_BOTTLE_DISCH);
    messenger.sendCmdArg(F("Pedestal_P5/K_APU_BOTTLE_DISCH"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_APU_BOTTLE_DISCH"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_DISCH_APU_LED);
    messenger.sendCmdArg(F("Pedestal_P5/K_DISCH_APU_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_DISCH_APU_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_DISCH_APU_HANDLE_LED);
    messenger.sendCmdArg(F("Pedestal_P5/K_DISCH_APU_HANDLE_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_DISCH_APU_HANDLE_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_ENG2_OVERHEAT);
    messenger.sendCmdArg(F("Pedestal_P5/K_ENG2_OVERHEAT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_ENG2_OVERHEAT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_DISCH2_LED);
    messenger.sendCmdArg(F("Pedestal_P5/K_DISCH2_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_DISCH2_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_L_BOTTLE_DISCH);
    messenger.sendCmdArg(F("Pedestal_P5/K_L_BOTTLE_DISCH"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_L_BOTTLE_DISCH"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_R_BOTTLE_DISCH);
    messenger.sendCmdArg(F("Pedestal_P5/K_R_BOTTLE_DISCH"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_R_BOTTLE_DISCH"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_EXT_TEST_L);
    messenger.sendCmdArg(F("Pedestal_P5/K_EXT_TEST_L"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_EXT_TEST_L"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_EXT_TEST_R);
    messenger.sendCmdArg(F("Pedestal_P5/K_EXT_TEST_R"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_EXT_TEST_R"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_EXT_TEST_APU);
    messenger.sendCmdArg(F("Pedestal_P5/K_EXT_TEST_APU"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_EXT_TEST_APU"));
    messenger.sendCmdEnd();

    // ADD MORE CONFIG REGISTRATIONS HERE

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}
