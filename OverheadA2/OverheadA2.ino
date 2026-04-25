#include <CmdMessenger.h>
#include <Encoder.h>
#include "HelperMethods.h"
#include "ComponentDefenition.h"
#include <TM1637Display.h>
#include <NoDelay.h>
#include <LedControl.h>


const unsigned long BigDelayInterval = 50;   // in ms
const unsigned long SmallDelayInterval = 1;  // in ms
unsigned long lastBigDelayTime = 0;
unsigned long lastSmallDelayTime = 0;

bool demoMode = false;
int screenIntensity = 0;

noDelay startupDelay(1000);
bool startupDone = false;

noDelay startupDelay3s(3000);
bool startupDone3s = false;

int dcAmpsSwitchCurrentPosition = 0;
int acAmpsSwitchCurrentPosition = 0;


TM1637Display dcAmps(pin11, pin10);  // DC amps  - 7Seg
TM1637Display cpsFreq(pin2, pin3);   // CPS FREQ  - 7Seg
// TM1637Display dcVolts(pin5, pin4);   // DC volts  - 7Seg
// TM1637Display acAmps(pin7, pin6);    // AC amps  - 7Seg
// TM1637Display acVolts(pin8, pin9);   // AC volts  - 7Seg


LedControl dcVolts = LedControl(4, 5, 12, 1);  // DataIn, CLK, LOAD/CS, number of devices
LedControl acAmps = LedControl(6, 7, 13, 1);   // DataIn, CLK, LOAD/CS, number of devices
LedControl acVolts = LedControl(9, 8, 14, 1);  // DataIn, CLK, LOAD/CS, number of devices

const int displayBrightness = 1;
noDelay acdcDisplyDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int acdcDisplayValueDemo = 123;


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // pinMode(pin0, INPUT_PULLUP);
  // pinMode(pin1, INPUT_PULLUP);
  //pinMode(pin2, INPUT_PULLUP);
  // pinMode(pin3, INPUT_PULLUP);
  // pinMode(pin4, INPUT_PULLUP);
  // pinMode(pin5, INPUT_PULLUP);
  // pinMode(pin6, INPUT_PULLUP);
  // pinMode(pin7, INPUT_PULLUP);
  // pinMode(pin8, INPUT_PULLUP);
  // pinMode(pin9, INPUT_PULLUP);
  // pinMode(pin10, INPUT_PULLUP);
  // pinMode(pin11, INPUT_PULLUP);
  // pinMode(pin12, INPUT_PULLUP);
  // pinMode(pin13, INPUT_PULLUP);
  // pinMode(pin14, INPUT_PULLUP);
  pinMode(pin15, OUTPUT);
  pinMode(pin16, OUTPUT);
  pinMode(pin17, OUTPUT);

  pinMode(pin18, INPUT_PULLUP);
  pinMode(pin19, INPUT_PULLUP);
  pinMode(pin20, INPUT_PULLUP);
  pinMode(pin21, INPUT_PULLUP);
  pinMode(pin22, INPUT_PULLUP);
  pinMode(pin23, INPUT_PULLUP);
  pinMode(pin24, INPUT_PULLUP);
  pinMode(pin25, INPUT_PULLUP);
  pinMode(pin26, INPUT_PULLUP);
  pinMode(pin27, INPUT_PULLUP);
  pinMode(pin28, INPUT_PULLUP);
  pinMode(pin29, INPUT_PULLUP);
  pinMode(pin30, INPUT_PULLUP);
  pinMode(pin31, INPUT_PULLUP);
  pinMode(pin32, INPUT_PULLUP);
  pinMode(pin33, INPUT_PULLUP);
  //pinMode(pin34, INPUT_PULLUP);
  pinMode(pin35, INPUT_PULLUP);
  //pinMode(pin36, INPUT_PULLUP);
  pinMode(pin37, INPUT_PULLUP);
  // pinMode(pin38, INPUT_PULLUP);
  pinMode(pin39, INPUT_PULLUP);
  pinMode(pin40, INPUT_PULLUP);
  pinMode(pin41, INPUT_PULLUP);
  pinMode(pin42, INPUT_PULLUP);
  pinMode(pin43, OUTPUT);
  pinMode(pin44, OUTPUT);
  pinMode(pin45, OUTPUT);
  // pinMode(pin46, INPUT_PULLUP);
  // pinMode(pin47, INPUT_PULLUP);
  // pinMode(pin48, INPUT_PULLUP);
  // pinMode(pin49, INPUT_PULLUP);
  // pinMode(pin50, INPUT_PULLUP);
  // pinMode(pin51, INPUT_PULLUP);
  // pinMode(pin52, INPUT_PULLUP);
  // pinMode(pin53, INPUT_PULLUP);
  // pinMode(pinA1, INPUT_PULLUP);
  // pinMode(pinA2, INPUT_PULLUP);
  // pinMode(pinA3, INPUT_PULLUP);
  // pinMode(pinA4, INPUT_PULLUP);
  // pinMode(pinA5, INPUT_PULLUP);
  // pinMode(pinA6, INPUT_PULLUP);
  // pinMode(pinA7, INPUT_PULLUP);
  // pinMode(pinA8, INPUT_PULLUP);
  // pinMode(pinA9, INPUT_PULLUP);
  // pinMode(pinA10, INPUT_PULLUP);
  // pinMode(pinA11, INPUT_PULLUP);
  // pinMode(pinA12, INPUT_PULLUP);
  // pinMode(pinA13, INPUT_PULLUP);
  // pinMode(pinA14, INPUT_PULLUP);
  // pinMode(pinA15, INPUT_PULLUP);
  // pinMode(pinA16, INPUT_PULLUP);


  initializeScreens();
  clearLeds();

 // delay(1000);

  attachCommandCallbacks();
}

