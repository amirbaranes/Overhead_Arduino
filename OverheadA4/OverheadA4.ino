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

noDelay startupDelay(1000);
bool startupDone = false;

noDelay startupDelay3s(3000);
bool startupDone3s = false;


Servo cabinDiffPressureServo;
int cabinDiffPressureAngle = 0;
int cabinDiffPressureMinimumAngle = 0;
int cabinDiffPressureMaximumAngle = 170;
noDelay cabinDiffPressureServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int cabinDiffPressureDemoCurrentValue = cabinDiffPressureMinimumAngle;

Servo cabinAltServo;
int cabinAltAngle = 0;
int cabinAltMinimumAngle = 0;
int cabinAltMaximumAngle = 170;
noDelay cabinAltServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int cabinAltDemoCurrentValue = cabinAltMinimumAngle;

Servo cabinClimbServo;
int cabinClimbAngle = 0;
int cabinClimbMinimumAngle = 0;
int cabinClimbMaximumAngle = 180;
noDelay cabinClimbServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int cabinClimbDemoCurrentValue = cabinClimbMinimumAngle;


Servo wingAntIceServo;
int wingAntIceAngle = 0;
int wingAntIceMinimumAngle = 180;
int wingAntIceMaximumAngle = 0;
noDelay wingAntIceServoDemo(1000);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct
int wingAntIceDemoCurrentValue = wingAntIceMinimumAngle;

void wingAntiIceKick();
void wingAntiIceKickBack();
noDelay wingAntiIceKickTime(100, wingAntiIceKick);           //Creats a noDelay varible set to 1000ms, will call ledBlink funct
noDelay wingAntiIceKickBackTime(1500, wingAntiIceKickBack);  //Creats a noDelay varible set to 1000ms, will call ledBlink funct


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);


  // pinMode(pin0, INPUT_PULLUP);
  // pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);
  pinMode(pin10, INPUT_PULLUP);
  pinMode(pin11, INPUT_PULLUP);
  pinMode(pin12, INPUT_PULLUP);
  pinMode(pin13, INPUT_PULLUP);
  pinMode(pin14, INPUT_PULLUP);
  pinMode(pin15, INPUT_PULLUP);
  pinMode(pin16, INPUT_PULLUP);
  pinMode(pin17, OUTPUT);
  pinMode(pin18, OUTPUT);
  pinMode(pin19, OUTPUT);
  pinMode(pin20, OUTPUT);
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
  pinMode(pin33, INPUT_PULLUP);
  // pinMode(pin34, INPUT_PULLUP); // servo
  pinMode(pin35, OUTPUT);
  pinMode(pin36, OUTPUT);
  pinMode(pin37, INPUT_PULLUP);
  pinMode(pin38, INPUT_PULLUP);
  pinMode(pin39, INPUT_PULLUP);
  pinMode(pin40, INPUT_PULLUP);
  pinMode(pin41, OUTPUT);
  pinMode(pin42, OUTPUT);
  pinMode(pin43, OUTPUT);
  pinMode(pin44, OUTPUT);
  pinMode(pin45, OUTPUT);
  pinMode(pin46, OUTPUT);
  pinMode(pin47, OUTPUT);
  pinMode(pin48, OUTPUT);
  pinMode(pin49, OUTPUT);
  pinMode(pin50, OUTPUT);
  pinMode(pin51, OUTPUT);
  pinMode(pin52, OUTPUT);
  pinMode(pin53, OUTPUT);
  //pinMode(pinA0, INPUT_PULLUP);// servo
  //pinMode(pinA1, INPUT_PULLUP);// servo
  //pinMode(pinA2, INPUT_PULLUP);// servo
  pinMode(pinA3, OUTPUT);
  pinMode(pinA4, OUTPUT);
  // pinMode(pinA5, INPUT_PULLUP);
  pinMode(pinA6, INPUT_PULLUP);
  pinMode(pinA7, INPUT_PULLUP);
  //pinMode(pinA8, INPUT_PULLUP);
  pinMode(pinA9, INPUT_PULLUP);
  //pinMode(pinA10, INPUT_PULLUP);
  pinMode(pinA11, OUTPUT);
  pinMode(pinA12, OUTPUT);

  // pinMode(pinA13, INPUT_PULLUP);
  // pinMode(pinA14, INPUT_PULLUP);
  // pinMode(pinA15, INPUT_PULLUP);

  clearLeds();

  attachCommandCallbacks();


  // ServoSection cabinClimbSections2[] = {
  //   { -3000, -2000, 0, 27 },
  //   { -1999, -1500, 27, 40 },
  //   { -1499, -1000, 40, 53 },
  //   { -999, -500, 53, 67 },
  //   { -499, 0, 67, 94 },
  //   { 1, 500, 94, 120 },
  //   { 501, 1000, 120, 133 },
  //   { 1001, 1500, 133, 145 },
  //   { 1501, 2000, 145, 156 },
  //   { 2001, 3700, 156, 175 },
  // };

  // int val = 1;

  // String debugString = String(val) + " value for cabin climb";
  // messenger.sendCmd(kDebug, debugString);

  // int result = mapCustomSections(val, cabinClimbSections2, 10);

  // String debugString2 = String(result) + " result value for cabin climb";
  // messenger.sendCmd(kDebug, debugString2);
  // if (result >= 0) {
  //   onCabinClimbServoValueChange(result);
  // }
}


