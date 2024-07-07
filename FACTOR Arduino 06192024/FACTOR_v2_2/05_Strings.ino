//Title Strings
const char title0[] PROGMEM = "Vessel Configuration";
const char title1[] PROGMEM = "Confirm Configuration";
const char title2[] PROGMEM = "FACTOR v2.2";
const char title3[] PROGMEM = "Day 0";
const char title4[] PROGMEM = "Day 7";
const char title5[] PROGMEM = "Day 8";
const char title6[] PROGMEM = "Begin Routine?";
const char title7[] PROGMEM = "1. PBMC Seed";
const char title8[] PROGMEM = "2. PBMC Washing";
const char title9[] PROGMEM = "3. DC Medium Fill";
const char title10[] PROGMEM = "4. Day 7 Harvest Part 1";
const char title11[] PROGMEM = "5. Day 7 Harvest Part 2";
const char title12[] PROGMEM = "6. DC + Lysate Seed";
const char title13[] PROGMEM = "7. Day 8 Harvest Part 1";
const char title14[] PROGMEM = "8. Day 8 Harvest Part 2";
const char title15[] PROGMEM = ": Fill";
const char title16[] PROGMEM = ": Drain";
const char title17[] PROGMEM = "Control Center";
const char title18[] PROGMEM = "Control Center- Linear Rail";
const char title19[] PROGMEM = "Control Center- Mitsubishi Servo";
const char title20[] PROGMEM = "Control Center- Pumps";
const char title21[] PROGMEM = "Control Center- Pinch Valves";
const char title22[] PROGMEM = "Manual Shake";
const char title23[] PROGMEM = "PBMC Seeding Complete";
const char title24[] PROGMEM = "PBMC Washing Complete";
const char title25[] PROGMEM = "DC Medium Fill Complete";
const char title26[] PROGMEM = "D7 Harvest Part 1 Complete";
const char title27[] PROGMEM = "D7 Harvest Part 2 Complete";
const char title28[] PROGMEM = "DC + Lysate Seed Complete";
const char title29[] PROGMEM = "D8 Harvest Part 1 Complete";
const char title30[] PROGMEM = "D8 Harvest Part 2 Complete";
const char title31[] PROGMEM = "Routine";
const char title32[] PROGMEM = "Routine Recovery";
const char title33[] PROGMEM = "Day 0- PBMC Seed";
const char title34[] PROGMEM = "Day 0- PBMC Wash";
const char title35[] PROGMEM = "Day 0- DC Medium Fill";
const char title36[] PROGMEM = "Day 7- Harvest Part 1";
const char title37[] PROGMEM = "Day 7- Harvest Part 2";
const char title38[] PROGMEM = "Day 8- Harvest Part 1";
const char title39[] PROGMEM = "Day 8- Harvest Part 2";
const char title40[] PROGMEM = "Confirm Routine Recovery";
const char title41[] PROGMEM = "Initialization Check";
const char title42[] PROGMEM = "Quick Schemes";

const char *const title_table[] PROGMEM = {title0, title1, title2, title3, title4, title5, title6, title7, title8, title9, title10, title11, title12, title13, title14, title15, title16, title17, title18, title19, title20, title21, title22, title23, title24, title25, title26, title27, title28, title29, title30, title31, title32, title33, title34, title35, title36, title37, title38, title39, title40, title41, title42};