void initializeScreens() {
  // Initialize 7 segments displays
  dcAmps.setBrightness(displayBrightness);
  cpsFreq.setBrightness(displayBrightness);
  // dcVolts.setBrightness(displayBrightness);
  // acAmps.setBrightness(displayBrightness);
  // acVolts.setBrightness(displayBrightness);

  dcAmps.clear();
  cpsFreq.clear();
  // dcVolts.clear();
  // acAmps.clear();
  // acVolts.clear();

  //Max7219
  dcVolts.shutdown(0, false);
  dcVolts.setIntensity(0, screenIntensity);
  dcVolts.clearDisplay(0);
  acAmps.shutdown(0, false);
  acAmps.setIntensity(0, screenIntensity);
  acAmps.clearDisplay(0);
  acVolts.shutdown(0, false);
  acVolts.setIntensity(0, screenIntensity);
  acVolts.clearDisplay(0);
}

void clearLeds() {
  updateLedValue(pin15, 0, lastStatePin15);
  updateLedValue(pin16, 0, lastStatePin16);
  updateLedValue(pin17, 0, lastStatePin17);
  updateLedValue(pin43, 0, lastStatePin43);
  updateLedValue(pin44, 0, lastStatePin44);
  updateLedValue(pin45, 0, lastStatePin45);
}

////////////////////////////
// Loop
////////////////////////////

void onStartupComplete() {
  // TODO: add startup logic here
}

void onStartupComplete3s() {
  // TODO: add 3s startup logic here
}

void loop() {
  messenger.feedinSerialData();

  if (!startupDone && startupDelay.update()) {
    startupDone = true;
    onStartupComplete();
  }

  if (!startupDone3s && startupDelay3s.update()) {
    startupDone3s = true;
    onStartupComplete3s();
  }

  if (demoMode == true) {
    testDisplay();
    onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    // DC amps  - 7Seg
    // CPS FREQ  - 7Seg
    // DC volts  - 7Seg
    // AC amps  - 7Seg
    // AC volts  - 7Seg
    //BAT discharge  --LED
    //TR Unit  --LED
    //Elec  --LED

    handleOnOffSwitch(pin18, lastStatePin18, buttonId18);                                                                                                                                              // MainT  - ON OFF
    handle8PositionRotary(pin19, pin20, pin21, pin22, pin23, pin24, pin25, batSelectorLeftLastState, buttonId19, buttonId20, buttonId21, buttonId22, buttonId23, buttonId24, buttonId25, buttonId26);  // BAT selector(left side) - 8 POS ROTARY

    handle7PositionRotary2(pin27, pin28, pin29, pin30, pin31, pin32, pin33, batSelectorRightLastState, buttonId27, buttonId28, buttonId29, buttonId30, buttonId31, buttonId32, buttonId33);  // // BAT selector(right side) - 7 POS ROTARY

    handleOnOffSwitch(pin35, lastStatePin35, buttonId35);  // DC - ON OFF                                                                                                                                            // DC - ON OFF
    handleOnOffSwitch(pin37, lastStatePin37, buttonId37);  // CAB/UTIL - ON(gally) - ON OFF
    //handleOnOffSwitch(pin38, lastStatePin38, buttonId38);                                                                                                                                              // IFE/PASS  - ON OFF
    handleOnOffOnSwitch(pin39, pin40, lastStatePin39, lastStatePin40, buttonId39, buttonId40);  // STANDBY POWER   - ON OFF ON

    handleOnOffSwitch(pin41, lastStatePin41, buttonId41);  // Drive 1 disconnect  - ON OFF
    handleOnOffSwitch(pin42, lastStatePin42, buttonId42);  // Drive 2 disconnect  - ON OFF
    //Drive 1 disconnect --LED
    //Drive 2 disconnect  --LED
    //Standby PWR OFF  --LED
  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;

    //  handlePotentiometer(pinA0, min0, max0, address0, 1, lastVal0);
  }
}

