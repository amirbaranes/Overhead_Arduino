////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 62 - 106



// GRD PWR ON   - Mom OFF Mom
const int pin29 = 29; //ON
const int pin30 = 30; // OFF
int lastStatePin29 = HIGH;
int lastStatePin30 = HIGH;
const char* buttonId29 = "BUTTON_62";
const char* buttonId30 = "BUTTON_63";

//GRD Power available  --LED
const int pin2 = 2;
int lastStatePin2 = HIGH;

// Bus trans   - ON OFF
const int pin3 = 3;
int lastStatePin3 = HIGH;
const char* buttonId3 = "BUTTON_64";

// Gen 1 - ON OFF ON
const int pin5 = 5; //ON
const int pin6 = 6; // OFF
int lastStatePin5 = HIGH;
int lastStatePin6 = HIGH;
const char* buttonId5 = "BUTTON_65";
const char* buttonId6 = "BUTTON_66";

// Gen 2 - ON OFF ON
const int pin7 = 7; //ON
const int pin8 = 8; // OFF
int lastStatePin7 = HIGH;
int lastStatePin8 = HIGH;
const char* buttonId7 = "BUTTON_67";
const char* buttonId8 = "BUTTON_68";

// APU Gen 1 - ON OFF ON
const int pin9 = 9; //ON
const int pin10 = 10; // OFF
int lastStatePin9 = HIGH;
int lastStatePin10 = HIGH;
const char* buttonId9 = "BUTTON_69";
const char* buttonId10 = "BUTTON_70";

// APU Gen 2 - ON OFF ON
const int pin11 = 11; //ON
const int pin12 = 12; // OFF
int lastStatePin11 = HIGH;
int lastStatePin12 = HIGH;
const char* buttonId11 = "BUTTON_71";
const char* buttonId12 = "BUTTON_72";

//Transfer bus off 1  --LED
const int pin13 = 13;
int lastStatePin13 = HIGH;

//Transfer bus off 2  --LED
const int pin14 = 14;
int lastStatePin14 = HIGH;

//Source off 1  --LED
const int pin15 = 15;
int lastStatePin15 = HIGH;

//Source off 2  --LED
const int pin16 = 16;
int lastStatePin16 = HIGH;

//Gen off bus 1  --LED
const int pin17 = 17;
int lastStatePin17 = HIGH;

//Gen off bus 2  --LED
const int pin18 = 18;
int lastStatePin18 = HIGH;

//Apu gen off bus  --LED
const int pin19 = 19;
int lastStatePin19 = HIGH;

//MainT  --LED
const int pin20 = 20;
int lastStatePin20 = HIGH;

//Low oil pressure  --LED
const int pin21 = 21;
int lastStatePin21 = HIGH;

//Fault  --LED
const int pin22 = 22;
int lastStatePin22 = HIGH;

//OverSpeed  --LED
const int pin23 = 23;
int lastStatePin23 = HIGH;

// EGT  - Servo
const int pin24 = 24;
int lastStatePin24 = HIGH;

// L wiper - 4 POS ROTARY
const int pin25 = 25; //PARK
const int pin26 = 26; // INT
const int pin27 = 27; // LOW
const int pin28 = 28; //HIGH
int leftWiperLastState = HIGH;
const char* buttonId25 = "BUTTON_73";
const char* buttonId26 = "BUTTON_74";
const char* buttonId27 = "BUTTON_75";
const char* buttonId28 = "BUTTON_76";
int leftWiperCandidateStateL = -1;
unsigned long leftWiperStateStartTimeL = 0;

// Circuit breaker  - Potentiometer,  not in used(replaced with // GRD PWR ON   - Mom OFF Mom)
//const int pin29 = 29;
//int lastStatePin29 = HIGH;

// Circuit breaker - panel  - Potentiometer, not in used(replaced with // GRD PWR ON   - Mom OFF Mom)
//const int pin30 = 30;
//int lastStatePin30 = HIGH;

//Lavatory smoke  --LED
const int pin31 = 31;
int lastStatePin31 = HIGH;

// Equip cooling supply - ALTN   - ON OFF
const int pin32 = 32;
int lastStatePin32 = HIGH;
const char* buttonId32 = "BUTTON_77";

// Equip cooling exhaust - ALTN   - ON OFF
const int pin33 = 33;
int lastStatePin33 = HIGH;
const char* buttonId33 = "BUTTON_78";

//Equip cooling supply - ALTN  --LED
const int pin34 = 34;
int lastStatePin34 = HIGH;

//Equip cooling exhaust - ALTN  --LED
const int pin35 = 35;
int lastStatePin35 = HIGH;

