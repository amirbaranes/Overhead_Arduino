#include <CmdMessenger.h>
#include <Encoder.h>
#include "HelperMethods.h"
#include "ComponentDefenition.h"
#include <LedControl.h>
#include <Servo.h>
#include <NoDelay.h>


const unsigned long BigDelayInterval = 50;   // in ms
const unsigned long SmallDelayInterval = 1;  // in ms
unsigned long lastBigDelayTime = 0;
unsigned long lastSmallDelayTime = 0;

bool demoMode = false;
int screenIntensity = 0;

noDelay startupDelay(1000);
bool startupDone = false;


// 7-Segment Displays (MAX7219 / LedControl)
LedControl vhf3Active = LedControl(pin2, pin3, pin4, 1); // vhf3 active
LedControl vhf3Stndby = LedControl(pin5, pin6, pin7, 1); // vhf3 stndby
LedControl adf1Active = LedControl(pin27, pin28, pin29, 1); // adf1 stby
LedControl adf1Stndby = LedControl(pin30, pin31, pin32, 1); // adf1 active

const int displayBrightness = 1;
noDelay displayDemo(500);

// ADF1 Dual Encoder - objects declared before loop()
Encoder adf1EncoderInner(pin35, pin34);
Encoder adf1EncoderOuter(pin36, pin37);
long adf1OldPositionInner = -9999;
long adf1OldPositionOuter = -9999;
long adf1NewPositionInner = 0;
long adf1NewPositionOuter = 0;

// Servo
Servo aileronServo;
int aileronServoAngle = 0;
int aileronServoMiddleAngle = 68;
int aileronServoMinimumAngle = 0;
int aileronServoMaximumAngle = 130;
noDelay aileronServoDemo(1000);
int aileronServoDemoCurrentValue = aileronServoMinimumAngle;


////////////////////////////
// Setup
////////////////////////////

void setup() {
  Serial.begin(115200);

  // ADF 1 button
  pinMode(pin33, INPUT_PULLUP);  // ADF 1 TFR

  // ADF1 dual encoder - pins handled by Encoder library

  // ADF1 digit button
  pinMode(pin38, INPUT_PULLUP);

  // ADF / ANT / Tone switches
  pinMode(pin39, INPUT_PULLUP);  // ADF
  pinMode(pin40, INPUT_PULLUP);  // ANT
  pinMode(pin41, INPUT_PULLUP);  // Tone OFF
  pinMode(pin42, INPUT_PULLUP);  // Tone ON

  // AILERON buttons
  pinMode(pin43, INPUT_PULLUP);  // wing Left
  pinMode(pin44, INPUT_PULLUP);  // wing right
  pinMode(pin45, INPUT_PULLUP);  // wing Left 2
  pinMode(pin46, INPUT_PULLUP);  // wing right 2
  pinMode(pin47, INPUT_PULLUP);  // nose left
  pinMode(pin48, INPUT_PULLUP);  // nose right

  // AILERON servo - handled by Servo.attach()

  // Stab trim switches
  pinMode(pin50, INPUT_PULLUP);  // ovrd
  pinMode(pin51, INPUT_PULLUP);  // norm

  // Cabin door LED
  pinMode(pin52, OUTPUT);

  // MicSelector right LEDs (OUTPUT)
  pinMode(pin18, OUTPUT);
  pinMode(pin19, OUTPUT);
  pinMode(pin20, OUTPUT);
  pinMode(pin21, OUTPUT);
  pinMode(pin22, OUTPUT);
  pinMode(pin23, OUTPUT);
  pinMode(pin24, OUTPUT);
  pinMode(pin25, OUTPUT);

  // MicSelector right buttons
  pinMode(pinA2, INPUT_PULLUP);
  pinMode(pinA3, INPUT_PULLUP);
  pinMode(pinA4, INPUT_PULLUP);
  pinMode(pinA5, INPUT_PULLUP);
  pinMode(pinA6, INPUT_PULLUP);
  pinMode(pinA7, INPUT_PULLUP);
  pinMode(pinA8, INPUT_PULLUP);
  pinMode(pinA1, INPUT_PULLUP);

   resetServos();
   initializeScreens();
   clearLeds();

  attachCommandCallbacks();

 // initializeServos();
}