void titleString(int form)
{
        if(form == 1)
        {
            stringBuilder(0, 1, 0, 2, 0,0);
            centerMessageArray(39, 0);
            writeDisplayString(1);
        }
        else if(form == 2)    //Control Center- Linear Rail
        {
            stringBuilder(0, 1, 0, 18, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(2);
        }
        else if(form == 3)    //Control Center- Pumps
        {
            stringBuilder(0, 1, 0, 20, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(37);
        }
        else if(form == 4)    //Control Center
        {
            stringBuilder(0, 1, 0, 17, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(3);
        }
        else if(form == 10) //Vessel Configuration Confirmation
        {
            stringBuilder(0, 1, 0, 1, 0, 0);
            if(routine == 1 || routine == 2 || routine == 3)    stringBuilder(0, 0, 0, 3, 0, 1);
            else if(routine == 4 || routine == 5 || routine == 6)               stringBuilder(0, 0, 0, 4, 0, 1);
            else if(routine == 7 || routine == 8)               stringBuilder(0, 0, 0, 5, 0, 1);

            centerMessageArray(39, 0);
            writeDisplayString(14);
        }
        else if(form == 11 || form == 12 || form == 13 || form == 18)
        {
            if(routine == 1)        stringBuilder(0, 1, 0, 7, 0, 0);
            else if(routine == 2)   stringBuilder(0, 1, 0, 8, 0, 0);
            else if(routine == 3)   stringBuilder(0, 1, 0, 9, 0, 0);
            else if(routine == 4)   stringBuilder(0, 1, 0, 10, 0, 0);
            else if(routine == 5)   stringBuilder(0, 1, 0, 11, 0, 0);
            else if(routine == 6)   stringBuilder(0, 1, 0, 12, 0, 0);
            else if(routine == 7)   stringBuilder(0, 1, 0, 13, 0, 0);
            else if(routine == 8)   stringBuilder(0, 1, 0, 14, 0, 0);
            else if(command == MANUAL)    stringBuilder(0, 1, 0, 22, 0, 0);   //manual shake

            //check if DPBS Fill or Drain Stats
            for(int i = 0; i < NUM_DRAINSTATES; i++)   //states with 3 timers
            {
                if(stateIndex == drainStates[i])    stringBuilder(0, 0, 0, 16, 0, 0);
            }

            for(int i = 0; i < NUM_FILLSTATES; i++)   //states with 3 timers
            {
                if(stateIndex == fillStates[i])     stringBuilder(0, 0, 0, 15, 0, 0);
            }

            centerMessageArray(39, 0);

            if(form == 11)        writeDisplayString(17);
            else if(form == 12)   writeDisplayString(25);
            else if(form == 13)   writeDisplayString(28);
            else if (form == 18)  writeDisplayString(39);
        }
        else if(form == 5)
        {
            stringBuilder(0, 1, 0, 0, 0, 0);
            stringBuilder(0, 0, 0, 4, 0, 1);
            centerMessageArray(39, 0);
            writeDisplayString(7);
        }
        else if(form == 22)
        {
            stringBuilder(0, 1, 0, 0, 0, 0);
            stringBuilder(0, 0, 0, 3, 0, 1);
            centerMessageArray(39, 0);
            writeDisplayString(58);
        }
        else if(form == 23)
        {
            stringBuilder(0, 1, 0, 0, 0, 0);
            stringBuilder(0, 0, 0, 5, 0, 1);
            centerMessageArray(39, 0);
            writeDisplayString(62);
        }
        else if(form == 7)
        {
            stringBuilder(0, 1, 0, 6, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(9);
        }
        else if(form == 24)
        {
            stringBuilder(0, 1, 0, 32, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(51);
        }
        else if(form == 25)
        {
            stringBuilder(0, 1, 0, 33, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(63);
        }
        else if(form == 26)
        {
            stringBuilder(0, 1, 0, 34, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(64);
        }
        else if(form == 27)
        {
            stringBuilder(0, 1, 0, 35, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(65);
        }
        else if(form == 28)
        {
            stringBuilder(0, 1, 0, 36, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(66);
        }
        else if(form == 29)
        {
            stringBuilder(0, 1, 0, 37, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(67);
        }
        else if(form == 30)
        {
            stringBuilder(0, 1, 0, 38, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(68);
        }
        else if(form == 31)
        {
            stringBuilder(0, 1, 0, 39, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(69);
        }
        else if(form == 32)   //Routine Recovery Routine
        {
            stringBuilder(0, 1, 0, 40, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(70);
        }
        else if(form == 33)   //Initialization Check
        {
            stringBuilder(0, 1, 0, 41, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(73);
        }
        else if(form == 34)   //Quick Schemes
        {
            stringBuilder(0, 1, 0, 42, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(24);
        }


        else if(form == 6)   //Day 0 Routine selection
        {
            stringBuilder(0, 1, 0, 3, 0, 0);
            stringBuilder(0, 0, 0, 31, 0, 1);
            centerMessageArray(39, 0);
            writeDisplayString(8);
        }
        else if(form == 8)   //Day 7 Routine selection
        {
            stringBuilder(0, 1, 0, 4, 0, 0);
            stringBuilder(0, 0, 0, 31, 0, 1);
            centerMessageArray(39, 0);
            writeDisplayString(12);
        }
        else if(form == 9)   //Day 8 Routine selection
        {
            stringBuilder(0, 1, 0, 5, 0, 0);
            stringBuilder(0, 0, 0, 31, 0, 1);
            centerMessageArray(39, 0);
            writeDisplayString(13);
        }
        else if(form == 14)   //Complete
        {
            if(stateIndex == 7 || recoveryState == 7)          stringBuilder(0, 1, 0, 23, 0, 0);
            else if(stateIndex == 17 || recoveryState == 17)   stringBuilder(0, 1, 0, 24, 0, 0);
            else if(stateIndex == 20 || recoveryState == 20)   stringBuilder(0, 1, 0, 25, 0, 0);
            else if(stateIndex == 29 || recoveryState == 29)   stringBuilder(0, 1, 0, 26, 0, 0);
            else if(stateIndex == 36 || recoveryState == 36)   stringBuilder(0, 1, 0, 27, 0, 0);
            else if(stateIndex == 43 || recoveryState == 43)   stringBuilder(0, 1, 0, 28, 0, 0);
            else if(stateIndex == 52 || recoveryState == 52)   stringBuilder(0, 1, 0, 29, 0, 0);
            else if(stateIndex == 59 || recoveryState == 59)   stringBuilder(0, 1, 0, 30, 0, 0);

            centerMessageArray(39, 0);
            writeDisplayString(34);            
        }
        else if(form == 15)   //Control Center- Mitsubishi Servo
        {
            stringBuilder(0, 1, 0, 19, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(36);
        }
        else if(form == 17)   //Control Center- Pinch Valve
        {
            stringBuilder(0, 1, 0, 21, 0, 0);
            centerMessageArray(39, 0);
            writeDisplayString(38);
        }

        

} //titleString()



//Message Strings
const char message0[] PROGMEM = "1L CellSTACK";
const char message1[] PROGMEM = "2L CellSTACK";
const char message2[] PROGMEM = "Empty";
const char message3[] PROGMEM = "Balance";
const char message4[] PROGMEM = "Routine:";

const char message5[] PROGMEM = "1. PBMC Seed";
const char message6[] PROGMEM = "2. PBMC Wash";
const char message7[] PROGMEM = "3. DC Medium Fill";
const char message8[] PROGMEM = "4. Day 7 Harvest Part 1";
const char message9[] PROGMEM = "5. Day 7 Harvest Part 2";
const char message10[] PROGMEM = "6. DC + Lysate Seed";
const char message11[] PROGMEM = "7. Day 8 Harvest Part 1";
const char message12[] PROGMEM = "8. Day 8 Harvest Part 2";

const char message13[] PROGMEM = "Top Position:";
const char message14[] PROGMEM = "Middle Position:";
const char message15[] PROGMEM = "Bottom Position:";
const char message16[] PROGMEM = "COMPLETE!";
const char message17[] PROGMEM = "Gentle Shake";
const char message18[] PROGMEM = "Time Remaining:";
const char message19[] PROGMEM = "Paused";
const char message20[] PROGMEM = "Step:";

const char message21[] PROGMEM = "Vigorous Shake";
const char message22[] PROGMEM = "Equilibrating";
const char message23[] PROGMEM = "Bag Wash";
const char message24[] PROGMEM = "50 mL/min";
const char message25[] PROGMEM = "100 mL/min";
const char message26[] PROGMEM = "200 mL/min";
const char message27[] PROGMEM = "Calibrate";
const char message28[] PROGMEM = "T-Flask(s)";
const char message29[] PROGMEM = "OPEN";
const char message30[] PROGMEM = "CLOSED";
const char message31[] PROGMEM = "20 mL/min";

const char message32[] PROGMEM = "PBMC Seed";
const char message33[] PROGMEM = "Equilibrate";
const char message34[] PROGMEM = "Routine Complete";
const char message35[] PROGMEM = "DPBS Fill 1";
const char message36[] PROGMEM = "DPBS Fill 2";
const char message37[] PROGMEM = "DPBS Fill 3";
const char message38[] PROGMEM = "Equilibrate 1";
const char message39[] PROGMEM = "Equilibrate 2";
const char message40[] PROGMEM = "Equilibrate 3";
const char message41[] PROGMEM = "Drain 1";
const char message42[] PROGMEM = "Drain 2";
const char message43[] PROGMEM = "Drain 3";
const char message44[] PROGMEM = "Drain 4";
const char message45[] PROGMEM = "Gentle Shake 1";
const char message46[] PROGMEM = "Gentle Shake 2";
const char message47[] PROGMEM = "Vigorous Shake 1";
const char message48[] PROGMEM = "Vigorous Shake 2";
const char message49[] PROGMEM = "Vigorous Shake 3";
const char message50[] PROGMEM = "DC Medium Fill";
const char message51[] PROGMEM = "Linear Rail Check";
const char message52[] PROGMEM = "Servo Check";
const char message53[] PROGMEM = "Pump Check";
const char message54[] PROGMEM = "Flow Meter Check";

const char message55[] PROGMEM = "F 20 mL/min";
const char message56[] PROGMEM = "R 20 mL/min";
const char message57[] PROGMEM = "F 50 mL/min";
const char message58[] PROGMEM = "R 50 mL/min";
const char message59[] PROGMEM = "F 100 mL/min";
const char message60[] PROGMEM = "R 100 mL/min";
const char message61[] PROGMEM = "OFF";
const char message62[] PROGMEM = "Gentle Shake 3";
const char message63[] PROGMEM = "Day 0";
const char message64[] PROGMEM = "Day 7";
const char message65[] PROGMEM = "Day 8";
const char message66[] PROGMEM = "Day 7/8";
const char message67[] PROGMEM = "Vigorous Shake 4";
const char message68[] PROGMEM = ": CS";
const char message69[] PROGMEM = ": TF";

const char *const message_table[] PROGMEM = {message0, message1, message2, message3, message4, message5, message6, message7, message8, message9, message10, message11, message12, message13, message14, message15, message16, message17, message18, message19, message20, message21, message22, message23, message24, message25, message26, message27, message28, message29, message30, message31, message32, message33, message34, message35, message36, message37, message38, message39, message40, message41, message42, message43, message44, message45, message46, message47, message48, message49, message50, message51, message52, message53, message54, message55, message56, message57, message58, message59, message60, message61, message62, message63, message64, message65, message66, message67, message68, message69};

void messageString(int form)
{
    if(form == 3)   //Control Center- Pumps
    {
        pumpString();

        if(manualFlowRate == 20)          stringBuilder(2, 1, 0, 31, 0, 0);
        else if(manualFlowRate == 50)     stringBuilder(2, 1, 0, 24, 0, 0);
        else if(manualFlowRate == 100)    stringBuilder(2, 1, 0, 25, 0, 0);
        writeDisplayString(41);
    }
    else if(form == 32)
    {
        recoveryString();
        writeDisplayString(72);
    }
    else if(form == 10 || form == 7)
    {    
        stringBuilder(2, 1, 0, 4, 1, 0);

        if(routine == 1)        stringBuilder(2, 0, 0, 5, 0, 1);
        else if(routine == 2)   stringBuilder(2, 0, 0, 6, 0, 1);
        else if(routine == 3)   stringBuilder(2, 0, 0, 7, 0, 1);
        else if(routine == 4)   stringBuilder(2, 0, 0, 8, 0, 1);
        else if(routine == 5)   stringBuilder(2, 0, 0, 9, 0, 1);
        else if(routine == 6)   stringBuilder(2, 0, 0, 10, 0, 1);
        else if(routine == 7)   stringBuilder(2, 0, 0, 11, 0, 1);
        else if(routine == 8)   stringBuilder(2, 0, 0, 12, 0, 1);

        //Serial.println(messageArray);
        if(form == 10)         writeDisplayString(15);
        else if(form == 7)     writeDisplayString(10);

        stringBuilder(2, 1, 0, 13, 1, 0);

        if(form == 10)
        {
            if(pos1_config == 1)        stringBuilder(2, 0, 0, 0, 0, 5);
            else if(pos1_config == 2)   stringBuilder(2, 0, 0, 1, 0, 5);
            else if(pos1_config == 3)   
            {
                if(routine == 1 || routine == 2 || routine == 3)                        stringBuilder(2, 0, 0, 2, 0, 5);
                else if(routine == 4 || routine == 5 || routine == 6 || routine == 7 || routine == 8)   stringBuilder(2, 0, 0, 3, 0, 5);
            }
            else if(pos1_config == 4)   stringBuilder(2, 0, 0, 28, 0, 5);

            stringBuilder(2, 0, 0, 14, 1, 0);

            if(pos2_config == 1)        stringBuilder(2, 0, 0, 0, 0, 2);
            else if(pos2_config == 2)   stringBuilder(2, 0, 0, 1, 0, 2);
            else if(pos2_config == 3)   
            {
                if(routine == 1 || routine == 2 || routine == 3)                        stringBuilder(2, 0, 0, 2, 0, 2);
                else if(routine == 4 || routine == 5 || routine == 6 || routine == 7 || routine == 8)   stringBuilder(2, 0, 0, 3, 0, 2);
            }
            else if(pos2_config == 4)   stringBuilder(2, 0, 0, 28, 0, 2);

            stringBuilder(2, 0, 0, 15, 1, 0);

            if(pos3_config == 1)        stringBuilder(2, 0, 0, 0, 0, 2);
            else if(pos3_config == 2)   stringBuilder(2, 0, 0, 1, 0, 2);
            else if(pos3_config == 3)   
            {
                if(routine == 1 || routine == 2 || routine == 3)                        stringBuilder(2, 0, 0, 2, 0, 2);
                else if(routine == 4 || routine == 5 || routine == 6 || routine == 7 || routine == 8)   stringBuilder(2, 0, 0, 3, 0, 2);
            }
            else if(pos3_config == 4)   stringBuilder(2, 0, 0, 28, 0, 2);
            
            //Serial.println(messageArray);
            writeDisplayString(16); 
        }
    }

    else if(form == 11)
    {
        //stringBuilder(2, 1, 0, 18, 1, 0);
        //writeDisplayString(24);

        pos1String();
        writeDisplayString(21);
       
        pos2String();
        writeDisplayString(22);

        pos3String();
        writeDisplayString(23);
    }
    else if(form == 12)   //Paused
    {
        stringBuilder(2, 1, 0, 19, 1, 0);
        centerMessageArray(37, 0);
        writeDisplayString(26);
    }
    else if(form == 13)
    {
        if (stateIndex == 4 || stateIndex == 6 || stateIndex == 11 || stateIndex == 15 || stateIndex == 21 || stateIndex == 40 || stateIndex == 42 || stateIndex == 44 || stateIndex == 60) // gentle shake
        {
          stringBuilder(2, 1, 0, 17, 0, 0);
          centerMessageArray(37, 0);
          writeDisplayString(29);
        }
        else if (stateIndex == 25 || stateIndex == 30 || stateIndex == 34 || stateIndex == 48 || stateIndex == 53 || stateIndex == 57) // vigorous shake
        {
          stringBuilder(2, 1, 0, 21, 0, 0);
          centerMessageArray(37, 0);
          writeDisplayString(29);
        }
        else if (stateIndex == 5 || stateIndex == 10 || stateIndex == 14 || stateIndex == 19 || stateIndex == 24 || stateIndex == 28 || stateIndex == 41 || stateIndex == 47 || stateIndex == 56) // equilibrating
        {
          stringBuilder(2, 1, 0, 22, 0, 0);
          centerMessageArray(37, 0);
          writeDisplayString(29);
        }
        else if(command == MANUAL)    //manual shake
        {
            if(buttonIndex == 57)   
            {
                stringBuilder(2, 1, 0, 17, 0, 0);
                stringBuilder(2, 0, 0, 63, 0, 1);
            }
            else if(buttonIndex == 8)   
            {
                stringBuilder(2, 1, 0, 17, 0, 0);
                stringBuilder(2, 0, 0, 66, 0, 1);
            }
            else if(buttonIndex == 58)
            {
                stringBuilder(2, 1, 0, 47, 0, 0);
                stringBuilder(2, 0, 0, 64, 0, 1);
            }
            else if(buttonIndex == 59)
            {
                stringBuilder(2, 1, 0, 48, 0, 0);
                stringBuilder(2, 0, 0, 64, 0, 1);
            }
            else if(buttonIndex == 64)
            {
                stringBuilder(2, 1, 0, 49, 0, 0);
                stringBuilder(2, 0, 0, 64, 0, 1);
            }
            else if(buttonIndex == 67)
            {
                stringBuilder(2, 1, 0, 47, 0, 0);
                stringBuilder(2, 0, 0, 65, 0, 1);
                stringBuilder(2, 0, 0, 68, 0, 0);
            }
            else if(buttonIndex == 66)
            {
                stringBuilder(2, 1, 0, 48, 0, 0);
                stringBuilder(2, 0, 0, 65, 0, 1);
                stringBuilder(2, 0, 0, 68, 0, 0);
            }
            else if(buttonIndex == 68)
            {
                stringBuilder(2, 1, 0, 49, 0, 0);
                stringBuilder(2, 0, 0, 65, 0, 1);
                stringBuilder(2, 0, 0, 68, 0, 0);
            }
            else if(buttonIndex == 179)
            {
                stringBuilder(2, 1, 0, 67, 0, 0);
                stringBuilder(2, 0, 0, 65, 0, 1);
                stringBuilder(2, 0, 0, 68, 0, 0);
            }
            else if(buttonIndex == 80)
            {
                stringBuilder(2, 1, 0, 47, 0, 0);
                stringBuilder(2, 0, 0, 65, 0, 1);
                stringBuilder(2, 0, 0, 69, 0, 0);
            }
            else if(buttonIndex == 81)
            {
                stringBuilder(2, 1, 0, 48, 0, 0);
                stringBuilder(2, 0, 0, 65, 0, 1);
                stringBuilder(2, 0, 0, 69, 0, 0);
            }
            else if(buttonIndex == 82)
            {
                stringBuilder(2, 1, 0, 49, 0, 0);
                stringBuilder(2, 0, 0, 65, 0, 1);
                stringBuilder(2, 0, 0, 69, 0, 0);
            }
            else if(buttonIndex == 180)
            {
                stringBuilder(2, 1, 0, 67, 0, 0);
                stringBuilder(2, 0, 0, 65, 0, 1);
                stringBuilder(2, 0, 0, 69, 0, 0);
            }
            
            centerMessageArray(37, 0);
            writeDisplayString(29);  
        }

        stringBuilder(2, 1, 0, 18, 0, 0);
        writeDisplayString(30);
    }
    else if(form == 17)    //Control Center- Pinch Valve
    {
        valveString();  
    }
}

void recoveryString()
{
    stringBuilder(2, 1, 0, 4, 0, 0);
    
    if(buttonIndex == 122)        
    {
        stringBuilder(2, 0, 0, 5, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 32, 0, 1);
    }
    else if(buttonIndex == 123)   
    {
        stringBuilder(2, 0, 0, 5, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 33, 0, 1);
    }
    else if(buttonIndex == 124)   
    {
        stringBuilder(2, 0, 0, 5, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 34, 0, 1);
    }
    else if(buttonIndex == 127)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 35, 0, 1);
    }
    else if(buttonIndex == 128)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 38, 0, 1);
    }
    else if(buttonIndex == 129)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 46, 0, 1);
    }
    else if(buttonIndex == 130)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 42, 0, 1);
    }
    else if(buttonIndex == 131)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 36, 0, 1);
    }
    else if(buttonIndex == 132)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 39, 0, 1);
    }
    else if(buttonIndex == 133)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 62, 0, 1);
    }
    else if(buttonIndex == 134)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 43, 0, 1);
    }
    else if(buttonIndex == 135)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 34, 0, 1);
    }
    else if(buttonIndex == 146)
    {
        stringBuilder(2, 0, 0, 7, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 50, 0, 1);
    }
    else if(buttonIndex == 139)
    {
        stringBuilder(2, 0, 0, 7, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 33, 0, 1);
    }
    else if(buttonIndex == 140)
    {
        stringBuilder(2, 0, 0, 7, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 34, 0, 1);
    }
    else if(buttonIndex == 121)
    {
        stringBuilder(2, 0, 0, 8, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 41, 0, 1);
    }
    else if(buttonIndex == 126)
    {
        stringBuilder(2, 0, 0, 8, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 35, 0, 1);
    }
    else if(buttonIndex == 137)
    {
        stringBuilder(2, 0, 0, 8, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 38, 0, 1);
    }
    else if(buttonIndex == 138)
    {
        stringBuilder(2, 0, 0, 8, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 47, 0, 1);
    }
    else if(buttonIndex == 141)
    {
        stringBuilder(2, 0, 0, 8, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 42, 0, 1);
    }
    else if(buttonIndex == 142)
    {
        stringBuilder(2, 0, 0, 8, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 36, 0, 1);
    }
    else if(buttonIndex == 143)
    {
        stringBuilder(2, 0, 0, 8, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 39, 0, 1);
    }
    else if(buttonIndex == 144)
    {
        stringBuilder(2, 0, 0, 8, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 34, 0, 1);
    }
    else if(buttonIndex == 148)
    {
        stringBuilder(2, 0, 0, 9, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 43, 0, 1);
    }
    else if(buttonIndex == 149)
    {
        stringBuilder(2, 0, 0, 9, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 37, 0, 1);
    }
    else if(buttonIndex == 150)
    {
        stringBuilder(2, 0, 0, 9, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 40, 0, 1);
    }
    else if(buttonIndex == 151)
    {
        stringBuilder(2, 0, 0, 9, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 49, 0, 1);
    }
    else if(buttonIndex == 152)
    {
        stringBuilder(2, 0, 0, 9, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 44, 0, 1);
    }
    else if(buttonIndex == 156)
    {
        stringBuilder(2, 0, 0, 9, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 34, 0, 1);
    }
    else if(buttonIndex == 154)
    {
        stringBuilder(2, 0, 0, 11, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 41, 0, 1);
    }
    else if(buttonIndex == 155)
    {
        stringBuilder(2, 0, 0, 11, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 35, 0, 1);
    }
    else if(buttonIndex == 157)
    {
        stringBuilder(2, 0, 0, 11, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 38, 0, 1);
    }
    else if(buttonIndex == 158)
    {
        stringBuilder(2, 0, 0, 11, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 47, 0, 1);
    }
    else if(buttonIndex == 159)
    {
        stringBuilder(2, 0, 0, 11, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 42, 0, 1);
    }
    else if(buttonIndex == 160)
    {
        stringBuilder(2, 0, 0, 11, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 36, 0, 1);
    }
    else if(buttonIndex == 161)
    {
        stringBuilder(2, 0, 0, 11, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 39, 0, 1);
    }
    else if(buttonIndex == 162)
    {
        stringBuilder(2, 0, 0, 11, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 34, 0, 1);
    }
    else if(buttonIndex == 165)
    {
        stringBuilder(2, 0, 0, 12, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 43, 0, 1);
    }
    else if(buttonIndex == 166)
    {
        stringBuilder(2, 0, 0, 12, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 37, 0, 1);
    }
    else if(buttonIndex == 167)
    {
        stringBuilder(2, 0, 0, 12, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 40, 0, 1);
    }
    else if(buttonIndex == 168)
    {
        stringBuilder(2, 0, 0, 12, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 49, 0, 1);
    }
    else if(buttonIndex == 169)
    {
        stringBuilder(2, 0, 0, 12, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 44, 0, 1);
    }
    else if(buttonIndex == 170)
    {
        stringBuilder(2, 0, 0, 12, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 34, 0, 1);
    }
    else if(buttonIndex == 173)
    {
        stringBuilder(2, 0, 0, 6, 0, 1);
        stringBuilder(2, 0, 0, 20, 2, 0);
        stringBuilder(2, 0, 0, 45, 0, 1);
    }
}

