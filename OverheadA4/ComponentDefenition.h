////////////////////////////
// Component Definitions
////////////////////////////

// Buttons start index 107 - 125



//WindowHeat-OverHeat 1  --LED
const int pin35 = 35;
int lastStatePin35 = HIGH;

//WindowHeat-OverHeat 2  --LED
const int pin36 = 36;
int lastStatePin36 = HIGH;

//WindowHeat-OverHeat 3  --LED
const int pin2 = 2;
int lastStatePin2 = HIGH;

//WindowHeat-OverHeat 4  --LED
const int pin3 = 3;
int lastStatePin3 = HIGH;

//WindowHeat-ON 1  --LED
const int pin4 = 4;
int lastStatePin4 = HIGH;

//WindowHeat-ON 2  --LED
const int pin5 = 5;
int lastStatePin5 = HIGH;

//WindowHeat-ON 3  --LED
const int pin6 = 6;
int lastStatePin6 = HIGH;

//WindowHeat-ON 4  --LED
const int pin7 = 7;
int lastStatePin7 = HIGH;


// WindowHeat-1 side on   - ON OFF 
const int pin8 = 8; 
int lastStatePin8 = HIGH;
const char* buttonId8 = "BUTTON_107";  

// WindowHeat-1 fwd on   - ON OFF 
const int pin9 = 9; 
int lastStatePin9 = HIGH;
const char* buttonId9 = "BUTTON_108";  

// WindowHeat - ON OFF ON
const int pin10 = 10; //ovht
const int pin11 = 11; // pwr test
int lastStatePin10 = HIGH;
int lastStatePin11 = HIGH;
const char* buttonId10 = "BUTTON_109";  
const char* buttonId11 = "BUTTON_110";  

// WindowHeat-2 side on   - ON OFF 
const int pin12 = 12; 
int lastStatePin12 = HIGH;
const char* buttonId12 = "BUTTON_111";  

// WindowHeat-2 fwd on   - ON OFF 
const int pin13 = 13; 
int lastStatePin13 = HIGH;
const char* buttonId13 = "BUTTON_112";  

// Probe heat 1 on   - ON OFF 
const int pin14 = 14; 
int lastStatePin14 = HIGH;
const char* buttonId14 = "BUTTON_113";  

// Probe heat 2 on   - ON OFF 
const int pin15 = 15; 
int lastStatePin15 = HIGH;
const char* buttonId15 = "BUTTON_114";  

// TAT test   - ON OFF 
const int pin16 = 16; 
int lastStatePin16 = HIGH;
const char* buttonId16 = "BUTTON_115";  

//Capt pitot  --LED
const int pin17 = 17;
int lastStatePin17 = HIGH;

//L elev pitot  --LED
const int pin18 = 18;
int lastStatePin18 = HIGH;

//L alpha vane  --LED
const int pin19 = 19;
int lastStatePin19 = HIGH;

//Temp probe  --LED
const int pin20 = 20;
int lastStatePin20 = HIGH;

//Fo pitot  --LED
const int pin21 = 21;
int lastStatePin21 = HIGH;

//R elev pitot  --LED
const int pin22 = 22;
int lastStatePin22 = HIGH;

//R alpha vane  --LED
const int pin23 = 23;
int lastStatePin23 = HIGH;

//Aux pitot  --LED
const int pin24 = 24;
int lastStatePin24 = HIGH;

//L valve open  --LED
const int pin25 = 25;
int lastStatePin25 = HIGH;

//R valve open --LED
const int pin26 = 26;
int lastStatePin26 = HIGH;

//cowl valve open 1  --LED
const int pin27 = 27;
int lastStatePin27 = HIGH;

//cowl valve open 2  --LED
const int pin28 = 28;
int lastStatePin28 = HIGH;

//cowl anti ice 1  --LED
const int pin29 = 29;
int lastStatePin29 = HIGH;

//cowl anti ice 2  --LED
const int pin30 = 30;
int lastStatePin30 = HIGH;

