////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 39 - 61



// DC amps  - 7Seg
const int pin10 = 10; // DIO
const int pin11 = 11; //CLK

// CPS FREQ  - 7Seg
const int pin2 = 2; // DIO
const int pin3 = 3; //CLK

// DC volts  - 7Seg
const int pin4 = 4; // DIO
const int pin5 = 5; //CLK

// AC amps  - 7Seg
const int pin6 = 6; // DIO
const int pin7 = 7; //CLK

// AC volts  - 7Seg
const int pin8 = 8; // DIO
const int pin9 = 9; //CLK

//BAT discharge  --LED
const int pin15 = 15;
int lastStatePin15 = HIGH;

//TR Unit  --LED
const int pin16 = 16;
int lastStatePin16 = HIGH;

//Elec  --LED
const int pin17 = 17;
int lastStatePin17 = HIGH;

// MainT  - ON OFF 
const int pin18 = 18; //ARM
int lastStatePin18 = HIGH;
const char* buttonId18 = "BUTTON_39";  

// BAT selector(left side) - 8 POS ROTARY
const int pin19 = 19; //Aux BAT 
const int pin20 = 20; // BAT
const int pin21 = 21; // BAT BUS
const int pin22 = 22; //STBY PWR
const int pin23 = 23; // TEST
const int pin24 = 24; // TR3
const int pin25 = 25; // TR2
const int pin26 = 26; // TR1
int batSelectorLeftLastState = HIGH;
const char* buttonId19 = "BUTTON_40";  
const char* buttonId20 = "BUTTON_41";  
const char* buttonId21 = "BUTTON_42";  
const char* buttonId22 = "BUTTON_43";  
const char* buttonId23 = "BUTTON_44";  
const char* buttonId24 = "BUTTON_45";  
const char* buttonId25 = "BUTTON_46";  
const char* buttonId26 = "BUTTON_47";  


// BAT selector(right side) - 7 POS ROTARY
const int pin27 = 27; //APU GEN
const int pin28 = 28; // GEN1
const int pin29 = 29; // GRD PWR
const int pin30 = 30; //STBY PWR
const int pin31 = 31; // TEST
const int pin32 = 32; // INV
const int pin33 = 33; // GEN2
int batSelectorRightLastState = HIGH;
const char* buttonId27 = "BUTTON_48";  
const char* buttonId28 = "BUTTON_49";  
const char* buttonId29 = "BUTTON_50";  
const char* buttonId30 = "BUTTON_51";  
const char* buttonId31 = "BUTTON_52";  
const char* buttonId32 = "BUTTON_53";  
const char* buttonId33 = "BUTTON_54";  

// DC - ON OFF 
const int pin35 = 35; //On
int lastStatePin35 = HIGH;
const char* buttonId35 = "BUTTON_55";  

// CAB/UTIL - ON(gally) - ON OFF 
const int pin37 = 37; //On
int lastStatePin37 = HIGH;
const char* buttonId37 = "BUTTON_56";  

// // IFE/PASS  - ON OFF (not supported)
// const int pin38 = 38; //On
// int lastStatePin38 = HIGH;
// const char* buttonId38 = "BUTTON_57"; 

// STANDBY POWER   - ON OFF ON
const int pin39 = 39; //Auto
const int pin40 = 40; // BAT
int lastStatePin39 = HIGH;
int lastStatePin40 = HIGH;
const char* buttonId39 = "BUTTON_58";  
const char* buttonId40 = "BUTTON_59";  

// Drive 1 disconnect  - ON OFF 
const int pin41 = 41; //On
int lastStatePin41 = HIGH;
const char* buttonId41 = "BUTTON_60"; 

// Drive 2 disconnect  - ON OFF 
const int pin42 = 42; //On
int lastStatePin42 = HIGH;
const char* buttonId42 = "BUTTON_61"; 

//Drive 1 disconnect --LED
const int pin43 = 43;
int lastStatePin43 = HIGH;

//Drive 2 disconnect  --LED
const int pin44 = 44;
int lastStatePin44 = HIGH;

//Standby PWR OFF  --LED
const int pin45 = 45;
int lastStatePin45 = HIGH;





