////////////////////////////
// Demo
////////////////////////////
void testDisplay() {
  if (acdcDisplyDemo.update())  //Checks to see if set time has past
  {
    if (acdcDisplayValueDemo == 999) {
      acdcDisplayValueDemo = 123;
    }
    dcAmps.showNumberDec(acdcDisplayValueDemo, false);
    cpsFreq.showNumberDec(acdcDisplayValueDemo, false);

    dcVolts.setDigit(0, 0, 1, false);  // Digit 7 (leftmost), value 1
    dcVolts.setDigit(0, 1, 1, false);  // Digit 7 (leftmost), value 1
    dcVolts.setDigit(0, 2, 1, false);  // Digit 7 (leftmost), value 1


    acAmps.setDigit(0, 0, 1, false);  // Digit 7 (leftmost), value 1
    acAmps.setDigit(0, 1, 1, false);  // Digit 7 (leftmost), value 1
    acAmps.setDigit(0, 2, 1, false);  // Digit 7 (leftmost), value 1

    acVolts.setDigit(0, 0, 1, false);  // Digit 7 (leftmost), value 1
    acVolts.setDigit(0, 1, 1, false);  // Digit 7 (leftmost), value 1
    acVolts.setDigit(0, 2, 1, false);  // Digit 7 (leftmost), value 1

    // dcVolts.showNumberDec(acdcDisplayValueDemo, true);
    // acAmps.showNumberDec(acdcDisplayValueDemo, true);  // doing issues
    // acVolts.showNumberDec(acdcDisplayValueDemo, true);
    acdcDisplayValueDemo++;
  }
}


////////////////////////////
// Messenger Callbacks
////////////////////////////

void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;
}

void onDcAmpsChange() {
  int val = messenger.readInt32Arg();
  dcAmps.showNumberDec(val, false, 3, 0);
}

void onCpsFreqChange() {
  int val = messenger.readInt32Arg();
  cpsFreq.showNumberDec(val, false, 3, 1);
}

void onDcVoltsChange() {
  int val = messenger.readInt32Arg();

  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }

  updateMax7219Display(dcVolts, reversed);
}

void onAcAmpsChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }

  updateMax7219Display(acAmps, reversed);
}

void onAcVoltsChange() {
  int val = messenger.readInt32Arg();
  int reversed = 0;
  while (val != 0) {
    int digit = val % 10;
    reversed = reversed * 10 + digit;
    val /= 10;
  }

  updateMax7219Display(acVolts, reversed);
}

void onAnBatDischargeChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin15, val, lastStatePin15);
}

void onAnTrUnitChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin16, val, lastStatePin16);
}

void onAnElecChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin17, val, lastStatePin17);
}

void onAnDrive1DisconnectChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin43, val, lastStatePin43);
}

void onAnDrive2DisconnectChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin44, val, lastStatePin44);
}

void onAnStbyPowerOffChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin45, val, lastStatePin45);
}

void onDcAmpsSwitchChange() {
  int val = messenger.readInt32Arg();
  dcAmpsSwitchCurrentPosition = val;

  if (dcAmpsSwitchCurrentPosition == 7) {
    dcAmps.setBrightness(displayBrightness, false);
    dcVolts.shutdown(0, true);
  } else if (dcAmpsSwitchCurrentPosition == 0 || dcAmpsSwitchCurrentPosition == 1) {
    dcAmps.setBrightness(displayBrightness, false);
    dcVolts.shutdown(0, false);
  } else {
    dcAmps.setBrightness(displayBrightness, true);
    dcVolts.shutdown(0, false);
  }
}

