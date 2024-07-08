//times (seconds)
  
unsigned long CS1L_Seed20 = 200, CS2L_Seed20 = 400;          //20 mL/min

//unsigned long CS1L_Drain200 = 60, CS2L_Drain200 = 120;       //200 mL/min
//unsigned long CS1L_Fill100 = 80, CS2L_Fill100 = 160;         //100 mL/min
//unsigned long CS1L_Fill200 = 52, CS2L_Fill200 = 104;         //200 mL/min
unsigned long CS1L_DCMFill100 = 56, CS2L_DCMFill100 = 110;   //100 mL/min  



//PBMC Seeding (retested Jan 2024)
unsigned long CS1L_Seed50 = 100, CS2L_Seed50 = 180;           //50 mL/min

unsigned long CS1L_Fill100 = 75, CS2L_Fill100 = 150;          //100 mL/min
unsigned long CS1L_DCMFill50 = 110, CS2L_DCMFill50 = 210;     //50 mL/min

unsigned long CS1L_Drain20_1 = 360, CS2L_Drain20_1 = 720;     //1st drain when volume is less than 100 mL per layer
unsigned long CS1L_Drain20 = 360, CS2L_Drain20 = 720;         //20 mL/min

unsigned long CS1L_Drain50 = 180, CS2L_Drain50 = 360;
/*unsigned long CS1L_Drain100_1 = 50, CS2L_Drain100_1 = 100;    //1st drain when volume is less than 100 mL per layer*/
unsigned long CS1L_Drain100 = 70, CS2L_Drain100 = 140;        //100 mL/min

unsigned long airPreLoad = 60;    //at 50 mL/min
unsigned long purgeTime = 30;     //at 20 mL/min


