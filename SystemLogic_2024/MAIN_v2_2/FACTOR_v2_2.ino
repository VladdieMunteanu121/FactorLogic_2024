bool quickTest = 0;   //0 = full pump timers; 1 = short pump timers

bool simple = 0;    //0 for full factor; 1 for simple display setup

bool login = 0;   //0 for no login; 1 for login

bool Site = 0;    //0 = Advent (unit 1); 1 = Flaskworks (unit 2)

#include <genieArduino.h>
#include <Stepper.h>

// 4D Systems
Genie genie;
int currentForm = 0;
int previousForm = 0;

//Arrays
char messageArray[255] = {};    //display max string length is 255 (max string length setting doesn't change this and apparently there isn't any way other way to increase string length)
char arduinoMessage[200] = {};    //message from peripheral Arduinos
char SMInput[20] = {};    //Serial Monitor input
char UserName[20] = {};   //Username keyboard input
char Password[20] = {};   //Password keyboard input

//Mitsubishi Servo 
int EM2 = 22;
int SON = 24; 
int MD0 = 26;
int ST1 = 28;
int DOG = 32;
int LSP = 34;
int LSN = 36;
int DI_0 = 40;
int DI_1 = 42;
int DI_2 = 44;
int DI_3 = 46;
int DI_4 = 30;

unsigned long ST1_ON_time;
unsigned long previousMillis = 0;
int ST1_switch_interval = 100; // the time after which the ST1_swtich will get turned off millis  
bool pin_status = HIGH;

int LSN_status = 1;
int LSP_status = 1;
unsigned long servo_startTime = millis();
long servo_Run30 = 88;
long servo_Run60 = 58;
long servo_Run90 = 88;
long servo_Run120 = 118;

int servoPos = 0; // 0 = home, 1 = equilibrate, 2 = drain, 3 = fill
//int servo_currentPos;
//int servo_desiredPos;
//int servo_previousPos;
int shakeMode = 0;


//Guide Rail
#define railDIRpin 13
#define railSTEPpin 12
const int rail_pulse_per_rev = 200;
Stepper rail(rail_pulse_per_rev, railDIRpin, railSTEPpin);

unsigned int railPos;   //1 = flat, 2 = drain, 3 = extract, 4 = home
//unsigned int railDesiredPos;
//unsigned int rail_previousPos;
//int railIncrement;  //1 = increment up, 2 = increment down

int LS_extract = 47;
int LS_extract_status;

// Pinch Valve
const int valve1PIN = 48;
bool valve1Status = false;    //NC

const int valve2PIN = 49;
bool valve2Status = false;    //NC

const int valve3PIN = 50;
bool valve3Status = false;    //NO



//Configuration
int stateIndex = 0, lastState = 0, buttonIndex = 0, routine = 0, recoveryIndex = 0, recoveryState = 0;
int pos1_config = 0, pos2_config = 0, pos3_config = 0; // 1 = 1 layer CS , 2 = 2 layer CS, 3 = Balance, 4 = T-flask
int arduino2 = 0,  arduino3 = 0;

enum stateArrayOptions {WAIT, RUN, MANUAL, CALIBRATE, TIMER, RECOVERY};
int command = WAIT;


//Watson-Marlow pump
const int WMDIRpin = 6; 
const int WMSTEPpin = 7;
const int WMDISABLEpin = 3;

int WM1_status = 2, WM2_status = 2, WM3_status = 2;   //0 = ON CW; 1 = ON CCW; 2 = OFF
int WM1_flowRate = 0, WM2_flowRate = 0, WM3_flowRate = 0;
float WM1speed;

//Pump specific speeds
float WM1speed20 = 3570.000;  //originally 3570.000 for 20 m/min... this value is equivalent to 10ml/min
float WM1speed50 = 8925.000;
float WM1speed100 = 17500.000;
float WM1speed200 = 34000.000;    //~185 mL/min

int manualFlowRate = 20;    //initialize
int purgeFlowRate = 20;


//timer variables -- all in seconds
unsigned long timeStart = 0, timeNow = 0, timeElapsed = 0, pauseStart = 0, pauseTime = 0, lastUpdatedTime = 0, timeSkip = 0;
unsigned long TotalSec1 = 0, remainingTotalSec1 = 0, TotalSec2 = 0, remainingTotalSec2 = 0, TotalSec3 = 0, remainingTotalSec3 = 0;
int TimerMin = 0, TimerSec = 0, pos1timer = 0, pos2timer = 0, pos3timer = 0; 

bool pause = 0;
bool purge = 0;


//All shakes timed by Servo Amp
unsigned long gentleShake1 = 38;  //seconds
unsigned long gentleShake2 = 17;

