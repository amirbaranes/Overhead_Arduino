#include <CmdMessenger.h>
#include <Encoder.h>
#include "HelperMethods.h"
#include "ComponentDefenition.h"
#include <Servo.h>
#include <NoDelay.h>
#include <LedControl.h>


const unsigned long BigDelayInterval = 50;   // in ms
const unsigned long SmallDelayInterval = 1;  // in ms
unsigned long lastBigDelayTime = 0;
unsigned long lastSmallDelayTime = 0;

bool demoMode = false;
noDelay demoModeDelay(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
bool readyToDemo = false;
bool shouldHandleServoReturn = true;

noDelay startupDelay(1000);
bool startupDone = false;

noDelay startupDelay3s(3000);
bool startupDone3s = false;
int yawDumperButtonLastStatus = -1;

Servo yawDumperServo;
int yawDumperServoAngle = 0;
int yawDumperServoMinimumAngle = 0;
int yawDumperServoMaximumAngle = 180;
noDelay yawDumperServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int yawDumperServoDemoCurrentValue = yawDumperServoMinimumAngle;

void yawDumperServoKick();
void yawDumperServoKickBack();
noDelay yawDumperServoKickTime(500, yawDumperServoKick);           //Creats a noDelay varible set to 1000ms, will call ledBlink funct
noDelay yawDumperServoKickBackTime(1500, yawDumperServoKickBack);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct


Servo fuelTempGaugeServo;
int fuelTempGaugeServoAngle = 0;
int fuelTempGaugeServoMinimumAngle = 45;
int fuelTempGaugeServoMaximumAngle = 160;
noDelay fuelTempGaugeServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int fuelTempGaugeServoDemoCurrentValue = fuelTempGaugeServoMinimumAngle;


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // pinMode(pin0, INPUT_PULLUP);
  // pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin5, INPUT_PULLUP);
  pinMode(pin6, INPUT_PULLUP);
  pinMode(pin7, INPUT_PULLUP);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);
  // pinMode(pin10, INPUT_PULLUP); servo
  pinMode(pin11, OUTPUT);
  pinMode(pin12, OUTPUT);
  pinMode(pin13, OUTPUT);
  pinMode(pin14, OUTPUT);
  pinMode(pin15, OUTPUT);
  pinMode(pin16, OUTPUT);
  pinMode(pin17, OUTPUT);
  pinMode(pin18, OUTPUT);
  pinMode(pin19, OUTPUT);
  pinMode(pin20, INPUT_PULLUP);
  pinMode(pin21, INPUT_PULLUP);
  pinMode(pin22, INPUT_PULLUP);
  pinMode(pin23, INPUT_PULLUP);
  pinMode(pin24, INPUT_PULLUP);
  pinMode(pin25, INPUT_PULLUP);
  pinMode(pin26, INPUT_PULLUP);
  pinMode(pin27, INPUT_PULLUP);
  pinMode(pin28, INPUT_PULLUP);
  pinMode(pin29, OUTPUT);
  pinMode(pin30, OUTPUT);
  pinMode(pin31, OUTPUT);
  pinMode(pin32, OUTPUT);
  //pinMode(pin33, INPUT_PULLUP); servo
  pinMode(pin34, OUTPUT);
  pinMode(pin35, OUTPUT);
  pinMode(pin36, OUTPUT);
  pinMode(pin37, INPUT_PULLUP);
  pinMode(pin38, INPUT_PULLUP);
  pinMode(pin39, INPUT_PULLUP);
  pinMode(pin40, INPUT_PULLUP);
  pinMode(pin41, INPUT_PULLUP);
  pinMode(pin42, INPUT_PULLUP);
  pinMode(pin43, INPUT_PULLUP);
  pinMode(pin44, INPUT_PULLUP);
  pinMode(pin45, OUTPUT);
  pinMode(pin46, OUTPUT);
  pinMode(pin47, OUTPUT);
  pinMode(pin48, OUTPUT);
  pinMode(pin49, OUTPUT);
  pinMode(pin50, OUTPUT);
  pinMode(pin51, INPUT_PULLUP);
  pinMode(pin52, INPUT_PULLUP);
  pinMode(pin53, INPUT_PULLUP);
  pinMode(pinA1, INPUT_PULLUP);
  pinMode(pinA2, INPUT_PULLUP);
  pinMode(pinA3, INPUT_PULLUP);
  pinMode(pinA4, INPUT_PULLUP);
  pinMode(pinA5, INPUT_PULLUP);
  pinMode(pinA6, INPUT_PULLUP);
  pinMode(pinA7, INPUT_PULLUP);
  pinMode(pinA8, INPUT_PULLUP);
  pinMode(pinA9, INPUT_PULLUP);
  pinMode(pinA10, INPUT_PULLUP);
  pinMode(pinA11, OUTPUT);
  // pinMode(pinA12, INPUT_PULLUP);
  // pinMode(pinA13, INPUT_PULLUP);
  // pinMode(pinA14, INPUT_PULLUP);
  // pinMode(pinA15, INPUT_PULLUP);
  // pinMode(pinA16, INPUT_PULLUP);


  clearLeds();

  attachCommandCallbacks();
}