void setTimer(int type)
{
    if(type == 0)
    {
        if(command == CALIBRATE)    TotalSec1 = 60;   //60 seconds
        else if(stateMachine[stateIndex][3] < 2)   //states with Pump
        {
            if(quickTest)          TotalSec1 = TotalSec2 = TotalSec3 = 5;    //short timers
            else if(stateIndex == 1 || stateIndex == 3)   //PBMC Seed
            {
                if(pos1_config == 1 && stateMachine[stateIndex][6] == 20)           TotalSec1 = CS1L_Seed20;    //1L CS
                else if(pos1_config == 1 && stateMachine[stateIndex][6] == 50)      TotalSec1 = CS1L_Seed50;    //1L CS
                else if(pos1_config == 2 && stateMachine[stateIndex][6] == 20)      TotalSec1 = CS2L_Seed20;    //2L CS
                else if(pos1_config == 2 && stateMachine[stateIndex][6] == 50)      TotalSec1 = CS2L_Seed50;    //2L CS
              
                if(pos2_config == 1 && stateMachine[stateIndex][6] == 20)           TotalSec2 = CS1L_Seed20;    //1L CS
                else if(pos2_config == 1 && stateMachine[stateIndex][6] == 50)      TotalSec2 = CS1L_Seed50;    //1L CS
                else if(pos2_config == 2 && stateMachine[stateIndex][6] == 20)      TotalSec2 = CS2L_Seed20;    //2L CS
                else if(pos2_config == 2 && stateMachine[stateIndex][6] == 50)      TotalSec2 = CS2L_Seed50;    //2L CS
              
                if(pos3_config == 1 && stateMachine[stateIndex][6] == 20)           TotalSec3 = CS1L_Seed20;    //1L CS
                else if(pos3_config == 1 && stateMachine[stateIndex][6] == 50)      TotalSec3 = CS1L_Seed50;    //1L CS
                else if(pos3_config == 2 && stateMachine[stateIndex][6] == 20)      TotalSec3 = CS2L_Seed20;    //2L CS
                else if(pos3_config == 2 && stateMachine[stateIndex][6] == 50)      TotalSec3 = CS2L_Seed50;    //2L CS
            }
            else if(stateIndex == 18)   //DC Medium Fill
            {
                if(pos1_config == 1)         TotalSec1 = CS1L_DCMFill50;   //1L CS
                else if(pos1_config == 2)    TotalSec1 = CS2L_DCMFill50;   //2L CS
              
                if(pos2_config == 1)         TotalSec2 = CS1L_DCMFill50;   //1L CS
                else if(pos2_config == 2)    TotalSec2 = CS2L_DCMFill50;   //2L CS
              
                if(pos3_config == 1)         TotalSec3 = CS1L_DCMFill50;   //1L CS
                else if(pos3_config == 2)    TotalSec3 = CS2L_DCMFill50;   //2L CS
            }
            else if(stateIndex == 61 || stateIndex == 62)   //PBMC & DC Medium Bag air pre-load
            {
                TotalSec1 = airPreLoad;    //change back to 60
                TotalSec2 = TotalSec3 = 0;
            }

           /* else if(stateIndex == 8)     //Day 0 Drain 1
            {
                if(pos1_config == 1 && stateMachine[stateIndex][6] == 100)             TotalSec1 = CS1L_Drain100_1;
                else if(pos1_config == 2 && stateMachine[stateIndex][6] == 100)        TotalSec1 = CS2L_Drain100_1;

                if(pos2_config == 1 && stateMachine[stateIndex][6] == 100)             TotalSec2 = CS1L_Drain100_1;
                else if(pos2_config == 2 && stateMachine[stateIndex][6] == 100)        TotalSec2 = CS2L_Drain100_1;

                if(pos3_config == 1 && stateMachine[stateIndex][6] == 100)             TotalSec3 = CS1L_Drain100_1;
                else if(pos3_config == 2 && stateMachine[stateIndex][6] == 100)        TotalSec3 = CS2L_Drain100_1;
            }
            else if(stateIndex == 22)    //Day 7 Drain 1
            {
                if(pos1_config == 1 && stateMachine[stateIndex][6] == 20)             TotalSec1 = CS1L_Drain20_1;
                else if(pos1_config == 2 && stateMachine[stateIndex][6] == 20)        TotalSec1 = CS2L_Drain20_1;

                if(pos2_config == 1 && stateMachine[stateIndex][6] == 20)             TotalSec2 = CS1L_Drain20_1;
                else if(pos2_config == 2 && stateMachine[stateIndex][6] == 20)        TotalSec2 = CS2L_Drain20_1;

                if(pos3_config == 1 && stateMachine[stateIndex][6] == 20)             TotalSec3 = CS1L_Drain20_1;
                else if(pos3_config == 2 && stateMachine[stateIndex][6] == 20)        TotalSec3 = CS2L_Drain20_1;
            }
            */
            else    //check for Drain or DPBS Fill states
            {
                for(int i = 0; i < NUM_DRAINSTATES; i++)
                {
                    if(stateIndex == drainStates[i])
                    {
                        if(pos1_config == 1 && stateMachine[stateIndex][6] == 20)         TotalSec1 = CS1L_Drain20;   //1L CS
                        else if(pos1_config == 1 && stateMachine[stateIndex][6] == 50)    TotalSec1 = CS1L_Drain50;   //1L CS
                        else if(pos1_config == 1 && stateMachine[stateIndex][6] == 100)   TotalSec1 = CS1L_Drain100;  //1L CS
                        //else if(pos1_config == 1 && stateMachine[stateIndex][6] == 200)   TotalSec1 = CS1L_Drain200;  //1L CS    
                        else if(pos1_config == 2 && stateMachine[stateIndex][6] == 20)    TotalSec1 = CS2L_Drain20;   //2L CS
                        else if(pos1_config == 2 && stateMachine[stateIndex][6] == 50)    TotalSec1 = CS2L_Drain50;   //2L CS
                        else if(pos1_config == 2 && stateMachine[stateIndex][6] == 100)   TotalSec1 = CS2L_Drain100;  //2L CS
                        //else if(pos1_config == 2 && stateMachine[stateIndex][6] == 200)   TotalSec1 = CS2L_Drain200;  //2L CS
                        
                        if(pos2_config == 1 && stateMachine[stateIndex][6] == 20)         TotalSec2 = CS1L_Drain20;   //1L CS
                        else if(pos2_config == 1 && stateMachine[stateIndex][6] == 50)    TotalSec2 = CS1L_Drain50;   //1L CS
                        else if(pos2_config == 1 && stateMachine[stateIndex][6] == 100)   TotalSec2 = CS1L_Drain100;  //1L CS
                        //else if(pos2_config == 1 && stateMachine[stateIndex][6] == 200)   TotalSec2 = CS1L_Drain200;  //1L CS 
                        else if(pos2_config == 2 && stateMachine[stateIndex][6] == 20)    TotalSec2 = CS2L_Drain20;   //2L CS 
                        else if(pos2_config == 2 && stateMachine[stateIndex][6] == 50)    TotalSec2 = CS2L_Drain50;   //2L CS
                        else if(pos2_config == 2 && stateMachine[stateIndex][6] == 100)   TotalSec2 = CS2L_Drain100;  //2L CS
                        //else if(pos2_config == 2 && stateMachine[stateIndex][6] == 200)   TotalSec2 = CS2L_Drain200;  //2L CS
                      
                        if(pos3_config == 1 && stateMachine[stateIndex][6] == 20)         TotalSec3 = CS1L_Drain20;   //1L CS
                        else if(pos3_config == 1 && stateMachine[stateIndex][6] == 50)    TotalSec3 = CS1L_Drain50;   //1L CS
                        else if(pos3_config == 1 && stateMachine[stateIndex][6] == 100)   TotalSec3 = CS1L_Drain100;  //1L CS
                        //else if(pos3_config == 1 && stateMachine[stateIndex][6] == 200)   TotalSec3 = CS1L_Drain200;  //1L CS
                        else if(pos3_config == 2 && stateMachine[stateIndex][6] == 20)    TotalSec3 = CS2L_Drain20;   //2L CS
                        else if(pos3_config == 2 && stateMachine[stateIndex][6] == 50)    TotalSec3 = CS2L_Drain50;   //2L CS
                        else if(pos3_config == 2 && stateMachine[stateIndex][6] == 100)   TotalSec3 = CS2L_Drain100;  //2L CS
                        //else if(pos3_config == 2 && stateMachine[stateIndex][6] == 200)   TotalSec3 = CS2L_Drain200;  //2L CS


                        if(stateIndex == 45 || stateIndex == 49 || stateIndex == 54 || stateIndex == 58)
                        {
                            if(pos1_config == 1)        TotalSec1 = CS1L_Drain50 * 2;
                            else if(pos1_config == 2)   TotalSec1 = CS2L_Drain50 * 2;

                            if(pos2_config == 1)        TotalSec2 = CS1L_Drain50 * 2;
                            else if(pos2_config == 2)   TotalSec2 = CS2L_Drain50 * 2;

                            if(pos3_config == 1)        TotalSec3 = CS1L_Drain50 * 2;
                            else if(pos3_config == 2)   TotalSec3 = CS2L_Drain50 * 2;
                        }

                        break;
                    }
                }

                for(int i = 0; i < NUM_FILLSTATES; i++)    //DPBS Fill states
                {
                    if(stateIndex == fillStates[i])
                    {               
                        if(pos1_config == 1 && stateMachine[stateIndex][6] == 100)        TotalSec1 = CS1L_Fill100;   //1L CS
                        //else if(pos1_config == 1 && stateMachine[stateIndex][6] == 200)   TotalSec1 = CS1L_Fill200;   //1L CS
                        else if(pos1_config == 2 && stateMachine[stateIndex][6] == 100)   TotalSec1 = CS2L_Fill100;   //2L CS
                        //else if(pos1_config == 2 && stateMachine[stateIndex][6] == 200)   TotalSec1 = CS2L_Fill200;   //2L CS
                      
                        if(pos2_config == 1 && stateMachine[stateIndex][6] == 100)        TotalSec2 = CS1L_Fill100;   //1L CS
                        //else if(pos2_config == 1 && stateMachine[stateIndex][6] == 200)   TotalSec2 = CS1L_Fill200;   //1L CS
                        else if(pos2_config == 2 && stateMachine[stateIndex][6] == 100)   TotalSec2 = CS2L_Fill100;   //2L CS
                        //else if(pos2_config == 2 && stateMachine[stateIndex][6] == 200)   TotalSec2 = CS2L_Fill200;   //2L CS
                        
                        if(pos3_config == 1 && stateMachine[stateIndex][6] == 100)        TotalSec3 = CS1L_Fill100;   //1L CS
                        //else if(pos3_config == 1 && stateMachine[stateIndex][6] == 200)   TotalSec3 = CS1L_Fill200;   //1L CS
                        else if(pos3_config == 2 && stateMachine[stateIndex][6] == 100)   TotalSec3 = CS2L_Fill100;   //2L CS
                        //else if(pos3_config == 2 && stateMachine[stateIndex][6] == 200)   TotalSec3 = CS2L_Fill200;   //2L CS

                        if(stateIndex == 46 || stateIndex == 50 || stateIndex == 55)
                        {
                            if(pos1_config == 1)        TotalSec1 = (CS1L_Fill100 * 2) - 30;
                            else if(pos1_config == 2)   TotalSec1 = (CS2L_Fill100 * 2) - 30;

                            if(pos2_config == 1)        TotalSec2 = (CS1L_Fill100 * 2) - 30;
                            else if(pos2_config == 2)   TotalSec2 = (CS2L_Fill100 * 2) - 30;

                            if(pos3_config == 1)        TotalSec3 = (CS1L_Fill100 * 2) - 30;
                            else if(pos3_config == 2)   TotalSec3 = (CS2L_Fill100 * 2) - 30;
                        }

                        break;
                    }
                }
            }

            if(pos1_config == 3)    TotalSec1 = 0;    //No vessel
            if(pos2_config == 3)    TotalSec2 = 0;
            if(pos3_config == 3)    TotalSec3 = 0;
        }
        //Equilibration States
        else if(stateMachine[stateIndex][0] == 1)
        {
            for(int i = 0 ; i < NUM_EQWASHSTATES; i++)
            {
                if(stateIndex == eqWashStates[i]) TotalSec1 = TotalSec2 = TotalSec3 = equilibrate;
            }
        }

        //States with Shake (No Pump)
        else if(stateIndex == 25 || (command == MANUAL && buttonIndex == 58))   TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake1;
        else if(stateIndex == 30 || (command == MANUAL && buttonIndex == 59))   TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake2;
        else if(stateIndex == 34 || (command == MANUAL && buttonIndex == 64))   TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake3;
        else if(stateIndex == 48 || (command == MANUAL && buttonIndex == 67))   TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake4;
        else if(stateIndex == 53 || (command == MANUAL && buttonIndex == 66))   TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake5;
        else if(stateIndex == 57 || (command == MANUAL && buttonIndex == 68))   TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake6;
        else if(command == MANUAL && buttonIndex == 80)                         TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake7;
        else if(command == MANUAL && buttonIndex == 81)                         TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake8;
        else if(command == MANUAL && buttonIndex == 82)                         TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake9;
        else if(command == MANUAL && buttonIndex == 179)                        TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake10;
        else if(command == MANUAL && buttonIndex == 180)                        TotalSec1 = TotalSec2 = TotalSec3 = vigorousShake11;
        else if(stateMachine[stateIndex][5] == 1 || (command == MANUAL && buttonIndex == 57))   TotalSec1 = TotalSec2 = TotalSec3 = gentleShake1;
        else if(stateMachine[stateIndex][5] == 12 || (command == MANUAL && buttonIndex == 8))   TotalSec1 = TotalSec2 = TotalSec3 = gentleShake2;                              
    }
    else if(type == 1)
    {
        if(pos1_config != 3)    TotalSec1 = purgeTime;
        if(pos2_config != 3)    TotalSec2 = purgeTime;
        if(pos3_config != 3)    TotalSec3 = purgeTime;
    }

    snprintf(messageArray, sizeof(messageArray) - 1, "\nTotalSec1 = %lu\nTotalSec2 = %lu\nTotalSec3 = %lu\n", TotalSec1, TotalSec2, TotalSec3);
    Serial.print(messageArray);

    timeStart = millis();

    Timer(0);
}  //setTimer()