void initializeServos() {
  cabinDiffPressureServo.write(cabinDiffPressureMinimumAngle);
  cabinAltServo.write(cabinAltMinimumAngle);
  cabinClimbServo.write(cabinClimbMinimumAngle);
  wingAntIceServo.write(wingAntIceMinimumAngle);
}

void resetServos() {
  // initialize servos
  wingAntIceServo.attach(pin34);
  wingAntIceServo.write(0);

  cabinDiffPressureServo.attach(pinA0);
  cabinDiffPressureServo.write(0);

  cabinAltServo.attach(pinA1);
  cabinAltServo.write(0);

  cabinClimbServo.attach(pinA2);
  cabinClimbServo.write(0);

  wingAntiIceKickTime.stop();
  wingAntiIceKickBackTime.stop();
}

void clearLeds() {
  updateLedValue(pin35, 0, lastStatePin35);
  updateLedValue(pin36, 0, lastStatePin36);
  updateLedValue(pin2, 0, lastStatePin2);
  updateLedValue(pin3, 0, lastStatePin3);
  updateLedValue(pin4, 0, lastStatePin4);
  updateLedValue(pin5, 0, lastStatePin5);
  updateLedValue(pin6, 0, lastStatePin6);
  updateLedValue(pin7, 0, lastStatePin7);
  updateLedValue(pin17, 0, lastStatePin17);
  updateLedValue(pin18, 0, lastStatePin18);
  updateLedValue(pin19, 0, lastStatePin19);
  updateLedValue(pin20, 0, lastStatePin20);
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
  updateLedValue(pin41, 0, lastStatePin41);
  updateLedValue(pin42, 0, lastStatePin42);
  updateLedValue(pin43, 0, lastStatePin43);
  updateLedValue(pin44, 0, lastStatePin44);
  updateLedValue(pin45, 0, lastStatePin45);
  updateLedValue(pin46, 0, lastStatePin46);
  updateLedValue(pin47, 0, lastStatePin47);
  updateLedValue(pin48, 0, lastStatePin48);
  updateLedValue(pin49, 0, lastStatePin49);
  updateLedValue(pin50, 0, lastStatePin50);
  updateLedValue(pin51, 0, lastStatePin51);
  updateLedValue(pin52, 0, lastStatePin52);
  updateLedValue(pin53, 0, lastStatePin53);
  updateLedValue(pinA3, 0, lastStatePinA3);
  updateLedValue(pinA4, 0, lastStatePinA4);
  updateLedValue(pinA11, 0, lastStatePinA11);
  updateLedValue(pinA12, 0, lastStatePinA12);
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
    handleWingAntiIceAutoReturn();

    onCabinClimbServoDemo();
    onCabinAltServoDemo();
    onCabinDiffPressureServoDemo();

    onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    //WindowHeat-OverHeat 1  --LED
    //WindowHeat-OverHeat 2  --LED
    //WindowHeat-OverHeat 3  --LED
    //WindowHeat-OverHeat 4  --LED
    //WindowHeat-ON 1  --LED
    //WindowHeat-ON 2  --LED
    //WindowHeat-ON 3  --LED
    //WindowHeat-ON 4  --LED
    handleOnOffSwitch(pin8, lastStatePin8, buttonId8);                                          // WindowHeat-1 side on   - ON OFF
    handleOnOffSwitch(pin9, lastStatePin9, buttonId9);                                          // WindowHeat-1 fwd on   - ON OFF
    handleOnOffOnSwitch(pin10, pin11, lastStatePin10, lastStatePin11, buttonId10, buttonId11);  // WindowHeat - ON OFF ON
    handleOnOffSwitch(pin12, lastStatePin12, buttonId12);                                       // WindowHeat-2 side on   - ON OFF
    handleOnOffSwitch(pin13, lastStatePin13, buttonId13);                                       // WindowHeat-2 fwd on   - ON OFF

    handleOnOffSwitch(pin14, lastStatePin14, buttonId14);  // Probe heat 1 on   - ON OFF
    handleOnOffSwitch(pin15, lastStatePin15, buttonId15);  // Probe heat 2 on   - ON OFF
    handleOnOffSwitch(pin16, lastStatePin16, buttonId16);  // TAT test   - ON OFF
                                                           //Capt pitot  --LED
                                                           //L elev pitot  --LED
                                                           //L alpha vane  --LED
                                                           //Temp probe  --LED
                                                           //Fo pitot  --LED
                                                           //R elev pitot  --LED
                                                           //R alpha vane  --LED
                                                           //Aux pitot  --LED
                                                           //L valve open  --LED
                                                           //R valve open --LED
                                                           //cowl valve open 1  --LED
                                                           //cowl valve open 2  --LED
                                                           //cowl anti ice 1  --LED
                                                           //cowl anti ice 2  --LED
    handleOnOffSwitch(pin31, lastStatePin31, buttonId31);  // Wing anti ice on   - ON OFF
    handleOnOffSwitch(pin32, lastStatePin32, buttonId32);  // Eng anti ice 1 on   - ON OFF
    handleOnOffSwitch(pin33, lastStatePin33, buttonId33);  // Eng anti ice 2 on   - ON OFF
                                                           // Wing anti ice 1  - Servo
    handleOnOffSwitch(pin37, lastStatePin37, buttonId37);  // HYD pump eng 1 on   - ON OFF
    handleOnOffSwitch(pin38, lastStatePin38, buttonId38);  // HYD pump eng 2 on   - ON OFF
    handleOnOffSwitch(pin39, lastStatePin39, buttonId39);  // HYD pump elec 1 on   - ON OFF
    handleOnOffSwitch(pin40, lastStatePin40, buttonId40);  // HYD pump elec 2 on   - ON OFF
    //Low Pressure eng1 --LED
    //Low Pressure eng2 --LED
    //Overheat elec 2  --LED
    //Overheat elec 1  --LED
    //Low Pressure elec 1  --LED
    //Low Pressure elec 2  --LED
    //Fwd entry  --LED
    //Fwd service  --LED
    //Left fwd overwing  --LED
    //Right fwd overwing  --LED
    //Left aft overwing  --LED
    //Right aft overwing  --LED
    //Aft entry  --LED
    //Aft service  --LED
    //Equp  --LED
    //Fwd cargo  --LED
    //Aft cargo  --LED
    handleOnOffSwitch(pinA6, lastStatePinA6, buttonIdA6);  // Voice recorder erase   - ON OFF
    handleOnOffSwitch(pinA7, lastStatePinA7, buttonIdA7);  // Voice recorder test   - ON OFF
    handleOnOffSwitch(pinA9, lastStatePinA9, buttonIdA9);  // Alt horn   - ON OFF
                                                           // Cabin pressure   - Servo
                                                           // Diff pressure   - Servo
                                                           // Cabin alt   - Servo

    wingAntiIceKickTime.update();
    handleWingAntiIceAutoReturnResetPosition();
  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;
  }
}

