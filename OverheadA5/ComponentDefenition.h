////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 0
// Buttons end index ?


//Voice recorder on 
const int pin49 = 49;
int lastStatePin49 = HIGH;
const char* buttonId49 = "BUTTON_50";

//Air Temp gauge -- Servo
const int pin48 = 48;
int lastStatePin48 = HIGH;

//Air temperture -- Potentiometer
const int pinA1 = A1;
int lastStatePinA1 = HIGH;

//Trim Air on 
const int pin2 = 2;
int lastStatePin2 = HIGH;
const char* buttonId2 = "BUTTON_51";

//CONT cab -- Potentiometer
const int pinA2 = A2;
int lastStatePinA2 = HIGH;

//FWD cab -- Potentiometer
const int pinA3 = A3;
int lastStatePinA3 = HIGH;

//AFT cab -- Potentiometer
const int pinA4 = A4;
int lastStatePinA4 = HIGH;

//Zone temp  --LED
const int pin3 = 3;
int lastStatePin3 = HIGH;

//Zone temp  --LED
const int pin4 = 4;
int lastStatePin4 = HIGH;

//Zone temp --LED
const int pin5 = 5;
int lastStatePin5 = HIGH;

//Dual bleed  --LED
const int pin6 = 6;
int lastStatePin6 = HIGH;

//Ram door full open 1  --LED
const int pin7 = 7;
int lastStatePin7 = HIGH;

//Ram door full open 2  --LED
const int pin8 = 8;
int lastStatePin8 = HIGH;

//Dect press 1 -- Servo
const int pin33 = 33;
int lastStatePin33 = HIGH;

//Dect press 2 -- Servo
const int pin36 = 36;
int lastStatePin36 = HIGH;

// L RECIRC FAN   - ON OFF
const int pin9 = 9;
int lastStatePin9 = HIGH;
const char* buttonId9 = "BUTTON_52";

// R RECIRC FAN   - ON OFF
const int pin10 = 10;
int lastStatePin10 = HIGH;
const char* buttonId10 = "BUTTON_53";

// OVHT test   - Button
const int pin11 = 11;
int lastStatePin11 = HIGH;
const char* buttonId11 = "BUTTON_54";

// L PACK   - ON OFF ON
const int pin12 = 12; //off
const int pin13 = 13; // high
int lastStatePin12 = HIGH;
int lastStatePin13 = HIGH;
const char* buttonId12 = "BUTTON_55";
const char* buttonId13 = "BUTTON_56";

// ISOLATION valve  - ON OFF ON
const int pin14 = 14; //close
const int pin15 = 15; // open
int lastStatePin14 = HIGH;
int lastStatePin15 = HIGH;
const char* buttonId14 = "BUTTON_57";
const char* buttonId15 = "BUTTON_58";

// R PACK   - ON OFF ON
const int pin16 = 16; //off
const int pin17 = 17; // high
int lastStatePin16 = HIGH;
int lastStatePin17 = HIGH;
const char* buttonId16 = "BUTTON_59";
const char* buttonId17 = "BUTTON_60";


// Eng bleed 1 on  - ON OFF
const int pin18 = 18;
int lastStatePin18 = HIGH;
const char* buttonId18 = "BUTTON_61";

// Eng bleed 2 on  - ON OFF
const int pin19 = 19;
int lastStatePin19 = HIGH;
const char* buttonId19 = "BUTTON_62";

// APU bleed  on  - ON OFF
const int pin20 = 20;
int lastStatePin20 = HIGH;
const char* buttonId20 = "BUTTON_63";

// Trip reset  - Button
const int pin47 = 47;
int lastStatePin47 = HIGH;
const char* buttonId47 = "BUTTON_64";


//Auto fail  --LED
const int pin21 = 21;
int lastStatePin21 = HIGH;

//Off sched decent  --LED
const int pin22 = 22;
int lastStatePin22 = HIGH;

//ALTN --LED
const int pin23 = 23;
int lastStatePin23 = HIGH;

//MANUAL  --LED
const int pin24 = 24;
int lastStatePin24 = HIGH;

//Pack left  --LED
const int pin25 = 25;
int lastStatePin25 = HIGH;

//Wing body overheat L  --LED
const int pin26 = 26;
int lastStatePin26 = HIGH;

//Bleed trip off L  --LED
const int pin27 = 27;
int lastStatePin27 = HIGH;

//Pack Right --LED
const int pin28 = 28;
int lastStatePin28 = HIGH;

//Wing body overheat R  --LED
const int pin29 = 29;
int lastStatePin29 = HIGH;

//Bleed trip off R  --LED
const int pin30 = 30;
int lastStatePin30 = HIGH;

// FLT ALT  - 7 Segment
const int pin31 = 31; //DIO
const int pin32 = 32; // CLK
int lastStatePin31 = HIGH;
int lastStatePin32 = HIGH;

// LAND ALT  - 7 Segment
const int pin34 = 34; //DIO
const int pin35 = 35; // CLK
int lastStatePin34 = HIGH;
int lastStatePin35 = HIGH;
const char* buttonId34 = "BUTTON_65";
const char* buttonId35 = "BUTTON_66";

// FLT ALT  - Rotatory encoder
const int pin37 = 37; //clk
const int pin38 = 38; // clk
int lastStatePin37 = HIGH;
int lastStatePin38 = HIGH;
const char* buttonId37 = "BUTTON_67";
const char* buttonId38 = "BUTTON_68";

// LAND ALT  - Rotatory encoder
const int pin39 = 39; //clk
const int pin40 = 40; // clk
int lastStatePin39 = HIGH;
int lastStatePin40 = HIGH;
const char* buttonId39 = "BUTTON_69";
const char* buttonId40 = "BUTTON_70";

//Manual alt valve servo -- Servo
const int pin41 = 41;
int lastStatePin41 = HIGH;

// Manual alt valve    - MOM OFF MOM
const int pin42 = 42; //close
const int pin43 = 43; // open
int lastStatePin42 = HIGH;
int lastStatePin43 = HIGH;
const char* buttonId42 = "BUTTON_71";
const char* buttonId43 = "BUTTON_72";

// ALTN presur  - 3 POS ROTARY
const int pin44 = 44; //auto
const int pin45 = 45; // ALTN
const int pin46 = 46; // MAN
int altnPresureLastState = HIGH;
const char* buttonId44 = "BUTTON_73";
const char* buttonId45 = "BUTTON_74";
const char* buttonId46 = "BUTTON_75";


// Declerade in Potentiometers.cpp
// Air temperture buttons 
// const char* airTempSelectorPosition0  ="BUTTON_80";
// const char* airTempSelectorPosition1 = "BUTTON_81";
// const char* airTempSelectorPosition2 = "BUTTON_82";
// const char* airTempSelectorPosition3 = "BUTTON_83";
// const char* airTempSelectorPosition4 = "BUTTON_84";
// const char* airTempSelectorPosition5 = "BUTTON_85";
// const char* airTempSelectorPosition6 = "BUTTON_86";
