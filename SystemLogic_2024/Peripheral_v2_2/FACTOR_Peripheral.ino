//Select Pump/Arduino
int pumpNumber = 3;   //2 = Pump 2 (middle pump/Arduino); 3 = Pump 3 (bottom pump/Arduino)


#include <Stepper.h>

char SMArray[300] = {};
char flowmeterArray[300] = {};
char messageArray[300] = {};

bool arrayRead = 0;
int i = 0;

const int WMDIRpin = 6; 
const int WMSTEPpin = 7;
const int WMDISABLEpin = 3;

float WMSPEED;

//Watson-Marlow pump speed- calibrated  
float WM2speed20 = 3570.000; //originally 3570.000 for 20 m/min... this value is equivalent to 10ml/min
float WM2speed50 = 8925.000;
float WM2speed100 = 17500.000;
float WM2speed200 = 30000.000;

float WM3speed20 = 3570.000;  //originally 3570.000 for 20 m/min... this value is equivalent to 10ml/min
float WM3speed50 = 8925.000;
float WM3speed100 = 17500.000;
float WM3speed200 = 30000.000;


//Serial COM from Culture Unit
char buffer1[20];
int buffer1size = 20;



void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);    //Arduino 1
    Serial3.begin(115200);    //SMD Flow Sensor

    pinMode(WMDIRpin, OUTPUT);
    pinMode(WMSTEPpin, OUTPUT);
    pinMode(WMDISABLEpin, OUTPUT);
    digitalWrite(WMDISABLEpin, HIGH);


    

    //Setup SMD Sensor
    Serial3.println("setstreamrate 1");
    checkResponse();
    //Serial3.println("datastreamon");    //No response given aside from flow data
    //checkResponse();
    
}

void checkResponse()
{
    delay(1000);
    for(i = 0; Serial3.available() > 0 && i < sizeof(messageArray) - 2; i++)
    {
        messageArray[i] = Serial3.read(); delay(1);
    }
    messageArray[i] = 0x00;

    
    if(strcmp(messageArray, "ok") == 13)
    {
        if(pumpNumber == 2)         snprintf(messageArray, sizeof(messageArray) - 2, "Arduino 2 OK");
        else if(pumpNumber == 3)    snprintf(messageArray, sizeof(messageArray) - 2, "Arduino 2 OK");
    }
    else   
    {
        if(pumpNumber == 2)         snprintf(messageArray, sizeof(messageArray) - 2, "Arduino 2 Error.");
        else if(pumpNumber == 3)    snprintf(messageArray, sizeof(messageArray) - 2, "Arduino 3 Error.");
    }

    Serial.println(messageArray);
    Serial1.println(messageArray);
}

void loop()
{
    if(Serial.available() > 0)    SMWrite();
    if(Serial1.available() > 0)   pump();
    if(Serial3.available() > 0)   flowmeterWrite();

    //flowMonitor();
    
}



void flowMonitor()
{
    Serial3.println("datastreamon");

    for(i = 0; Serial3.available() > 0 && i < sizeof(flowmeterArray) - 2; i++)
        {
            flowmeterArray[i] = Serial3.read(); delay(1);
        }

    
    
    flowmeterArray[i] = 0x00; //delay(1);

    Serial.print("SMD: ");  Serial.println(flowmeterArray);

}


