#include <CmdMessenger.h>
#include <Encoder.h>
#include "HelperMethods.h"
#include "ComponentDefenition.h"
#include <Servo.h>
#include <NoDelay.h>


bool isSimConnected = false;

const unsigned long BigDelayInterval = 50;   // in ms
const unsigned long SmallDelayInterval = 1;  // in ms
unsigned long lastBigDelayTime = 0;
unsigned long lastSmallDelayTime = 0;

bool demoMode = false;
bool shouldHandleServoReturn = true;

Servo egtServo;
int egtServoAngle = 0;
int egtServoMinimumAngle = 0;
int egtServoMaximumAngle = 140;
noDelay egtServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int egtServoDemoCurrentValue = egtServoMinimumAngle;



Servo engineStartLeftServo;
int engineStartLeftServoAngle = 0;

Servo engineStartRightServo;
int engineStartRightServoAngle = 0;

void leftEngStartKick();
void leftEngStartKickBack();
noDelay LeftEngKick(100, leftEngStartKick);               //Creats a noDelay varible set to 1000ms, will call ledBlink funct
noDelay LeftEngKickBackTime(1000, leftEngStartKickBack);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct

void rightEngStartKick();
void rightEngStartKickBack();
noDelay RightEngKick(100, rightEngStartKick);               //Creats a noDelay varible set to 1000ms, will call ledBlink funct
noDelay RightEngKickBackTime(1000, rightEngStartKickBack);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct



////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);


  //pinMode(pin0, INPUT_PULLUP);
  //pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, INPUT_PULLUP);
  //  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin5, INPUT_PULLUP);
  pinMode(pin6, INPUT_PULLUP);
  pinMode(pin7, INPUT_PULLUP);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);
  pinMode(pin10, INPUT_PULLUP);
  pinMode(pin11, INPUT_PULLUP);
  pinMode(pin12, INPUT_PULLUP);
  pinMode(pin13, OUTPUT);
  pinMode(pin14, OUTPUT);
  pinMode(pin15, OUTPUT);
  pinMode(pin16, OUTPUT);
  pinMode(pin17, OUTPUT);
  pinMode(pin18, OUTPUT);
  pinMode(pin19, OUTPUT);
  pinMode(pin20, OUTPUT);
  pinMode(pin21, OUTPUT);
  pinMode(pin22, OUTPUT);
  pinMode(pin23, OUTPUT);
  //pinMode(pin24, INPUT_PULLUP); servo
  pinMode(pin25, INPUT_PULLUP);
  pinMode(pin26, INPUT_PULLUP);
  pinMode(pin27, INPUT_PULLUP);
  pinMode(pin28, INPUT_PULLUP);
  pinMode(pin29, INPUT_PULLUP);
  pinMode(pin30, INPUT_PULLUP);
  pinMode(pin31, OUTPUT);
  pinMode(pin32, INPUT_PULLUP);
  pinMode(pin33, INPUT_PULLUP);
  pinMode(pin34, OUTPUT);
  pinMode(pin35, OUTPUT);
  pinMode(pin36, INPUT_PULLUP);
  pinMode(pin37, INPUT_PULLUP);
  pinMode(pin38, OUTPUT);
  pinMode(pin39, INPUT_PULLUP);
  pinMode(pin40, INPUT_PULLUP);
  pinMode(pin41, INPUT_PULLUP);
  pinMode(pin42, INPUT_PULLUP);
  pinMode(pin43, INPUT_PULLUP);
  pinMode(pin44, INPUT_PULLUP);
  pinMode(pin45, OUTPUT);
  pinMode(pin46, INPUT_PULLUP);
  pinMode(pin47, INPUT_PULLUP);
  pinMode(pin48, INPUT_PULLUP);
  pinMode(pin49, INPUT_PULLUP);
  pinMode(pin50, INPUT_PULLUP);
  pinMode(pin51, INPUT_PULLUP);
  pinMode(pin52, INPUT_PULLUP);
  pinMode(pin53, INPUT_PULLUP);
  // pinMode(pinA0, INPUT_PULLUP);
  //pinMode(pinA1, INPUT_PULLUP); servo
  //pinMode(pinA2, INPUT_PULLUP); servo
  pinMode(pinA3, INPUT_PULLUP);
  pinMode(pinA4, INPUT_PULLUP);
  pinMode(pinA5, INPUT_PULLUP);
  pinMode(pinA6, INPUT_PULLUP);
  pinMode(pinA7, INPUT_PULLUP);
  pinMode(pinA8, INPUT_PULLUP);
  pinMode(pinA9, INPUT_PULLUP);
  pinMode(pinA10, INPUT_PULLUP);
  pinMode(pinA11, INPUT_PULLUP);
  pinMode(pinA12, INPUT_PULLUP);
  pinMode(pinA13, INPUT_PULLUP);
  pinMode(pinA14, INPUT_PULLUP);
  //pinMode(pinA15, INPUT_PULLUP);

  resetServos();
  clearLeds();

  attachCommandCallbacks();

  initializeServos();
}

