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

  // MicSelector left LEDs (OUTPUT)
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);

  // MicSelector left buttons
  pinMode(pin10, INPUT_PULLUP);
  pinMode(pin11, INPUT_PULLUP);
  pinMode(pin12, INPUT_PULLUP);
  pinMode(pin13, INPUT_PULLUP);
  pinMode(pin14, INPUT_PULLUP);
  pinMode(pin15, INPUT_PULLUP);
  pinMode(pin16, INPUT_PULLUP);
  pinMode(pin17, INPUT_PULLUP);

  // R/T button
  pinMode(pin18, INPUT_PULLUP);

  // I/C, MASK, BOOK switches
  pinMode(pin19, INPUT_PULLUP);
  pinMode(pin20, INPUT_PULLUP);
  pinMode(pin21, INPUT_PULLUP);

  // V/B/R  - 3 POS ROTARY
  pinMode(pin22, INPUT_PULLUP);
  pinMode(pin23, INPUT_PULLUP);
  pinMode(pin24, INPUT_PULLUP);

  // ALT, NORM switches
  pinMode(pin25, INPUT_PULLUP);
  pinMode(pin26, INPUT_PULLUP);

  // Audio panel LEDs (OUTPUT)
  pinMode(pin27, OUTPUT);   // VHF1
  pinMode(pin28, OUTPUT);   // VHF2
  pinMode(pin29, OUTPUT);   // VHF3
  pinMode(pin30, OUTPUT);   // HF1
  pinMode(pin31, OUTPUT);   // HF2
  pinMode(pin32, OUTPUT);   // FLT
  pinMode(pin33, OUTPUT);   // SVO
  pinMode(pin34, OUTPUT);   // PA
  pinMode(pin35, OUTPUT);   // NAV1
  pinMode(pin36, OUTPUT);   // NAV2
  pinMode(pin37, OUTPUT);   // ADF1
  pinMode(pin38, OUTPUT);   // ADF2
  pinMode(pin39, OUTPUT);   // MKR
  pinMode(pin40, OUTPUT);   // SPKR

  // Audio panel switches
  pinMode(pin41, INPUT_PULLUP);   // VHF1
  pinMode(pin42, INPUT_PULLUP);   // VHF2
  pinMode(pin43, INPUT_PULLUP);   // VHF3
  pinMode(pin44, INPUT_PULLUP);   // HF1
  pinMode(pin45, INPUT_PULLUP);   // HF2
  pinMode(pin46, INPUT_PULLUP);   // FLT
  pinMode(pin47, INPUT_PULLUP);   // SVO
  pinMode(pin48, INPUT_PULLUP);   // PA
  pinMode(pin49, INPUT_PULLUP);   // NAV1
  pinMode(pin50, INPUT_PULLUP);   // NAV2
  pinMode(pin51, INPUT_PULLUP);   // ADF1
  pinMode(pin52, INPUT_PULLUP);   // ADF2
  pinMode(pin53, INPUT_PULLUP);   // MKR
  pinMode(pinA15, INPUT_PULLUP);  // SPKR

  clearLeds();

  attachCommandCallbacks();
}