unsigned long vigorousShake1 = 47; 
unsigned long vigorousShake2 = 47; 
unsigned long vigorousShake3 = 92; 
unsigned long vigorousShake4 = 92; 
unsigned long vigorousShake5 = 92; 
unsigned long vigorousShake6 = 92; 
unsigned long vigorousShake7 = 92; 
unsigned long vigorousShake8 = 92; 
unsigned long vigorousShake9 = 122; 
unsigned long vigorousShake10 = 32; 
unsigned long vigorousShake11 = 32; 
unsigned long equilibrate = 10;


//Arrays
const int NUM_VESSELCONFIGBUTTONS = 36;   //Vessel Configuration Buttons
int vesselConfigButtons[] = {22, 23, 24, 25, 27, 28, 29, 31, 32, 34, 35, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109};

const int NUM_FILLSTATES = 8;   //DPBS Fill states
int fillStates[] = {9, 13, 23, 27, 32, 46, 50, 55};

const int NUM_DRAINSTATES = 11;        //Drain states
int drainStates[] = {8, 12, 16, 22, 26, 31, 35, 45, 49, 54, 58};   

//int drainTrigger = 0;    //so that commands in TIMER do not loop

const int NUM_COMPLETESTATES = 8;   //routine complete states
int completeStates[] = {7, 17, 20, 29, 36, 43, 52, 59};

const int NUM_EQWASHSTATES = 13; // equilibration and bag wash states
int eqWashStates[] = {2, 5, 10, 14, 19, 24, 28, 33, 38, 41, 47, 51, 56};

const int NUM_GENTLESHAKESTATES = 9;   //gentle shake states
int gentleShakeStates[] = {4, 6, 11, 15, 21, 40, 42, 44, 60};

int gentleShakeTrigger = 0;


//stop perfusion counter
int pump1Complete = 0, pump2Complete = 0, pump3Complete = 0;


//Shake Mech position
int shakeMechPos = 0;   //0 = Home; 1 = PBMC/DPBS Fill; 2 = DC Medium Fill; 3 = Drain; 4 = Equilibrate; 5 = Extract
 
//State Machine
const int stateRows = 65;
const int stateColumns = 10;


//Button Machine
const int buttonRows = 185;
const int buttonColumns = 2;
extern int buttonMachine[buttonRows][buttonColumns];

//Recovery Table
const int recoveryRows = 45;
const int recoveryColumns = 2;
extern int recoveryTable[recoveryRows][recoveryColumns];

//Servo Pos: 0 = home (flat), 1 = equilibrate (90), 2 = drain (145), 3 = fill (angled)
//Rail Pos: 1 = flat, 2 = oscillate, 3 = extract, 4 = fill, 5 = Drain
//Pump DIR: 0 = ON CW; 1 = ON CCW; 2 = OFF
//Shake Type: 1 = Gentle 1; 2 = Gentle 2; 3 = Vigorous 1; 4 = Vigorous 2; 5 = Vigorous 3; 6 = Vigorous 4; 7 = Vigorous 5; 8 = Vigorous 6; 

//Pinch Valves 1 - 2: 1 channel Normally Closed (NC); 0 = closed (not energized); 1 = open (energized)
//Pinch Valve 3: 1 channel Normally Open (NO); 0 = open (not energized); 1 = closed (energized)

