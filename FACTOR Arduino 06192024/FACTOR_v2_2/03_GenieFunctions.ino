void myGenieEventHandler(void) 
{
    genieFrame Event;
    genie.DequeueEvent(&Event);  // Remove the next queued event from the buffer, and process it below

    if (Event.reportObject.cmd == GENIE_REPORT_EVENT)
    {
        if(Event.reportObject.object == GENIE_OBJ_WINBUTTON)  // If the Reported Message was from a WINBUTTON
        {
            buttonIndex = Event.reportObject.index;  //Index of button pressed
            snprintf(messageArray, sizeof(messageArray) - 1, "B%i,", buttonIndex); Serial.print(messageArray);
        }

        if(Event.reportObject.object == GENIE_OBJ_KEYBOARD)
        {
            if(Event.reportObject.index == 0)
            {
                Keyboard(genie.GetEventData(&Event));
                return;
            }
        }
          
        if(command != CALIBRATE || buttonIndex == 11)    command = buttonMachine[buttonIndex][0];    //if current command is CALIBRATE then do not update
        
        //Routine Selection
        if (buttonIndex == 36)       routine = 1;    //Day 0 PBMC Seed
        else if(buttonIndex == 37)   routine = 2;    //Day 0 PBMC Washing
        else if(buttonIndex == 39)   routine = 3;    //Day 0 DC Medium Fill
        else if(buttonIndex == 42)   routine = 4;    //Day 7 Harvest Part 1
        else if(buttonIndex == 43)   routine = 5;    //Day 7 Harvest Part 2
        else if(buttonIndex == 45)   routine = 6;    //Day 7 DC + Lysate Seed
        else if(buttonIndex == 46)   routine = 7;    //Day 8 Harvest Part 1
        else if(buttonIndex == 47)   routine = 8;    //Day 8 Harvest Part 2
        
        //Vessel Configuration
        for(int i = 0; i < NUM_VESSELCONFIGBUTTONS; i++)
        {
            if(buttonIndex == vesselConfigButtons[i])
            {
                if(buttonIndex == 22 || buttonIndex == 23 || buttonIndex == 27 || buttonIndex == 85 || buttonIndex == 86 || buttonIndex == 89 || buttonIndex == 96 || buttonIndex == 97 || buttonIndex == 100 || buttonIndex == 107)   //Top Vessel Configuration
                {
                    if(buttonIndex == 22 || buttonIndex == 85 || buttonIndex == 96)        pos1_config = 1;   //1 L CS
                    else if(buttonIndex == 23 || buttonIndex == 86 || buttonIndex == 97)   pos1_config = 2;   //2L CS
                    else if(buttonIndex == 27 || buttonIndex == 89 || buttonIndex == 100)  pos1_config = 3;   //Balance/Empty
                    else if(buttonIndex == 107)                                            pos1_config = 4;   //T-Flasks

                    pos1String();
                    if(routine == 1 || routine == 2 || routine == 3)  writeDisplayString(55);
                    else if(routine == 4 || routine == 5 || routine == 6)             writeDisplayString(4);
                    else if(routine == 7 || routine == 8)             writeDisplayString(59);
                }       
                else if(buttonIndex == 35 || buttonIndex == 34 || buttonIndex == 32|| buttonIndex == 93 || buttonIndex == 94 || buttonIndex == 95 || buttonIndex == 104 || buttonIndex == 105 || buttonIndex == 106 || buttonIndex == 108)   //Middle Vessel Configuration
                {
                    if(buttonIndex == 35 || buttonIndex == 95 || buttonIndex == 108)        pos2_config = 1;
                    else if(buttonIndex == 34 || buttonIndex == 94 || buttonIndex == 105)   pos2_config = 2;
                    else if(buttonIndex == 32 || buttonIndex == 93 || buttonIndex == 104)   pos2_config = 3;
                    else if(buttonIndex == 106)                       pos2_config = 4;

                    pos2String();
                    if(routine == 1 || routine == 2 || routine == 3)  writeDisplayString(56);
                    else if(routine == 4 || routine == 5 || routine == 6)             writeDisplayString(5);
                    else if(routine == 7 || routine == 8)             writeDisplayString(60);
                }
                else if(buttonIndex == 28 || buttonIndex == 29 || buttonIndex == 31 || buttonIndex == 90 || buttonIndex == 91 || buttonIndex == 92 || buttonIndex == 101 || buttonIndex == 102 || buttonIndex == 103 || buttonIndex == 109)    //Bottom Vessel Configuration
                {  
                    if(buttonIndex == 28 || buttonIndex == 90 || buttonIndex == 109)         pos3_config = 1;   //1L CS
                    else if(buttonIndex == 29 || buttonIndex == 91 || buttonIndex == 102)    pos3_config = 2;   //2L CS
                    else if(buttonIndex == 31 || buttonIndex == 92 || buttonIndex == 103)    pos3_config = 3;   //Balance/Empty
                    else if(buttonIndex == 101)                        pos3_config = 4;   //T-Flasks

                    pos3String();
                    if(routine == 1 || routine == 2 || routine == 3)  writeDisplayString(57);
                    else if(routine == 4 || routine == 5 || routine == 6)             writeDisplayString(6);
                    else if(routine == 7 || routine == 8)             writeDisplayString(61);
                }  
                else if(buttonIndex == 24 || buttonIndex == 87 || buttonIndex == 98)    //Back buttons
                {    
                    if(buttonIndex == 87)         changeForm(6);    //Day 0 Back button
                    else if(buttonIndex == 24)    changeForm(8);    //Day 7 Back button
                    else if(buttonIndex == 98)    changeForm(9);    //Day 8 Back button

                    clearConfiguration();
                }

                else if(buttonIndex == 25 || buttonIndex == 88 || buttonIndex == 99)   //Confirm Button
                {
                    if(pos1_config > 0 && pos2_config > 0 && pos3_config > 0)   //All 3 positions must be selected
                    {
                        changeForm(10);
                        //snprintf(messageArray, messageArraySize, "\nroutine = %i\npos1_config = %i\npos2_config = %i\npos3_config = %i\n", routine, pos1_config, pos2_config, pos3_config);
                        //Serial.print(messageArray);
                    }
                    else return;
                }
            }
        }

        if (buttonIndex == 51 && stateIndex == 37) changeForm(19);
        else if (buttonIndex == 51 && stateIndex != 37) changeForm(12);

        if (buttonIndex == 33)  
        {
          endTimer();
          changeState(stateMachine[stateIndex][4]);
        }

        if(buttonIndex == 11)   //Back button on Form 3
        {
            manualFlowRate = 50;    //reset flow rate
        }
        else if(buttonIndex == 26)    //Pump Calibrate
        {
            stringBuilder(2, 1, 0, 27, 0, 0);
            writeDisplayString(41);
        }
        
        else if(buttonIndex == 20)    //Back button form 4
        {  
            closeValves();    //close all pinch valves
            stopWM(1);
            stopWM(2);
            stopWM(3);
            setRail(1);
            setServo(0, 0);
            shakeMechPos = 0;
        }
        else if(buttonIndex == 40)    //Begin button on Form 7
        {
            changeForm(16);
            servoFunctions(1);
            
            if(recoveryState)
            {
                stateIndex = recoveryState;
                changeState(stateIndex);
            }
            else if(routine == 1)   changeState(61);   
            else if(routine == 2)   changeState(60);
            else if(routine == 3)   changeState(62);
            else if(routine == 4)   changeState(21);
            else if(routine == 5)   changeState(30);
            else if(routine == 6)   changeState(37);
            else if(routine == 7)   changeState(44);
            else if(routine == 8)   changeState(53);

        }
        else if(buttonIndex == 49)    //Back button Form 10
        {
            if(routine == 1 || routine == 2 || routine == 3)        changeForm(22);
            else if(routine == 4 || routine == 5 || routine == 6)   changeForm(5);
            else if(routine == 7 || routine == 8)                   changeForm(23);
        }
        else if(buttonIndex == 50)    //Confirm button on Form 10
        {
            changeForm(7);
        }
        else if(buttonIndex == 51)    //Pause button on Form 11 and Form 13
        {
            startPause();
        }
        else if(buttonIndex == 52 || buttonIndex == 30)    //Resume button on Form 12
        {
            if(stateMachine[stateIndex][3] < 2)   //states with 3 timers
            {
                changeForm(11);

                //Write "COMPLETE!" if timer is complete
                if(pos1timer && pos1_config != 3)     
                {
                    stringBuilder(2, 1, 0, 16, 0, 0);
                    writeDisplayString(18);  
                }  

                if(pos2timer && pos2_config != 3)
                {
                  stringBuilder(2, 1, 0, 16, 0, 0);
                  writeDisplayString(19);
                }   

                if(pos3timer && pos3_config != 3)
                {
                    stringBuilder(2, 1, 0, 16, 0, 0);
                    writeDisplayString(20);
                }
            }
            else if(stateMachine[stateIndex][3] == 2)   //states with 1 timer
            {
                changeForm(13);
            }

            endPause();
        }
        else if(buttonIndex == 60)   //Manual control flow rate selection
        {
            if(manualFlowRate == 20)
            {
                manualFlowRate = 50;
                stringBuilder(2, 1, 0, 24, 0, 0);
            }
            else if(manualFlowRate == 50)   
            {
                manualFlowRate = 100;
                stringBuilder(2, 1, 0, 25, 0, 0);
            }
            else if(manualFlowRate == 100)   
            {
                manualFlowRate = 20;
                stringBuilder(2, 1, 0, 31, 0, 0);
            }

            writeDisplayString(41);       
        }
        else if (buttonIndex == 75) //CONTINUE BUTTON ON FORM 18
        {
          changeState(stateMachine[stateIndex][4]);
        }
        else if (buttonIndex == 77) clearConfiguration();
        else if(buttonIndex == 118)   //Back button on Form 24
        {
            routine = 0;
            recoveryState = 0;
        }
        else if(buttonIndex == 172)    //Confirm button on Form 32
        {
            if(recoveryState == 7 || recoveryState == 17 || recoveryState == 20 || recoveryState == 29 || recoveryState == 36 || recoveryState == 52 || recoveryState == 59)    changeForm(14);    //Routine Complete
            else if(routine == 1 || routine == 2 || routine == 3)   changeForm(22);   //to vessel configuration
            else if(routine == 4 || routine == 5 || routine == 6)   changeForm(5);
            else if(routine == 7 || routine == 8)                   changeForm(23);
        }
        else if(command == TIMER)   //for counting number of times complete button is pressed
        {
            if(buttonIndex == 176)        pump1Complete++;
            else if(buttonIndex == 177)   pump2Complete++;
            else if(buttonIndex == 178)   pump3Complete++;
        }
        
        if(buttonMachine[buttonIndex][1])   changeForm(buttonMachine[buttonIndex][1]);
    }
}  //myGenieEventHandler()