//Instruction Strings
const char instruction0[] PROGMEM = "Clamp bags.";
const char instruction1[] PROGMEM = "Remove tubing from pinch valve and pumps.";
const char instruction2[] PROGMEM = "Remove CellSTACKs from FACTOR.";
const char instruction3[] PROGMEM = "Place CellSTACKs in incubator for 2 hours.";
const char instruction4[] PROGMEM = "Clamp and seal off bags.";
const char instruction5[] PROGMEM = "Weld DC Medium bag to Inlet tubing.";
const char instruction6[] PROGMEM = "Proceed to Day 0: 3. DC Medium Fill.";
const char instruction7[] PROGMEM = "Seal off DC Medium bag.";
const char instruction8[] PROGMEM = "Seal off each CellSTACK from the manifold tubing.";
const char instruction9[] PROGMEM = "Place CellSTACKs in incubator for 7 days.";

const char instruction10[] PROGMEM = "Ensure:";
const char instruction11[] PROGMEM = "Bags are unclamped.";
const char instruction12[] PROGMEM = "Tubing is secure.";
const char instruction13[] PROGMEM = "CellSTACKs are secure.";
const char instruction14[] PROGMEM = "Hold PBMC bag upside down with\n   tubing up.";
const char instruction15[] PROGMEM = "Hold DC Medium bag upside down with\n   tubing up";
const char instruction16[] PROGMEM = "Hang PBMC bag from bag hook.";
const char instruction17[] PROGMEM = "Hang DC Medium bag from bag hook.";

