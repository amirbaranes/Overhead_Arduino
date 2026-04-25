#include <CmdMessenger.h>
#include <Encoder.h>
#include "HelperMethods.h"
#include "ComponentDefenition.h"
#include "TM1637.h"
#include <Servo.h>
#include <NoDelay.h>



bool isSimConnected = false;

const unsigned long BigDelayInterval = 50;   // in ms
const unsigned long SmallDelayInterval = 1;  // in ms
unsigned long lastBigDelayTime = 0;
unsigned long lastSmallDelayTime = 0;

bool demoMode = false;

noDelay startupDelay(2000);
bool startupDone = false;

noDelay startupDelay3s(4000);
bool startupDone3s = false;

TM1637 fltAltDisply;
TM1637 landAltDisply;
noDelay altDisplyDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int altDisplayValueDemo = 12345;


Servo airTempServo;
int airTempServoAngle = 0;
int airTempServoMinimumAngle = 10;
int airTempServoMaximumAngle = 150;
noDelay airTempServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int airTempServoDemoCurrentValue = airTempServoMinimumAngle;

Servo ductPress1Servo;
int ductPress1ServoAngle = 0;
int ductPress1ServoMinimumAngle = 15;
int ductPress1ServoMaximumAngle = 145;
noDelay ductPress1ServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int ductPress1ServoDemoCurrentValue = ductPress1ServoMinimumAngle;

Servo ductPress2Servo;
int ductPress2ServoAngle = 0;
int ductPress2ServoMinimumAngle = 5;
int ductPress2ServoMaximumAngle = 128;
noDelay ductPress2ServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int ductPress2ServoDemoCurrentValue = ductPress2ServoMinimumAngle;

Servo manualAltServo;
int manualAltServoAngle = 0;
int manualAltServoMinimumAngle = 0;
int manualAltServoMaximumAngle = 100;
noDelay manualAltServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int manualAltServoDemoCurrentValue = manualAltServoMinimumAngle;



//Air Temperture - 300 DEGREES
int airTempPotLastVal = 0;
int airTempPotMin = 290;
int airTempPotMax = 0;
const char* airTempPotAddress = "PMDGNG3:EVT_OH_AIRCOND_TEMP_SELECTOR_CONT_800";

int contCabPotLastVal = 0;
int contCabPotMin = 0;
int contCabPotMax = 270;
const char* contCabPotAddress = "PMDGNG3:EVT_OH_AIRCOND_TEMP_SELECTOR_CONT_800";

int fwdCabPotLastVal = 0;
int fwdCabPotMin = 0;
int fwdCabPotMax = 270;
const char* fwdCabPotAddress = "PMDGNG3:EVT_OH_AIRCOND_TEMP_SELECTOR_FWD_800";

int aftCabPotLastVal = 0;
int aftCabPotMin = 0;
int aftCabPotMax = 270;
const char* aftCabPotAddress = "PMDGNG3:EVT_OH_AIRCOND_TEMP_SELECTOR_AFT_800";


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // pinMode(pin0, INPUT_PULLUP);
  // pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, INPUT_PULLUP);
  pinMode(pin10, INPUT_PULLUP);
  pinMode(pin11, INPUT_PULLUP);
  pinMode(pin12, INPUT_PULLUP);
  pinMode(pin13, INPUT_PULLUP);
  pinMode(pin14, INPUT_PULLUP);
  pinMode(pin15, INPUT_PULLUP);
  pinMode(pin16, INPUT_PULLUP);
  pinMode(pin17, INPUT_PULLUP);
  pinMode(pin18, INPUT_PULLUP);
  pinMode(pin19, INPUT_PULLUP);
  pinMode(pin20, INPUT_PULLUP);
  pinMode(pin21, OUTPUT);
  pinMode(pin22, OUTPUT);
  pinMode(pin23, OUTPUT);
  pinMode(pin24, OUTPUT);
  pinMode(pin25, OUTPUT);
  pinMode(pin26, OUTPUT);
  pinMode(pin27, OUTPUT);
  pinMode(pin28, OUTPUT);
  pinMode(pin29, OUTPUT);
  pinMode(pin30, OUTPUT);
  pinMode(pin31, INPUT_PULLUP);
  pinMode(pin32, INPUT_PULLUP);
  //pinMode(pin33, INPUT_PULLUP); Servo
  pinMode(pin34, INPUT_PULLUP);
  pinMode(pin35, INPUT_PULLUP);
  //pinMode(pin36, INPUT_PULLUP); / Servo
  pinMode(pin37, INPUT_PULLUP);
  pinMode(pin38, INPUT_PULLUP);
  pinMode(pin39, INPUT_PULLUP);
  pinMode(pin40, INPUT_PULLUP);
  pinMode(pin41, INPUT_PULLUP);
  pinMode(pin42, INPUT_PULLUP);
  pinMode(pin43, INPUT_PULLUP);
  pinMode(pin44, INPUT_PULLUP);
  pinMode(pin45, INPUT_PULLUP);
  pinMode(pin46, INPUT_PULLUP);
  pinMode(pin47, INPUT_PULLUP);
  //pinMode(pin48, INPUT_PULLUP);// Servo
  pinMode(pin49, INPUT_PULLUP);
  // pinMode(pin50, INPUT_PULLUP);
  // pinMode(pin51, INPUT_PULLUP);
  // pinMode(pin52, INPUT_PULLUP);
  // pinMode(pin53, INPUT_PULLUP);
  //pinMode(pinA1, INPUT_PULLUP);  //  Potentiometer
  // pinMode(pinA2, INPUT_PULLUP);//  Potentiometer
  // pinMode(pinA3, INPUT_PULLUP);//  Potentiometer
  // pinMode(pinA4, INPUT_PULLUP);//  Potentiometer
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