void TimerContinue()
{
    //Update current time, calculate elapsed time, and update duration remaining on the screen every 1 second
    timeNow = millis() + timeSkip;
    timeElapsed = (timeNow - pauseTime - timeStart) / 1000ul;   //elapsed time in seconds

    if(stateMachine[stateIndex][3] < 2)   //3 timers
    {
        //Check if timer has completed
        if((pump1Complete >= 3 || timeElapsed > TotalSec1) && pos1timer == 0)
        {
            if(WM1_status < 2)  stopWM(1);    //Pump is running; needed for when only 1 or 2 pumps are running
            if(pos1_config != 3 && stateIndex != 61 && stateIndex != 62)    //Do not display "COMPLETE!" when pre-loading bag with air
            {
              stringBuilder(2, 1, 0, 16, 0, 0);
              writeDisplayString(18);
            }
            pos1timer++;    //indicates timer is complete

            //reverse flow when seeding PBMCs to drain line of 1L CS
            if(stateIndex == 1 || stateIndex == 18) reverseFlow(1);
        }

        if((pump2Complete >= 3 || timeElapsed > TotalSec2) && pos2timer == 0)
        {
            if(WM2_status < 2)  stopWM(2);    
            if(pos2_config != 3 && stateIndex != 61 && stateIndex != 62)
            {
                stringBuilder(2, 1, 0, 16, 0, 0);
                writeDisplayString(19);
            }
            pos2timer++;    //indicates timer is complete

            //reverse flow when seeding PBMCs to drain line of 1L CS
            if(stateIndex == 1 || stateIndex == 18) reverseFlow(2);          
        }

        if((pump3Complete >= 3 || timeElapsed > TotalSec3) && pos3timer == 0)    //timer is complete
        {
            if(WM3_status < 2)  stopWM(3);   
            if(pos3_config != 3 && stateIndex != 61 && stateIndex != 62)
            {
                stringBuilder(2, 1, 0, 16, 0, 0);
                writeDisplayString(20);
            }
            pos3timer++;    //indicates timer is complete

            //reverse flow when seeding PBMCs to drain line of 1L CS
            if(stateIndex == 1 || stateIndex == 18) reverseFlow(3);
        }

        if(timeElapsed - lastUpdatedTime > 1)   //update display every 1 second
        {
                if (pos1timer == 0)   remainingTotalSec1 = TotalSec1 - timeElapsed;
                if (pos2timer == 0)   remainingTotalSec2 = TotalSec2 - timeElapsed;
                if (pos3timer == 0)   remainingTotalSec3 = TotalSec3 - timeElapsed;
        
                Timer(1);
                lastUpdatedTime = timeElapsed;
        }

        if(pos1timer > 0 && pos2timer > 0 && pos3timer > 0)   //all timers complete
        {
            endTimer();

            if((stateIndex == 1 || stateIndex == 18) && purge == 0)
            {
                airPurge(0);
                return;
            }
            else
            {
                for(int i = 0; i < NUM_DRAINSTATES && purge == 0; i++)
                {
                    if(stateIndex == drainStates[i])
                    {
                        airPurge(1);
                        return;
                    }
                }
            }
            purge = 0;



            
            if(stateMachine[stateIndex][4])
            {
                command = RUN; //trigger loop state change
                changeState(stateMachine[stateIndex][4]);
            }
            else    command = WAIT;
        }
    }
    else if(stateMachine[stateIndex][5] || command == TIMER || stateMachine[stateIndex][0] == 1)    //1 timer states
    {
       //Serial.println(remainingTotalSec1);
        //Check if timer has completed
        if(timeElapsed > TotalSec1) 
        {
            endTimer();
           
            if(stateIndex > 0)
            {
                if(stateMachine[stateIndex][5] == 1 || stateMachine[stateIndex][5] == 2 || stateMachine[stateIndex][5] == 12)    //gentle shake
                {
                    servo_reset();
                    command = RUN; //trigger loop state change
                    changeState(stateMachine[stateIndex][4]);
                }
                else if (stateMachine[stateIndex][5] == 3 || stateMachine[stateIndex][5] == 4 || stateMachine[stateIndex][5] == 5 || stateMachine[stateIndex][5] == 6 || stateMachine[stateIndex][5] == 7 || stateMachine[stateIndex][5] == 8) //vigorous shake  //vigorous shake
                {
                    servo_reset();
                    command = RUN; //trigger loop state change
                    changeState(stateMachine[stateIndex][4]);
                }
                else
                {
                  for (int i = 0 ; i < NUM_EQWASHSTATES; i++)
                  {
                    if (stateIndex == eqWashStates[i])
                    {
                      servo_reset();
                      command = RUN; //trigger loop state change
                      changeState(stateMachine[stateIndex][4]);
                    }
                  }
                }      
            }
            else if(command == TIMER)    //for manual shakes
            {
                if(buttonIndex == 57 || buttonIndex == 58 || buttonIndex == 59 || buttonIndex == 64 ||buttonIndex == 66 || buttonIndex == 67 || buttonIndex == 68 || buttonIndex == 80 || buttonIndex == 81 || buttonIndex == 82 || buttonIndex == 179 || buttonIndex == 180 )   //manual shake
                {
                    servo_reset();    
                }
                command = WAIT;   //avoid looping back into function
                changeForm(previousForm);
            }     
        }

        else if(timeElapsed - lastUpdatedTime > 1)
        {
            remainingTotalSec1 = TotalSec1 - timeElapsed;
            Timer(1);
            lastUpdatedTime = timeElapsed;
        }
    }  
} //TimerContinue()