const char instruction18[] PROGMEM = "Place CellSTACKs in fridge for 30 minutes.";
const char instruction19[] PROGMEM = "Seal off PBMC bag.";
const char instruction20[] PROGMEM = "";
const char instruction21[] PROGMEM = "";
const char instruction22[] PROGMEM = "";
const char instruction23[] PROGMEM = "";
const char instruction24[] PROGMEM = "";
const char instruction25[] PROGMEM = "";
const char instruction26[] PROGMEM = "";
const char instruction27[] PROGMEM = "";
const char instruction28[] PROGMEM = "";
const char instruction29[] PROGMEM = "";
const char instruction30[] PROGMEM = "";


const char *const instruction_table[] PROGMEM = {instruction0, instruction1, instruction2, instruction3, instruction4, instruction5, instruction6, instruction7, instruction8, instruction9, instruction10, instruction11, instruction12, instruction13, instruction14, instruction15, instruction16, instruction17, instruction18, instruction19, instruction20, instruction21, instruction22, instruction23, instruction24, instruction25, instruction26, instruction27, instruction28, instruction29, instruction30};

void instructionString(int form)
{
    if(form == 7)   
    {
        stringBuilder(1, 1, 0, 10, 0, 0);
        stringBuilder(1, 0, 1, 11, 1, 0);
        stringBuilder(1, 0, 2, 12, 1, 0);
        stringBuilder(1, 0, 3, 13, 1, 0);

        if(routine == 1)        stringBuilder(1, 0, 4, 14, 1, 0);
        else if(routine == 3)   stringBuilder(1, 0, 4, 15, 1, 0);

        writeDisplayString(11);
    }
    else if(form == 14)
    {
        if(stateIndex == 7 || recoveryState == 7)   
        {
            stringBuilder(1, 1, 1, 19, 1, 0);
            stringBuilder(1, 0, 2, 1, 1, 0);
            stringBuilder(1, 0, 3, 2, 1, 0);
            stringBuilder(1, 0, 4, 3, 1, 0);
        }
        else if(stateIndex == 17 || recoveryState == 17)
        {
             stringBuilder(1, 1, 1, 4, 1, 0);
             stringBuilder(1, 0, 2, 5, 1, 0);
             stringBuilder(1, 0, 3, 6, 1, 0);
        }
        else if(stateIndex == 20 || recoveryState == 20)
        {
            stringBuilder(1, 1, 1, 7, 1, 0);
            stringBuilder(1, 0, 2, 8, 1, 0);
            stringBuilder(1, 0, 3, 2, 1, 0);
            stringBuilder(1, 0, 4, 9, 1, 0);
        }
        else if(stateIndex == 29 || stateIndex == 52 || recoveryState == 29 || recoveryState == 52)
        {
            stringBuilder(1, 1, 1, 0, 1, 0);
            stringBuilder(1, 0, 2, 1, 1, 0);
            stringBuilder(1, 0, 3, 2, 1, 0);
            stringBuilder(1, 0, 4, 18, 1, 0);
        }
        else if(stateIndex == 36 || stateIndex == 59 || recoveryState == 36 || recoveryState == 59)
        {
            stringBuilder(1, 1, 1, 4, 1, 0);
            stringBuilder(1, 0, 2, 1, 1, 0);
            stringBuilder(1, 0, 3, 2, 1, 0);
        }

        writeDisplayString(33);
    } 
    else if(form == 18)
    {
        if(routine == 1)        stringBuilder(1, 1, 1, 16, 1, 0);
        else if(routine == 3)   stringBuilder(1, 1, 1, 17, 1, 0);
        writeDisplayString(40);
    }  
}