void clearLeds() {
  // MicSelector left LEDs
  updateLedValue(pin2, 0, lastStatePin2);
  updateLedValue(pin3, 0, lastStatePin3);
  updateLedValue(pin4, 0, lastStatePin4);
  updateLedValue(pin5, 0, lastStatePin5);
  updateLedValue(pin6, 0, lastStatePin6);
  updateLedValue(pin7, 0, lastStatePin7);
  updateLedValue(pin8, 0, lastStatePin8);
  updateLedValue(pin9, 0, lastStatePin9);

  // Audio panel LEDs
  updateLedValue(pin27, 0, lastStatePin27);
  updateLedValue(pin28, 0, lastStatePin28);
  updateLedValue(pin29, 0, lastStatePin29);
  updateLedValue(pin30, 0, lastStatePin30);
  updateLedValue(pin31, 0, lastStatePin31);
  updateLedValue(pin32, 0, lastStatePin32);
  updateLedValue(pin33, 0, lastStatePin33);
  updateLedValue(pin34, 0, lastStatePin34);
  updateLedValue(pin35, 0, lastStatePin35);
  updateLedValue(pin36, 0, lastStatePin36);
  updateLedValue(pin37, 0, lastStatePin37);
  updateLedValue(pin38, 0, lastStatePin38);
  updateLedValue(pin39, 0, lastStatePin39);
  updateLedValue(pin40, 0, lastStatePin40);
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

    // MicSelector left buttons
    handleMomentaryButton(pin10, lastStatePin10, buttonId10);  // MicSelector left 1
    handleMomentaryButton(pin11, lastStatePin11, buttonId11);  // MicSelector left 2
    handleMomentaryButton(pin12, lastStatePin12, buttonId12);  // MicSelector left 3
    handleMomentaryButton(pin13, lastStatePin13, buttonId13);  // MicSelector left 4
    handleMomentaryButton(pin14, lastStatePin14, buttonId14);  // MicSelector left 5
    handleMomentaryButton(pin15, lastStatePin15, buttonId15);  // MicSelector left 6
    handleMomentaryButton(pin16, lastStatePin16, buttonId16);  // MicSelector left 7
    handleMomentaryButton(pin17, lastStatePin17, buttonId17);  // MicSelector left 8

    // R/T button
    handleMomentaryButton(pin18, lastStatePin18, buttonId18);

    // I/C, MASK, BOOK switches
    handleOnOffSwitch(pin19, lastStatePin19, buttonId19);  // I/C
    handleOnOffSwitch(pin20, lastStatePin20, buttonId20);  // MASK
    handleOnOffSwitch(pin21, lastStatePin21, buttonId21);  // BOOK

    // V/B/R  - 3 POS ROTARY
    handle3PositionRotary(pin22, pin23, pin24, vbrLastState, buttonId22, buttonId23, buttonId24);

    // ALT, NORM switches
    handleOnOffSwitch(pin25, lastStatePin25, buttonId25);  // ALT
    handleOnOffSwitch(pin26, lastStatePin26, buttonId26);  // NORM

    // Audio panel switches
    handleOnOffSwitch(pin41, lastStatePin41, buttonId41);  // VHF1
    handleOnOffSwitch(pin42, lastStatePin42, buttonId42);  // VHF2
    handleOnOffSwitch(pin43, lastStatePin43, buttonId43);  // VHF3
    handleOnOffSwitch(pin44, lastStatePin44, buttonId44);  // HF1
    handleOnOffSwitch(pin45, lastStatePin45, buttonId45);  // HF2
    handleOnOffSwitch(pin46, lastStatePin46, buttonId46);  // FLT
    handleOnOffSwitch(pin47, lastStatePin47, buttonId47);  // SVO
    handleOnOffSwitch(pin48, lastStatePin48, buttonId48);  // PA
    handleOnOffSwitch(pin49, lastStatePin49, buttonId49);  // NAV1
    handleOnOffSwitch(pin50, lastStatePin50, buttonId50);  // NAV2
    handleOnOffSwitch(pin51, lastStatePin51, buttonId51);  // ADF1
    handleOnOffSwitch(pin52, lastStatePin52, buttonId52);  // ADF2
    handleOnOffSwitch(pin53, lastStatePin53, buttonId53);  // MKR
    handleOnOffSwitch(pinA15, lastStatePinA15, buttonIdA15);  // SPKR
  }
}


////////////////////////////
// Demo
////////////////////////////

void onAnnounciatorsDemo() {
  // MicSelector left LEDs
  testAnnounciatorBlink(pin2);
  testAnnounciatorBlink(pin3);
  testAnnounciatorBlink(pin4);
  testAnnounciatorBlink(pin5);
  testAnnounciatorBlink(pin6);
  testAnnounciatorBlink(pin7);
  testAnnounciatorBlink(pin8);
  testAnnounciatorBlink(pin9);

  // Audio panel LEDs
  testAnnounciatorBlink(pin27);
  testAnnounciatorBlink(pin28);
  testAnnounciatorBlink(pin29);
  testAnnounciatorBlink(pin30);
  testAnnounciatorBlink(pin31);
  testAnnounciatorBlink(pin32);
  testAnnounciatorBlink(pin33);
  testAnnounciatorBlink(pin34);
  testAnnounciatorBlink(pin35);
  testAnnounciatorBlink(pin36);
  testAnnounciatorBlink(pin37);
  testAnnounciatorBlink(pin38);
  testAnnounciatorBlink(pin39);
  testAnnounciatorBlink(pin40);
}


////////////////////////////
// Messenger Callbacks
////////////////////////////

void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;
}

// MicSelector left LED callbacks
void onMicSelLeft1LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin2, val, lastStatePin2); }
void onMicSelLeft2LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin3, val, lastStatePin3); }
void onMicSelLeft3LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin4, val, lastStatePin4); }
void onMicSelLeft4LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin5, val, lastStatePin5); }
void onMicSelLeft5LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin6, val, lastStatePin6); }
void onMicSelLeft6LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin7, val, lastStatePin7); }
void onMicSelLeft7LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin8, val, lastStatePin8); }
void onMicSelLeft8LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin9, val, lastStatePin9); }