void initializeServos() {
  delay(1000);
  egtServo.write(egtServoMinimumAngle);
}

void resetServos() {
  // initialize servos
  egtServo.attach(pin24);
  egtServo.write(0);

  engineStartLeftServo.attach(pinA1);
  engineStartLeftServo.write(0);
  engineStartRightServo.attach(pinA2);
  engineStartRightServo.write(0);
  LeftEngKick.stop();
  LeftEngKickBackTime.stop();
  RightEngKick.stop();
  RightEngKickBackTime.stop();


  engineStartLeftServo.write(0);
}



void clearLeds() {
  updateLedValue(pin2, 0, lastStatePin2);
  updateLedValue(pin13, 0, lastStatePin13);

  updateLedValue(pin14, 0, lastStatePin14);
  updateLedValue(pin15, 0, lastStatePin15);
  updateLedValue(pin16, 0, lastStatePin16);
  updateLedValue(pin17, 0, lastStatePin17);
  updateLedValue(pin18, 0, lastStatePin18);
  updateLedValue(pin19, 0, lastStatePin19);
  updateLedValue(pin20, 0, lastStatePin20);
  updateLedValue(pin21, 0, lastStatePin21);
  updateLedValue(pin22, 0, lastStatePin22);
  updateLedValue(pin23, 0, lastStatePin23);
  updateLedValue(pin31, 0, lastStatePin31);
  updateLedValue(pin34, 0, lastStatePin34);
  updateLedValue(pin35, 0, lastStatePin35);
  updateLedValue(pin38, 0, lastStatePin38);
  updateLedValue(pin45, 0, lastStatePin45);
}



////////////////////////////
// Loop
////////////////////////////