////////////////////////////
// Eng Servo auto return
////////////////////////////
void wingAntiIceKickBack() {
  wingAntiIceKickBackTime.stop();
  wingAntIceServo.write(wingAntIceMinimumAngle);
}

void wingAntiIceKick() {
  wingAntiIceKickTime.stop();
  wingAntIceServo.write(wingAntIceMaximumAngle);
}

void handleWingAntiIceAutoReturnResetPosition() {

  if (lastStatePin31 == HIGH && wingAntIceServo.read() == wingAntIceMaximumAngle) {
    if (wingAntiIceKickBackTime.enabled() == false) {
      wingAntiIceKickBackTime.start();
    }
    wingAntiIceKickBackTime.update();
  }
}

void handleWingAntiIceAutoReturn() {

  if (lastStatePin31 == LOW && wingAntIceServo.read() == wingAntIceMinimumAngle) {
    if (wingAntiIceKickTime.enabled() == false) {
      if (demoMode == true) {
        wingAntiIceKickTime.setdelay(3000);
      }
      wingAntiIceKickTime.start();
    }
  }

  if (demoMode == true) {
    handleWingAntiIceAutoReturnResetPosition();
  }
}


void onCabinDiffPressureServoDemo() {

  if (cabinDiffPressureServoDemo.update())  //Checks to see if set time has past
  {
    if (cabinDiffPressureDemoCurrentValue == cabinDiffPressureMaximumAngle) {
      cabinDiffPressureDemoCurrentValue = cabinDiffPressureMinimumAngle;
    }
    onCabinDiffPressureServoValueChange(cabinDiffPressureDemoCurrentValue);
    cabinDiffPressureDemoCurrentValue += 10;
  }
}