airTempServo.attach(pin48);
ductPress1Servo.attach(pin33);
ductPress2Servo.attach(pin36);
manualAltServo.attach(pin41);

  initializeScreens();
  //resetServos();
  clearLeds();

  attachCommandCallbacks();

  //initializeServos();
}

void initializeServos() {
 // delay(1000);
  airTempServo.write(airTempServoMinimumAngle);
  ductPress1Servo.write(ductPress1ServoMinimumAngle);
  ductPress2Servo.write(ductPress2ServoMinimumAngle);
  manualAltServo.write(0);
}

void resetServos() {
  //airTempServo.attach(pin48);
  airTempServo.write(0);
 // ductPress1Servo.attach(pin33);
  ductPress1Servo.write(0);
 // ductPress2Servo.attach(pin36);
  ductPress2Servo.write(0);
  //manualAltServo.attach(pin41);
  manualAltServo.write(0);
}

void initializeScreens() {
  fltAltDisply.begin(pin32, pin31, 6);   //  clock pin, data pin, #digits
  landAltDisply.begin(pin35, pin34, 6);  //  clock pin, data pin, #digits
  fltAltDisply.setBrightness(2);
  landAltDisply.setBrightness(2);
  fltAltDisply.displayClear();
  landAltDisply.displayClear();
}

void clearLeds() {
  updateLedValue(pin3, 0, lastStatePin3);
  updateLedValue(pin4, 0, lastStatePin4);
  updateLedValue(pin5, 0, lastStatePin5);
  updateLedValue(pin6, 0, lastStatePin6);
  updateLedValue(pin7, 0, lastStatePin7);
  updateLedValue(pin8, 0, lastStatePin8);
  updateLedValue(pin21, 0, lastStatePin21);
  updateLedValue(pin22, 0, lastStatePin22);
  updateLedValue(pin23, 0, lastStatePin23);
  updateLedValue(pin24, 0, lastStatePin24);
  updateLedValue(pin25, 0, lastStatePin25);
  updateLedValue(pin26, 0, lastStatePin26);
  updateLedValue(pin27, 0, lastStatePin27);
  updateLedValue(pin28, 0, lastStatePin28);
  updateLedValue(pin29, 0, lastStatePin29);
  updateLedValue(pin30, 0, lastStatePin30);
}


////////////////////////////
// Loop
////////////////////////////

void onStartupComplete() {
  // TODO: add startup logic here
    resetServos();
}

