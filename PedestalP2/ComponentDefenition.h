////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 21 - 60 (Pedestal P2 scope)
// Since Pedestal uses its own DEVICE_ADDRESS/VJOY, button IDs are independent from Overhead


// VHF 2 Active  - 7Seg
const int pin2 = 2; // DIO
const int pin3 = 3; //CLK
const int pin4 = 4; //CS

// VHF 2 Stndby  - 7Seg
const int pin5 = 5; // DIO
const int pin6 = 6; //CLK
const int pin7 = 7; //CS

//verified
// VHF 2 TFR  - Momentary Button (push button)
const int pin8 = 8;
int lastStatePin8 = HIGH;
const char* buttonId8 = "BUTTON_21";

//verified
// VHF 2 com test  - Momentary Button (push button)
const int pin9 = 9;
int lastStatePin9 = HIGH;
const char* buttonId9 = "BUTTON_22";

//verified
// VHF 2 high digit  - Rotary Encoder
const int pin10 = 10;    // CLK (decrease)
const int pin11 = 11;    // DT (increase)
int lastStatePin10 = HIGH;
int lastStatePin11 = HIGH;
const char* buttonId10 = "BUTTON_23";   // CW
const char* buttonId11 = "BUTTON_24";   // CCW

//verified
// VHF 2 low digit  - Rotary Encoder
const int pin12 = 12;    // CLK (decrease)
const int pin13 = 13;    // DT (increase)
int lastStatePin12 = HIGH;
int lastStatePin13 = HIGH;
const char* buttonId12 = "BUTTON_25";   // CW
const char* buttonId13 = "BUTTON_26";   // CCW

// NAV 2 Active  - 7Seg
const int pin14 = 14; // DIO
const int pin15 = 15; //CLK
const int pin16 = 16; //CS

// NAV 2 Stndby  - 7Seg
const int pin17 = 17; // DIO
const int pin18 = 18; //CLK
const int pin19 = 19; //CS

//verified
// NAV 2 TFR  - Momentary Button (push button)
const int pin20 = 20;
int lastStatePin20 = HIGH;
const char* buttonId20 = "BUTTON_27";

//verified
// NAV 2 com test  - Momentary Button (push button)
const int pin21 = 21;
int lastStatePin21 = HIGH;
const char* buttonId21 = "BUTTON_28";

//verified
// NAV 2 high digit  - Rotary Encoder
const int pin22 = 22;    // CLK (decrease)
const int pin23 = 23;    // DT (increase)
int lastStatePin22 = HIGH;
int lastStatePin23 = HIGH;
const char* buttonId22 = "BUTTON_29";   // CW
const char* buttonId23 = "BUTTON_30";  // CCW

// NAV 2 low digit  - Rotary Encoder
const int pin24 = 24;    // CLK (decrease)
const int pin25 = 25;    // DT (increase)
int lastStatePin24 = HIGH;
int lastStatePin25 = HIGH;
const char* buttonId24 = "BUTTON_31";  // CW
const char* buttonId25 = "BUTTON_32";  // CCW

//verified
// XPDR mode  - 6 POS ROTARY (off/alt/xpndr/TA/TA-RA/test)
const int pin26 = 26; // off
const int pin27 = 27; // alt
const int pin28 = 28; // xpndr
const int pin29 = 29; // TA
const int pin30 = 30; // TA/RA
const int pin47 = 47; // test
int xpdrModeLastState = -1;
const char* buttonId26 = "BUTTON_33";
const char* buttonId27 = "BUTTON_34";
const char* buttonId28 = "BUTTON_35";
const char* buttonId29 = "BUTTON_36";
const char* buttonId30 = "BUTTON_37";
const char* buttonId47 = "BUTTON_38";

// XPDR display  - 7Seg
const int pin31 = 31; // DIO
const int pin32 = 32; //CLK
const int pin33 = 33; //CS


// XPDR first digit  - Rotary Encoder
const int pin34 = 34;    // CLK (decrease)
const int pin35 = 35;    // DT (increase)
int lastStatePin34 = HIGH;
int lastStatePin35 = HIGH;
const char* buttonId34 = "BUTTON_39";  // CW
const char* buttonId35 = "BUTTON_40";  // CCW

// XPDR second digit  - Rotary Encoder
const int pin36 = 36;    // CLK (decrease)
const int pin37 = 37;    // DT (increase)
int lastStatePin36 = HIGH;
int lastStatePin37 = HIGH;
const char* buttonId36 = "BUTTON_41";  // CW
const char* buttonId37 = "BUTTON_42";  // CCW

// XPDR third digit  - Rotary Encoder
const int pin38 = 38;    // CLK (decrease)
const int pin39 = 39;    // DT (increase)
int lastStatePin38 = HIGH;
int lastStatePin39 = HIGH;
const char* buttonId38 = "BUTTON_43";  // CW
const char* buttonId39 = "BUTTON_44";  // CCW

// XPDR fourth digit  - Rotary Encoder
const int pin40 = 40;    // CLK (decrease)
const int pin41 = 41;    // DT (increase)
int lastStatePin40 = HIGH;
int lastStatePin41 = HIGH;
const char* buttonId40 = "BUTTON_45";  // CW
const char* buttonId41 = "BUTTON_46";  // CCW

//verified
// XPDR 1  - Switch ON OFF
const int pin42 = 42;
int lastStatePin42 = HIGH;
const char* buttonId42 = "BUTTON_47";

//verified
// XPDR 2  - Switch ON OFF
const int pin43 = 43;
int lastStatePin43 = HIGH;
const char* buttonId43 = "BUTTON_48";

//verified
// Alt Source 1  - Switch ON OFF
const int pin44 = 44;
int lastStatePin44 = HIGH;
const char* buttonId44 = "BUTTON_49";

//verified
// Alt Source 2  - Switch ON OFF
const int pin45 = 45;
int lastStatePin45 = HIGH;
const char* buttonId45 = "BUTTON_50";

//verified
// Ident  - Momentary Button (push button)
const int pin46 = 46;
int lastStatePin46 = HIGH;
const char* buttonId46 = "BUTTON_51";

// XPDR test  --LED
const int pin48 = 48;
int lastStatePin48 = HIGH;

//verified
// SELCAL 1  - Momentary Button (push button)
const int pin49 = 49;
int lastStatePin49 = HIGH;
const char* buttonId49 = "BUTTON_52";

//verified
// SELCAL 2  - Momentary Button (push button)
const int pin50 = 50;
int lastStatePin50 = HIGH;
const char* buttonId50 = "BUTTON_53";

//verified
// SELCAL 3  - Momentary Button (push button)
const int pin51 = 51;
int lastStatePin51 = HIGH;
const char* buttonId51 = "BUTTON_54";

//verified
// SELCAL 4  - Momentary Button (push button)
const int pin52 = 52;
int lastStatePin52 = HIGH;
const char* buttonId52 = "BUTTON_55";

//verified
// SELCAL 5  - Momentary Button (push button)
const int pin53 = 53;
int lastStatePin53 = HIGH;
const char* buttonId53 = "BUTTON_56";

// SELCAL 1 led  --LED
const int pinA1 = A1;
int lastStatePinA1 = HIGH;

// SELCAL 2 led  --LED
const int pinA2 = A2;
int lastStatePinA2 = HIGH;

// SELCAL 3 led  --LED
const int pinA3 = A3;
int lastStatePinA3 = HIGH;

// SELCAL 4 led  --LED
const int pinA4 = A4;
int lastStatePinA4 = HIGH;

// SELCAL 5 led  --LED
const int pinA5 = A7;
int lastStatePinA5 = HIGH;