void Timer(int continueTimer)
{
    if(stateMachine[stateIndex][3] < 2)   //separate timer for each position
    {
        //Top Position
        if(!continueTimer && TotalSec1 > 0)
        {
            TimerMin = ((TotalSec1 % 86400) % 3600) / 60;
            TimerSec = ((TotalSec1 % 86400) % 3600) % 60;
            displayTime(1);
        }
        else if(continueTimer && pos1timer == 0)
        {
            TimerMin = ((remainingTotalSec1 % 86400) % 3600) / 60;   
            TimerSec = ((remainingTotalSec1 % 86400) % 3600) % 60;    
            displayTime(1);
        }

        //Middle Position
        if(!continueTimer && TotalSec2 > 0)
        {
            TimerMin = ((TotalSec2 % 86400) % 3600) / 60;
            TimerSec = ((TotalSec2 % 86400) % 3600) % 60;
            displayTime(2);
        }
        else if(continueTimer && pos2timer == 0)
        {
            TimerMin = ((remainingTotalSec2 % 86400) % 3600) / 60;   
            TimerSec = ((remainingTotalSec2 % 86400) % 3600) % 60;
            displayTime(2); 
        }
        
        //Bottom Position
        if(!continueTimer && TotalSec3 > 0)    //begin timer
        {
            TimerMin = ((TotalSec3 % 86400) % 3600) / 60;    //timer min
            TimerSec = ((TotalSec3 % 86400) % 3600) % 60;    //timer sec 
            displayTime(3);
        }
        else if(continueTimer && pos3timer == 0)    //continue timer
        {
            TimerMin = ((remainingTotalSec3 % 86400) % 3600) / 60;   //timer min
            TimerSec = ((remainingTotalSec3 % 86400) % 3600) % 60;    //timer sec
            displayTime(3);
        }          
    }
    else if(stateMachine[stateIndex][5] || command == TIMER)  //single timer for all positions
    {
        if(!continueTimer)
        {
            TimerMin = ((TotalSec1 % 36400) % 3600) / 60;
            TimerSec = ((TotalSec1 % 86400) % 3600) % 60;
        }
        else if(continueTimer)
        {
            TimerMin = ((remainingTotalSec1 % 36400) % 3600) / 60;
            TimerSec = ((remainingTotalSec1 % 86400) % 3600) % 60;
        }
        displayTime(0);
    }
    else
    {
      for (int i = 0 ; i < NUM_EQWASHSTATES; i++)
      {
        if (stateIndex == eqWashStates[i])
        {
          if(!continueTimer)
          {
            TimerMin = ((TotalSec1 % 36400) % 3600) / 60;
            TimerSec = ((TotalSec1 % 86400) % 3600) % 60;
          }
          else if(continueTimer)
          {
            TimerMin = ((remainingTotalSec1 % 36400) % 3600) / 60;
            TimerSec = ((remainingTotalSec1 % 86400) % 3600) % 60;
          }
          displayTime(0);
        }
      }
    }
} //Timer()