// Wing anti ice on   - ON OFF 
const int pin31 = 31; 
int lastStatePin31 = HIGH;
const char* buttonId31 = "BUTTON_116";  

// Eng anti ice 1 on   - ON OFF 
const int pin32 = 32; 
int lastStatePin32 = HIGH;
const char* buttonId32 = "BUTTON_117";  

// Eng anti ice 2 on   - ON OFF 
const int pin33 = 33; 
int lastStatePin33 = HIGH;
const char* buttonId33 = "BUTTON_118";  

// Wing anti ice 1  - Servo
const int pin34 = 34; 

// HYD pump eng 1 on   - ON OFF 
const int pin37 = 37; 
int lastStatePin37 = HIGH;
const char* buttonId37 = "BUTTON_119";  

// HYD pump eng 2 on   - ON OFF 
const int pin38 = 38; 
int lastStatePin38 = HIGH;
const char* buttonId38 = "BUTTON_120";  

// HYD pump elec 1 on   - ON OFF 
const int pin39 = 39; 
int lastStatePin39 = HIGH;
const char* buttonId39 = "BUTTON_121";  

// HYD pump elec 2 on   - ON OFF 
const int pin40 = 40; 
int lastStatePin40 = HIGH;
const char* buttonId40 = "BUTTON_122";  

//Low Pressure eng1 --LED
const int pin41 = 41;
int lastStatePin41 = HIGH;

//Low Pressure eng2 --LED
const int pin42 = 42;
int lastStatePin42 = HIGH;

//Overheat elec 2  --LED
const int pin43 = 43;
int lastStatePin43 = HIGH;

//Overheat elec 1  --LED
const int pin44 = 44;
int lastStatePin44 = HIGH;

//Low Pressure elec 1  --LED
const int pin45 = 45;
int lastStatePin45 = HIGH;

//Low Pressure elec 2  --LED
const int pin46 = 46;
int lastStatePin46 = HIGH;

//Fwd entry  --LED
const int pin47 = 47;
int lastStatePin47 = HIGH;

//Fwd service  --LED
const int pin48 = 48;
int lastStatePin48 = HIGH;

//Left fwd overwing  --LED
const int pin49 = 49;
int lastStatePin49 = HIGH;

//Right fwd overwing  --LED
const int pin50 = 50;
int lastStatePin50 = HIGH;

//Left aft overwing  --LED
const int pin51 = 51;
int lastStatePin51 = HIGH;

//Right aft overwing  --LED
const int pin52 = 52;
int lastStatePin52 = HIGH;

//Aft entry  --LED
const int pin53 = 53;
int lastStatePin53 = HIGH;

// Diff pressure   - Servo
const int pinA0 = A0; 
int lastStatePinA0 = HIGH;

// Cabin alt   - Servo
const int pinA1 = A1; 
int lastStatePinA1 = HIGH;

// Cabin pressure   - Servo
const int pinA2 = A2; 
int lastStatePinA2 = HIGH;

//Fwd cargo  --LED
const int pinA3 = A3;
int lastStatePinA3 = HIGH;

//Aft cargo  --LED
const int pinA4 = A4;
int lastStatePinA4 = HIGH;

// Voice recorder erase   - ON OFF 
const int pinA6 = A6; 
int lastStatePinA6 = HIGH;
const char* buttonIdA6 = "BUTTON_123";  

// Voice recorder test   - ON OFF 
const int pinA7 = A7; 
int lastStatePinA7 = HIGH;
const char* buttonIdA7 = "BUTTON_124";  

// Alt horn   - ON OFF 
const int pinA9 = A9; 
int lastStatePinA9 = HIGH;
const char* buttonIdA9 = "BUTTON_125";  

//Aft service  --LED
const int pinA11 = A11;
int lastStatePinA11 = HIGH;

//Equp  --LED
const int pinA12 = A12;
int lastStatePinA12 = HIGH;
























