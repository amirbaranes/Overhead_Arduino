////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 1 - 18, reserved through 43 (Pedestal P3 scope)
// Since Pedestal uses its own DEVICE_ADDRESS/VJOY, button IDs are independent from Overhead



// VHF 3 Active  - 7Seg
const int pin2 = 2; // DIO
const int pin3 = 3; //CLK
const int pin4 = 4; //CS

// VHF 3 Stndby  - 7Seg
const int pin5 = 5; // DIO
const int pin6 = 6; //CLK
const int pin7 = 7; //CS

// ADF 1 Active  - 7Seg
const int pin27 = 27; // DIO
const int pin28 = 28; //CLK
const int pin29 = 29; //CS

// ADF 1 Stndby  - 7Seg
const int pin30 = 30; // DIO
const int pin31 = 31; //CLK
const int pin32 = 32; //CS

//Verified
// ADF 1 TFR  - Momentary Button (push button)
const int pin33 = 33;
int lastStatePin33 = HIGH;
const char* buttonId33 = "BUTTON_1";

//Verified
// ADF1 Dual Encoder (high/low digit)
const int pin34 = 34;    // Inner CLK
const int pin35 = 35;    // Inner DT
const int pin36 = 36;    // Outer CLK
const int pin37 = 37;    // Outer DT
const char* buttonId34 = "BUTTON_2";   // Inner CW
const char* buttonId35 = "BUTTON_3";   // Inner CCW
const char* buttonId36 = "BUTTON_4";   // Outer CW
const char* buttonId37 = "BUTTON_5";   // Outer CCW

//Verified
// ADF1 digit button  - Momentary Button (push button)
const int pin38 = 38;
int lastStatePin38 = HIGH;
const char* buttonId38 = "BUTTON_6";

//Verified
// ADF  - Switch ON OFF
const int pin39 = 39;
int lastStatePin39 = HIGH;
const char* buttonId39 = "BUTTON_7";

//Verified
// ANT  - Switch ON OFF
const int pin40 = 40;
int lastStatePin40 = HIGH;
const char* buttonId40 = "BUTTON_8";

//Verified
// Tone OFF  - Switch ON OFF
const int pin41 = 41;
int lastStatePin41 = HIGH;
const char* buttonId41 = "BUTTON_9";

//Verified
// Tone ON  - Switch ON OFF
const int pin42 = 42;
int lastStatePin42 = HIGH;
const char* buttonId42 = "BUTTON_10";

//Verified
// AILERON wing Left  - Momentary Button (push button)
const int pin43 = 43;
int lastStatePin43 = HIGH;
const char* buttonId43 = "BUTTON_11";

//Verified
// AILERON wing right  - Momentary Button (push button)
const int pin44 = 44;
int lastStatePin44 = HIGH;
const char* buttonId44 = "BUTTON_12";

//Verified
// AILERON wing Left 2  - Momentary Button (push button)
const int pin45 = 45;
int lastStatePin45 = HIGH;
const char* buttonId45 = "BUTTON_13";

//Verified
// AILERON wing right 2  - Momentary Button (push button)
const int pin46 = 46;
int lastStatePin46 = HIGH;
const char* buttonId46 = "BUTTON_14";

//Verified
// AILERON nose left  - Momentary Button (push button)
const int pin47 = 47;
int lastStatePin47 = HIGH;
const char* buttonId47 = "BUTTON_15";

//Verified
// AILERON nose right  - Momentary Button (push button)
const int pin48 = 48;
int lastStatePin48 = HIGH;
const char* buttonId48 = "BUTTON_16";

// AILERON Servo
const int pin49 = 49;

//Verified
// Stab trim ovrd  - Switch ON OFF
const int pin50 = 50;
int lastStatePin50 = HIGH;
const char* buttonId50 = "BUTTON_17";

//Verified
// Stab trim norm  - Switch ON OFF
const int pin51 = 51;
int lastStatePin51 = HIGH;
const char* buttonId51 = "BUTTON_18";

// Cabin door led  --LED
const int pin52 = 52;
int lastStatePin52 = HIGH;

// Flood Bright - Potentiometer (analog input)
const int pinA0 = A0;
int pinA0PotLastVal = 0;
int pinA0PotMin = 0;
int pinA0PotMax = 150;
const char* pinA0PotAddress = "PMDGNG3:EVT_PED_FLOOD_CONTROL";  // TODO: Replace with real PMDG address

// MicSelector right 1 led  --LED
const int pin18 = 18;
int lastStatePin18 = HIGH;

// MicSelector right 2 led  --LED
const int pin19 = 19;
int lastStatePin19 = HIGH;

// MicSelector right 3 led  --LED
const int pin20 = 20;
int lastStatePin20 = HIGH;

// MicSelector right 4 led  --LED
const int pin21 = 21;
int lastStatePin21 = HIGH;

// MicSelector right 5 led  --LED
const int pin22 = 22;
int lastStatePin22 = HIGH;

// MicSelector right 6 led  --LED
const int pin23 = 23;
int lastStatePin23 = HIGH;

// MicSelector right 7 led  --LED
const int pin24 = 24;
int lastStatePin24 = HIGH;

// MicSelector right 8 led  --LED
const int pin25 = 25;
int lastStatePin25 = HIGH;

// MicSelector right 1  - Momentary Button (push button)
const int pinA2 = A2;
int lastStatePinA2 = HIGH;
const char* buttonIdA2 = "BUTTON_19";

// MicSelector right 2  - Momentary Button (push button)
const int pinA3 = A3;
int lastStatePinA3 = HIGH;
const char* buttonIdA3 = "BUTTON_20";

// MicSelector right 3  - Momentary Button (push button)
const int pinA4 = A4;
int lastStatePinA4 = HIGH;
const char* buttonIdA4 = "BUTTON_21";

// MicSelector right 4  - Momentary Button (push button)
const int pinA5 = A5;
int lastStatePinA5 = HIGH;
const char* buttonIdA5 = "BUTTON_22";

// MicSelector right 5  - Momentary Button (push button)
const int pinA6 = A6;
int lastStatePinA6 = HIGH;
const char* buttonIdA6 = "BUTTON_23";

// MicSelector right 6  - Momentary Button (push button)
const int pinA7 = A7;
int lastStatePinA7 = HIGH;
const char* buttonIdA7 = "BUTTON_24";

// MicSelector right 7  - Momentary Button (push button)
const int pinA8 = A8;
int lastStatePinA8 = HIGH;
const char* buttonIdA8 = "BUTTON_25";

// MicSelector right 8  - Momentary Button (push button)
const int pinA1 = A1;
int lastStatePinA9 = HIGH;
const char* buttonIdA9 = "BUTTON_26";
