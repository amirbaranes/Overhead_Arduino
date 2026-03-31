////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 110 - 132 (Pedestal P5 scope)
// 737 Fire Panel


// OVHT DET 1 A  - Switch ON OFF
const int pin2 = 2;
int lastStatePin2 = HIGH;
const char* buttonId2 = "BUTTON_110";

// OVHT DET 1 B  - Switch ON OFF
const int pin3 = 3;
int lastStatePin3 = HIGH;
const char* buttonId3 = "BUTTON_111";

// Eng1 overheat  --LED
const int pin4 = 4;
int lastStatePin4 = HIGH;

// Fault inop  - Momentary Button (push button)
const int pin5 = 5;
int lastStatePin5 = HIGH;
const char* buttonId5 = "BUTTON_112";

// Ovht fire  - Momentary Button (push button)
const int pin6 = 6;
int lastStatePin6 = HIGH;
const char* buttonId6 = "BUTTON_113";

// DISCH1  --LED
const int pin7 = 7;
int lastStatePin7 = HIGH;

// DISCH1  - 3 POS ROTARY (L/R/N)
const int pin8 = 8;   // L
const int pin9 = 9;   // R
const int pin10 = 10; // N
int disch1RotaryLastState = HIGH;
const char* buttonId8 = "BUTTON_114";
const char* buttonId9 = "BUTTON_115";
const char* buttonId10 = "BUTTON_116";

// DISCH1 Pull  - Switch ON OFF
const int pin11 = 11;
int lastStatePin11 = HIGH;
const char* buttonId11 = "BUTTON_117";

// DISCH1 back button  - Momentary Button (push button)
const int pin12 = 12;
int lastStatePin12 = HIGH;
const char* buttonId12 = "BUTTON_118";

// Wheel well  --LED
const int pin13 = 13;
int lastStatePin13 = HIGH;

// Fault  --LED
const int pin14 = 14;
int lastStatePin14 = HIGH;

// APU DET Inop  --LED
const int pin15 = 15;
int lastStatePin15 = HIGH;

// APU Bottle disch  --LED
const int pin16 = 16;
int lastStatePin16 = HIGH;

// DISCH APU  --LED
const int pin17 = 17;
int lastStatePin17 = HIGH;

// DISCH APU  - 3 POS ROTARY (L/R/N)
const int pin18 = 18;  // L
const int pin19 = 19;  // R
const int pin20 = 20;  // N
int dischApuRotaryLastState = HIGH;
const char* buttonId18 = "BUTTON_119";
const char* buttonId19 = "BUTTON_120";
const char* buttonId20 = "BUTTON_121";

// DISCH APU Pull  - Switch ON OFF
const int pin21 = 21;
int lastStatePin21 = HIGH;
const char* buttonId21 = "BUTTON_122";

// DISCH APU  --LED (handle indicator)
const int pin22 = 22;
int lastStatePin22 = HIGH;

// DISCH APU back button  - Momentary Button (push button)
const int pin23 = 23;
int lastStatePin23 = HIGH;
const char* buttonId23 = "BUTTON_123";

// OVHT DET 2 A  - Switch ON OFF
const int pin24 = 24;
int lastStatePin24 = HIGH;
const char* buttonId24 = "BUTTON_124";

// OVHT DET 2 B  - Switch ON OFF
const int pin25 = 25;
int lastStatePin25 = HIGH;
const char* buttonId25 = "BUTTON_125";

// Eng2 overheat  --LED
const int pin26 = 26;
int lastStatePin26 = HIGH;

// DISCH2  --LED
const int pin27 = 27;
int lastStatePin27 = HIGH;

// DISCH2  - 3 POS ROTARY (L/R/N)
const int pin28 = 28;  // L
const int pin29 = 29;  // R
const int pin30 = 30;  // N
int disch2RotaryLastState = HIGH;
const char* buttonId28 = "BUTTON_126";
const char* buttonId29 = "BUTTON_127";
const char* buttonId30 = "BUTTON_128";

// DISCH2 Pull  - Switch ON OFF
const int pin31 = 31;
int lastStatePin31 = HIGH;
const char* buttonId31 = "BUTTON_129";

// DISCH2 back button  - Momentary Button (push button)
const int pin32 = 32;
int lastStatePin32 = HIGH;
const char* buttonId32 = "BUTTON_130";

// L bottle disch  --LED
const int pin33 = 33;
int lastStatePin33 = HIGH;

// R bottle disch  --LED
const int pin34 = 34;
int lastStatePin34 = HIGH;

// Ext test 1  - Momentary Button (push button)
const int pin35 = 35;
int lastStatePin35 = HIGH;
const char* buttonId35 = "BUTTON_131";

// Ext test 2  - Momentary Button (push button)
const int pin36 = 36;
int lastStatePin36 = HIGH;
const char* buttonId36 = "BUTTON_132";

// Ext test L  --LED
const int pin37 = 37;
int lastStatePin37 = HIGH;

// Ext test R  --LED
const int pin38 = 38;
int lastStatePin38 = HIGH;

// Ext test APU  --LED
const int pin39 = 39;
int lastStatePin39 = HIGH;
