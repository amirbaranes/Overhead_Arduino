////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 100 - 117 (Pedestal P3 scope)
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

//Verified
// ADF 1 TFR  - Momentary Button (push button)
const int pin33 = 33;
int lastStatePin33 = HIGH;
const char* buttonId33 = "BUTTON_100";

//Verified
// ADF1 Dual Encoder (high/low digit)
const int pin34 = 34;    // Inner CLK
const int pin35 = 35;    // Inner DT
const int pin36 = 36;    // Outer CLK
const int pin37 = 37;    // Outer DT
const char* buttonId34 = "BUTTON_101";   // Inner CW
const char* buttonId35 = "BUTTON_102";   // Inner CCW
const char* buttonId36 = "BUTTON_103";   // Outer CW
const char* buttonId37 = "BUTTON_104";   // Outer CCW

//Verified
// ADF1 digit button  - Momentary Button (push button)
const int pin38 = 38;
int lastStatePin38 = HIGH;
const char* buttonId38 = "BUTTON_105";

//Verified
// ADF  - Switch ON OFF
const int pin39 = 39;
int lastStatePin39 = HIGH;
const char* buttonId39 = "BUTTON_106";

//Verified
// ANT  - Switch ON OFF
const int pin40 = 40;
int lastStatePin40 = HIGH;
const char* buttonId40 = "BUTTON_107";

//Verified
// Tone OFF  - Switch ON OFF
const int pin41 = 41;
int lastStatePin41 = HIGH;
const char* buttonId41 = "BUTTON_108";

//Verified
// Tone ON  - Switch ON OFF
const int pin42 = 42;
int lastStatePin42 = HIGH;
const char* buttonId42 = "BUTTON_109";

//Verified
// AILERON wing Left  - Momentary Button (push button)
const int pin43 = 43;
int lastStatePin43 = HIGH;
const char* buttonId43 = "BUTTON_110";

//Verified
// AILERON wing right  - Momentary Button (push button)
const int pin44 = 44;
int lastStatePin44 = HIGH;
const char* buttonId44 = "BUTTON_111";

//Verified
// AILERON wing Left 2  - Momentary Button (push button)
const int pin45 = 45;
int lastStatePin45 = HIGH;
const char* buttonId45 = "BUTTON_112";

//Verified
// AILERON wing right 2  - Momentary Button (push button)
const int pin46 = 46;
int lastStatePin46 = HIGH;
const char* buttonId46 = "BUTTON_113";

//Verified
// AILERON nose left  - Momentary Button (push button)
const int pin47 = 47;
int lastStatePin47 = HIGH;
const char* buttonId47 = "BUTTON_114";

//Verified
// AILERON nose right  - Momentary Button (push button)
const int pin48 = 48;
int lastStatePin48 = HIGH;
const char* buttonId48 = "BUTTON_115";

// AILERON Servo
const int pin49 = 49;

//Verified
// Stab trim ovrd  - Switch ON OFF
const int pin50 = 50;
int lastStatePin50 = HIGH;
const char* buttonId50 = "BUTTON_116";

//Verified
// Stab trim norm  - Switch ON OFF
const int pin51 = 51;
int lastStatePin51 = HIGH;
const char* buttonId51 = "BUTTON_117";

// Cabin door led  --LED
const int pin52 = 52;
int lastStatePin52 = HIGH;

// Flood Bright - Potentiometer (analog input)
const int pinA0 = A0;
int pinA0PotLastVal = 0;
int pinA0PotMin = 0;
int pinA0PotMax = 270;
const char* pinA0PotAddress = "PMDGNG3:EVT_PEDESTAL_FLOOD_BRIGHT";  // TODO: Replace with real PMDG address
