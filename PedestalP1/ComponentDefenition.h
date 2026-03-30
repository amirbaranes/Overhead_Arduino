////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 1 - 20 (Pedestal P1 scope)
// Since Pedestal uses its own DEVICE_ADDRESS/VJOY, button IDs are independent from Overhead



// VHF1 Active  - 7Seg
const int pin2 = 2; // DIO
const int pin3 = 3; //CLK
const int pin4 = 4; //CS

// VHF1 Stndby  - 7Seg
const int pin5 = 5; // DIO
const int pin6 = 6; //CLK
const int pin7 = 7; //CS

// VHF1 TFR  - Momentary Button (push button)
const int pin8 = 8;
int lastStatePin8 = HIGH;
const char* buttonId8 = "BUTTON_1";

// VHF1 test  - Momentary Button (push button)
const int pin9 = 9;
int lastStatePin9 = HIGH;
const char* buttonId9 = "BUTTON_2";

// VHF1 high digit  - Rotary Encoder
const int pin10 = 10;    // CLK
const int pin11 = 11;  // DT
int lastStatePin10 = HIGH;
int lastStatePin11 = HIGH;
const char* buttonId10 = "BUTTON_3";   // CW
const char* buttonId11 = "BUTTON_4"; // CCW

// VHF1 low digit  - Rotary Encoder
const int pin12 = 12;    // CLK
const int pin13 = 13;  // DT
int lastStatePin12 = HIGH;
int lastStatePin13 = HIGH;
const char* buttonId12 = "BUTTON_5";   // CW
const char* buttonId13 = "BUTTON_6"; // CCW

// NAV1 Active  - 7Seg
const int pin14 = 14; // DIO
const int pin15 = 15; //CLK
const int pin16 = 16; //CS

// NAV1 Stndby  - 7Seg
const int pin17 = 17; // DIO
const int pin18 = 18; //CLK
const int pin19 = 19; //CS

// NAV1 TFR  - Momentary Button (push button)
const int pin20 = 20;
int lastStatePin20 = HIGH;
const char* buttonId20 = "BUTTON_7";

// NAV1 test  - Momentary Button (push button)
const int pin21 = 21;
int lastStatePin21 = HIGH;
const char* buttonId21 = "BUTTON_8";

// NAV1 high digit  - Rotary Encoder
const int pin22 = 22;    // CLK
const int pin23 = 23;  // DT
int lastStatePin22 = HIGH;
int lastStatePin23 = HIGH;
const char* buttonId22 = "BUTTON_9";   // CW
const char* buttonId23 = "BUTTON_10"; // CCW

// NAV1 low digit  - Rotary Encoder
const int pin24 = 12;    // CLK
const int pin25 = 13;  // DT
int lastStatePin24 = HIGH;
int lastStatePin25 = HIGH;
const char* buttonId24 = "BUTTON_11";   // CW
const char* buttonId25 = "BUTTON_12"; // CCW

//CargoFire ext fwd  --LED
const int pin26 = 26;
int lastStatePin26 = HIGH;

//CargoFire ext aft  --LED
const int pin27 = 27;
int lastStatePin27 = HIGH;

// CargoFire test (push button)
const int pin28 = 28;
int lastStatePin28 = HIGH;
const char* buttonId28 = "BUTTON_13";

// CargoFire det fwd  - 3 POS ROTARY
const int pin29 = 29; //A
const int pin30 = 30; // Norm
const int pin31 = 31; // B
int CargoFireDetFwdLastState = HIGH;
const char* buttonId29 = "BUTTON_14";  
const char* buttonId30 = "BUTTON_15";  
const char* buttonId31 = "BUTTON_16";  

// CargoFire det aft  - 3 POS ROTARY
const int pin32 = 32; //A
const int pin33 = 33; // Norm
const int pin34 = 34; // B
int CargoFireDetAftLastState = HIGH;
const char* buttonId32 = "BUTTON_17";  
const char* buttonId33 = "BUTTON_18";  
const char* buttonId34 = "BUTTON_19"; 

//CargoFire detector fault  --LED
const int pin35 = 35;
int lastStatePin35 = HIGH;

//CargoFire fwd arm yellow  --LED
const int pin36 = 36;
int lastStatePin36 = HIGH;

//CargoFire fwd arm red  --LED
const int pin37 = 37;
int lastStatePin37 = HIGH;

// CargoFire fwd arm button (push button)
const int pin38 = 38;
int lastStatePin38 = HIGH;
const char* buttonId38 = "BUTTON_20";

// CargoFire aft arm yellow  --LED
const int pin39 = 39;
int lastStatePin39 = HIGH;

// CargoFire aft arm red  --LED
const int pin40 = 40;
int lastStatePin40 = HIGH;

// CargoFire aft arm button (push button)
const int pin41 = 41;
int lastStatePin41 = HIGH;
const char* buttonId41 = "BUTTON_21";

// CargoFire discharg(push button)
const int pin42 = 42;
int lastStatePin42 = HIGH;
const char* buttonId42 = "BUTTON_22";

// CargoFire discharg1  --LED
const int pin43 = 43;
int lastStatePin43 = HIGH;

// CargoFire discharg2  --LED
const int pin44 = 44;
int lastStatePin44 = HIGH;

// wx radar tilt - Potentiometer (analog input)
const int pinA0 = A0;
int pinA0PotLastVal = 0;
int pinA0PotMin = 0;
int pinA0PotMax = 270;
const char* pinA0PotAddress = "PMDGNG3:EVT_PEDESTAL_EXAMPLE";  // TODO: Replace with real PMDG address

// wx radar tilt 2 - Potentiometer (analog input)
const int pinA1 = A1;
int pinA1PotLastVal = 0;
int pinA1PotMin = 0;
int pinA1PotMax = 270;
const char* pinA1PotAddress = "PMDGNG3:EVT_PEDESTAL_EXAMPLE";  // TODO: Replace with real PMDG address

// wx radar mode  - 3 POS ROTARY
const int pin47 = 47; // test
const int pin48 = 48; // wx
const int pin49 = 49; // turb_map
int wxRadarModeLastState = HIGH;
const char* buttonId47 = "BUTTON_23";  
const char* buttonId48 = "BUTTON_24";  
const char* buttonId49 = "BUTTON_25"; 
