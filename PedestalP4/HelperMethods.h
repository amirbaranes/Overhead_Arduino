#include <CmdMessenger.h>
#include <Encoder.h>
#include <LedControl.h>

////////////////////////////
// Constants and Globals
////////////////////////////
#define DEVICE_ADDRESS "1234:BEAD:4" // Same VJOY as P1/P2/P3
#define DEVICE_GUID "{5788b476-f491-4fdc-af2f-bc3372768c76}"

enum {
  kRequest = 0,
  kCommand = 1,
  kEvent = 2,
  kDebug = 3,
  kSimCommand = 4,

  // === Data channels for components receiving data FROM SPAD.next ===

  // MicSelector left LEDs
  K_MIC_SEL_LEFT_1_LED = 10,
  K_MIC_SEL_LEFT_2_LED = 11,
  K_MIC_SEL_LEFT_3_LED = 12,
  K_MIC_SEL_LEFT_4_LED = 13,
  K_MIC_SEL_LEFT_5_LED = 14,
  K_MIC_SEL_LEFT_6_LED = 15,
  K_MIC_SEL_LEFT_7_LED = 16,
  K_MIC_SEL_LEFT_8_LED = 17,

  // Audio panel LEDs
  K_AN_VHF1 = 18,
  K_AN_VHF2 = 19,
  K_AN_VHF3 = 20,
  K_AN_HF1 = 21,
  K_AN_HF2 = 22,
  K_AN_FLT = 23,
  K_AN_SVO = 24,
  K_AN_PA = 25,
  K_AN_NAV1 = 26,
  K_AN_NAV2 = 27,
  K_AN_ADF1 = 28,
  K_AN_ADF2 = 29,
  K_AN_MKR = 30,
  K_AN_SPKR = 31,

  // ADD MORE DATA CHANNELS HERE (increment from 31)
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