void onCabinDiffPressureServoValueChange(int value) {
  cabinDiffPressureServo.write(value);
}

void onCabinAltServoDemo() {

  if (cabinAltServoDemo.update())  //Checks to see if set time has past
  {
    if (cabinAltDemoCurrentValue == cabinAltMaximumAngle) {
      cabinAltDemoCurrentValue = cabinAltMinimumAngle;
    }
    onCabinAltServoValueChange(cabinAltDemoCurrentValue);
    cabinAltDemoCurrentValue++;
  }
}

void onCabinAltServoValueChange(int value) {
  cabinAltServo.write(value);
}



void onCabinClimbServoDemo() {
  if (cabinClimbServoDemo.update())  //Checks to see if set time has past
  {
    if (cabinClimbDemoCurrentValue == cabinClimbMaximumAngle) {
      cabinClimbDemoCurrentValue = cabinClimbMinimumAngle;
    }
    onCabinClimbServoValueChange(cabinClimbDemoCurrentValue);
    cabinClimbDemoCurrentValue += 10;
  }
}

void onCabinClimbServoValueChange(int value) {
  cabinClimbServo.write(value);
}


////////////////////////////
// Messenger Callbacks
////////////////////////////
void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;
}

void onWingAntiIceServo() {
  int val = messenger.readInt32Arg();
  if (val == 0) {
    handleWingAntiIceAutoReturn();
  }
}

ServoSection cabinDiffSections[] = {
  { 0, 1, 0, 15 },
  { 1, 2, 15, 30 },
  { 2, 3, 30, 47 },
  { 3, 4, 47, 65 },
  { 4, 5, 65, 83 },
  { 5, 6, 83, 105 },
  { 6, 7, 105, 123 },
  { 7, 8, 123, 142 },
  { 8, 9, 142, 158 },
  { 9, 10, 158, 172 },
};
void onCabinDiffPressureServo() {
  double val = messenger.readDoubleArg();

  double result = mapCustomSections(val, cabinDiffSections, 10);

  if (result >= 0) {
    onCabinDiffPressureServoValueChange(result);
  }
}

ServoSection cabinAltSections[] = {
  { 0, 5000, 0, 30 },
  { 5001, 10000, 30, 56 },
  { 10001, 15000, 56, 85 },
  { 15001, 20000, 85, 107 },
  { 20001, 25000, 107, 123 },
  { 25001, 30000, 123, 136 },
  { 30001, 35000, 136, 149 },
  { 35001, 40000, 149, 159 },
  { 40001, 50000, 159, 170 }
};
void onCabinAltServo() {
  double val = messenger.readDoubleArg();

  double result = mapCustomSections(val, cabinAltSections, 9);

  if (result >= 0) {
    onCabinAltServoValueChange(result);
  }
}

ServoSection cabinClimbSections[] = {
  { -3000, -2000, 0, 27 },
  { -1999, -1500, 27, 40 },
  { -1499, -1000, 40, 53 },
  { -999, -500, 53, 67 },
  { -499, 0, 67, 94 },
  { 1, 500, 94, 120 },
  { 501, 1000, 120, 133 },
  { 1001, 1500, 133, 145 },
  { 1501, 2000, 145, 156 },
  { 2001, 3700, 156, 175 },
};
double lastCabinVSValue = 0;
double lastResultVSValue = 0;
bool lastCabinVSValueInitialized = false;
void onCabinClimbServo() {
  double val = messenger.readDoubleArg();
  
  if (lastCabinVSValueInitialized == false) {
    lastCabinVSValue = val;
    lastCabinVSValueInitialized = true;
  }

  double lastAbsolute = fabs(lastCabinVSValue);
  double valAbsolute = fabs(val);

  double diff = fabs(valAbsolute - lastAbsolute);
 // int diff = percentageDifference(val, lastCabinVSValue);

  String debugString4 = String(lastCabinVSValue) + " lastValue for cabin climb, " + String(val) + " ,val for cabin climb" + String(diff) +  " ,diff for cabin climb";
  messenger.sendCmd(kDebug, debugString4);

  if(diff > 100 && int(val) != 0) {
    String debugString9 = " ignore diff value for cabin climb";
    messenger.sendCmd(kDebug, debugString9);
    lastCabinVSValue = val;
    return;
  }


  int result = mapCustomSections(val, cabinClimbSections, 10);
  lastResultVSValue = result;

   String debugString2 = String(result) + " result value for cabin climb";
   messenger.sendCmd(kDebug, debugString2);

  if (result >= 0) {
    onCabinClimbServoValueChange(result);
  }
  lastCabinVSValue = val;
}