void loop() {
  messenger.feedinSerialData();


  if (demoMode == true) {
    handleLeftEngineGrndToOffAutoReturn();
    handleRightEngineGrndToOffAutoReturn();
    onEgtvalueChangeDemo();
    onAnnounciatorsDemo();
  }


  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    handleOnOffOnSwitch(pin29, pin30, lastStatePin29, lastStatePin30, buttonId29, buttonId30);  // GRD PWR ON   - Mom OFF Mom
    //GRD Power available  --LED
    handleOnOffSwitch(pin3, lastStatePin3, buttonId3);                                          // Bus trans   - ON OFF
    handleOnOffOnSwitch(pin5, pin6, lastStatePin5, lastStatePin6, buttonId5, buttonId6);        // Gen 1 - ON OFF ON
    handleOnOffOnSwitch(pin7, pin8, lastStatePin7, lastStatePin8, buttonId7, buttonId8);        // Gen 2 - ON OFF ON
    handleOnOffOnSwitch(pin9, pin10, lastStatePin9, lastStatePin10, buttonId9, buttonId10);     // APU Gen 1 - ON OFF ON
    handleOnOffOnSwitch(pin11, pin12, lastStatePin11, lastStatePin12, buttonId11, buttonId12);  // APU Gen 2 - ON OFF ON
    //Transfer bus off 1  --LED
    //Transfer bus off 2  --LED
    //Source off 1  --LED
    //Source off 2  --LED
    //Gen off bus 1  --LED
    //Gen off bus 2  --LED
    //Apu gen off bus  --LED
    //MainT  --LED
    //Low oil pressure  --LED
    //Fault  --LED
    //OverSpeed  --LED
    // EGT  - Servo
    handle4PositionRotary(pin25, pin26, pin27, leftWiperLastState, buttonId25, buttonId26, buttonId27, buttonId28, leftWiperCandidateStateL, leftWiperStateStartTimeL);  // L wiper - 4 POS ROTARY
    //handlePotentiometer(pin29, 0, 100, lastStatePin29); // Circuit breaker  - Potentiometer
    // handlePotentiometer(pin30, 0, 100, lastStatePin30); // Circuit breaker - panel  - Potentiometer
    //Lavatory smoke  --LED
    handleOnOffSwitch(pin32, lastStatePin32, buttonId32);  // Equip cooling supply - ALTN   - ON OFF
    handleOnOffSwitch(pin33, lastStatePin33, buttonId33);  // Equip cooling exhaust - ALTN   - ON OFF
    //Equip cooling supply - ALTN  --LED
    //Equip cooling exhaust - ALTN  --LED
    handleOnOffOnSwitch(pin36, pin37, lastStatePin36, lastStatePin37, buttonId36, buttonId37);  // Emergency lights - Armed - ON OFF ON
    //Emergency lights - Not armed  --LED
    handleOnOffOnSwitch(pin39, pin40, lastStatePin39, lastStatePin40, buttonId39, buttonId40);  // No smoking  - ON OFF ON
    handleOnOffOnSwitch(pin41, pin42, lastStatePin41, lastStatePin42, buttonId41, buttonId42);  // Fasten Belts  - ON OFF ON
    handleOnOffSwitch(pin43, lastStatePin43, buttonId43);                                       // Attend  - ON OFF
    handleOnOffSwitch(pin44, lastStatePin44, buttonId44);                                       // GRD CALL  - ON OFF
    //GRD CALL - ALTN  --LED
    handle4PositionRotary(pin46, pin47, pin48, RightWiperLastState, buttonId46, buttonId47, buttonId48, buttonId49, RightWiperCandidateStateL, RightWiperStateStartTimeL);                      // L wiper - 4 POS ROTARY
    handle4PositionRotary2(pinA11, pinA12, pinA13, pinA14, EngineStartLLastState, buttonIdA11, buttonIdA12, buttonIdA13, buttonIdA14, EngineStartLCandidateState, EngineStartLStateStartTime);  // Engine start L  - 4 POS ROTARY
    handle4PositionRotary(pin50, pin51, pin52, EngineStartRLastState, buttonId50, buttonId51, buttonId52, buttonId53, EngineStartRCandidateState, EngineStartRStateStartTime);                  // Engine start R  - 4 POS ROTARY
    // Engine start L - Servo
    // Engine start R  - Servo
    handleOnOffOnSwitch(pinA3, pinA4, lastStatePinA3, lastStatePinA4, buttonIdA3, buttonIdA4);  // Engine start IGN  - ON OFF ON
    handleOnOffSwitch(pinA5, lastStatePinA5, buttonIdA5);                                       //LOGO  - ON OFF
    handleOnOffOnSwitch(pinA6, pinA7, lastStatePinA6, lastStatePinA7, buttonIdA6, buttonIdA7);  // Position  - ON OFF ON
    handleOnOffSwitch(pinA8, lastStatePinA8, buttonIdA8);                                       //Anti collision  - ON OFF
    handleOnOffSwitch(pinA9, lastStatePinA9, buttonIdA9);                                       //Wing  - ON OFF
    handleOnOffSwitch(pinA10, lastStatePinA10, buttonIdA10);                                    //Wheel  - ON OFF

    LeftEngKick.update();
    RightEngKick.update();
    handleLeftEngineGrndToOffResetPosition();
    handleRightEngineGrndToOffResetPosition();
  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;

    //  handlePotentiometer(pinA0, min0, max0, address0, 1, lastVal0);
  }
}