void pos1String() //Top
{
    if(pos1_config == 1)        stringBuilder(2, 1, 0, 0, 0, 0);
    else if(pos1_config == 2)   stringBuilder(2, 1, 0, 1, 0, 0);
    else if(pos1_config == 3)   
    {
        if(routine == 1 || routine == 2 || routine == 3)                        stringBuilder(2, 1, 0, 2, 0, 0);
        else if(routine == 4 || routine == 5 || routine == 6 || routine == 7 || routine == 8)   stringBuilder(2, 1, 0, 3, 0, 0);
    }
    else if(pos1_config == 4)   stringBuilder(2, 1, 0, 28, 0, 0);
}

void pos2String() //Middle
{
    if(pos2_config == 1)        stringBuilder(2, 1, 0, 0, 0, 0);
    else if(pos2_config == 2)   stringBuilder(2, 1, 0, 1, 0, 0);
    else if(pos2_config == 3)   
    {
        if(routine == 1 || routine == 2 || routine == 3)                        stringBuilder(2, 1, 0, 2, 0, 0);
        else if(routine == 4 || routine == 5 || routine == 6 || routine == 7 || routine == 8)   stringBuilder(2, 1, 0, 3, 0, 0);
    }
    else if(pos2_config == 4)   stringBuilder(2, 1, 0, 28, 0, 0);
}

