////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 61 - 78 (Pedestal P3 scope)
// Since Pedestal uses its own DEVICE_ADDRESS/VJOY, button IDs are independent from Overhead


// ADF 2 Active  - 7Seg
const int pin2 = 2; // DIO
const int pin3 = 3; //CLK
const int pin4 = 4; //CS

// ADF 2 Stndby  - 7Seg
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

// ADF 1 TFR  - Momentary Button (push button)
const int pin33 = 33;
int lastStatePin33 = HIGH;
const char* buttonId33 = "BUTTON_61";

// ADF1 high digit  - Rotary Encoder
const int pin34 = 34;    // CLK (decrease)
const int pin35 = 35;    // DT (increase)
int lastStatePin34 = HIGH;
int lastStatePin35 = HIGH;
const char* buttonId34 = "BUTTON_62";   // CW
const char* buttonId35 = "BUTTON_63";   // CCW

// ADF1 low digit  - Rotary Encoder
const int pin36 = 36;    // CLK (decrease)
const int pin37 = 37;    // DT (increase)
int lastStatePin36 = HIGH;
int lastStatePin37 = HIGH;
const char* buttonId36 = "BUTTON_64";   // CW
const char* buttonId37 = "BUTTON_65";   // CCW

// ADF1 digit button  - Momentary Button (push button)
const int pin38 = 38;
int lastStatePin38 = HIGH;
const char* buttonId38 = "BUTTON_66";

// ADF  - Switch ON OFF
const int pin39 = 39;
int lastStatePin39 = HIGH;
const char* buttonId39 = "BUTTON_67";

// ANT  - Switch ON OFF
const int pin40 = 40;
int lastStatePin40 = HIGH;
const char* buttonId40 = "BUTTON_68";

// Tone OFF  - Switch ON OFF
const int pin41 = 41;
int lastStatePin41 = HIGH;
const char* buttonId41 = "BUTTON_69";

// Tone ON  - Switch ON OFF
const int pin42 = 42;
int lastStatePin42 = HIGH;
const char* buttonId42 = "BUTTON_70";

// AILERON wing Left  - Momentary Button (push button)
const int pin43 = 43;
int lastStatePin43 = HIGH;
const char* buttonId43 = "BUTTON_71";

// AILERON wing right  - Momentary Button (push button)
const int pin44 = 44;
int lastStatePin44 = HIGH;
const char* buttonId44 = "BUTTON_72";

// AILERON wing Left 2  - Momentary Button (push button)
const int pin45 = 45;
int lastStatePin45 = HIGH;
const char* buttonId45 = "BUTTON_73";

// AILERON wing right 2  - Momentary Button (push button)
const int pin46 = 46;
int lastStatePin46 = HIGH;
const char* buttonId46 = "BUTTON_74";

// AILERON nose left  - Momentary Button (push button)
const int pin47 = 47;
int lastStatePin47 = HIGH;
const char* buttonId47 = "BUTTON_75";

// AILERON nose right  - Momentary Button (push button)
const int pin48 = 48;
int lastStatePin48 = HIGH;
const char* buttonId48 = "BUTTON_76";

// AILERON Servo
const int pin49 = 49;

// Stab trim ovrd  - Switch ON OFF
const int pin50 = 50;
int lastStatePin50 = HIGH;
const char* buttonId50 = "BUTTON_77";

// Stab trim norm  - Switch ON OFF
const int pin51 = 51;
int lastStatePin51 = HIGH;
const char* buttonId51 = "BUTTON_78";

// Cabin door led  --LED
const int pin52 = 52;
int lastStatePin52 = HIGH;