////////////////////////////
// Eng Servo auto return
////////////////////////////

void leftEngStartKick() {
  LeftEngKick.stop();
  engineStartLeftServo.write(180);
}

void leftEngStartKickBack() {
  LeftEngKickBackTime.stop();
  engineStartLeftServo.write(0);
}

void handleLeftEngineGrndToOffResetPosition() {
  if (digitalRead(pinA14) == LOW && engineStartLeftServo.read() == 180) {
    Serial.println("Should reset engine L servo position");
    if (LeftEngKickBackTime.enabled() == false) {
      LeftEngKickBackTime.start();
    }

    LeftEngKickBackTime.update();
  }
}

void handleLeftEngineGrndToOffAutoReturn() {

    String debugString1 = " pinA13 = " + String(digitalRead(pinA13))  ;
        messenger.sendCmd(kDebug, debugString1);

         String debugString2 = " engineStartLeftServo = " + String(engineStartLeftServo.read())  ;
        messenger.sendCmd(kDebug, debugString2);

  if (digitalRead(pinA13) == LOW && engineStartLeftServo.read() == 0) {
    if (LeftEngKick.enabled() == false) {
      if (demoMode == true) {
        LeftEngKick.setdelay(3000);
      }
      String debugString3 = " start  "  ;
        messenger.sendCmd(kDebug, debugString3);
      LeftEngKick.start();
    }
  }

  LeftEngKick.update();

  if (demoMode == true) {
    handleLeftEngineGrndToOffResetPosition();
  }
}

void rightEngStartKick() {
  RightEngKick.stop();
  engineStartRightServo.write(180);
}

void rightEngStartKickBack() {
  RightEngKickBackTime.stop();
  engineStartRightServo.write(0);
}

void handleRightEngineGrndToOffResetPosition() {
  if (digitalRead(pin53) == LOW && engineStartRightServo.read() == 180) {
    if (RightEngKickBackTime.enabled() == false) {
      RightEngKickBackTime.start();
    }

    RightEngKickBackTime.update();
  }
}

void handleRightEngineGrndToOffAutoReturn() {
  if (digitalRead(pin52) == LOW && engineStartRightServo.read() == 0) {
    if (RightEngKick.enabled() == false) {
      if (demoMode == true) {
        RightEngKick.setdelay(3000);
      }
      RightEngKick.start();
    }
  }

  RightEngKick.update();

  if (demoMode == true) {
    handleRightEngineGrndToOffResetPosition();
  }
}


void onEgtvalueChangeDemo() {

  if (egtServoDemo.update())  //Checks to see if set time has past
  {
    if (egtServoDemoCurrentValue == egtServoMaximumAngle) {
      egtServoDemoCurrentValue = egtServoMinimumAngle;
    }
    onEgtValueChange(egtServoDemoCurrentValue);
    egtServoDemoCurrentValue++;
  }
}

void onEgtValueChange(int value) {
  egtServo.write(value);
}


////////////////////////////
// Messenger Callbacks
////////////////////////////

void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;
}

void onEgtServoChange() {

  double val = messenger.readDoubleArg();

  // Serial.println("onFuelTempGaugeDataChange");
  // Serial.println(val);

  // assuming the range of the value from pmdg in 0 - +1000
  // minimum needle position is -40 degree
  double value = val / (double)1000;
  double percentagePosition = (egtServoMaximumAngle - egtServoMinimumAngle) * value;
  int finalValue = egtServoMinimumAngle + percentagePosition;
  onEgtValueChange(finalValue);
}