// Emergency lights - Armed - ON OFF ON
const int pin36 = 36; //ARMED
const int pin37 = 37; // On
int lastStatePin36 = HIGH;
int lastStatePin37 = HIGH;
const char* buttonId36 = "BUTTON_79";
const char* buttonId37 = "BUTTON_80";

//Emergency lights - Not armed  --LED
const int pin38 = 38;
int lastStatePin38 = HIGH;

// No smoking  - ON OFF ON
const int pin39 = 39; //AUTO
const int pin40 = 40; // ON
int lastStatePin39 = HIGH;
int lastStatePin40 = HIGH;
const char* buttonId39 = "BUTTON_81";
const char* buttonId40 = "BUTTON_82";

// Fasten Belts  - ON OFF ON
const int pin41 = 41; //AUTO
const int pin42 = 42; // ON
int lastStatePin41 = HIGH;
int lastStatePin42 = HIGH;
const char* buttonId41 = "BUTTON_83";
const char* buttonId42 = "BUTTON_84";

// Attend  - ON OFF
const int pin43 = 43;
int lastStatePin43 = HIGH;
const char* buttonId43 = "BUTTON_85";

// GRD CALL  - ON OFF
const int pin44 = 44;
int lastStatePin44 = HIGH;
const char* buttonId44 = "BUTTON_86";

//GRD CALL - ALTN  --LED
const int pin45 = 45;
int lastStatePin45 = HIGH;

// R wiper - 4 POS ROTARY
const int pin46 = 46; //PARK
const int pin47 = 47; // INT
const int pin48 = 48; // LOW
const int pin49 = 49; //HIGH
int RightWiperLastState = HIGH;
const char* buttonId46 = "BUTTON_87";
const char* buttonId47 = "BUTTON_88";
const char* buttonId48 = "BUTTON_89";
const char* buttonId49 = "BUTTON_90";
int RightWiperCandidateStateL = -1;
unsigned long RightWiperStateStartTimeL = 0;


// Engine start L  - 4 POS ROTARY
const int pinA11 = A11; //GRD
const int pinA12 = A12; // OFF
const int pinA13 = A13; // CONT
const int pinA14 = A14; //FLT
int EngineStartLLastState = HIGH;
const char* buttonIdA11 = "BUTTON_91";
const char* buttonIdA12 = "BUTTON_92";
const char* buttonIdA13 = "BUTTON_93";
const char* buttonIdA14 = "BUTTON_94";
int EngineStartLCandidateState = -1;
unsigned long EngineStartLStateStartTime = 0;


// Engine start R  - 4 POS ROTARY
const int pin50 = 50; //GRD
const int pin51 = 51; // OFF
const int pin52 = 52; // CONT
const int pin53 = 53; //FLT
int EngineStartRLastState = HIGH;
const char* buttonId50 = "BUTTON_95";
const char* buttonId51 = "BUTTON_96";
const char* buttonId52 = "BUTTON_97";
const char* buttonId53 = "BUTTON_98";
int EngineStartRCandidateState = -1;
unsigned long EngineStartRStateStartTime = 0;


// Engine start L - Servo
const int pinA1 = A1;
int lastStatePinA1 = HIGH;

// Engine start R  - Servo
const int pinA2 = A2;
int lastStatePinA2 = HIGH;

// Engine start IGN  - ON OFF ON
const int pinA3 = A3; //Left
const int pinA4 = A4; // Right
int lastStatePinA3 = HIGH;
int lastStatePinA4 = HIGH;
const char* buttonIdA3 = "BUTTON_99";
const char* buttonIdA4 = "BUTTON_100";

//LOGO  - ON OFF
const int pinA5 = A5;
int lastStatePinA5 = HIGH;
const char* buttonIdA5 = "BUTTON_101";

// Position  - ON OFF ON
const int pinA6 = A6; //Strobe
const int pinA7 = A7; // Steady
int lastStatePinA6 = HIGH;
int lastStatePinA7 = HIGH;
const char* buttonIdA6 = "BUTTON_102";
const char* buttonIdA7 = "BUTTON_103";

//Anti collision  - ON OFF
const int pinA8 = A8;
int lastStatePinA8 = HIGH;
const char* buttonIdA8 = "BUTTON_104";

//Wing  - ON OFF
const int pinA9 = A9;
int lastStatePinA9 = HIGH;
const char* buttonIdA9 = "BUTTON_105";

//Wheel  - ON OFF
const int pinA10 = A10;
int lastStatePinA10 = HIGH;
const char* buttonIdA10 = "BUTTON_106";
