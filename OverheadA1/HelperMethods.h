#include <CmdMessenger.h>
#include <Encoder.h>

////////////////////////////
// Constants and Globals
////////////////////////////
#define DEVICE_ADDRESS "1234:BEAD:3" // Last digits represents the VJOY id

#define DEVICE_GUID "{5d5299ac-b856-4086-8e2c-0f983cacf284}"

enum {
  kRequest = 0,
  kCommand = 1,
  kEvent = 2,
  kDebug = 3, 
  kSimCommand = 4,

  KStbyHydLowQuantity = 11,
  KStbyHydLowPressure = 12,
  KFltCtrlALowPressure = 13,
  KFltCtrlBLowPressure = 14,
  KYawDumperLed = 15,
  KFeelDiffPress = 16,
  KSpeedTrimFail = 17,
  KMachTrimFail = 18,
  KAutoSlatFail = 19,
  KEnvValveCloseLeft = 20,
  KEnvValveCloseRight = 21,
  KSparValveCloseLeft = 22,
  KSparValveCloseRight = 23,
  KFuelTempGaugeData = 24,
  KFilterBypassLeft = 25,
  KFilterBypassRight = 26,
  KValvueOpen = 27,
  KFuelPumpLLowPressure = 28,
  KFuelPumpRLowPressure = 29,
  KFuelPumpLAftLowPressure = 30,
  KFuelPumpRAftLowPressure = 31,
  KFuelPumpLFwdLowPressure = 32,
  KFuelPumpRFwdLowPressure = 33,
  KStbyRudOn = 34,
  KYawDumperServo = 35,
};

inline CmdMessenger messenger(Serial);
inline bool isSimConnected = false;

typedef struct {
    double in_min;
    double in_max;
    double out_min;
    double out_max;
} ServoSection;


////////////////////////////
// Forward Declarations
////////////////////////////

void sendButtonState(const char* buttonId, const char* action);
void testAnnounciatorBlink(int pin);
double mapCustomSections(double pos, ServoSection* sections, int num_sections);

// General
void attachCommandCallbacks();
void onIdentifyRequest();
void updateLedValue(int pin, int value , int& lastPinValue);

// Buttons
void handleMomentaryButton(int buttonPin, int &lastState, const char* buttonId);
void handleOnOffSwitch(int switchPin, int& lastState, const char* buttonId);
void handleOnOffOnSwitch(int switchPin1, int switchPin2, int& lastState1, int& lastState2, const char* buttonId1, const char* buttonId2);

// Rotary Switches
void handle2PositionRotary(int pin1, int &lastState, const char* buttonId1, const char* buttonId2);
void handle3PositionRotary(int pin1, int pin2, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3);
void handle4PositionRotary(int pin1, int pin2, int pin3, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, int &candidateState, unsigned long &stateStartTime);
void handle5PositionRotary(int pin1, int pin2, int pin3, int pin4, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5);
void handle6PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6);
void handle7PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7);
void handle8PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7, const char* buttonId8);

// Rotary Encoders
void handleDualEncoderRotary(Encoder& encoderObjectInner, Encoder& encoderObjectOuter, long& newPosition1Inner, long& oldPosition1Inner, long& newPosition1Outer, long& oldPosition1Outer, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, bool fastTuneSupport);
void handleRotaryEncoder(int clkPin, int dtPin, int& lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoder2(int clkPin, int dtPin, int &lastState, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoderWithButton(int clkPin, int dtPin, int &lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);

// Potentiometers
void handlePotentiometer(  int pin, int min, int max, const char* addresses[], int addressCount, int &lastValue);

// callbacks
void onUnknownCommand();
void onSimState();
void onIdentifyRequest();
void onKLvar1Change();