void resetServos() {
  yawDumperServo.attach(pin10);
  yawDumperServo.write(0);
  yawDumperServoKickTime.stop();
  yawDumperServoKickBackTime.stop();

  fuelTempGaugeServo.attach(pin33);
  fuelTempGaugeServo.write(0);
}

void initializeServos() {
  fuelTempGaugeServo.write(fuelTempGaugeServoMinimumAngle);
}



void clearLeds() {
  updateLedValue(pin11, 0, lastStatePin11);
  updateLedValue(pin12, 0, lastStatePin12);
  updateLedValue(pin13, 0, lastStatePin13);
  updateLedValue(pin14, 0, lastStatePin14);
  updateLedValue(pin15, 0, lastStatePin15);
  updateLedValue(pin16, 0, lastStatePin16);
  updateLedValue(pin17, 0, lastStatePin17);
  updateLedValue(pin18, 0, lastStatePin18);
  updateLedValue(pin19, 0, lastStatePin19);
  updateLedValue(pin29, 0, lastStatePin29);
  updateLedValue(pin30, 0, lastStatePin30);
  updateLedValue(pin31, 0, lastStatePin31);
  updateLedValue(pin32, 0, lastStatePin32);
  updateLedValue(pin33, 0, lastStatePin33);
  updateLedValue(pin34, 0, lastStatePin34);
  updateLedValue(pin35, 0, lastStatePin35);
  updateLedValue(pin36, 0, lastStatePin36);
  updateLedValue(pin45, 0, lastStatePin45);
  updateLedValue(pin46, 0, lastStatePin46);
  updateLedValue(pin47, 0, lastStatePin47);
  updateLedValue(pin48, 0, lastStatePin48);
  updateLedValue(pin49, 0, lastStatePin49);
  updateLedValue(pin50, 0, lastStatePin50);
  updateLedValue(pinA11, 0, lastStatePinA11);
}

////////////////////////////
// Loop
////////////////////////////

void onStartupComplete() {
  resetServos();
}

void onStartupComplete3s() {
  initializeServos();
}