void resetServos() {
  aileronServo.attach(pin49);
 aileronServo.write(0);
  // delay(1000);
}

void initializeServos() {
  aileronServo.write(aileronServoMiddleAngle);
  //delay(500);
}

void initializeScreens() {
  vhf3Active.shutdown(0, false);
  vhf3Active.setIntensity(0, screenIntensity);
  vhf3Active.clearDisplay(0);

  vhf3Stndby.shutdown(0, false);
  vhf3Stndby.setIntensity(0, screenIntensity);
  vhf3Stndby.clearDisplay(0);

  adf1Active.shutdown(0, false);
  adf1Active.setIntensity(0, screenIntensity);
  adf1Active.clearDisplay(0);

  adf1Stndby.shutdown(0, false);
  adf1Stndby.setIntensity(0, screenIntensity);
  adf1Stndby.clearDisplay(0);
}

void clearLeds() {
  updateLedValue(pin52, 0, lastStatePin52);  // Cabin door led

  // MicSelector right LEDs
  updateLedValue(pin18, 0, lastStatePin18);
  updateLedValue(pin19, 0, lastStatePin19);
  updateLedValue(pin20, 0, lastStatePin20);
  updateLedValue(pin21, 0, lastStatePin21);
  updateLedValue(pin22, 0, lastStatePin22);
  updateLedValue(pin23, 0, lastStatePin23);
  updateLedValue(pin24, 0, lastStatePin24);
  updateLedValue(pin25, 0, lastStatePin25);
}

////////////////////////////
// Loop
////////////////////////////

void onStartupComplete() {
  // TODO: add startup logic here
  aileronServo.write(0);
}

int adftest = 0;