void onStartupComplete3s() {
  // TODO: add 3s startup logic here
  initializeServos();
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
    onAirTempServoDemo();
    onDuctPress1ServoDemo();
    onDuctPress2ServoDemo();
    oManualAltServoDemo();
    onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    handleOnOffSwitch(pin49, lastStatePin49, buttonId49);  // Voice recorder - ON OFF
    handleOnOffSwitch(pin2, lastStatePin2, buttonId2);     // Trim air ON OFF

    //Trim Air on --LED

    //Zone temp  --LED
    //Zone temp  --LED
    //Zone temp --LED
    //Dual bleed  --LED
    //Ram door full open 1  --LED
    //Ram door full open 2  --LED
    //Dect press 1 -- Servo
    //Dect press 2 -- Servo

    handleOnOffSwitch(pin9, lastStatePin9, buttonId9);                                          // L RECIRC FAN   - ON OFF
    handleOnOffSwitch(pin10, lastStatePin10, buttonId10);                                       // R RECIRC FAN   - ON OFF
    handleMomentaryButton(pin11, lastStatePin11, buttonId11);                                   // OVHT test   - Button
    handleOnOffOnSwitch(pin12, pin13, lastStatePin12, lastStatePin13, buttonId12, buttonId13);  // L PACK   - ON OFF ON
    handleOnOffOnSwitch(pin14, pin15, lastStatePin14, lastStatePin15, buttonId14, buttonId15);  // ISOLATION valve  - ON OFF ON
    handleOnOffOnSwitch(pin16, pin17, lastStatePin16, lastStatePin17, buttonId16, buttonId17);  // R PACK   - ON OFF ON
    handleOnOffOnSwitch(pin16, pin17, lastStatePin16, lastStatePin17, buttonId16, buttonId17);  // R PACK   - ON OFF ON
    handleOnOffSwitch(pin18, lastStatePin18, buttonId18);                                       // Eng bleed 1 on  - ON OFF
    handleOnOffSwitch(pin19, lastStatePin19, buttonId19);                                       // Eng bleed 2 on  - ON OFF
    handleOnOffSwitch(pin20, lastStatePin20, buttonId20);                                       // APU bleed  on  - ON OFF
    handleMomentaryButton(pin47, lastStatePin47, buttonId47);                                   // Trip reset  - Button
    //Auto fail  --LED
    //Off sched decent  --LED
    //ALTN --LED
    //MANUAL  --LED
    //Pack left  --LED
    //Wing body overheat L  --LED
    //Bleed trip off L  --LED
    //Pack Right --LED
    //Wing body overheat R  --LED
    //Bleed trip off R  --LED

    // FLT ALT  - 7 Segment
    // LAND ALT  - 7 Segment
    handleRotaryEncoder2(pin37, pin38, lastStatePin37, buttonId37, buttonId38);  // FLT ALT  - Rotatory encoder
    handleRotaryEncoder2(pin39, pin40, lastStatePin39, buttonId39, buttonId40);  // LAND ALT  - Rotatory encoder
    //Manual alt valve servo -- Servo
    handleOnOffOnSwitch(pin42, pin43, lastStatePin42, lastStatePin43, buttonId42, buttonId43);      // Manual alt valve    - MOM OFF MOM
    handle3PositionRotary(pin44, pin45, altnPresureLastState, buttonId44, buttonId45, buttonId46);  // ALTN presur  - 3 POS ROTARY


    handlePotentiometerTempSelector(pinA1, airTempPotLastVal);                                        //Air Temperture - 300 DEGREES
    handlePotentiometer2(pinA4, contCabPotMax, contCabPotMin, contCabPotAddress, contCabPotLastVal);  //CONT cab -- Potentiometer
    handlePotentiometer2(pinA3, fwdCabPotMax, fwdCabPotMin, fwdCabPotAddress, fwdCabPotLastVal);      //FWD cab -- Potentiometer
    handlePotentiometer2(pinA2, aftCabPotMax, aftCabPotMin, aftCabPotAddress, aftCabPotLastVal);      //AFT cab -- Potentiometer
  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;
  }
}


void onAirTempServoValueChange(int value) {
  airTempServo.write(value);
}

void onDuctPress1ServoValueChange(int value) {
  ductPress1Servo.write(value);
}

void onDuctPress2ServoValueChange(int value) {
  ductPress2Servo.write(value);
}

void onManualAltServoValueChange(int value) {
  manualAltServo.write(value);
}



////////////////////////////
// Messenger Callbacks
////////////////////////////
void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;
}


void onAirTempServoChange() {
  double val = messenger.readDoubleArg();
  val = (val - (double)32) * 5.0 / 9.0;

  // assuming the range of the value from pmdg in 0 - +100
  double value = val / (double)100;
  double percentagePosition = (airTempServoMaximumAngle - airTempServoMinimumAngle) * value;
  int finalValue = airTempServoMinimumAngle + percentagePosition;
  onAirTempServoValueChange(finalValue);
}

