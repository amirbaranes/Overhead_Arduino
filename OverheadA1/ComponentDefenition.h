////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 0 - 38



// flt control A  - ON OFF ON
const int pinA9 = A9; // STB
const int pinA10 = A10; // ON
int lastStatePinA9 = HIGH;
int lastStatePinA10 = HIGH;
const char* buttonIdA9 = "BUTTON_126";
const char* buttonIdA10 = "BUTTON_1";

// flt control B  - ON OFF ON
const int pin2 = 2;
const int pin3 = 3;
int lastStatePin2 = HIGH;
int lastStatePin3 = HIGH;
const char* buttonId2 = "BUTTON_2";
const char* buttonId3 = "BUTTON_3";

// Alternate flaps  - ON OFF
const int pin4 = 4; //ARM
int lastStatePin4 = HIGH;
const char* buttonId4 = "BUTTON_4";

// Spoilers A   - ON OFF
const int pin5 = 5; //ARM
int lastStatePin5 = HIGH;
const char* buttonId5 = "BUTTON_5";

// Spoilers B   - ON OFF
const int pin6 = 6; //ARM
int lastStatePin6 = HIGH;
const char* buttonId6 = "BUTTON_6";

// Alternate flaps   - ON OFF ON
const int pin7 = 7; // UP
const int pin8 = 8; // DOWN
int lastStatePin7 = HIGH;
int lastStatePin8 = HIGH;
const char* buttonId7 = "BUTTON_7";
const char* buttonId8 = "BUTTON_8";

// Yaw damper    - ON OFF
const int pin9 = 9; //On
int lastStatePin9 = HIGH;
const char* buttonId9 = "BUTTON_9";

// Yaw damper servo -     - Servo
const int pin10 = 10; //PWN
int lastStatePin10 = HIGH;
const char* buttonId10 = "BUTTON_10";

//stndby HYD low quantity  --LED
const int pin11 = 11;
int lastStatePin11 = HIGH;

//stndby HYD low pressure  --LED
const int pin12 = 12;
int lastStatePin12 = HIGH;

//Rud On  --LED
const int pin13 = 13;
int lastStatePin13 = HIGH;

//FLT Control B Low pressure  --LED
const int pin14 = 14;
int lastStatePin14 = HIGH;

//FLT Control A Low pressure  --LED
const int pin15 = 15;
int lastStatePin15 = HIGH;

//Feel diff press  --LED
const int pin16 = 16;
int lastStatePin16 = HIGH;

//Speed trim fail  --LED
const int pin17 = 17;
int lastStatePin17 = HIGH;

//Mach trim fail  --LED
const int pin18 = 18;
int lastStatePin18 = HIGH;

//Auto slat fail  --LED
const int pin19 = 19;
int lastStatePin19 = HIGH;

//Yaw Dumper Led  --LED
const int pinA11 = A11; //
int lastStatePinA11 = HIGH;


// VHF NAV    - ON OFF ON
const int pin20 = 20; //Both on Left
const int pin21 = 21; //Both on Right
int lastStatePin20 = HIGH;
int lastStatePin21 = HIGH;
const char* buttonId20 = "BUTTON_11";
const char* buttonId21 = "BUTTON_12";


// IRS NAV  - ON OFF ON
const int pin22 = 22; //Both on Left
const int pin23 = 23; //Both on Right
int lastStatePin22 = HIGH;
int lastStatePin23 = HIGH;
const char* buttonId22 = "BUTTON_13";
const char* buttonId23 = "BUTTON_14";


// Displays source - 3 POS ROTARY
const int pin24 = 24; //auto
const int pin25 = 25; // all in 1
const int pin26 = 26; // all in 2
int displaySourceLastState = HIGH;
const char* buttonId24 = "BUTTON_15";
const char* buttonId25 = "BUTTON_16";
const char* buttonId26 = "BUTTON_17";


// control panel source   - ON OFF ON
const int pin27 = 27; //- all in 1
const int pin28 = 28; //- all in 2
int lastStatePin27 = HIGH;
int lastStatePin28 = HIGH;
const char* buttonId27 = "BUTTON_18";
const char* buttonId28 = "BUTTON_19";


// FMC - ON OFF ON
const int pinA7 = A7; //- Both left
const int pinA8 = A8; //- Both Right
int lastStatePinA7 = HIGH;
int lastStatePinA8 = HIGH;
const char* buttonIdA7 = "BUTTON_20";
const char* buttonIdA8 = "BUTTON_21";