void loop() {
  messenger.feedinSerialData();

  if (!startupDone && startupDelay.update()) {
    startupDone = true;
    onStartupComplete();
  }

    // handleDualEncoderRotaryV2(adf1EncoderInner, adf1EncoderOuter,
    //   adf1OldPositionInner, adf1OldPositionOuter,
    //   buttonId34, buttonId35, buttonId36, buttonId37);  // ADF1 dual encoder V2

    handleDualEncoderRotary(adf1EncoderInner, adf1EncoderOuter,
      adf1NewPositionInner, adf1OldPositionInner, adf1NewPositionOuter, adf1OldPositionOuter,
      buttonId34, buttonId35, buttonId36, buttonId37, false);  // ADF1 dual encoder V1

    // handleRotaryEncoderWithButton(pin37, pin36, adftest, buttonId34, buttonId35);
    // // int i = digitalRead(pin35);
    // // Serial.println(i);


  if (demoMode == true) {
    testDisplay();
    onAileronServoDemo();
    onAnnounciatorsDemo();
  }

  unsigned long currentTime = millis();

  if (currentTime - lastBigDelayTime >= BigDelayInterval) {
    lastBigDelayTime = currentTime;

    // ADF 1
    handleMomentaryButton(pin33, lastStatePin33, buttonId33);  // ADF 1 TFR

    handleMomentaryButton(pin38, lastStatePin38, buttonId38);  // ADF1 digit button

    // ADF / ANT / Tone switches
    handleOnOffSwitch(pin39, lastStatePin39, buttonId39);  // ADF
    handleOnOffSwitch(pin40, lastStatePin40, buttonId40);  // ANT
    handleOnOffSwitch(pin41, lastStatePin41, buttonId41);  // Tone OFF
    handleOnOffSwitch(pin42, lastStatePin42, buttonId42);  // Tone ON

    // AILERON buttons
    handleMomentaryButton(pin43, lastStatePin43, buttonId43);  // wing Left
    handleMomentaryButton(pin44, lastStatePin44, buttonId44);  // wing right
    handleMomentaryButton(pin45, lastStatePin45, buttonId45);  // wing Left 2
    handleMomentaryButton(pin46, lastStatePin46, buttonId46);  // wing right 2
    handleMomentaryButton(pin47, lastStatePin47, buttonId47);  // nose left
    handleMomentaryButton(pin48, lastStatePin48, buttonId48);  // nose right

    // Stab trim switches
    handleOnOffSwitch(pin50, lastStatePin50, buttonId50);  // ovrd
    handleOnOffSwitch(pin51, lastStatePin51, buttonId51);  // norm

    // MicSelector right buttons
    handleMomentaryButton(pinA2, lastStatePinA2, buttonIdA2);  // MicSelector right 1
    handleMomentaryButton(pinA3, lastStatePinA3, buttonIdA3);  // MicSelector right 2
    handleMomentaryButton(pinA4, lastStatePinA4, buttonIdA4);  // MicSelector right 3
    handleMomentaryButton(pinA5, lastStatePinA5, buttonIdA5);  // MicSelector right 4
    handleMomentaryButton(pinA6, lastStatePinA6, buttonIdA6);  // MicSelector right 5
    handleMomentaryButton(pinA7, lastStatePinA7, buttonIdA7);  // MicSelector right 6
    handleMomentaryButton(pinA8, lastStatePinA8, buttonIdA8);  // MicSelector right 7
    handleMomentaryButton(pinA1, lastStatePinA9, buttonIdA9);  // MicSelector right 8
  }

  if (currentTime - lastSmallDelayTime >= SmallDelayInterval) {
    lastSmallDelayTime = currentTime;

    handlePotentiometer2(pinA0, pinA0PotMin, pinA0PotMax, pinA0PotAddress, pinA0PotLastVal);  // Flood Bright
  }
}


////////////////////////////
// Demo
////////////////////////////

void testDisplay() {
  if (displayDemo.update()) {
   // Generate random VHF frequencies xx.xxx (drop leading 1 from 1xx.xxx)
    char vhfBuf[10];
    sprintf(vhfBuf, "%d.%03d", random(18, 37), random(0, 1000));
    showNumberOnDisplay(vhf3Active, vhfBuf, 5);

    sprintf(vhfBuf, "%d.%03d", random(18, 37), random(0, 1000));
    showNumberOnDisplay(vhf3Stndby, vhfBuf, 5);

    // Generate random ADF frequencies (190 - 1799 kHz, no decimal)
    char adfBuf[6];
    sprintf(adfBuf, "%d", random(190, 1800));
    showNumberOnDisplay(adf1Active, adfBuf, 5);

    sprintf(adfBuf, "%d", random(190, 1800));
    showNumberOnDisplay(adf1Stndby, adfBuf, 5);

//         vhf3Active.setDigit(0, 0, 1, false);
//     vhf3Active.setDigit(0, 1, 1, false);
//     vhf3Active.setDigit(0, 2, 1, false);

// //adf2 active
//     vhf3Stndby.setDigit(0, 0, 1, false);
//     vhf3Stndby.setDigit(0, 1, 1, false);
//     vhf3Stndby.setDigit(0, 2, 1, false);

//     adf1Active.setDigit(0, 0, 1, false);
//     adf1Active.setDigit(0, 1, 1, false);
//     adf1Active.setDigit(0, 2, 1, false);

// //adf1Stndby
//     adf1Stndby.setDigit(0, 0, 1, false);
//     adf1Stndby.setDigit(0, 1, 1, false);
//     adf1Stndby.setDigit(0, 2, 1, false);
  }
}