void SMWrite()
{
    for(i = 0; Serial.available() > 0 && i < sizeof(SMArray) - 2; i++)
    {
        SMArray[i] = Serial.read();
        SMArray[i+1] = 0x00; delay(1);
    }

    //Serial.println(strcmp(SMArray, "12"));

    if(strcmp(SMArray, "1") == 0)         snprintf(messageArray, sizeof(messageArray) - 2, "name");
    else if(strcmp(SMArray, "2") == 0)    snprintf(messageArray, sizeof(messageArray) - 2, "getversion");
    else if(strcmp(SMArray, "3") == 0)    snprintf(messageArray, sizeof(messageArray) - 2, "getmc");
    else if(strcmp(SMArray, "4") == 0)    snprintf(messageArray, sizeof(messageArray) - 2, "getoffset");
    else if(strcmp(SMArray, "5") == 0)    
    {
        snprintf(messageArray, sizeof(messageArray) - 2, "getsettings");
        arrayRead = 1;
    }
    else if(strcmp(SMArray, "6") == 0)    snprintf(messageArray, sizeof(messageArray) - 2, "enable_uart_checksum");
    else if(strcmp(SMArray, "7") == 0)    snprintf(messageArray, sizeof(messageArray) - 2, "disable_uart_checksum");
    else if(strcmp(SMArray, "8") == 0)    snprintf(messageArray, sizeof(messageArray) - 2, "clearstatus");
    else if(strcmp(SMArray, "9") == 0)    snprintf(messageArray, sizeof(messageArray) - 2, "datastreamon");
    else if(strcmp(SMArray, "10") == 0)   snprintf(messageArray, sizeof(messageArray) - 2, "datastreamoff");
    else if(strcmp(SMArray, "11") == 0)   snprintf(messageArray, sizeof(messageArray) - 2, "datasingle");
    else if(strcmp(SMArray, "12") == 32)  snprintf(messageArray, sizeof(messageArray) - 2, "setfilt %c%c%c", SMArray[3], SMArray[4], SMArray[5]);   //Set Average Filter Rate from 10 - 500 (format: 12 XXX);


    else if(strcmp(SMArray, "13") == 32)  snprintf(messageArray, sizeof(messageArray) - 2, "setstreamrate %c%c%c", SMArray[3], SMArray[4], SMArray[5]);   //Set Stream Rate from 1 - 400 Hz (format 13 XXX);
    else if(strcmp(SMArray, "14") == 32)  snprintf(messageArray, sizeof(messageArray) - 2, "set_datastream_data %c %c %c %c %c", SMArray[3], SMArray[4], SMArray[5], SMArray[6], SMArray[7]);   //Set Datastream Format
    else if(strcmp(SMArray, "15") == 0)   snprintf(messageArray, sizeof(messageArray) - 2, "accumzero");
    else if(strcmp(SMArray, "16") == 0)   snprintf(messageArray, sizeof(messageArray) - 2, "getsig");
    else if(strcmp(SMArray, "17") == 0)   snprintf(messageArray, sizeof(messageArray) - 2, "calzero");
    else if(strcmp(SMArray, "18") == 0)   snprintf(messageArray, sizeof(messageArray) - 2, "calflow");
    else if(strcmp(SMArray, "19") == 32)  snprintf(messageArray, sizeof(messageArray) - 2, "calrealflow %c%c%c%c%c", SMArray[3], SMArray[4], SMArray[5], SMArray[6], SMArray[7]);   //Flow Calibration Input
    else if(strcmp(SMArray, "20") == 0)   snprintf(messageArray, sizeof(messageArray) - 2, "setcal");
    else if(strcmp(SMArray, "21") == 32)  snprintf(messageArray, sizeof(messageArray) - 2, "tare %c%c%c", SMArray[3], SMArray[4], SMArray[5]);    //Enable/Disable Taring   (format: 21 ON or 21 OFF)


    Serial3.println(messageArray);
    Serial.print("Serial Input: "); Serial.println(SMArray);
    Serial.print("Input Command: "); Serial.println(messageArray); Serial.println();
}




void flowmeterWrite()
{
    i = 0;

    if(arrayRead)   //necessary b/c serial buffer fills before all characters from sensor are received and settings message is truncated.
    {
        for(int loop = 0; loop < 3; loop++)
        {
            delay(5);
            for(i; Serial3.available() > 0 && i < sizeof(flowmeterArray) - 2; i++)
            {
                flowmeterArray[i] = Serial3.read();
            }
        }
        arrayRead = !arrayRead;
    }
    else
    {
        for(i; Serial3.available() > 0 && i < sizeof(flowmeterArray) - 2; i++)
        {
            flowmeterArray[i] = Serial3.read(); delay(1);
        }

    }
    
    flowmeterArray[i] = 0x00; //delay(1);

    Serial.print("SMD: ");  Serial.println(flowmeterArray);
}

void pump()
{
    int i = 0;

    while(Serial1.available() > 0 && i < buffer1size)
    {
      buffer1[i] = Serial1.read(); i++; delay(1);
      buffer1[i] = 0x00;
    }

    Serial.print("FACTOR: "); Serial.println(buffer1);

    if(strstr(buffer1, "START") > 0)
    {
        //Copy flow rate from buffer1 to FlowRate buffer then convert to integer
        char WMspeed[4];
        WMspeed[0] = buffer1[5];
        WMspeed[1] = buffer1[6];
        WMspeed[2] = buffer1[7]; 
        WMspeed[3] = 0x00;

        if(pumpNumber == 2)
        {
            if(strcmp("020", WMspeed) == 0)         WMSPEED = WM2speed20;
            else if(strcmp("050", WMspeed) == 0)    WMSPEED = WM2speed50;
            else if(strcmp("100", WMspeed) == 0)    WMSPEED = WM2speed100;
            else if(strcmp("200", WMspeed) == 0)    WMSPEED = WM2speed200;
        }
        else if(pumpNumber == 3)
        {
            if(strcmp("020", WMspeed) == 0)         WMSPEED = WM3speed20;
            else if(strcmp("050", WMspeed) == 0)    WMSPEED = WM3speed50;
            else if(strcmp("100", WMspeed) == 0)    WMSPEED = WM3speed100;
            else if(strcmp("200", WMspeed) == 0)    WMSPEED = WM3speed200;
        }

        char WMdir[2];
        WMdir[0] = buffer1[8];
        WMdir[1] = 0x00;
        int WMDIR = atoi(WMdir);

        Serial.print("\nWMSPEED: ");  Serial.println(WMSPEED);
        //Serial.print("WMDIR: ");    Serial.println(WMDIR);

        start_motor(WMDIR, WMSPEED, 0);
    }

    else if(strcmp("STOP", buffer1) == 0)
    {
        digitalWrite(WMDISABLEpin, HIGH);           
    }
}    