// Audio panel LED callbacks
void onAnVhf1Change() { int val = messenger.readInt32Arg(); updateLedValue(pin27, val, lastStatePin27); }
void onAnVhf2Change() { int val = messenger.readInt32Arg(); updateLedValue(pin28, val, lastStatePin28); }
void onAnVhf3Change() { int val = messenger.readInt32Arg(); updateLedValue(pin29, val, lastStatePin29); }
void onAnHf1Change() { int val = messenger.readInt32Arg(); updateLedValue(pin30, val, lastStatePin30); }
void onAnHf2Change() { int val = messenger.readInt32Arg(); updateLedValue(pin31, val, lastStatePin31); }
void onAnFltChange() { int val = messenger.readInt32Arg(); updateLedValue(pin32, val, lastStatePin32); }
void onAnSvoChange() { int val = messenger.readInt32Arg(); updateLedValue(pin33, val, lastStatePin33); }
void onAnPaChange() { int val = messenger.readInt32Arg(); updateLedValue(pin34, val, lastStatePin34); }
void onAnNav1Change() { int val = messenger.readInt32Arg(); updateLedValue(pin35, val, lastStatePin35); }
void onAnNav2Change() { int val = messenger.readInt32Arg(); updateLedValue(pin36, val, lastStatePin36); }
void onAnAdf1Change() { int val = messenger.readInt32Arg(); updateLedValue(pin37, val, lastStatePin37); }
void onAnAdf2Change() { int val = messenger.readInt32Arg(); updateLedValue(pin38, val, lastStatePin38); }
void onAnMkrChange() { int val = messenger.readInt32Arg(); updateLedValue(pin39, val, lastStatePin39); }
void onAnSpkrChange() { int val = messenger.readInt32Arg(); updateLedValue(pin40, val, lastStatePin40); }


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  // MicSelector left LEDs
  messenger.attach(K_MIC_SEL_LEFT_1_LED, onMicSelLeft1LedChange);
  messenger.attach(K_MIC_SEL_LEFT_2_LED, onMicSelLeft2LedChange);
  messenger.attach(K_MIC_SEL_LEFT_3_LED, onMicSelLeft3LedChange);
  messenger.attach(K_MIC_SEL_LEFT_4_LED, onMicSelLeft4LedChange);
  messenger.attach(K_MIC_SEL_LEFT_5_LED, onMicSelLeft5LedChange);
  messenger.attach(K_MIC_SEL_LEFT_6_LED, onMicSelLeft6LedChange);
  messenger.attach(K_MIC_SEL_LEFT_7_LED, onMicSelLeft7LedChange);
  messenger.attach(K_MIC_SEL_LEFT_8_LED, onMicSelLeft8LedChange);

  // Audio panel LEDs
  messenger.attach(K_AN_VHF1, onAnVhf1Change);
  messenger.attach(K_AN_VHF2, onAnVhf2Change);
  messenger.attach(K_AN_VHF3, onAnVhf3Change);
  messenger.attach(K_AN_HF1, onAnHf1Change);
  messenger.attach(K_AN_HF2, onAnHf2Change);
  messenger.attach(K_AN_FLT, onAnFltChange);
  messenger.attach(K_AN_SVO, onAnSvoChange);
  messenger.attach(K_AN_PA, onAnPaChange);
  messenger.attach(K_AN_NAV1, onAnNav1Change);
  messenger.attach(K_AN_NAV2, onAnNav2Change);
  messenger.attach(K_AN_ADF1, onAnAdf1Change);
  messenger.attach(K_AN_ADF2, onAnAdf2Change);
  messenger.attach(K_AN_MKR, onAnMkrChange);
  messenger.attach(K_AN_SPKR, onAnSpkrChange);
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

    // === MicSelector left LEDs ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_LEFT_1_LED);
    messenger.sendCmdArg(F("Pedestal_P4/K_MIC_SEL_LEFT_1_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_LEFT_1_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_LEFT_2_LED);
    messenger.sendCmdArg(F("Pedestal_P4/K_MIC_SEL_LEFT_2_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_LEFT_2_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_LEFT_3_LED);
    messenger.sendCmdArg(F("Pedestal_P4/K_MIC_SEL_LEFT_3_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_LEFT_3_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_LEFT_4_LED);
    messenger.sendCmdArg(F("Pedestal_P4/K_MIC_SEL_LEFT_4_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_LEFT_4_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_LEFT_5_LED);
    messenger.sendCmdArg(F("Pedestal_P4/K_MIC_SEL_LEFT_5_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_LEFT_5_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_LEFT_6_LED);
    messenger.sendCmdArg(F("Pedestal_P4/K_MIC_SEL_LEFT_6_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_LEFT_6_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_LEFT_7_LED);
    messenger.sendCmdArg(F("Pedestal_P4/K_MIC_SEL_LEFT_7_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_LEFT_7_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_LEFT_8_LED);
    messenger.sendCmdArg(F("Pedestal_P4/K_MIC_SEL_LEFT_8_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_LEFT_8_LED"));
    messenger.sendCmdEnd();

    // === Audio panel LEDs ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_VHF1);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_VHF1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_VHF1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_VHF2);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_VHF2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_VHF2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_VHF3);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_VHF3"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_VHF3"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_HF1);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_HF1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_HF1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_HF2);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_HF2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_HF2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_FLT);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_FLT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_FLT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_SVO);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_SVO"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_SVO"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_PA);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_PA"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_PA"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_NAV1);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_NAV1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_NAV1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_NAV2);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_NAV2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_NAV2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_ADF1);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_ADF1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_ADF1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_ADF2);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_ADF2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_ADF2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_MKR);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_MKR"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_MKR"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_SPKR);
    messenger.sendCmdArg(F("Pedestal_P4/K_AN_SPKR"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_SPKR"));
    messenger.sendCmdEnd();

    // ADD MORE CONFIG REGISTRATIONS HERE

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}