void onAileronServoDemo() {
  if (aileronServoDemo.update()) {
    if (aileronServoDemoCurrentValue == aileronServoMaximumAngle) {
      aileronServoDemoCurrentValue = aileronServoMinimumAngle;
    }
    aileronServo.write(aileronServoDemoCurrentValue);
    aileronServoDemoCurrentValue++;
  }
}

void onAnnounciatorsDemo() {
  testAnnounciatorBlink(pin52);  // Cabin door led

  // MicSelector right LEDs
  testAnnounciatorBlink(pin18);
  testAnnounciatorBlink(pin19);
  testAnnounciatorBlink(pin20);
  testAnnounciatorBlink(pin21);
  testAnnounciatorBlink(pin22);
  testAnnounciatorBlink(pin23);
  testAnnounciatorBlink(pin24);
  testAnnounciatorBlink(pin25);
}


////////////////////////////
// Messenger Callbacks
////////////////////////////

void onUnknownCommand() {}

void onSimState() {
  int val = messenger.readInt32Arg();
  isSimConnected = val == 1;

  //aileronServo.write(0);
}

// Display callbacks
void onVhf3ActiveChange() {
  double val = messenger.readDoubleArg();
  char buf[10];
  dtostrf(val, 7, 3, buf);
  showNumberOnDisplay(vhf3Active, buf + 1, 5);
}

void onVhf3StndbyChange() {
  double val = messenger.readDoubleArg();
  char buf[10];
  dtostrf(val, 7, 3, buf);
  showNumberOnDisplay(vhf3Stndby, buf + 1, 5);
}

void showAdfDisplay(LedControl &disp, const char* value) {
  int d[8];
  int count = 0;
  int dpPos = -1;
  for (int i = 0; value[i]; i++) {
    if (value[i] == '.') dpPos = count - 1;
    else if (value[i] >= '0' && value[i] <= '9') d[count++] = value[i] - '0';
  }
  for (int pos = 0; pos < 5; pos++) {
    if (pos < count) {
      disp.setDigit(0, pos, d[pos], pos == dpPos);
    } else {
      disp.setChar(0, pos, ' ', false);
    }
  }
}

void onAdf1ActiveChange() {
  double val = messenger.readDoubleArg();
  char buf[10];
  dtostrf(val, 6, 1, buf);
  char* p = buf;
  while (*p == ' ') p++;
  showAdfDisplay(adf1Active, p);
}

void onAdf1StndbyChange() {
  long val = messenger.readInt32Arg();
  char buf[10];
  sprintf(buf, "%ld.%ld", val / 10, val % 10);
  showAdfDisplay(adf1Stndby, buf);
}

// Servo callback
void onAileronServoChange() {
  long val = messenger.readInt32Arg();
  int finalValue = map(val, -12000, 12000, aileronServoMinimumAngle, aileronServoMaximumAngle);
  finalValue = constrain(finalValue, aileronServoMinimumAngle, aileronServoMaximumAngle);
  aileronServo.write(finalValue);
}

// LED callback
void onCabinDoorLedChange() {
  int val = messenger.readInt32Arg();
  updateLedValue(pin52, val, lastStatePin52);
}

// MicSelector right LED callbacks
void onMicSelRight1LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin18, val, lastStatePin18); }
void onMicSelRight2LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin19, val, lastStatePin19); }
void onMicSelRight3LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin20, val, lastStatePin20); }
void onMicSelRight4LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin21, val, lastStatePin21); }
void onMicSelRight5LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin22, val, lastStatePin22); }
void onMicSelRight6LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin23, val, lastStatePin23); }
void onMicSelRight7LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin24, val, lastStatePin24); }
void onMicSelRight8LedChange() { int val = messenger.readInt32Arg(); updateLedValue(pin25, val, lastStatePin25); }


