////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 44 - 74 (Pedestal P4 scope)
// Since Pedestal uses its own DEVICE_ADDRESS/VJOY, button IDs are independent from Overhead


//Verified
// MicSelector left 1 led  --LED
const int pin2 = 2;
int lastStatePin2 = HIGH;

//Verified
// MicSelector left 2 led  --LED
const int pin3 = 3;
int lastStatePin3 = HIGH;

//Verified
// MicSelector left 3 led  --LED
const int pin4 = 4;
int lastStatePin4 = HIGH;

//Verified
// MicSelector left 4 led  --LED
const int pin5 = 5;
int lastStatePin5 = HIGH;

//Verified
// MicSelector left 5 led  --LED
const int pin6 = 6;
int lastStatePin6 = HIGH;

//Verified
// MicSelector left 6 led  --LED
const int pin7 = 7;
int lastStatePin7 = HIGH;

//Verified
// MicSelector left 7 led  --LED
const int pin8 = 8;
int lastStatePin8 = HIGH;

//Verified
// MicSelector left 8 led  --LED
const int pin9 = 9;
int lastStatePin9 = HIGH;

//Verified
// MicSelector left 1  - Momentary Button (push button)
const int pin10 = 10;
int lastStatePin10 = HIGH;
const char* buttonId10 = "BUTTON_44";

//Verified
// MicSelector left 2  - Momentary Button (push button)
const int pin11 = 11;
int lastStatePin11 = HIGH;
const char* buttonId11 = "BUTTON_45";

//Verified
// MicSelector left 3  - Momentary Button (push button)
const int pin12 = 12;
int lastStatePin12 = HIGH;
const char* buttonId12 = "BUTTON_46";

//Verified
// MicSelector left 4  - Momentary Button (push button)
const int pin13 = 13;
int lastStatePin13 = HIGH;
const char* buttonId13 = "BUTTON_47";

//Verified
// MicSelector left 5  - Momentary Button (push button)
const int pin14 = 14;
int lastStatePin14 = HIGH;
const char* buttonId14 = "BUTTON_48";

//Verified
// MicSelector left 6  - Momentary Button (push button)
const int pin15 = 15;
int lastStatePin15 = HIGH;
const char* buttonId15 = "BUTTON_49";

//Verified
// MicSelector left 7  - Momentary Button (push button)
const int pin16 = 16;
int lastStatePin16 = HIGH;
const char* buttonId16 = "BUTTON_50";

//Verified
// MicSelector left 8  - Momentary Button (push button)
const int pin17 = 17;
int lastStatePin17 = HIGH;
const char* buttonId17 = "BUTTON_51";

//Verified
// R/T  - Momentary Button (push button)
const int pin18 = 18;
int lastStatePin18 = HIGH;
const char* buttonId18 = "BUTTON_52";

//Verified
// I/C  - Switch ON OFF
const int pin19 = 19;
int lastStatePin19 = HIGH;
const char* buttonId19 = "BUTTON_53";

//Verified
// MASK  - Switch ON OFF
const int pin20 = 20;
int lastStatePin20 = HIGH;
const char* buttonId20 = "BUTTON_54";

//Verified
// BOOK  - Switch ON OFF
const int pin21 = 21;
int lastStatePin21 = HIGH;
const char* buttonId21 = "BUTTON_55";

//Verified
// V/B/R  - 3 POS ROTARY
const int pin22 = 22; // V
const int pin23 = 23; // B
const int pin24 = 24; // R
int vbrLastState = HIGH;
const char* buttonId22 = "BUTTON_56";
const char* buttonId23 = "BUTTON_57";
const char* buttonId24 = "BUTTON_58";

//Verified
// ALT  - Switch ON OFF
const int pin25 = 25;
int lastStatePin25 = HIGH;
const char* buttonId25 = "BUTTON_59";

//Verified
// NORM  - Switch ON OFF
const int pin26 = 26;
int lastStatePin26 = HIGH;
const char* buttonId26 = "BUTTON_60";


// VHF1  --LED
const int pin27 = 27;
int lastStatePin27 = HIGH;

// VHF2  --LED
const int pin28 = 28;
int lastStatePin28 = HIGH;

// VHF3  --LED
const int pin29 = 29;
int lastStatePin29 = HIGH;

// HF1  --LED
const int pin30 = 30;
int lastStatePin30 = HIGH;

// HF2  --LED
const int pin31 = 31;
int lastStatePin31 = HIGH;

// FLT  --LED
const int pin32 = 32;
int lastStatePin32 = HIGH;

// SVO  --LED
const int pin33 = 33;
int lastStatePin33 = HIGH;

// PA  --LED
const int pin34 = 34;
int lastStatePin34 = HIGH;

// NAV1  --LED
const int pin35 = 35;
int lastStatePin35 = HIGH;

// NAV2  --LED
const int pin36 = 36;
int lastStatePin36 = HIGH;

// ADF1  --LED
const int pin37 = 37;
int lastStatePin37 = HIGH;

// ADF2  --LED
const int pin38 = 38;
int lastStatePin38 = HIGH;

// MKR  --LED
const int pin39 = 39;
int lastStatePin39 = HIGH;

// SPKR  --LED
const int pin40 = 40;
int lastStatePin40 = HIGH;

//Verified
// VHF1  - Switch ON OFF
const int pin41 = 41;
int lastStatePin41 = HIGH;
const char* buttonId41 = "BUTTON_61";

//Verified
// VHF2  - Switch ON OFF
const int pin42 = 42;
int lastStatePin42 = HIGH;
const char* buttonId42 = "BUTTON_62";

//Verified
// VHF3  - Switch ON OFF
const int pin43 = 43;
int lastStatePin43 = HIGH;
const char* buttonId43 = "BUTTON_63";

//Verified
// HF1  - Switch ON OFF
const int pin44 = 44;
int lastStatePin44 = HIGH;
const char* buttonId44 = "BUTTON_64";

//Verified
// HF2  - Switch ON OFF
const int pin45 = 45;
int lastStatePin45 = HIGH;
const char* buttonId45 = "BUTTON_65";

//Verified
// FLT  - Switch ON OFF
const int pin46 = 46;
int lastStatePin46 = HIGH;
const char* buttonId46 = "BUTTON_66";

//Verified
// SVO  - Switch ON OFF
const int pin47 = 47;
int lastStatePin47 = HIGH;
const char* buttonId47 = "BUTTON_67";

//Verified
// PA  - Switch ON OFF
const int pin48 = 48;
int lastStatePin48 = HIGH;
const char* buttonId48 = "BUTTON_68";

//Verified
// NAV1  - Switch ON OFF
const int pin49 = 49;
int lastStatePin49 = HIGH;
const char* buttonId49 = "BUTTON_69";

//Verified
// NAV2  - Switch ON OFF
const int pin50 = 50;
int lastStatePin50 = HIGH;
const char* buttonId50 = "BUTTON_70";

//Verified
// ADF1  - Switch ON OFF
const int pin51 = 51;
int lastStatePin51 = HIGH;
const char* buttonId51 = "BUTTON_71";

//Verified
// ADF2  - Switch ON OFF
const int pin52 = 52;
int lastStatePin52 = HIGH;
const char* buttonId52 = "BUTTON_72";

//Verified
// MKR  - Switch ON OFF
const int pin53 = 53;
int lastStatePin53 = HIGH;
const char* buttonId53 = "BUTTON_73";

//Verified
// SPKR  - Switch ON OFF
const int pinA15 = A15;
int lastStatePinA15 = HIGH;
const char* buttonIdA15 = "BUTTON_74";
