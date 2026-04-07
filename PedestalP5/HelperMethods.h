#include <CmdMessenger.h>
#include <Encoder.h>
#include <LedControl.h>

////////////////////////////
// Constants and Globals
////////////////////////////
#define DEVICE_ADDRESS "1234:BEAD:2" // Same VJOY as P1/P2/P3/P4
#define DEVICE_GUID "{3e38fa2c-a899-4d33-879d-b631e22b059a}"

enum {
  kRequest = 0,
  kCommand = 1,
  kEvent = 2,
  kDebug = 3,
  kSimCommand = 4,

  // === Data channels for components receiving data FROM SPAD.next ===

  // LEDs
  K_ENG1_OVERHEAT = 10,
  K_DISCH1_LED = 11,
  K_WHEEL_WELL = 12,
  K_FAULT = 13,
  K_APU_DET_INOP = 14,
  K_APU_BOTTLE_DISCH = 15,
  K_DISCH_APU_LED = 16,
  K_DISCH_APU_HANDLE_LED = 17,
  K_ENG2_OVERHEAT = 18,
  K_DISCH2_LED = 19,
  K_L_BOTTLE_DISCH = 20,
  K_R_BOTTLE_DISCH = 21,
  K_EXT_TEST_L = 22,
  K_EXT_TEST_R = 23,
  K_EXT_TEST_APU = 24,

  // ADD MORE DATA CHANNELS HERE (increment from 24)
};

inline CmdMessenger messenger(Serial);
inline bool isSimConnected = false;


////////////////////////////
// Forward Declarations
////////////////////////////

void sendButtonState(const char* buttonId, const char* action);
void testAnnounciatorBlink(int pin);

// General
void attachCommandCallbacks();
void onIdentifyRequest();
void updateLedValue(int pin, int value, int& lastPinValue);
void updateMax7219Display(LedControl display, long number, int decimalPlaces = 0);
void showNumberOnDisplay(LedControl &disp, const char* value, int deviceDigits);

// Buttons
void handleMomentaryButton(int buttonPin, int &lastState, const char* buttonId);
void handleOnOffSwitch(int switchPin, int& lastState, const char* buttonId);
void handleOnOffOnSwitch(int switchPin1, int switchPin2, int& lastState1, int& lastState2, const char* buttonId1, const char* buttonId2);

// Rotary Switches
void handle2PositionRotary(int pin1, int pin2, int &lastState, const char* buttonId1, const char* buttonId2);
void handle3PositionRotary(int pin1, int pin2, int pin3, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3);
void handle4PositionRotary(int pin1, int pin2, int pin3, int pin4, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, int &candidateState, unsigned long &stateStartTime);
void handle5PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5);
void handle6PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6);
void handle7PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7);
void handle8PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8, int &lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7, const char* buttonId8);

// Rotary Encoders
void handleDualEncoderRotary(Encoder& encoderObjectInner, Encoder& encoderObjectOuter, long& newPosition1Inner, long& oldPosition1Inner, long& newPosition1Outer, long& oldPosition1Outer, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, bool fastTuneSupport);
void handleRotaryEncoder(int clkPin, int dtPin, int& lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoder2(int clkPin, int dtPin, int &lastState, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoderWithButton(int clkPin, int dtPin, int &lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);

// Potentiometers
void handlePotentiometer(int pin, int min, int max, const char* addresses[], int addressCount, int &lastValue);
void handlePotentiometer2(int pin, int min, int max, const char* address, int &lastValue);