void attachCommandCallbacks() {
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest, onIdentifyRequest);

  // Displays
  messenger.attach(K_VHF3_ACTIVE, onVhf3ActiveChange);
  messenger.attach(K_VHF3_STNDBY, onVhf3StndbyChange);
  messenger.attach(K_ADF1_ACTIVE, onAdf1ActiveChange);
  messenger.attach(K_ADF1_STNDBY, onAdf1StndbyChange);

  // Servo
  messenger.attach(K_AILERON_SERVO, onAileronServoChange);

  // LED
  messenger.attach(K_CABIN_DOOR_LED, onCabinDoorLedChange);

  // MicSelector right LEDs
  messenger.attach(K_MIC_SEL_RIGHT_1_LED, onMicSelRight1LedChange);
  messenger.attach(K_MIC_SEL_RIGHT_2_LED, onMicSelRight2LedChange);
  messenger.attach(K_MIC_SEL_RIGHT_3_LED, onMicSelRight3LedChange);
  messenger.attach(K_MIC_SEL_RIGHT_4_LED, onMicSelRight4LedChange);
  messenger.attach(K_MIC_SEL_RIGHT_5_LED, onMicSelRight5LedChange);
  messenger.attach(K_MIC_SEL_RIGHT_6_LED, onMicSelRight6LedChange);
  messenger.attach(K_MIC_SEL_RIGHT_7_LED, onMicSelRight7LedChange);
  messenger.attach(K_MIC_SEL_RIGHT_8_LED, onMicSelRight8LedChange);
}


void onIdentifyRequest() {
  const char* request = messenger.readStringArg();

  if (strcmp(request, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F(DEVICE_GUID));
    messenger.sendCmdArg("Pedestal_P3");
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
    messenger.sendCmdArg(K_VHF3_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P3/K_VHF3_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_VHF3_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_VHF3_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P3/K_VHF3_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_VHF3_STNDBY"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_ADF1_ACTIVE);
    messenger.sendCmdArg(F("Pedestal_P3/K_ADF1_ACTIVE"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_ADF1_ACTIVE"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_ADF1_STNDBY);
    messenger.sendCmdArg(F("Pedestal_P3/K_ADF1_STNDBY"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_ADF1_STNDBY"));
    messenger.sendCmdEnd();

    // === Servo ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_AILERON_SERVO);
    messenger.sendCmdArg(F("Pedestal_P3/K_AILERON_SERVO"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_AILERON_SERVO"));
    messenger.sendCmdEnd();

    // === LED ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_CABIN_DOOR_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_CABIN_DOOR_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_CABIN_DOOR_LED"));
    messenger.sendCmdEnd();

    // === MicSelector right LEDs ===

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_RIGHT_1_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_MIC_SEL_RIGHT_1_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_RIGHT_1_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_RIGHT_2_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_MIC_SEL_RIGHT_2_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_RIGHT_2_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_RIGHT_3_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_MIC_SEL_RIGHT_3_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_RIGHT_3_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_RIGHT_4_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_MIC_SEL_RIGHT_4_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_RIGHT_4_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_RIGHT_5_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_MIC_SEL_RIGHT_5_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_RIGHT_5_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_RIGHT_6_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_MIC_SEL_RIGHT_6_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_RIGHT_6_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_RIGHT_7_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_MIC_SEL_RIGHT_7_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_RIGHT_7_LED"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg(F("ADD"));
    messenger.sendCmdArg(K_MIC_SEL_RIGHT_8_LED);
    messenger.sendCmdArg(F("Pedestal_P3/K_MIC_SEL_RIGHT_8_LED"));
    messenger.sendCmdArg(F("U8"));
    messenger.sendCmdArg(F("RW"));
    messenger.sendCmdArg(F("K_MIC_SEL_RIGHT_8_LED"));
    messenger.sendCmdEnd();

    // ADD MORE CONFIG REGISTRATIONS HERE

    delay(1000);

    messenger.sendCmdStart(kCommand);
    messenger.sendCmdArg("REFRESHDATA");
    messenger.sendCmdEnd();

    messenger.sendCmd(kRequest, "CONFIG");
  }
}