void onCabinClimbServoReset() {
    onCabinClimbServoValueChange(0);
    delay(500);
    onCabinClimbServoValueChange(lastResultVSValue);
}


void onWingAntiIceServoChange() {
  int val = messenger.readInt32Arg();
  // Do something...
}

void onAnWindowheatOverheat1() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin35, val, lastStatePin35);
}

void onAnWindowheatOverheat2() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin36, val, lastStatePin36);
}

void onAnWindowheatOverheat3() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin2, val, lastStatePin2);
}

void onAnWindowheatOverheat4() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin3, val, lastStatePin3);
}

void onAnWindowheatOn1() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin4, val, lastStatePin4);
}

void onAnWindowheatOn2() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin5, val, lastStatePin5);
}

void onAnWindowheatOn3() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin6, val, lastStatePin6);
}

void onAnWindowheatOn4() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin7, val, lastStatePin7);
}

void onAnCaptPitot() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin17, val, lastStatePin17);
}

void onAnLElevPitot() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin18, val, lastStatePin18);
}

void onAnLAlphaVane() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin19, val, lastStatePin19);
}

void onAnTempProbe() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin20, val, lastStatePin20);
}

void onAnFoPitot() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin21, val, lastStatePin21);
}

void onAnRElevPitot() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin22, val, lastStatePin22);
}

void onAnRAlphaVane() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin23, val, lastStatePin23);
}

void onAnAuxPitot() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin24, val, lastStatePin24);
}

void onAnLValveOpen() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin25, val, lastStatePin25);
}

void onAnRValveOpen() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin26, val, lastStatePin26);
}

void onAnCowlValveOpen1() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin27, val, lastStatePin27);
}

void onAnCowlValveOpen2() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin28, val, lastStatePin28);
}

void onAnCowlAntiIce1() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin29, val, lastStatePin29);
}

void onAnCowlAntiIce2() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin30, val, lastStatePin30);
}

void onAnLowPressureEng1() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin41, val, lastStatePin41);
}

void onAnLowPressureEng2() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin42, val, lastStatePin42);
}

void onAnOverheatElec2() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin43, val, lastStatePin43);
}

void onAnOverheatElec1() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin44, val, lastStatePin44);
}

void onAnLowPressureElec1() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin45, val, lastStatePin45);
}

void onAnLowPressureElec2() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin46, val, lastStatePin46);
}

void onAnFwdEntry() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin47, val, lastStatePin47);
}

void onAnFwdService() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin48, val, lastStatePin48);
}

void onAnLeftFwdOverwing() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin49, val, lastStatePin49);
}

void onAnRightFwdOverwing() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin50, val, lastStatePin50);
}

void onAnLeftAftOverwing() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin51, val, lastStatePin51);
}

void onAnRightAftOverwing() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin52, val, lastStatePin52);
}

void onAnAftEntry() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin53, val, lastStatePin53);
}

void onAnFwdCargo() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA3, val, lastStatePinA3);
}

void onAnAftCargo() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA4, val, lastStatePinA4);
}

void onAnAftService() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA11, val, lastStatePinA11);
}

void onAnEqup() {
  int val = messenger.readInt32Arg();
  updateLedValue(pinA12, val, lastStatePinA12);
}