void pos3String() //Bottom
{
    if(pos3_config == 1)        stringBuilder(2, 1, 0, 0, 0, 0);
    else if(pos3_config == 2)   stringBuilder(2, 1, 0, 1, 0, 0);
    else if(pos3_config == 3)   
    {
        if(routine == 1 || routine == 2 || routine == 3)           stringBuilder(2, 1, 0, 2, 0, 0);
        else if(routine == 4 || routine == 5 || routine == 6 || routine == 7 || routine == 8)   stringBuilder(2, 1, 0, 3, 0, 0);
    }
    else if(pos3_config == 4)   stringBuilder(2, 1, 0, 28, 0, 0);
}

void valveString()
{
    if(valve1Status)          stringBuilder(2, 1, 0, 29, 0, 0);
    else if(!valve1Status)    stringBuilder(2, 1, 0, 30, 0, 0);
    writeDisplayString(52);

    if(valve2Status)          stringBuilder(2, 1, 0, 29, 0, 0);
    else if(!valve2Status)    stringBuilder(2, 1, 0, 30, 0, 0);
    writeDisplayString(53);

    if(!valve3Status)         stringBuilder(2, 1, 0, 29, 0, 0);
    else if(valve3Status)     stringBuilder(2, 1, 0, 30, 0, 0);
    writeDisplayString(54);
}