void onDectPress1Change() {
  int val = messenger.readInt32Arg();

  // assuming the range of the value from pmdg in 0 - +80
  double value = val / (double)80;
  double percentagePosition = (ductPress1ServoMaximumAngle - ductPress1ServoMinimumAngle) * value;
  int finalValue = ductPress1ServoMinimumAngle + percentagePosition;
  onDuctPress1ServoValueChange(finalValue);
}

void onDectPress2Change() {
  int val = messenger.readInt32Arg();

  // assuming the range of the value from pmdg in 0 - +80
  double value = val / (double)80;
  double percentagePosition = (ductPress2ServoMaximumAngle - ductPress2ServoMinimumAngle) * value;
  int finalValue = ductPress2ServoMinimumAngle + percentagePosition;
  onDuctPress2ServoValueChange(finalValue);
}

void onManualAltValveServoChange() {
  int val = messenger.readInt32Arg();

  // assuming the range of the value from pmdg in 0 - +80
  double value = val / (double)100;
  double percentagePosition = (manualAltServoMaximumAngle - manualAltServoMinimumAngle) * value;
  int finalValue = manualAltServoMinimumAngle + percentagePosition;
  if (finalValue <= 100) {
    onManualAltServoValueChange(100 - finalValue);
  }
}



void onFltAltDisplayChange() {
  double val = messenger.readDoubleArg();

  fltAltDisply.displayInt(val, true);
}

void onLandAltDisplayChange() {
  int val = messenger.readInt32Arg();

  landAltDisply.displayInt(val, true);
}




void onZoneTemp1Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin3, val, lastStatePin3);
}

void onZoneTemp2Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin4, val, lastStatePin4);
}

void onZoneTemp3Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin5, val, lastStatePin5);
}

void onDualBleedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin6, val, lastStatePin6);
}

void onRamDoorFullOpen1Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin7, val, lastStatePin7);
}

void onRamDoorFullOpen2Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin8, val, lastStatePin8);
}

void onAutoFailChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin21, val, lastStatePin21);
}

void onOffSchedDescentChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin22, val, lastStatePin22);
}

void onAltnChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin23, val, lastStatePin23);
}

void onManualChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin24, val, lastStatePin24);
}

void onPackLeftChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin25, val, lastStatePin25);
}

void onWingBodyOverheatLChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin26, val, lastStatePin26);
}

void onBleedTripOffLChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin27, val, lastStatePin27);
}

void onPackRightChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin28, val, lastStatePin28);
}

void onWingBodyOverheatRChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin29, val, lastStatePin29);
}

void onBleedTripOffRChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin30, val, lastStatePin30);
}




void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  messenger.attach(AN_ZONE_TEMP_1, onZoneTemp1Change);
  messenger.attach(AN_ZONE_TEMP_2, onZoneTemp2Change);
  messenger.attach(AN_ZONE_TEMP_3, onZoneTemp3Change);
  messenger.attach(AN_DUAL_BLEED, onDualBleedChange);
  messenger.attach(AN_RAM_DOOR_FULL_OPEN_1, onRamDoorFullOpen1Change);
  messenger.attach(AN_RAM_DOOR_FULL_OPEN_2, onRamDoorFullOpen2Change);
  messenger.attach(AN_AUTO_FAIL, onAutoFailChange);
  messenger.attach(AN_OFF_SCHED_DESCENT, onOffSchedDescentChange);
  messenger.attach(AN_ALTN, onAltnChange);
  messenger.attach(AN_MANUAL, onManualChange);
  messenger.attach(AN_PACK_LEFT, onPackLeftChange);
  messenger.attach(AN_WING_BODY_OVERHEAT_L, onWingBodyOverheatLChange);
  messenger.attach(AN_BLEED_TRIP_OFF_L, onBleedTripOffLChange);
  messenger.attach(AN_PACK_RIGHT, onPackRightChange);
  messenger.attach(AN_WING_BODY_OVERHEAT_R, onWingBodyOverheatRChange);
  messenger.attach(AN_BLEED_TRIP_OFF_R, onBleedTripOffRChange);

  messenger.attach(FLT_ALT_DISPLAY, onFltAltDisplayChange);
  messenger.attach(LAND_ALT_DISPLAY, onLandAltDisplayChange);

  messenger.attach(AIR_TEMP_SERVO, onAirTempServoChange);
  messenger.attach(DECT_PRESS_1_SERVO, onDectPress1Change);
  messenger.attach(DECT_PRESS_2_SERVO, onDectPress2Change);
  messenger.attach(MANUAL_ALT_VALVE_SERVO, onManualAltValveServoChange);
}