int buttonState = 0;

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

  if (demoModeDelay.update() || readyToDemo == true) {
    readyToDemo = true;
    if (demoMode == true) {
      handleYawDumperAutoReturn();
      onFuelTempGaugeServoDemo();
      onAnnounciatorsDemo();
    }
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    handleOnOffOnSwitch(pinA9, pinA10, lastStatePinA9, lastStatePinA10, buttonIdA9, buttonIdA10);  // flt control A
    handleOnOffOnSwitch(pin2, pin3, lastStatePin2, lastStatePin3, buttonId2, buttonId3);           // flt control B
    handleOnOffSwitch(pin4, lastStatePin4, buttonId4);                                             // Alternate flaps  - ON OFF
    handleOnOffSwitch(pin5, lastStatePin5, buttonId5);                                             // Spoilers A   - ON OFF
    handleOnOffSwitch(pin6, lastStatePin6, buttonId6);                                             // Spoilers B   - ON OFF
    handleOnOffOnSwitch(pin7, pin8, lastStatePin7, lastStatePin8, buttonId7, buttonId8);           // Alternate flaps   - ON OFF ON
    handleOnOffSwitch(pin9, lastStatePin9, buttonId9);                                             // // Yaw damper    - ON OFF
    // Yaw damper servo -     - Servo
    //stndby HYD low quantity  --LED
    //stndby HYD low pressure  --LED
    //FLT Control A Low pressure  --LED
    //FLT Control B Low pressure  --LED
    //Yaw Dumper Led  --LED
    //Feel diff press  --LED
    //Speed trim fail  --LED
    //Mach trim fail  --LED
    //Auto slat fail  --LED
    handleOnOffOnSwitch(pin20, pin21, lastStatePin20, lastStatePin21, buttonId20, buttonId21);        // VHF NAV    - ON OFF ON
    handleOnOffOnSwitch(pin22, pin23, lastStatePin22, lastStatePin23, buttonId22, buttonId23);        /// IRS NAV  - ON OFF ON
    handle3PositionRotary(pin24, pin25, displaySourceLastState, buttonId24, buttonId25, buttonId26);  // Displays source - 3 POS ROTARY
    handleOnOffOnSwitch(pin27, pin28, lastStatePin27, lastStatePin28, buttonId27, buttonId28);        // control panel source   - ON OFF ON
    handleOnOffOnSwitch(pinA7, pinA8, lastStatePinA7, lastStatePinA8, buttonIdA7, buttonIdA8);        // FMC - ON OFF ON
    //env valve closed left  --LED
    //env valve closed right  --LED
    //spar valve closed left  --LED
    //spar valve closed right  --LED
    // Fuel temp gauge data  - Servo
    //Filter bypass left  --LED
    //Filter bypass right  --LED
    //Valve open  --LED
    handle2PositionRotary(pin37, crossFeedLastState, buttonId37, buttonId38);  // Cross feed - 2 POS ROTARY
    handleOnOffSwitch(pin39, lastStatePin39, buttonId39);                      // Fuel pump L   - ON OFF
    handleOnOffSwitch(pin40, lastStatePin40, buttonId40);                      // Fuel pump R   - ON OFF
    handleOnOffSwitch(pin41, lastStatePin41, buttonId41);                      // Fuel pump L Aft   - ON OFF
    handleOnOffSwitch(pin42, lastStatePin42, buttonId42);                      // Fuel pump L Fwd   - ON OFF
    handleOnOffSwitch(pin43, lastStatePin43, buttonId43);                      /// Fuel pump R Aft   - ON OFF
    handleOnOffSwitch(pin44, lastStatePin44, buttonId44);                      /// Fuel pump R Fwd   - ON OFF
    //"Fuel pump L Low pressure "  --LED
    //"Fuel pump R Low pressure "  --LED
    //"Fuel pump L Aft Low pressure "  --LED
    //"Fuel pump L Fwd Low pressure "  --LED
    //"Fuel pump R Aft Low pressure "  --LED
    //"Fuel pump R Fwd Low pressure "  --LED
    handleOnOffSwitch(pin51, lastStatePin51, buttonId51);                                       // Landing retractable L   - ON OFF
    handleOnOffSwitch(pin52, lastStatePin52, buttonId52);                                       // Landing retractable R   - ON OFF
    handleOnOffSwitch(pin53, lastStatePin53, buttonId53);                                       // Landing fixed L   - ON OFF
    handleOnOffSwitch(pinA1, lastStatePinA1, buttonIdA1);                                       // Landing fixed R   - ON OFF
    handleOnOffSwitch(pinA2, lastStatePinA2, buttonIdA2);                                       // Runway turnoff L   - ON OFF
    handleOnOffSwitch(pinA3, lastStatePinA3, buttonIdA3);                                       // Runway turnoff R   - ON OFF
    handleOnOffSwitch(pinA4, lastStatePinA4, buttonIdA4);                                       // Taxi   - ON OFF
    handleOnOffOnSwitch(pinA5, pinA6, lastStatePinA5, lastStatePinA6, buttonIdA5, buttonIdA6);  // APU - ON OFF ON


    // if(yawDumperButtonLastStatus == 0){
    //   handleYawDumperAutoReturn();
    // }
    yawDumperServoKickTime.update();
     handleYawDumperAutoReturnResetPosition();

  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;

    //  handlePotentiometer(pinA0, min0, max0, address0, 1, lastVal0);
  }
}



void yawDumperServoKickTest() {

  handleYawDumperAutoReturn();
}