// Duplicates from original enum are merged into one method:
void onEngineStartLPositionChange() {
  int val = messenger.readInt32Arg();

  if (val == 1) {
    handleLeftEngineGrndToOffAutoReturn();
  }
}

void onEngineStartRPositionChange() {
  int val = messenger.readInt32Arg();

  if (val == 1) {
    handleRightEngineGrndToOffAutoReturn();
  }
}

void onAnGrndPwrAvailableChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin2, val, lastStatePin2);
}

void onAnTranserBusOff1Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin13, val, lastStatePin13);
}

void onAnTranserBusOff2Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin14, val, lastStatePin14);
}

void onAnSourceOff1Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin15, val, lastStatePin15);
}

void onAnSourceOff2Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin16, val, lastStatePin16);
}

void onAnGenOffBus1Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin17, val, lastStatePin17);
}

void onAnGenOffBus2Change() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin18, val, lastStatePin18);
}

void onAnApuGenOffBusChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin19, val, lastStatePin19);
}

void onAnMainTChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin20, val, lastStatePin20);
}

void onAnLowOilPressChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin21, val, lastStatePin21);
}

void onAnFaultChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin22, val, lastStatePin22);
}

void onAnOverspeedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin23, val, lastStatePin23);
}

void onAnLavatorySmokeChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin31, val, lastStatePin31);
}

void onAnEquipCoolingSupplyChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin34, val, lastStatePin34);
}

void onAnEquipCoolingExhaustChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin35, val, lastStatePin35);
}

void onAnEmergencyLightsChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin38, val, lastStatePin38);
}

void onAngrdCallAltnChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin45, val, lastStatePin45);
}


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  messenger.attach(EGTServo, onEgtServoChange);
  messenger.attach(AN_GRND_PWR_AVAILABLE, onAnGrndPwrAvailableChange);
  messenger.attach(AN_TRANSER_BUS_OFF_1, onAnTranserBusOff1Change);
  messenger.attach(AN_TRANSER_BUS_OFF_2, onAnTranserBusOff2Change);
  messenger.attach(AN_SOURCE_OFF_1, onAnSourceOff1Change);
  messenger.attach(AN_SOURCE_OFF_2, onAnSourceOff2Change);
  messenger.attach(AN_GEN_OFF_BUS_1, onAnGenOffBus1Change);
  messenger.attach(AN_GEN_OFF_BUS_2, onAnGenOffBus2Change);
  messenger.attach(AN_APU_GEN_OFF_BUS, onAnApuGenOffBusChange);
  messenger.attach(AN_MAIN_T, onAnMainTChange);
  messenger.attach(AN_LOW_OIL_PRESS, onAnLowOilPressChange);
  messenger.attach(AN_FAULT, onAnFaultChange);
  messenger.attach(AN_OVERSPEED, onAnOverspeedChange);
  messenger.attach(AN_LAVATORY_SMOKE, onAnLavatorySmokeChange);
  messenger.attach(AN_EQUIP_COOLING_SUPPLY, onAnEquipCoolingSupplyChange);
  messenger.attach(AN_EQUIP_COOLING_EXHAUST, onAnEquipCoolingExhaustChange);
  messenger.attach(AN_EMERGENCY_LIGHTS, onAnEmergencyLightsChange);
  messenger.attach(AN_GRD_CALL_ALTN, onAngrdCallAltnChange);
  messenger.attach(ENGINGE_START_L_SERVO, onEngineStartLPositionChange);
  messenger.attach(ENGINGE_START_R_SERVO, onEngineStartRPositionChange);
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("OverHead_A3");
    messenger.sendCmdEnd();
  } else if (strcmp(request, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();
  } else if (strcmp(request, "CONFIG") == 0) {

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(EGTServo);
    messenger.sendCmdArg(F("OverHead_A3/EGTServo"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("EGTServo"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_GRND_PWR_AVAILABLE);
    messenger.sendCmdArg(F("OverHead_A3/AN_GRND_PWR_AVAILABLE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_GRND_PWR_AVAILABLE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_TRANSER_BUS_OFF_1);
    messenger.sendCmdArg(F("OverHead_A3/AN_TRANSER_BUS_OFF_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_TRANSER_BUS_OFF_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_TRANSER_BUS_OFF_2);
    messenger.sendCmdArg(F("OverHead_A3/AN_TRANSER_BUS_OFF_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_TRANSER_BUS_OFF_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_SOURCE_OFF_1);
    messenger.sendCmdArg(F("OverHead_A3/AN_SOURCE_OFF_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_SOURCE_OFF_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_SOURCE_OFF_2);
    messenger.sendCmdArg(F("OverHead_A3/AN_SOURCE_OFF_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_SOURCE_OFF_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_GEN_OFF_BUS_1);
    messenger.sendCmdArg(F("OverHead_A3/AN_GEN_OFF_BUS_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_GEN_OFF_BUS_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_GEN_OFF_BUS_2);
    messenger.sendCmdArg(F("OverHead_A3/AN_GEN_OFF_BUS_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_GEN_OFF_BUS_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_APU_GEN_OFF_BUS);
    messenger.sendCmdArg(F("OverHead_A3/AN_APU_GEN_OFF_BUS"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_APU_GEN_OFF_BUS"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_MAIN_T);
    messenger.sendCmdArg(F("OverHead_A3/AN_MAIN_T"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_MAIN_T"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_LOW_OIL_PRESS);
    messenger.sendCmdArg(F("OverHead_A3/AN_LOW_OIL_PRESS"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_LOW_OIL_PRESS"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_FAULT);
    messenger.sendCmdArg(F("OverHead_A3/AN_FAULT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_FAULT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_OVERSPEED);
    messenger.sendCmdArg(F("OverHead_A3/AN_OVERSPEED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_OVERSPEED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_LAVATORY_SMOKE);
    messenger.sendCmdArg(F("OverHead_A3/AN_LAVATORY_SMOKE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_LAVATORY_SMOKE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_EQUIP_COOLING_SUPPLY);
    messenger.sendCmdArg(F("OverHead_A3/AN_EQUIP_COOLING_SUPPLY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_EQUIP_COOLING_SUPPLY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_EQUIP_COOLING_EXHAUST);
    messenger.sendCmdArg(F("OverHead_A3/AN_EQUIP_COOLING_EXHAUST"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_EQUIP_COOLING_EXHAUST"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_EMERGENCY_LIGHTS);
    messenger.sendCmdArg(F("OverHead_A3/AN_EMERGENCY_LIGHTS"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_EMERGENCY_LIGHTS"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_GRD_CALL_ALTN);
    messenger.sendCmdArg(F("OverHead_A3/AN_GRD_CALL_ALTN"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_GRD_CALL_ALTN"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(ENGINGE_START_L_SERVO);
    messenger.sendCmdArg(F("OverHead_A3/ENGINGE_START_L_SERVO"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("ENGINGE_START_L_SERVO"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(ENGINGE_START_R_SERVO);
    messenger.sendCmdArg(F("OverHead_A3/ENGINGE_START_R_SERVO"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("ENGINGE_START_R_SERVO"));
    messenger.sendCmdEnd();

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin2);
  testAnnounciatorBlink(pin13);
  testAnnounciatorBlink(pin14);
  testAnnounciatorBlink(pin15);
  testAnnounciatorBlink(pin16);
  testAnnounciatorBlink(pin17);
  testAnnounciatorBlink(pin18);
  testAnnounciatorBlink(pin19);

  testAnnounciatorBlink(pin20);
  testAnnounciatorBlink(pin21);
  testAnnounciatorBlink(pin22);
  testAnnounciatorBlink(pin23);

  testAnnounciatorBlink(pin31);
  testAnnounciatorBlink(pin34);
  testAnnounciatorBlink(pin35);
  testAnnounciatorBlink(pin38);
  testAnnounciatorBlink(pin45);
}
