#include <CmdMessenger.h>
#include <Encoder.h>

////////////////////////////
// Constants and Globals
////////////////////////////
#define DEVICE_ADDRESS "1234:BEAD:3"  // Last digits represents the VJOY id
#define DEVICE_GUID "{f6b564aa-808a-48f9-a3ac-238832e2becb}"

enum {
  kRequest = 0,
  kCommand = 1,
  kEvent = 2,
  kDebug = 3,
  kSimCommand = 4,

  AN_WINDOWHEAT_OVERHEAT_1 = 10,
  AN_WINDOWHEAT_OVERHEAT_2 = 11,
  AN_WINDOWHEAT_OVERHEAT_3 = 12,
  AN_WINDOWHEAT_OVERHEAT_4 = 13,
  AN_WINDOWHEAT_ON_1 = 14,
  AN_WINDOWHEAT_ON_2 = 15,
  AN_WINDOWHEAT_ON_3 = 16,
  AN_WINDOWHEAT_ON_4 = 17,
  AN_CAPT_PITOT = 18,
  AN_L_ELEV_PITOT = 19,
  AN_L_ALPHA_VANE = 20,
  AN_TEMP_PROBE = 21,
  AN_FO_PITOT = 22,
  AN_R_ELEV_PITOT = 23,
  AN_R_ALPHA_VANE = 24,
  AN_AUX_PITOT = 25,
  AN_L_VALVE_OPEN = 26,
  AN_R_VALVE_OPEN = 27,
  AN_COWL_VALVE_OPEN_1 = 28,
  AN_COWL_VALVE_OPEN_2 = 29,
  AN_COWL_ANTI_ICE_1 = 30,
  AN_COWL_ANTI_ICE_2 = 31,
  AN_LOW_PRESSURE_ENG1 = 32,
  AN_LOW_PRESSURE_ENG2 = 33,
  AN_OVERHEAT_ELEC_2 = 34,
  AN_OVERHEAT_ELEC_1 = 35,
  AN_LOW_PRESSURE_ELEC_1 = 36,
  AN_LOW_PRESSURE_ELEC_2 = 37,
  AN_FWD_ENTRY = 38,
  AN_FWD_SERVICE = 39,
  AN_LEFT_FWD_OVERWING = 40,
  AN_RIGHT_FWD_OVERWING = 41,
  AN_LEFT_AFT_OVERWING = 42,
  AN_RIGHT_AFT_OVERWING = 43,
  AN_AFT_ENTRY = 44,
  AN_FWD_CARGO = 45,
  AN_AFT_CARGO = 46,
  AN_AFT_SERVICE = 47,
  AN_EQUP = 48,

  WING_ANTI_ICE_SERVO = 49,
  DIFF_PRESSURE_SERVO = 50,
  CABIN_ALT_SERVO = 51,
  CABIN_PRESSURE_SERVO = 52,
  CABIN_PRESSURE_SERVO_RESET = 53,

};

typedef struct {
    double in_min;
    double in_max;
    double out_min;
    double out_max;
} ServoSection;

inline CmdMessenger messenger(Serial);

////////////////////////////
// Forward Declarations
////////////////////////////

void sendButtonState(const char* buttonId, const char* action);
void testAnnounciatorBlink(int pin);
double mapCustomSections(double pos, ServoSection* sections, int num_sections);
double percentageDifference(double num1, double num2);

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

// Rotary Encoders
void handleDualEncoderRotary(Encoder& encoderObjectInner, Encoder& encoderObjectOuter, long& newPosition1Inner, long& oldPosition1Inner, long& newPosition1Outer, long& oldPosition1Outer, const char* buttonId1, const char* buttonId2, const char* buttonId3, const char* buttonId4, bool fastTuneSupport);
void handleRotaryEncoder(int clkPin, int dtPin, int& lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoder2(int clkPin, int dtPin, int& lastState, const char* buttonIdCW, const char* buttonIdCCW);
void handleRotaryEncoderWithButton(int clkPin, int dtPin, int& lastStateCLK, const char* buttonIdCW, const char* buttonIdCCW);

// Potentiometers
void handlePotentiometer(int pin, int min, int max, const char* addresses[], int addressCount, int& lastValue);