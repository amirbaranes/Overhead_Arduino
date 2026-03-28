#include <CmdMessenger.h>
#include <Encoder.h>

////////////////////////////
// Constants and Globals
////////////////////////////
#define DEVICE_ADDRESS "1234:BEAD:3"  // Last digits represents the VJOY id
#define DEVICE_GUID "{65c4afa4-b344-408c-974c-69dc706fc51e}"

enum {
  kRequest = 0,
  kCommand = 1,
  kEvent = 2,
  kDebug = 3,
  kSimCommand = 4,

  EGTServo = 10,
  AN_GRND_PWR_AVAILABLE = 11,
  AN_TRANSER_BUS_OFF_1 = 12,
  AN_TRANSER_BUS_OFF_2 = 13,
  AN_SOURCE_OFF_1 = 14,
  AN_SOURCE_OFF_2 = 15,
  AN_GEN_OFF_BUS_1 = 16,
  AN_GEN_OFF_BUS_2 = 17,
  AN_APU_GEN_OFF_BUS = 18,
  AN_MAIN_T = 19,
  AN_LOW_OIL_PRESS = 20,
  AN_FAULT = 21,
  AN_OVERSPEED = 22,
  AN_LAVATORY_SMOKE = 23,
  AN_EQUIP_COOLING_SUPPLY = 24,
  AN_EQUIP_COOLING_EXHAUST = 25,
  AN_EMERGENCY_LIGHTS = 26,
  AN_GRD_CALL_ALTN = 27,
  ENGINGE_START_L_SERVO = 28,
  ENGINGE_START_R_SERVO = 29,
};

inline CmdMessenger messenger(Serial);

////////////////////////////
// Forward Declarations
////////////////////////////

void sendButtonState(const char* buttonId, const char* action);
void testAnnounciatorBlink(int pin);

// General
void attachCommandCallbacks();
void onIdentifyRequest();
void updateLedValue(int pin, int value, int& lastPinValue);

// Buttons
void handleMomentaryButton(int buttonPin, int& lastState, const char* buttonId);
void handleOnOffSwitch(int switchPin, int& lastState, const char* buttonId);
void handleOnOffOnSwitch(int switchPin1, int switchPin2, int& lastState1, int& lastState2, const char* buttonId1, const char* buttonId2);

// Rotary Switches
void handle2PositionRotary(int pin1, int& lastState, const char* buttonId1, const char* buttonId2);
void handle3PositionRotary(int pin1, int pin2, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3);
void handle4PositionRotary(int pin1, int pin2, int pin3, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, int& candidateState, unsigned long& stateStartTime);
void handle5PositionRotary(int pin1, int pin2, int pin3, int pin4, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5);
void handle6PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6);
void handle7PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7);
void handle8PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7, const char* buttonId8);
void handle4PositionRotary2(int pin1, int pin2, int pin3, int pin4, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, int& candidateState, unsigned long& stateStartTime);

// Rotary Encoders
void handleDualEncoderRotary(Encoder& encoderObjectInner, Encoder& encoderObjectOuter, long& newPosition1Inner, long& oldPosition1Inner, long& newPosition1Outer, long& oldPosition1Outer, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, bool fastTuneSupport);
void handleRotaryEncoder(int clkPin, int dtPin, int& lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoder2(int clkPin, int dtPin, int& lastState, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoderWithButton(int clkPin, int dtPin, int& lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);

// Potentiometers
void handlePotentiometer(int pin, int min, int max, const char* addresses[], int addressCount, int& lastValue);