void pumpString()
{
    if(WM1_status == 2)                               stringBuilder(2, 1, 0, 61, 0, 0); 
    else if(WM1_status == 0 && WM1_flowRate == 20)    stringBuilder(2, 1, 0, 55, 0, 0);
    else if(WM1_status == 0 && WM1_flowRate == 50)    stringBuilder(2, 1, 0, 57, 0, 0);
    else if(WM1_status == 0 && WM1_flowRate == 100)   stringBuilder(2, 1, 0, 59, 0, 0);
    else if(WM1_status == 1 && WM1_flowRate == 20)    stringBuilder(2, 1, 0, 56, 0, 0);
    else if(WM1_status == 1 && WM1_flowRate == 50)    stringBuilder(2, 1, 0, 58, 0, 0);
    else if(WM1_status == 1 && WM1_flowRate == 100)   stringBuilder(2, 1, 0, 60, 0, 0);

    writeDisplayString(76);

    if(WM2_status == 2)                               stringBuilder(2, 1, 0, 61, 0, 0); 
    else if(WM2_status == 0 && WM2_flowRate == 20)    stringBuilder(2, 1, 0, 55, 0, 0);
    else if(WM2_status == 0 && WM2_flowRate == 50)    stringBuilder(2, 1, 0, 57, 0, 0);
    else if(WM2_status == 0 && WM2_flowRate == 100)   stringBuilder(2, 1, 0, 59, 0, 0);
    else if(WM2_status == 1 && WM2_flowRate == 20)    stringBuilder(2, 1, 0, 56, 0, 0);
    else if(WM2_status == 1 && WM2_flowRate == 50)    stringBuilder(2, 1, 0, 58, 0, 0);
    else if(WM2_status == 1 && WM2_flowRate == 100)   stringBuilder(2, 1, 0, 60, 0, 0);

    writeDisplayString(77);

    if(WM3_status == 2)                               stringBuilder(2, 1, 0, 61, 0, 0); 
    else if(WM3_status == 0 && WM3_flowRate == 20)    stringBuilder(2, 1, 0, 55, 0, 0);
    else if(WM3_status == 0 && WM3_flowRate == 50)    stringBuilder(2, 1, 0, 57, 0, 0);
    else if(WM3_status == 0 && WM3_flowRate == 100)   stringBuilder(2, 1, 0, 59, 0, 0);
    else if(WM3_status == 1 && WM3_flowRate == 20)    stringBuilder(2, 1, 0, 56, 0, 0);
    else if(WM3_status == 1 && WM3_flowRate == 50)    stringBuilder(2, 1, 0, 58, 0, 0);
    else if(WM3_status == 1 && WM3_flowRate == 100)   stringBuilder(2, 1, 0, 60, 0, 0);

    writeDisplayString(78);
}