////////////////////////////
//  Servo auto return
////////////////////////////
void yawDumperServoKickBack() {
  yawDumperServoKickBackTime.stop();
  yawDumperServo.write(yawDumperServoMinimumAngle);
}

void yawDumperServoKick() {
  yawDumperServoKickTime.stop();
  yawDumperServo.write(yawDumperServoMaximumAngle);
}

void handleYawDumperAutoReturnResetPosition() {
  if (digitalRead(pin9) == 0 && yawDumperServo.read() == yawDumperServoMaximumAngle) {
    if (yawDumperServoKickBackTime.enabled() == false) {
      yawDumperServoKickBackTime.start();
    }
    yawDumperServoKickBackTime.update();
  }
}

void handleYawDumperAutoReturn() {
  if (digitalRead(pin9) == 1 && yawDumperServo.read() == yawDumperServoMinimumAngle) {
    if (yawDumperServoKickTime.enabled() == false) {
      if (demoMode == true) {
        yawDumperServoKickTime.setdelay(3000);
      }
      yawDumperServoKickTime.start();
    }
  }

  if (demoMode == true) {
    handleYawDumperAutoReturnResetPosition();
  }
}

void OnFuelTempGaugeServoValueChange(int value) {
  fuelTempGaugeServo.write(value);
}

void onFuelTempGaugeServoDemo() {

  if (fuelTempGaugeServoDemo.update())  //Checks to see if set time has past
  {
    if (fuelTempGaugeServoDemoCurrentValue == fuelTempGaugeServoMaximumAngle) {
      fuelTempGaugeServoDemoCurrentValue = fuelTempGaugeServoMinimumAngle;
    }
    OnFuelTempGaugeServoValueChange(fuelTempGaugeServoDemoCurrentValue);
    fuelTempGaugeServoDemoCurrentValue++;
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

void onYawDumperServoChange() {
  int val = messenger.readInt32Arg();

  if(val == 0){
    handleYawDumperAutoReturn();
  }
}

void onFuelTempGaugeDataChange() {
  double val = messenger.readDoubleArg();

  // Serial.println("onFuelTempGaugeDataChange");
  // Serial.println(val);

  // assuming the range of the value from pmdg in -40 - +40
  // minimum needle position is -40 degree
  double value = (val + 40) / (double)80;
  double percentagePosition = (fuelTempGaugeServoMaximumAngle - fuelTempGaugeServoMinimumAngle) * value;
  int finalValue = fuelTempGaugeServoMinimumAngle + percentagePosition;


  // Serial.println("final value");
  // Serial.println( finalValue);

  OnFuelTempGaugeServoValueChange(finalValue);
}



void onStbyHydLowQuantityChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin11, val, lastStatePin11);
}

void onStbyHydLowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin12, val, lastStatePin12);
}

void onFltCtrlALowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin15, val, lastStatePin15);
}

void onFltCtrlBLowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin14, val, lastStatePin14);
}

void onYawDumperLedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA11, val, lastStatePinA11);
}

void onFeelDiffPressChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin16, val, lastStatePin16);
}

void onSpeedTrimFailChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin17, val, lastStatePin17);
}

void onMachTrimFailChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin18, val, lastStatePin18);
}

void onAutoSlatFailChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin19, val, lastStatePin19);
}

void onEnvValveCloseLeftChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin29, val, lastStatePin29);
}

void onEnvValveCloseRightChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin30, val, lastStatePin30);
}

void onSparValveCloseLeftChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin31, val, lastStatePin31);
}

void onSparValveCloseRightChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin32, val, lastStatePin32);
}

void onFilterBypassLeftChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin34, val, lastStatePin34);
}

void onFilterBypassRightChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin35, val, lastStatePin35);
}

void onValvueOpenChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin36, val, lastStatePin36);
}

void onFuelPumpLLowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin45, val, lastStatePin45);
}

void onFuelPumpRLowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin46, val, lastStatePin46);
}

void onFuelPumpLAftLowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin47, val, lastStatePin47);
}

void onFuelPumpRAftLowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin49, val, lastStatePin49);
}

void onFuelPumpLFwdLowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin48, val, lastStatePin48);
}

void onFuelPumpRFwdLowPressureChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin50, val, lastStatePin50);
}

void onStbyRudOnChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin13, val, lastStatePin13);
}