//add PBMC bag air fill 
int stateMachine[stateRows][stateColumns] =
{
  // 0        1           2        3        4             5         6         7          8           9              
  // Servo    ---         Guide    Pump     Next State    Shake     Pump      Valve 1    Valve 2     Valve 3
  //          ---         Rail     Dir                    Type      Speed     DCM        PBMC/DPBS   Drain
  {  0     ,  0        ,  1     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, // State 0

  //Day 0******************************************************************************************************************************************************************************
  {  0     ,  0        ,  1     ,  0     ,  5          ,  false  ,  50     ,  0       ,  1         ,  1       }, //State 1 (routine 1: PBMC Seed 1)
          {  3     ,  0        ,  4     ,  2     ,  3          ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 2 (routine 1: Bag wash) *removed*
          {  3     ,  0        ,  4     ,  0     ,  4          ,  false  ,  50     ,  0       ,  0         ,  1       }, //State 3 (routine 1: PBMC Seed 2) *removed*
          {  0     ,  0        ,  2     ,  2     ,  5          ,  1      ,  false  ,  0       ,  0         ,  1       }, //State 4 (routine 1: Gentle Shake) *removed*
  {  1     ,  0        ,  1     ,  2     ,  7          ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 5 (routine 1: Equilibrate)
          {  0     ,  0        ,  3     ,  2     ,  7          ,  1      ,  false  ,  0       ,  0         ,  1       }, //State 6 (routine 1: Gentle Shake) *removed*
  {  0     ,  0        ,  3     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 7 (routine 1: Complete)

  {  2     ,  0        ,  5     ,  1     ,  9          ,  false  ,  100    ,  0       ,  0         ,  0       }, //State 8 (routine 2: Drain 1)
  {  0     ,  0        ,  1     ,  0     ,  10         ,  false  ,  100    ,  0       ,  1         ,  1       }, //State 9 (routine 2: Fill 1)
  {  1     ,  0        ,  1     ,  2     ,  11         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 10 (routine 2: Equilibrate)
  {  0     ,  0        ,  1     ,  2     ,  12         ,  1     ,  false  ,  0       ,  0         ,  1       }, //State 11 (routine 2: Gentle Shake 2)
  {  2     ,  0        ,  5     ,  1     ,  13         ,  false  ,  100    ,  0       ,  0         ,  0       }, //State 12 (routine 2: Drain 2)
  {  0     ,  0        ,  1     ,  0     ,  14         ,  false  ,  100    ,  0       ,  1         ,  1       }, //State 13 (routine 2: Fill 2)
  {  1     ,  0        ,  1     ,  2     ,  15         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 14 (routine 2: Equilibrate)
  {  0     ,  0        ,  1     ,  2     ,  16         ,  1     ,  false  ,  0       ,  0         ,  1       }, //State 15 (routine 2: Gentle Shake 3)
  {  2     ,  0        ,  5     ,  1     ,  17         ,  false  ,  100    ,  0       ,  0         ,  0       }, //State 16 (routine 2: Drain 3)
  {  0     ,  0        ,  1     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 17 (routine 2: Complete)
 
  {  0     ,  0        ,  1     ,  0     ,  19         ,  false  ,  50     ,  1       ,  0         ,  1       }, //State 18 (routine 3: DC Medium Fill)
  {  1     ,  0        ,  1     ,  2     ,  20         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 19 (routine 3: Equilibrate)
  {  0     ,  0        ,  3     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 20 (routine 3: Complete)

  //Day 7******************************************************************************************************************************************************************************
  {  0     ,  0        ,  1     ,  2     ,  22         ,  1      ,  false  ,  0       ,  0         ,  1       }, //State 21 (routine 4: Gentle Shake)
  {  2     ,  0        ,  5     ,  1     ,  23         ,  false  ,  50     ,  0       ,  0         ,  0       }, //State 22 (routine 4: Drain 1)
  {  0     ,  0        ,  1     ,  0     ,  24         ,  false  ,  100    ,  0       ,  1         ,  1       }, //State 23 (routine 4: Fill 1)
  {  1     ,  0        ,  1     ,  2     ,  25         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 24  (routine 4: Equilibrate 1)
  {  0     ,  0        ,  1     ,  2     ,  26         ,  3      ,  false  ,  0       ,  0         ,  1       }, //State 25 (routine 4: Vigorous Shake 1) 
  {  2     ,  0        ,  5     ,  1     ,  27         ,  false  ,  50     ,  0       ,  0         ,  0       }, //State 26 (routine 4: Drain 2)
  {  0     ,  0        ,  1     ,  0     ,  28         ,  false  ,  100    ,  0       ,  1         ,  1       }, //State 27 (routine 4: Fill 2)
  {  1     ,  0        ,  1     ,  2     ,  29         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 28 (routine 4: Equilibrate 2)
  {  0     ,  0        ,  3     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 29 (routine 4: Complete)

  {  0     ,  0        ,  1     ,  2     ,  31         ,  4      ,  false  ,  0       ,  0         ,  1       }, //State 30 (routine 5: Vigorous Shake 2)
  {  2     ,  0        ,  5     ,  1     ,  32         ,  false  ,  50     ,  0       ,  0         ,  0       }, //State 31 (routine 5: Drain 3)
  {  0     ,  0        ,  1     ,  0     ,  33         ,  false  ,  100    ,  0       ,  1         ,  1       }, //State 32 (routine 5: Fill 3)
  {  1     ,  0        ,  1     ,  2     ,  34         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 33  (routine 5: Equilibrate)
  {  0     ,  0        ,  1     ,  2     ,  35         ,  5      ,  false  ,  0       ,  0         ,  1       }, //State 34 (routine 5: Vigorous Shake 3)
  {  2     ,  0        ,  5     ,  1     ,  36         ,  false  ,  50     ,  0       ,  0         ,  0       }, //State 35 (routine 5: Drain 4)
  {  0     ,  0        ,  3     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 36 (routine 5: Complete)
 
  {  0     ,  0        ,  1     ,  0     ,  41         ,  false  ,  20     ,  0       ,  0         ,  1       }, //State 37 (routine 6: DC + Lysate Seed 1)
  {  3     ,  0        ,  4     ,  2     ,  39         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 38 (routine 6: Bag wash) *removed*
  {  3     ,  0        ,  4     ,  0     ,  40         ,  false  ,  20     ,  0       ,  0         ,  1       }, //State 39 (routine 6: DC + Lysate Seed 2) *removed*
  {  0     ,  0        ,  2     ,  2     ,  41         ,  1      ,  false  ,  0       ,  0         ,  1       }, //State 40 (routine 6: Gentle Shake) *removed*
  {  1     ,  0        ,  1     ,  2     ,  43         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 41 (routine 6: Equilibrate)
  {  0     ,  0        ,  2     ,  2     ,  43         ,  1      ,  false  ,  0       ,  0         ,  1       }, //State 42 (routine 6: Gentle Shake) *removed*
  {  0     ,  0        ,  3     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 43 (routine 6: Complete)

  //Day 8******************************************************************************************************************************************************************************
  {  0     ,  0        ,  1     ,  2     ,  45         ,  1      ,  false  ,  0       ,  0         ,  1       }, //State 44 (routine 7: Gentle Shake)
  {  2     ,  0        ,  5     ,  1     ,  46         ,  false  ,  50     ,  0       ,  0         ,  0       }, //State 45 (routine 7: Drain 1)
  {  0     ,  0        ,  1     ,  0     ,  47         ,  false  ,  100    ,  0       ,  1         ,  1       }, //State 46 (routine 7: Fill 1)
  {  1     ,  0        ,  1     ,  2     ,  48         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 47 (routine 7: Equilibrate 1)
  {  0     ,  0        ,  1     ,  2     ,  49         ,  6      ,  false  ,  0       ,  0         ,  1       }, //State 48 (routine 7: Vigorous Shake 1)
  {  2     ,  0        ,  5     ,  1     ,  50         ,  false  ,  50     ,  0       ,  0         ,  0       }, //State 49 (routine 7: Drain 2)
  {  0     ,  0        ,  1     ,  0     ,  51         ,  false  ,  100    ,  0       ,  1         ,  1       }, //State 50 (routine 7: Fill 2)
  {  1     ,  0        ,  1     ,  2     ,  52         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 51 (routine 7: Equilibrate 2)
  {  0     ,  0        ,  3     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 52 (routine 7: Complete)

  {  0     ,  0        ,  1     ,  2     ,  54         ,  7      ,  false  ,  0       ,  0         ,  1       }, //State 53 (routine 8: Vigorous Shake 2)
  {  2     ,  0        ,  5     ,  1     ,  55         ,  false  ,  50     ,  0       ,  0         ,  0       }, //State 54 (routine 8: Drain 3)
  {  0     ,  0        ,  1     ,  0     ,  56         ,  false  ,  100    ,  0       ,  1         ,  1       }, //State 55 (routine 8: Fill 3)
  {  1     ,  0        ,  1     ,  2     ,  57         ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 56 (routine 8: Equilibrate)
  {  0     ,  0        ,  1     ,  2     ,  58         ,  8      ,  false  ,  0       ,  0         ,  1       }, //State 57 (routine 8: Vigorous Shake 3)
  {  2     ,  0        ,  5     ,  1     ,  59         ,  false  ,  50     ,  0       ,  0         ,  0       }, //State 58 (routine 8: Drain 4)
  {  0     ,  0        ,  3     ,  2     ,  false      ,  false  ,  false  ,  0       ,  0         ,  1       }, //State 59 (routine 8: Complete)

  //New**********************************************************************************************************************************************************************************
  {  0     ,  0        ,  1     ,  2     ,  8          ,  1      ,  false  ,  0       ,  0         ,  1       }, //State 60 (routine 2: Gentle Shake 1)
  {  0     ,  0        ,  1     ,  1     ,  63         ,  false  ,  50     ,  0       ,  1         ,  1       }, //State 61 (routine 1: air pre-load)
  {  0     ,  0        ,  1     ,  1     ,  64         ,  false  ,  50     ,  1       ,  0         ,  1       }, //State 62 (routine 3: air pre-load)

  {  0     ,  0        ,  1     ,  2     ,  1          ,  false  ,  false  ,  1       ,  0         ,  1       }, //State 63 (routine 1: hang bag)
  {  0     ,  0        ,  1     ,  2     ,  18         ,  false  ,  false  ,  1       ,  0         ,  1       }, //State 64 (routine 3: hang bag)
}; //stateMachine()
