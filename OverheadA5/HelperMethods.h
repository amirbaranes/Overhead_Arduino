#include <CmdMessenger.h>
#include <Encoder.h>

////////////////////////////
// Constants and Globals
////////////////////////////
#define DEVICE_ADDRESS "1234:BEAD:0"  // Last digits represents the VJOY id
#define DEVICE_GUID "{1ebdbf6a-7c20-4db8-807e-b21e5a74d963}"


enum {
  kRequest = 0,
  kCommand = 1,
  kEvent = 2,
  kSimCommand = 4,

  AN_ZONE_TEMP_1 = 11,
  AN_ZONE_TEMP_2 = 12,
  AN_ZONE_TEMP_3 = 13,
  AN_DUAL_BLEED = 14,
  AN_RAM_DOOR_FULL_OPEN_1 = 15,
  AN_RAM_DOOR_FULL_OPEN_2 = 16,
  AN_AUTO_FAIL = 17,
  AN_OFF_SCHED_DESCENT = 18,
  AN_ALTN = 19,
  AN_MANUAL = 20,
  AN_PACK_LEFT = 21,
  AN_WING_BODY_OVERHEAT_L = 22,
  AN_BLEED_TRIP_OFF_L = 23,
  AN_PACK_RIGHT = 24,
  AN_WING_BODY_OVERHEAT_R = 25,
  AN_BLEED_TRIP_OFF_R = 26,

  // 7-Segment Displays
  FLT_ALT_DISPLAY = 27,
  LAND_ALT_DISPLAY = 28,

  // Servo Components
  AIR_TEMP_SERVO = 29,
  DECT_PRESS_1_SERVO = 30,
  DECT_PRESS_2_SERVO = 31,
  MANUAL_ALT_VALVE_SERVO = 32
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

// Buttons
void handleMomentaryButton(int buttonPin, int& lastState, const char* buttonId);
void handleOnOffSwitch(int switchPin, int& lastState, const char* buttonId);
void handleOnOffOnSwitch(int switchPin1, int switchPin2, int& lastState1, int& lastState2, const char* buttonId1, const char* buttonId2);
void updateLedValue(int pin, int value, int& lastPinValue);

// Rotary Switches
void handle2PositionRotary(int pin1, int& lastState, const char* buttonId1, const char* buttonId2);
void handle3PositionRotary(int pin1, int pin2, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3);
void handle4PositionRotary(int pin1, int pin2, int pin3, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, int& candidateState, unsigned long& stateStartTime);
void handle5PositionRotary(int pin1, int pin2, int pin3, int pin4, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5);
void handle6PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6);
void handle7PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7);
void handle8PositionRotary(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int& lastState, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, const char* buttonId5, const char* buttonId6, const char* buttonId7, const char* buttonId8);

// Rotary Encoders
void handleDualEncoderRotary(Encoder& encoderObjectInner, Encoder& encoderObjectOuter, long& newPosition1Inner, long& oldPosition1Inner, long& newPosition1Outer, long& oldPosition1Outer, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, bool fastTuneSupport);
void handleRotaryEncoder(int clkPin, int dtPin, int& lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoder2(int clkPin, int dtPin, int& lastState, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoderWithButton(int clkPin, int dtPin, int& lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);

// Potentiometers
void handlePotentiometer(int pin, int min, int max, const char* addresses[], int addressCount, int& lastValue);
void handlePotentiometer2(
  int pin,    
  int min, // 290
  int max, // 0    
  const char* address,     
  int &lastValue       
);
void handlePotentiometerTempSelector(int pin, int& lastValue);