void displayTime(int position)
{
    if(currentForm == 3)    snprintf(messageArray, sizeof(messageArray) - 1, "%i m %i s", TimerMin, TimerSec);    //calibrate pumps
    else                    snprintf(messageArray, sizeof(messageArray) - 1, "%i minutes\n%i seconds", TimerMin, TimerSec);
    
    if(position)
    {
        if(position == 1 && pos1_config != 3)       writeDisplayString(18);
        else if(position == 2 && pos2_config != 3)  writeDisplayString(19);
        else if(position == 3 && pos3_config != 3)  writeDisplayString(20);
    }
    else if(!position)
    {
        if(currentForm == 3)    writeDisplayString(41);
        else                    writeDisplayString(31);
    }
}

void startPause()
{
    pause = 1;

    pauseStart = millis();

    if(WM1_status < 2)  stopWM(1);
    if(WM2_status < 2)  stopWM(2);
    if(WM3_status < 2)  stopWM(3);

    closeValves();

    Serial.print("SP,");
}

void endPause()
{
    pauseTime = pauseTime + millis() - pauseStart;
    
    if(stateMachine[stateIndex][3] < 2)
    {
        if(purge == 1)    startWM(0, stateMachine[stateIndex][3], purgeFlowRate);
        else              startWM(0, stateMachine[stateIndex][3], stateMachine[stateIndex][6]);
    }

    valveControl(1, stateMachine[stateIndex][7]);   //DC Medium line
    valveControl(2, stateMachine[stateIndex][8]);   //PBMC/DPBS line
    valveControl(3, stateMachine[stateIndex][9]);   //NAC Drain/DC Harvest line

    pause = 0;
    Serial.print("EP,");
}

void endTimer()
{   
    timeStart = timeNow = timeElapsed = pauseStart = pauseTime = lastUpdatedTime = 0;
    TotalSec1 = TotalSec2 = TotalSec3 = 0;
    pos1timer = pos2timer = pos3timer = 0;
    timeSkip = TimerMin = TimerSec = 0;
    pump1Complete = pump2Complete = pump3Complete = 0;
    Serial.print("RTV,");
}