void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  messenger.attach(AN_WINDOWHEAT_OVERHEAT_1, onAnWindowheatOverheat1);
  messenger.attach(AN_WINDOWHEAT_OVERHEAT_2, onAnWindowheatOverheat2);
  messenger.attach(AN_WINDOWHEAT_OVERHEAT_3, onAnWindowheatOverheat3);
  messenger.attach(AN_WINDOWHEAT_OVERHEAT_4, onAnWindowheatOverheat4);
  messenger.attach(AN_WINDOWHEAT_ON_1, onAnWindowheatOn1);
  messenger.attach(AN_WINDOWHEAT_ON_2, onAnWindowheatOn2);
  messenger.attach(AN_WINDOWHEAT_ON_3, onAnWindowheatOn3);
  messenger.attach(AN_WINDOWHEAT_ON_4, onAnWindowheatOn4);
  messenger.attach(AN_CAPT_PITOT, onAnCaptPitot);
  messenger.attach(AN_L_ELEV_PITOT, onAnLElevPitot);
  messenger.attach(AN_L_ALPHA_VANE, onAnLAlphaVane);
  messenger.attach(AN_TEMP_PROBE, onAnTempProbe);
  messenger.attach(AN_FO_PITOT, onAnFoPitot);
  messenger.attach(AN_R_ELEV_PITOT, onAnRElevPitot);
  messenger.attach(AN_R_ALPHA_VANE, onAnRAlphaVane);
  messenger.attach(AN_AUX_PITOT, onAnAuxPitot);
  messenger.attach(AN_L_VALVE_OPEN, onAnLValveOpen);
  messenger.attach(AN_R_VALVE_OPEN, onAnRValveOpen);
  messenger.attach(AN_COWL_VALVE_OPEN_1, onAnCowlValveOpen1);
  messenger.attach(AN_COWL_VALVE_OPEN_2, onAnCowlValveOpen2);
  messenger.attach(AN_COWL_ANTI_ICE_1, onAnCowlAntiIce1);
  messenger.attach(AN_COWL_ANTI_ICE_2, onAnCowlAntiIce2);
  messenger.attach(AN_LOW_PRESSURE_ENG1, onAnLowPressureEng1);
  messenger.attach(AN_LOW_PRESSURE_ENG2, onAnLowPressureEng2);
  messenger.attach(AN_OVERHEAT_ELEC_2, onAnOverheatElec2);
  messenger.attach(AN_OVERHEAT_ELEC_1, onAnOverheatElec1);
  messenger.attach(AN_LOW_PRESSURE_ELEC_1, onAnLowPressureElec1);
  messenger.attach(AN_LOW_PRESSURE_ELEC_2, onAnLowPressureElec2);
  messenger.attach(AN_FWD_ENTRY, onAnFwdEntry);
  messenger.attach(AN_FWD_SERVICE, onAnFwdService);
  messenger.attach(AN_LEFT_FWD_OVERWING, onAnLeftFwdOverwing);
  messenger.attach(AN_RIGHT_FWD_OVERWING, onAnRightFwdOverwing);
  messenger.attach(AN_LEFT_AFT_OVERWING, onAnLeftAftOverwing);
  messenger.attach(AN_RIGHT_AFT_OVERWING, onAnRightAftOverwing);
  messenger.attach(AN_AFT_ENTRY, onAnAftEntry);
  messenger.attach(AN_FWD_CARGO, onAnFwdCargo);
  messenger.attach(AN_AFT_CARGO, onAnAftCargo);
  messenger.attach(AN_AFT_SERVICE, onAnAftService);
  messenger.attach(AN_EQUP, onAnEqup);
  messenger.attach(WING_ANTI_ICE_SERVO, onWingAntiIceServo);
  messenger.attach(DIFF_PRESSURE_SERVO, onCabinDiffPressureServo);
  messenger.attach(CABIN_ALT_SERVO, onCabinAltServo);
  messenger.attach(CABIN_PRESSURE_SERVO, onCabinClimbServo);
  messenger.attach(CABIN_PRESSURE_SERVO_RESET, onCabinClimbServoReset);
}