void onAcAmpsSwitchChange() {
  int val = messenger.readInt32Arg();
  acAmpsSwitchCurrentPosition = val;


  if (acAmpsSwitchCurrentPosition == 6) {
    cpsFreq.setBrightness(displayBrightness, false);
    acVolts.shutdown(0, true);
    acAmps.shutdown(0, true);
  } else if (acAmpsSwitchCurrentPosition == 5) {
    cpsFreq.setBrightness(displayBrightness, true);
    acVolts.shutdown(0, false);
    acAmps.shutdown(0, true);
  } else if (acAmpsSwitchCurrentPosition == 4) {
    cpsFreq.setBrightness(displayBrightness, true);
    acVolts.shutdown(0, false);
    acAmps.shutdown(0, false);
  } else if (acAmpsSwitchCurrentPosition == 3) {
    cpsFreq.setBrightness(displayBrightness, false);
    acVolts.shutdown(0, false);
    acAmps.shutdown(0, false);
  } else if (acAmpsSwitchCurrentPosition == 2) {
    cpsFreq.setBrightness(displayBrightness, true);
    acVolts.shutdown(0, false);
    acAmps.shutdown(0, false);
  } else if (acAmpsSwitchCurrentPosition == 1) {
    cpsFreq.setBrightness(displayBrightness, false);
    acVolts.shutdown(0, false);
    acAmps.shutdown(0, true);
  } else if (acAmpsSwitchCurrentPosition == 0) {
    cpsFreq.setBrightness(displayBrightness, true);
    acVolts.shutdown(0, false);
    acAmps.shutdown(0, true);
  }
}


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  messenger.attach(K_DC_AMPS, onDcAmpsChange);
  messenger.attach(K_CPS_FREQ, onCpsFreqChange);
  messenger.attach(K_DC_VOLTS, onDcVoltsChange);
  messenger.attach(K_AC_AMPS, onAcAmpsChange);
  messenger.attach(K_AC_VOLTS, onAcVoltsChange);
  messenger.attach(K_AN_BAT_DISCHARGE, onAnBatDischargeChange);
  messenger.attach(K_AN_TR_UNIT, onAnTrUnitChange);
  messenger.attach(K_AN_ELEC, onAnElecChange);
  messenger.attach(K_AN_DRIVE_1_DISCONNECT, onAnDrive1DisconnectChange);
  messenger.attach(K_AN_DRIVE_2_DISCONNECT, onAnDrive2DisconnectChange);
  messenger.attach(K_AN_STBY_POWER_OFF, onAnStbyPowerOffChange);
  messenger.attach(K_DC_AMPS_SWITCH, onDcAmpsSwitchChange);
  messenger.attach(K_AC_AMPS_SWITCH, onAcAmpsSwitchChange);
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg("{a2ed4ab6-50d1-4018-b6ad-4868cea0474d}");
    messenger.sendCmdArg("OverHead_A2");
    messenger.sendCmdEnd();
  } else if (strcmp(request, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();
  } else if (strcmp(request, "CONFIG") == 0) {

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_DC_AMPS);
    messenger.sendCmdArg(F("OverHead_A2/K_DC_AMPS"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_DC_AMPS"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CPS_FREQ);
    messenger.sendCmdArg(F("OverHead_A2/K_CPS_FREQ"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CPS_FREQ"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_DC_VOLTS);
    messenger.sendCmdArg(F("OverHead_A2/K_DC_VOLTS"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_DC_VOLTS"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AC_AMPS);
    messenger.sendCmdArg(F("OverHead_A2/K_AC_AMPS"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AC_AMPS"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AC_VOLTS);
    messenger.sendCmdArg(F("OverHead_A2/K_AC_VOLTS"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AC_VOLTS"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_BAT_DISCHARGE);
    messenger.sendCmdArg(F("OverHead_A2/K_AN_BAT_DISCHARGE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_BAT_DISCHARGE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_TR_UNIT);
    messenger.sendCmdArg(F("OverHead_A2/K_AN_TR_UNIT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_TR_UNIT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_ELEC);
    messenger.sendCmdArg(F("OverHead_A2/K_AN_ELEC"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_ELEC"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_DRIVE_1_DISCONNECT);
    messenger.sendCmdArg(F("OverHead_A2/K_AN_DRIVE_1_DISCONNECT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_DRIVE_1_DISCONNECT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_DRIVE_2_DISCONNECT);
    messenger.sendCmdArg(F("OverHead_A2/K_AN_DRIVE_2_DISCONNECT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_DRIVE_2_DISCONNECT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AN_STBY_POWER_OFF);
    messenger.sendCmdArg(F("OverHead_A2/K_AN_STBY_POWER_OFF"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AN_STBY_POWER_OFF"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_DC_AMPS_SWITCH);
    messenger.sendCmdArg(F("OverHead_A2/K_DC_AMPS_SWITCH"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_DC_AMPS_SWITCH"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AC_AMPS_SWITCH);
    messenger.sendCmdArg(F("OverHead_A2/K_AC_AMPS_SWITCH"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AC_AMPS_SWITCH"));
    messenger.sendCmdEnd();

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin15);
  testAnnounciatorBlink(pin16);
  testAnnounciatorBlink(pin17);
  testAnnounciatorBlink(pin43);
  testAnnounciatorBlink(pin44);
  testAnnounciatorBlink(pin45);
}