void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("OverHead_A5");
    messenger.sendCmdEnd();

  } else if (strcmp(request, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();

  } else if (strcmp(request, "CONFIG") == 0) {

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_ZONE_TEMP_1);
    messenger.sendCmdArg(F("OverHead_A5/AN_ZONE_TEMP_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_ZONE_TEMP_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_ZONE_TEMP_2);
    messenger.sendCmdArg(F("OverHead_A5/AN_ZONE_TEMP_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_ZONE_TEMP_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_ZONE_TEMP_3);
    messenger.sendCmdArg(F("OverHead_A5/AN_ZONE_TEMP_3"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_ZONE_TEMP_3"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_DUAL_BLEED);
    messenger.sendCmdArg(F("OverHead_A5/AN_DUAL_BLEED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_DUAL_BLEED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_RAM_DOOR_FULL_OPEN_1);
    messenger.sendCmdArg(F("OverHead_A5/AN_RAM_DOOR_FULL_OPEN_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_RAM_DOOR_FULL_OPEN_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_RAM_DOOR_FULL_OPEN_2);
    messenger.sendCmdArg(F("OverHead_A5/AN_RAM_DOOR_FULL_OPEN_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_RAM_DOOR_FULL_OPEN_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_AUTO_FAIL);
    messenger.sendCmdArg(F("OverHead_A5/AN_AUTO_FAIL"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_AUTO_FAIL"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_OFF_SCHED_DESCENT);
    messenger.sendCmdArg(F("OverHead_A5/AN_OFF_SCHED_DESCENT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_OFF_SCHED_DESCENT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_ALTN);
    messenger.sendCmdArg(F("OverHead_A5/AN_ALTN"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_ALTN"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_MANUAL);
    messenger.sendCmdArg(F("OverHead_A5/AN_MANUAL"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_MANUAL"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_PACK_LEFT);
    messenger.sendCmdArg(F("OverHead_A5/AN_PACK_LEFT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_PACK_LEFT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WING_BODY_OVERHEAT_L);
    messenger.sendCmdArg(F("OverHead_A5/AN_WING_BODY_OVERHEAT_L"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WING_BODY_OVERHEAT_L"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_BLEED_TRIP_OFF_L);
    messenger.sendCmdArg(F("OverHead_A5/AN_BLEED_TRIP_OFF_L"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_BLEED_TRIP_OFF_L"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_PACK_RIGHT);
    messenger.sendCmdArg(F("OverHead_A5/AN_PACK_RIGHT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_PACK_RIGHT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WING_BODY_OVERHEAT_R);
    messenger.sendCmdArg(F("OverHead_A5/AN_WING_BODY_OVERHEAT_R"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WING_BODY_OVERHEAT_R"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_BLEED_TRIP_OFF_R);
    messenger.sendCmdArg(F("OverHead_A5/AN_BLEED_TRIP_OFF_R"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_BLEED_TRIP_OFF_R"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(FLT_ALT_DISPLAY);
    messenger.sendCmdArg(F("OverHead_A5/FLT_ALT_DISPLAY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("FLT_ALT_DISPLAY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(LAND_ALT_DISPLAY);
    messenger.sendCmdArg(F("OverHead_A5/LAND_ALT_DISPLAY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("LAND_ALT_DISPLAY"));
    messenger.sendCmdEnd();

    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(AIR_TEMP_SERVO);
    // messenger.sendCmdArg(F("OverHead_A5/AIR_TEMP_SERVO"));
    // messenger.sendCmdArg(F("U8"));
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("AIR_TEMP_SERVO"));
    // messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("SUBSCRIBE"));
    messenger.sendCmdArg(AIR_TEMP_SERVO);
    messenger.sendCmdArg(F("PMDGNG3:AIR_TemperatureNeedle"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(1);
    messenger.sendCmdEnd();

    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(DECT_PRESS_1_SERVO);
    // messenger.sendCmdArg(F("OverHead_A5/DECT_PRESS_1_SERVO"));
    // messenger.sendCmdArg(F("U8"));
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("DECT_PRESS_1_SERVO"));
    // messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("SUBSCRIBE"));
    messenger.sendCmdArg(DECT_PRESS_1_SERVO);
    messenger.sendCmdArg(F("PMDGNG3:AIR_DuctPress_0"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(2);
    messenger.sendCmdEnd();

    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(DECT_PRESS_2_SERVO);
    // messenger.sendCmdArg(F("OverHead_A5/DECT_PRESS_2_SERVO"));
    // messenger.sendCmdArg(F("U8"));
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("DECT_PRESS_2_SERVO"));
    // messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("SUBSCRIBE"));
    messenger.sendCmdArg(DECT_PRESS_2_SERVO);
    messenger.sendCmdArg(F("PMDGNG3:AIR_DuctPress_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(2);
    messenger.sendCmdEnd();

    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(MANUAL_ALT_VALVE_SERVO);
    // messenger.sendCmdArg(F("OverHead_A5/MANUAL_ALT_VALVE_SERVO"));
    // messenger.sendCmdArg(F("U8"));
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("MANUAL_ALT_VALVE_SERVO"));
    // messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("SUBSCRIBE"));
    messenger.sendCmdArg(MANUAL_ALT_VALVE_SERVO);
    messenger.sendCmdArg(F("PMDGNG3:AIR_CabinValveNeedle"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(1);
    messenger.sendCmdEnd();


    delay(250);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin3);
  testAnnounciatorBlink(pin4);
  testAnnounciatorBlink(pin5);
  testAnnounciatorBlink(pin6);
  testAnnounciatorBlink(pin7);
  testAnnounciatorBlink(pin8);


  testAnnounciatorBlink(pin21);
  testAnnounciatorBlink(pin22);
  testAnnounciatorBlink(pin23);
  testAnnounciatorBlink(pin24);
  testAnnounciatorBlink(pin25);
  testAnnounciatorBlink(pin26);
  testAnnounciatorBlink(pin27);
  testAnnounciatorBlink(pin28);
  testAnnounciatorBlink(pin29);
  testAnnounciatorBlink(pin30);
}

void testDisplay() {

  if (altDisplyDemo.update())  //Checks to see if set time has past
  {
    if (altDisplayValueDemo == 99999) {
      altDisplayValueDemo = 12345;
    }
    fltAltDisply.displayInt(altDisplayValueDemo);
    landAltDisply.displayInt(altDisplayValueDemo);
    altDisplayValueDemo++;
  }
}

void onAirTempServoDemo() {

  if (airTempServoDemo.update())  //Checks to see if set time has past
  {
    if (airTempServoDemoCurrentValue == airTempServoMaximumAngle) {
      airTempServoDemoCurrentValue = airTempServoMinimumAngle;
    }
    onAirTempServoValueChange(airTempServoDemoCurrentValue);
    airTempServoDemoCurrentValue++;
  }
}

void onDuctPress1ServoDemo() {

  if (ductPress1ServoDemo.update())  //Checks to see if set time has past
  {
    if (ductPress1ServoDemoCurrentValue == ductPress1ServoMaximumAngle) {
      ductPress1ServoDemoCurrentValue = ductPress1ServoMinimumAngle;
    }
    onDuctPress1ServoValueChange(ductPress1ServoDemoCurrentValue);
    ductPress1ServoDemoCurrentValue += 5;
  }
}

void onDuctPress2ServoDemo() {

  if (ductPress2ServoDemo.update())  //Checks to see if set time has past
  {
    if (ductPress2ServoDemoCurrentValue == ductPress2ServoMaximumAngle) {
      ductPress2ServoDemoCurrentValue = ductPress2ServoMinimumAngle;
    }
    onDuctPress2ServoValueChange(ductPress2ServoDemoCurrentValue);
    ductPress2ServoDemoCurrentValue++;
  }
}

void oManualAltServoDemo() {

  if (manualAltServoDemo.update())  //Checks to see if set time has past
  {
    if (manualAltServoDemoCurrentValue == manualAltServoMaximumAngle) {
      manualAltServoDemoCurrentValue = manualAltServoMinimumAngle;
    }
    onManualAltServoValueChange(manualAltServoDemoCurrentValue);
    manualAltServoDemoCurrentValue++;
  }
}