void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("OverHead_A4");
    messenger.sendCmdEnd();
  } else if (strcmp(request, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();
  } else if (strcmp(request, "CONFIG") == 0) {

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WINDOWHEAT_OVERHEAT_1);
    messenger.sendCmdArg(F("OverHead_A4/AN_WINDOWHEAT_OVERHEAT_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WINDOWHEAT_OVERHEAT_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WINDOWHEAT_OVERHEAT_2);
    messenger.sendCmdArg(F("OverHead_A4/AN_WINDOWHEAT_OVERHEAT_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WINDOWHEAT_OVERHEAT_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WINDOWHEAT_OVERHEAT_3);
    messenger.sendCmdArg(F("OverHead_A4/AN_WINDOWHEAT_OVERHEAT_3"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WINDOWHEAT_OVERHEAT_3"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WINDOWHEAT_OVERHEAT_4);
    messenger.sendCmdArg(F("OverHead_A4/AN_WINDOWHEAT_OVERHEAT_4"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WINDOWHEAT_OVERHEAT_4"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WINDOWHEAT_ON_1);
    messenger.sendCmdArg(F("OverHead_A4/AN_WINDOWHEAT_ON_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WINDOWHEAT_ON_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WINDOWHEAT_ON_2);
    messenger.sendCmdArg(F("OverHead_A4/AN_WINDOWHEAT_ON_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WINDOWHEAT_ON_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WINDOWHEAT_ON_3);
    messenger.sendCmdArg(F("OverHead_A4/AN_WINDOWHEAT_ON_3"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WINDOWHEAT_ON_3"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_WINDOWHEAT_ON_4);
    messenger.sendCmdArg(F("OverHead_A4/AN_WINDOWHEAT_ON_4"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_WINDOWHEAT_ON_4"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_CAPT_PITOT);
    messenger.sendCmdArg(F("OverHead_A4/AN_CAPT_PITOT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_CAPT_PITOT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_L_ELEV_PITOT);
    messenger.sendCmdArg(F("OverHead_A4/AN_L_ELEV_PITOT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_L_ELEV_PITOT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_L_ALPHA_VANE);
    messenger.sendCmdArg(F("OverHead_A4/AN_L_ALPHA_VANE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_L_ALPHA_VANE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_TEMP_PROBE);
    messenger.sendCmdArg(F("OverHead_A4/AN_TEMP_PROBE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_TEMP_PROBE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_FO_PITOT);
    messenger.sendCmdArg(F("OverHead_A4/AN_FO_PITOT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_FO_PITOT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_R_ELEV_PITOT);
    messenger.sendCmdArg(F("OverHead_A4/AN_R_ELEV_PITOT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_R_ELEV_PITOT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_R_ALPHA_VANE);
    messenger.sendCmdArg(F("OverHead_A4/AN_R_ALPHA_VANE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_R_ALPHA_VANE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_AUX_PITOT);
    messenger.sendCmdArg(F("OverHead_A4/AN_AUX_PITOT"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_AUX_PITOT"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_L_VALVE_OPEN);
    messenger.sendCmdArg(F("OverHead_A4/AN_L_VALVE_OPEN"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_L_VALVE_OPEN"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_R_VALVE_OPEN);
    messenger.sendCmdArg(F("OverHead_A4/AN_R_VALVE_OPEN"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_R_VALVE_OPEN"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_COWL_VALVE_OPEN_1);
    messenger.sendCmdArg(F("OverHead_A4/AN_COWL_VALVE_OPEN_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_COWL_VALVE_OPEN_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_COWL_VALVE_OPEN_2);
    messenger.sendCmdArg(F("OverHead_A4/AN_COWL_VALVE_OPEN_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_COWL_VALVE_OPEN_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_COWL_ANTI_ICE_1);
    messenger.sendCmdArg(F("OverHead_A4/AN_COWL_ANTI_ICE_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_COWL_ANTI_ICE_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_COWL_ANTI_ICE_2);
    messenger.sendCmdArg(F("OverHead_A4/AN_COWL_ANTI_ICE_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_COWL_ANTI_ICE_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_LOW_PRESSURE_ENG1);
    messenger.sendCmdArg(F("OverHead_A4/AN_LOW_PRESSURE_ENG1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_LOW_PRESSURE_ENG1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_LOW_PRESSURE_ENG2);
    messenger.sendCmdArg(F("OverHead_A4/AN_LOW_PRESSURE_ENG2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_LOW_PRESSURE_ENG2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_OVERHEAT_ELEC_2);
    messenger.sendCmdArg(F("OverHead_A4/AN_OVERHEAT_ELEC_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_OVERHEAT_ELEC_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_OVERHEAT_ELEC_1);
    messenger.sendCmdArg(F("OverHead_A4/AN_OVERHEAT_ELEC_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_OVERHEAT_ELEC_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_LOW_PRESSURE_ELEC_1);
    messenger.sendCmdArg(F("OverHead_A4/AN_LOW_PRESSURE_ELEC_1"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_LOW_PRESSURE_ELEC_1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_LOW_PRESSURE_ELEC_2);
    messenger.sendCmdArg(F("OverHead_A4/AN_LOW_PRESSURE_ELEC_2"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_LOW_PRESSURE_ELEC_2"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_FWD_ENTRY);
    messenger.sendCmdArg(F("OverHead_A4/AN_FWD_ENTRY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_FWD_ENTRY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_FWD_SERVICE);
    messenger.sendCmdArg(F("OverHead_A4/AN_FWD_SERVICE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_FWD_SERVICE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_LEFT_FWD_OVERWING);
    messenger.sendCmdArg(F("OverHead_A4/AN_LEFT_FWD_OVERWING"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_LEFT_FWD_OVERWING"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_RIGHT_FWD_OVERWING);
    messenger.sendCmdArg(F("OverHead_A4/AN_RIGHT_FWD_OVERWING"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_RIGHT_FWD_OVERWING"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_LEFT_AFT_OVERWING);
    messenger.sendCmdArg(F("OverHead_A4/AN_LEFT_AFT_OVERWING"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_LEFT_AFT_OVERWING"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_RIGHT_AFT_OVERWING);
    messenger.sendCmdArg(F("OverHead_A4/AN_RIGHT_AFT_OVERWING"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_RIGHT_AFT_OVERWING"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_AFT_ENTRY);
    messenger.sendCmdArg(F("OverHead_A4/AN_AFT_ENTRY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_AFT_ENTRY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_FWD_CARGO);
    messenger.sendCmdArg(F("OverHead_A4/AN_FWD_CARGO"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_FWD_CARGO"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_AFT_CARGO);
    messenger.sendCmdArg(F("OverHead_A4/AN_AFT_CARGO"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_AFT_CARGO"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_AFT_SERVICE);
    messenger.sendCmdArg(F("OverHead_A4/AN_AFT_SERVICE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_AFT_SERVICE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(AN_EQUP);
    messenger.sendCmdArg(F("OverHead_A4/AN_EQUP"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("AN_EQUP"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(WING_ANTI_ICE_SERVO);
    messenger.sendCmdArg(F("OverHead_A4/WING_ANTI_ICE_SERVO"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("WING_ANTI_ICE_SERVO"));
    messenger.sendCmdEnd();

    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(DIFF_PRESSURE_SERVO);
    // messenger.sendCmdArg(F("OverHead_A4/DIFF_PRESSURE_SERVO"));
    // messenger.sendCmdArg(F("U8"));
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("DIFF_PRESSURE_SERVO"));
    // messenger.sendCmdEnd();

    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(CABIN_ALT_SERVO);
    // messenger.sendCmdArg(F("OverHead_A4/CABIN_ALT_SERVO"));
    // messenger.sendCmdArg(F("U8"));
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("CABIN_ALT_SERVO"));
    // messenger.sendCmdEnd();

    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(CABIN_PRESSURE_SERVO);
    // messenger.sendCmdArg(F("OverHead_A4/CABIN_PRESSURE_SERVO"));
    // messenger.sendCmdArg(F("U8"));
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("CABIN_PRESSURE_SERVO"));
    // messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("SUBSCRIBE"));
    messenger.sendCmdArg(DIFF_PRESSURE_SERVO);
    messenger.sendCmdArg(F("PMDGNG3:AIR_CabinDPNeedle"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(0.01);
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("SUBSCRIBE"));
    messenger.sendCmdArg(CABIN_ALT_SERVO);
    messenger.sendCmdArg(F("PMDGNG3:AIR_CabinAltNeedle"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(100);
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("SUBSCRIBE"));
    messenger.sendCmdArg(CABIN_PRESSURE_SERVO);
    messenger.sendCmdArg(F("PMDGNG3:AIR_CabinVSNeedle"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(10);
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(CABIN_PRESSURE_SERVO_RESET);
    messenger.sendCmdArg(F("OverHead_A4/CABIN_PRESSURE_SERVO_RESET"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("CABIN_PRESSURE_SERVO_RESET"));
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
  testAnnounciatorBlink(pin3);
  testAnnounciatorBlink(pin4);
  testAnnounciatorBlink(pin5);
  testAnnounciatorBlink(pin6);
  testAnnounciatorBlink(pin7);
  testAnnounciatorBlink(pin35);
  testAnnounciatorBlink(pin36);
  testAnnounciatorBlink(pin17);
  testAnnounciatorBlink(pin18);
  testAnnounciatorBlink(pin19);
  testAnnounciatorBlink(pin20);
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
  testAnnounciatorBlink(pin41);
  testAnnounciatorBlink(pin42);
  testAnnounciatorBlink(pin43);
  testAnnounciatorBlink(pin44);
  testAnnounciatorBlink(pin45);
  testAnnounciatorBlink(pin46);
  testAnnounciatorBlink(pin47);
  testAnnounciatorBlink(pin48);
  testAnnounciatorBlink(pin49);
  testAnnounciatorBlink(pin50);
  testAnnounciatorBlink(pin51);
  testAnnounciatorBlink(pin52);
  testAnnounciatorBlink(pin53);
  testAnnounciatorBlink(pinA11);
  testAnnounciatorBlink(pinA12);
  testAnnounciatorBlink(pinA3);
  testAnnounciatorBlink(pinA4);
}