void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);


  messenger.attach(KStbyHydLowQuantity, onStbyHydLowQuantityChange);
  messenger.attach(KStbyHydLowPressure, onStbyHydLowPressureChange);
  messenger.attach(KFltCtrlALowPressure, onFltCtrlALowPressureChange);
  messenger.attach(KFltCtrlBLowPressure, onFltCtrlBLowPressureChange);
  messenger.attach(KYawDumperLed, onYawDumperLedChange);
  messenger.attach(KFeelDiffPress, onFeelDiffPressChange);
  messenger.attach(KSpeedTrimFail, onSpeedTrimFailChange);
  messenger.attach(KMachTrimFail, onMachTrimFailChange);
  messenger.attach(KAutoSlatFail, onAutoSlatFailChange);
  messenger.attach(KEnvValveCloseLeft, onEnvValveCloseLeftChange);
  messenger.attach(KEnvValveCloseRight, onEnvValveCloseRightChange);
  messenger.attach(KSparValveCloseLeft, onSparValveCloseLeftChange);
  messenger.attach(KSparValveCloseRight, onSparValveCloseRightChange);
  messenger.attach(KFuelTempGaugeData, onFuelTempGaugeDataChange);
  messenger.attach(KFilterBypassLeft, onFilterBypassLeftChange);
  messenger.attach(KFilterBypassRight, onFilterBypassRightChange);
  messenger.attach(KValvueOpen, onValvueOpenChange);
  messenger.attach(KFuelPumpLLowPressure, onFuelPumpLLowPressureChange);
  messenger.attach(KFuelPumpRLowPressure, onFuelPumpRLowPressureChange);
  messenger.attach(KFuelPumpLAftLowPressure, onFuelPumpLAftLowPressureChange);
  messenger.attach(KFuelPumpRAftLowPressure, onFuelPumpRAftLowPressureChange);
  messenger.attach(KFuelPumpLFwdLowPressure, onFuelPumpLFwdLowPressureChange);
  messenger.attach(KFuelPumpRFwdLowPressure, onFuelPumpRFwdLowPressureChange);
  messenger.attach(KStbyRudOn, onStbyRudOnChange);
  messenger.attach(KYawDumperServo, onYawDumperServoChange);
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("OverHead_A1");
    messenger.sendCmdEnd();

  } else if (strcmp(request, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();

  } else if (strcmp(request, "CONFIG") == 0) {

    messenger.sendCmdStart(kCommand);                        // This is a "1" or Command:1 from Spad list
    messenger.sendCmdArg(F("ADD"));                          // Subcommand..ADD - SUBSCRIBE - UNSUBSCRIBE - EMULATE
    messenger.sendCmdArg(KYawDumperServo);                   // CMDID value defined at the top as "12" this will be the DATA channel
    messenger.sendCmdArg(F("OverHead_A1/KYawDumperServo"));  // will become "SERIAL:<guid>/**/**"
    messenger.sendCmdArg(F("U8"));                           // Value Type .. (Signed/Unsigned) one of S8,S16,S32,S64,U8,U16,U32,U64,FLT32,FLT64,ASCIIZ
    messenger.sendCmdArg(F("RW"));                           // Access Type RO - ReadOnly, RW - ReadWrite
    messenger.sendCmdArg(F("KYawDumperServo"));              // NAME of item for the UI
    messenger.sendCmdEnd();

    //     messenger.sendCmdStart(kCommand);                        // This is a "1" or Command:1 from Spad list
    // messenger.sendCmdArg(F("SUBSCRIBE"));                          // Subcommand..ADD - SUBSCRIBE - UNSUBSCRIBE - EMULATE
    // messenger.sendCmdArg(KYawDumperServo);                   // CMDID value defined at the top as "12" this will be the DATA channel
    // messenger.sendCmdArg(F("PMDGNG3:FCTL_YawDamper_Sw"));  // will become "SERIAL:<guid>/**/**"
    // messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KStbyHydLowQuantity);
    messenger.sendCmdArg(F("OverHead_A1/KStbyHydLowQuantity"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KStbyHydLowQuantity"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KStbyHydLowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KStbyHydLowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KStbyHydLowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFltCtrlALowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KFltCtrlALowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFltCtrlALowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFltCtrlBLowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KFltCtrlBLowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFltCtrlBLowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KYawDumperLed);
    messenger.sendCmdArg(F("OverHead_A1/KYawDumperLed"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KYawDumperLed"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFeelDiffPress);
    messenger.sendCmdArg(F("OverHead_A1/KFeelDiffPress"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFeelDiffPress"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KSpeedTrimFail);
    messenger.sendCmdArg(F("OverHead_A1/KSpeedTrimFail"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KSpeedTrimFail"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KMachTrimFail);
    messenger.sendCmdArg(F("OverHead_A1/KMachTrimFail"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KMachTrimFail"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KAutoSlatFail);
    messenger.sendCmdArg(F("OverHead_A1/KAutoSlatFail"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KAutoSlatFail"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KEnvValveCloseLeft);
    messenger.sendCmdArg(F("OverHead_A1/KEnvValveCloseLeft"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KEnvValveCloseLeft"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KEnvValveCloseRight);
    messenger.sendCmdArg(F("OverHead_A1/KEnvValveCloseRight"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KEnvValveCloseRight"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KSparValveCloseLeft);
    messenger.sendCmdArg(F("OverHead_A1/KSparValveCloseLeft"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KSparValveCloseLeft"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KSparValveCloseRight);
    messenger.sendCmdArg(F("OverHead_A1/KSparValveCloseRight"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KSparValveCloseRight"));
    messenger.sendCmdEnd();

    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(KFuelTempGaugeData);
    // messenger.sendCmdArg(F("OverHead_A1/KFuelTempGaugeData"));
    // messenger.sendCmdArg(F("U8"));
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("KFuelTempGaugeData"));
    // messenger.sendCmdEnd();
    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("SUBSCRIBE"));
    messenger.sendCmdArg(KFuelTempGaugeData);
    messenger.sendCmdArg(F("PMDGNG3:FUEL_FuelTempNeedle"));
     messenger.sendCmdArg(F("U8"));
     messenger.sendCmdArg(0.5);
    messenger.sendCmdEnd();



    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFilterBypassLeft);
    messenger.sendCmdArg(F("OverHead_A1/KFilterBypassLeft"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFilterBypassLeft"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFilterBypassRight);
    messenger.sendCmdArg(F("OverHead_A1/KFilterBypassRight"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFilterBypassRight"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KValvueOpen);
    messenger.sendCmdArg(F("OverHead_A1/KValvueOpen"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KValvueOpen"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFuelPumpLLowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KFuelPumpLLowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFuelPumpLLowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFuelPumpRLowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KFuelPumpRLowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFuelPumpRLowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFuelPumpLAftLowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KFuelPumpLAftLowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFuelPumpLAftLowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFuelPumpRAftLowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KFuelPumpRAftLowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFuelPumpRAftLowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFuelPumpLFwdLowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KFuelPumpLFwdLowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFuelPumpLFwdLowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KFuelPumpRFwdLowPressure);
    messenger.sendCmdArg(F("OverHead_A1/KFuelPumpRFwdLowPressure"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KFuelPumpRFwdLowPressure"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(KStbyRudOn);
    messenger.sendCmdArg(F("OverHead_A1/KStbyRudOn"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("KStbyRudOn"));
    messenger.sendCmdEnd();


    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin11);
  testAnnounciatorBlink(pin12);
  testAnnounciatorBlink(pin13);
  testAnnounciatorBlink(pin14);
  testAnnounciatorBlink(pin15);
  testAnnounciatorBlink(pin16);
  testAnnounciatorBlink(pin17);
  testAnnounciatorBlink(pin18);
  testAnnounciatorBlink(pin19);

  testAnnounciatorBlink(pinA11);
  testAnnounciatorBlink(pin29);
  testAnnounciatorBlink(pin30);
  testAnnounciatorBlink(pin31);
  testAnnounciatorBlink(pin32);
  testAnnounciatorBlink(pin34);
  testAnnounciatorBlink(pin35);
  testAnnounciatorBlink(pin36);

  testAnnounciatorBlink(pin45);
  testAnnounciatorBlink(pin46);
  testAnnounciatorBlink(pin47);
  testAnnounciatorBlink(pin48);
  testAnnounciatorBlink(pin49);
  testAnnounciatorBlink(pin50);
}