//env valve closed left  --LED
const int pin29 = 29;
int lastStatePin29 = HIGH;

//env valve closed right  --LED
const int pin30 = 30;
int lastStatePin30 = HIGH;

//spar valve closed left  --LED
const int pin31 = 31;
int lastStatePin31 = HIGH;

//spar valve closed right  --LED
const int pin32 = 32;
int lastStatePin32 = HIGH;

// Fuel temp gauge data  - Servo
const int pin33 = 33; //PWN
int lastStatePin33 = HIGH;

//Filter bypass left  --LED
const int pin34 = 34;
int lastStatePin34 = HIGH;

//Filter bypass right  --LED
const int pin35 = 35;
int lastStatePin35 = HIGH;

//Valve open  --LED
const int pin36 = 36;
int lastStatePin36 = HIGH;

// Cross feed - 2 POS ROTARY
const int pin37 = 37; // open
const int pin38 = 38; // close
int crossFeedLastState = HIGH;
const char* buttonId37 = "BUTTON_22";
const char* buttonId38 = "BUTTON_23";

// Fuel pump L   - ON OFF
const int pin39 = 39; //
int lastStatePin39 = HIGH;
const char* buttonId39 = "BUTTON_24";

// Fuel pump R   - ON OFF
const int pin40 = 40; //
int lastStatePin40 = HIGH;
const char* buttonId40 = "BUTTON_25";

// Fuel pump L Aft   - ON OFF
const int pin41 = 41; //
int lastStatePin41 = HIGH;
const char* buttonId41 = "BUTTON_26";

// Fuel pump L Fwd   - ON OFF
const int pin42 = 42; //
int lastStatePin42 = HIGH;
const char* buttonId42 = "BUTTON_27";

// Fuel pump R Aft   - ON OFF
const int pin43 = 43; //
int lastStatePin43 = HIGH;
const char* buttonId43 = "BUTTON_28";

// Fuel pump R Fwd   - ON OFF
const int pin44 = 44; //
int lastStatePin44 = HIGH;
const char* buttonId44 = "BUTTON_29";

//"Fuel pump L Low pressure "  --LED
const int pin45 = 45;
int lastStatePin45 = HIGH;

//"Fuel pump R Low pressure "  --LED
const int pin46 = 46;
int lastStatePin46 = HIGH;

//"Fuel pump L Aft Low pressure "  --LED
const int pin47 = 47;
int lastStatePin47 = HIGH;

//"Fuel pump L Fwd Low pressure "  --LED
const int pin48 = 48;
int lastStatePin48 = HIGH;

//"Fuel pump R Aft Low pressure "  --LED
const int pin49 = 49;
int lastStatePin49 = HIGH;

//"Fuel pump R Fwd Low pressure "  --LED
const int pin50 = 50;
int lastStatePin50 = HIGH;

// Landing retractable L   - ON OFF
const int pin51 = 51; //
int lastStatePin51 = HIGH;
const char* buttonId51 = "BUTTON_30";

// Landing retractable R   - ON OFF
const int pin52 = 52; //
int lastStatePin52 = HIGH;
const char* buttonId52 = "BUTTON_31";

// Landing fixed L   - ON OFF
const int pin53 = 53; //
int lastStatePin53 = HIGH;
const char* buttonId53 = "BUTTON_32";

// Landing fixed R   - ON OFF
const int pinA1 = A1; //
int lastStatePinA1 = HIGH;
const char* buttonIdA1 = "BUTTON_33";

// Runway turnoff L   - ON OFF
const int pinA2 = A2; //
int lastStatePinA2 = HIGH;
const char* buttonIdA2 = "BUTTON_34";

// Runway turnoff R   - ON OFF
const int pinA3 = A3; //
int lastStatePinA3 = HIGH;
const char* buttonIdA3 = "BUTTON_35";

// Taxi   - ON OFF
const int pinA4 = A4; //
int lastStatePinA4 = HIGH;
const char* buttonIdA4 = "BUTTON_36";

// APU - ON OFF ON
const int pinA5 = A5; //- ON
const int pinA6 = A6; //- START
int lastStatePinA5 = HIGH;
int lastStatePinA6 = HIGH;
const char* buttonIdA5 = "BUTTON_37";
const char* buttonIdA6 = "BUTTON_38";


