#include <CmdMessenger.h>
#include <Encoder.h>
#include <LedControl.h>

////////////////////////////
// Constants and Globals
////////////////////////////
#define DEVICE_ADDRESS "1234:BEAD:4" // TODO: Assign unique VJOY id (Overhead uses :0 and :3)
#define DEVICE_GUID "{5318a347-9230-41aa-8162-32189b668199}"

enum {
  kRequest = 0,
  kCommand = 1,
  kEvent = 2,
  kDebug = 3,
  kSimCommand = 4,

  // === Data channels for components receiving data FROM SPAD.next ===

  // 7-Segment Displays
  K_VHF1_ACTIVE = 10,
  K_VHF1_STNDBY = 11,
  K_VHF2_ACTIVE = 12,
  K_VHF2_STNDBY = 13,

  // LED Annunciators
  K_CARGO_FIRE_EXT_FWD = 14,
  K_CARGO_FIRE_EXT_AFT = 15,
  K_CARGO_FIRE_DETECTOR_FAULT = 16,
  K_CARGO_FIRE_FWD_ARM_YELLOW = 17,
  K_CARGO_FIRE_FWD_ARM_RED = 18,
  K_CARGO_FIRE_AFT_ARM_YELLOW = 19,
  K_CARGO_FIRE_AFT_ARM_RED = 20,
  K_CARGO_FIRE_DISCHARG1 = 21,
  K_CARGO_FIRE_DISCHARG2 = 22,

  // ADD MORE DATA CHANNELS HERE (increment from 22)
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
void updateMax7219Display(LedControl display, long number);

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
void handlePotentiometer(int pin, int min, int max, const char* addresses[], int addressCount, int &lastValue);
void handlePotentiometer2(int pin, int min, int max, const char* address, int &lastValue);
