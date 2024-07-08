void loop()
{
    genie.DoEvents();

    //Testing commands from Serial Monitor
    if(Serial.available() > 0)    SMInputwrite();   
    if(Serial2.available() > 0)   arduinoResponse(2);

    if(command == RUN)
    {
        if(stateIndex != lastState)
        {
          lastState = stateIndex;
          //servo_previousPos = servoPos;
          //rail_previousPos = railPos;
          
          //Servo / Guide Rail
          if(railPos != stateMachine[stateIndex][2] || servoPos != stateMachine[stateIndex][0])   changeForm(16);


          
          //Valves
          valveControl(1, stateMachine[stateIndex][7]);   //DC Medium line
          valveControl(2, stateMachine[stateIndex][8]);   //PBMC/DPBS line
          valveControl(3, stateMachine[stateIndex][9]);   //NAC Drain/DC Harvest line


          //Set Servo and Rail Positions
          if(stateIndex == 60 || stateIndex == 21 || stateIndex == 30 || stateIndex == 44 || stateIndex == 53)    //beggining of routine (first equilibrate CS)
          {
              changeForm(16);
              setServo(1, 0);
              setRail(1);              
              delay(10000);
              setRail(3);
              delay(1500);
              setServo(0, 0);
          }
          else if(servoPos == 1)    //previous state was equilibrate
          {
              setRail(3);    //go to extract
              setServo(0, 0);         //go to flat
          }

          setRail(stateMachine[stateIndex][2]);  
          setServo(stateMachine[stateIndex][0], stateMachine[stateIndex][5]);

          //Change Form
          if(stateMachine[stateIndex][3] < 2)   changeForm(11);   //states with 3 timers
          else if(stateIndex == 63 || stateIndex == 64)   changeForm(18);   //Hang Bag states
          else if(stateIndex == 7 || stateIndex == 17 || stateIndex == 20 || stateIndex == 29 || stateIndex == 36 || stateIndex == 43 || stateIndex == 52 || stateIndex == 59)    changeForm(14);   //complete states
          else if(stateMachine[stateIndex][3] == 2 || stateMachine[stateIndex][5] || stateMachine[stateIndex][0] == 1 || stateIndex == 61 || stateIndex == 62)    changeForm(13);   //states with 1 timer (no pump || shake || equilibrate || air pre-load)

          if(stateMachine[stateIndex][3] < 2 || stateMachine[stateIndex][5] || stateMachine[stateIndex][0] == 1)  //Pump ON (either CW or CCW) || Shaking (no Pump)
          {
              setTimer(0);
              command = TIMER;
          }

          //WM Pumps
          if(stateMachine[stateIndex][3] < 2)   //Pump ON either CW or CCW)
          {
              startWM(0, stateMachine[stateIndex][3], stateMachine[stateIndex][6]);
          }
        } //if(stateIndex != lastState)
    } //if(command == RUN)

    else if(command == MANUAL)
    {
        if(buttonIndex == 4 || buttonIndex == 5 || buttonIndex == 6 || buttonIndex == 7 || buttonIndex == 9)
        {
            changeForm(16);

            if(buttonIndex == 4)         setRail(5);
            else if(buttonIndex == 5)    setRail(3);
            else if(buttonIndex == 6)    setRail(1);
            else if(buttonIndex == 7)    setRail(10);   //increment up 1
            else if(buttonIndex == 9)    setRail(11);   //increment down 1

            changeForm(previousForm); 
            command = WAIT;
        }
        else if(buttonIndex == 12 || buttonIndex == 13 || buttonIndex == 14 || buttonIndex == 15 || buttonIndex == 16 || buttonIndex == 17 || buttonIndex == 69 || buttonIndex == 70 || buttonIndex == 71)
        {
            if(buttonIndex == 12)         startWM(1, 0, manualFlowRate);
            else if(buttonIndex == 13)    startWM(1, 1, manualFlowRate);
            else if(buttonIndex == 14)    stopWM(1);
            else if(buttonIndex == 15)    startWM(2, 0, manualFlowRate);
            else if(buttonIndex == 16)    startWM(2, 1, manualFlowRate);
            else if(buttonIndex == 17)    stopWM(2);
            else if(buttonIndex == 69)    startWM(3, 0, manualFlowRate);
            else if(buttonIndex == 70)    startWM(3, 1, manualFlowRate);
            else if(buttonIndex == 71)    stopWM(3);
            command = WAIT;

            pumpString();
        }

        //Pinch valves
        else if(buttonIndex == 74 || buttonIndex == 83 || buttonIndex == 84)
        {
            if(buttonIndex == 74)    //DC Medium
            {
                valveControl(1, !valve1Status);
            }
            else if(buttonIndex == 83)    //PBMCs/DPBS
            {
                valveControl(2, !valve2Status);
            }
            else if(buttonIndex == 84)    //NAC Drain/DC Harvest
            {
                valveControl(3, !valve3Status);
            }
            valveString();
            command = WAIT;
        }
        else if(buttonIndex == 55 || buttonIndex == 61 || buttonIndex == 62 || buttonIndex == 63)   //Form 15: Control Center- Servo
        {
            changeForm(16);

            if(buttonIndex == 55)         servoFunctions(1);    //Initial Homing
            else if(buttonIndex == 61)    setServo(1, 0);   
            else if(buttonIndex == 62)    setServo(2, 0); 
            else if(buttonIndex == 63)    setServo(0, 0); 

            changeForm(previousForm);
            command = WAIT;
        }
        else if(buttonIndex == 57 || buttonIndex == 58 || buttonIndex == 59 || buttonIndex == 64 ||buttonIndex == 66 || buttonIndex == 67 || buttonIndex == 68 || buttonIndex == 80 ||buttonIndex == 81 || buttonIndex == 82 || buttonIndex == 8 || buttonIndex == 179 || buttonIndex == 180)
        {
            changeForm(13);

            if(railPos != 1 || servoPos != 0)   //not at flat home position
            {
                if(servoPos == 1)    //current position is equilibrate
                {
                    setRail(3);    //go to extract
                    setServo(0, 0);         //go to flat                
                }

                setRail(1);
                setServo(0, 0);
            }

            if(buttonIndex == 57)         setServo(0, 1);   //Gentle Shake Day 0
            else if(buttonIndex == 8)     setServo(0, 12);    //Gentle Shake Day 7/8
            else if(buttonIndex == 58)    setServo(0, 3);   
            else if(buttonIndex == 59)    setServo(0, 4);
            else if(buttonIndex == 64)    setServo(0, 5); 
            else if(buttonIndex == 66)    setServo(0, 7);   
            else if(buttonIndex == 67)    setServo(0, 6);             
            else if(buttonIndex == 68)    setServo(0, 8);
            else if(buttonIndex == 80)    setServo(0, 9);
            else if(buttonIndex == 81)    setServo(0, 10);
            else if(buttonIndex == 82)    setServo(0, 11); 
            else if(buttonIndex == 179)   setServo(0, 13);
            else if(buttonIndex == 180)   setServo(0, 14);

            setTimer(0);
            command = TIMER;
        }
        else if(buttonIndex == 53 || buttonIndex == 78 || buttonIndex == 181 || buttonIndex == 182 || buttonIndex == 183 || buttonIndex == 184)    //Manual Position Controls
        {
            closeValves();

            changeForm(21);

            if(buttonIndex == 53)   //Home Position
            {
                setServo(0, 0);
                setRail(1);                
                shakeMechPos = 0;
            }
            else if(buttonIndex == 78)    //Equilibrate to Extract Position
            {
                setServo(1, 0);
                setRail(1);              
                delay(10000);
                setRail(3);
                delay(1500);
                setServo(0, 0);
                shakeMechPos = 5;
            }
            else if(buttonIndex == 181)  //PBMC/DPBS Fill Position
            {
                valveControl(2, true);
                setServo(1, 0);
                setRail(1);
                shakeMechPos = 1;
            }
            else if(buttonIndex == 184)    //Drain Position
            {
                valveControl(3, false);
                setRail(5);
                setServo(2, 0);
                shakeMechPos = 3;
            }
            else if(buttonIndex == 182)   //DC Medium Fill Position
            {
                valveControl(1, true);
                setServo(1, 0);
                setRail(1);              
                shakeMechPos = 2;
            }
            else if(buttonIndex == 183)   //Equilibrate Position
            {
                setServo(1, 0);
                setRail(1);
                shakeMechPos = 4;
            }

            changeForm(4);
            command = WAIT;
        }
    }   //command == MANUAL
    else if(command == CALIBRATE)
    {
        if(buttonIndex == 12 || buttonIndex == 13 || buttonIndex == 14 || buttonIndex == 15 || buttonIndex == 16 || buttonIndex == 17 || buttonIndex == 69 || buttonIndex == 70 || buttonIndex == 71)
        {
            if(buttonIndex == 12)         startWM(1, 0, manualFlowRate);
            else if(buttonIndex == 13)    startWM(1, 1, manualFlowRate);
            else if(buttonIndex == 14)    stopWM(1);
            else if(buttonIndex == 15)    startWM(2, 0, manualFlowRate);
            else if(buttonIndex == 16)    startWM(2, 1, manualFlowRate);
            else if(buttonIndex == 17)    stopWM(2);  
            else if(buttonIndex == 69)    startWM(3, 0, manualFlowRate);
            else if(buttonIndex == 70)    startWM(3, 1, manualFlowRate);
            else if(buttonIndex == 71)    stopWM(3);

            setTimer(0);
            command = TIMER;
        }
    }
    else if(command == TIMER)       TimerContinue(); 
    else if(command == RECOVERY)    recoveryButton();
}

void recoveryButton()
{
    if(buttonIndex == 122)        recoveryIndex = 0;
    else if(buttonIndex == 123)   recoveryIndex = 1;
    else if(buttonIndex == 124)   recoveryIndex = 2;
    else if(buttonIndex == 127)   recoveryIndex = 3;
    else if(buttonIndex == 128)   recoveryIndex = 4;
    else if(buttonIndex == 129)   recoveryIndex = 5;
    else if(buttonIndex == 130)   recoveryIndex = 6;
    else if(buttonIndex == 131)   recoveryIndex = 7;
    else if(buttonIndex == 132)   recoveryIndex = 8;
    else if(buttonIndex == 133)   recoveryIndex = 9;
    else if(buttonIndex == 134)   recoveryIndex = 10;
    else if(buttonIndex == 135)   recoveryIndex = 11;
    else if(buttonIndex == 146)   recoveryIndex = 12;
    else if(buttonIndex == 139)   recoveryIndex = 13;
    else if(buttonIndex == 140)   recoveryIndex = 14;
    else if(buttonIndex == 121)   recoveryIndex = 15;
    else if(buttonIndex == 126)   recoveryIndex = 16;
    else if(buttonIndex == 137)   recoveryIndex = 17;
    else if(buttonIndex == 138)   recoveryIndex = 18;
    else if(buttonIndex == 141)   recoveryIndex = 19;
    else if(buttonIndex == 142)   recoveryIndex = 20;
    else if(buttonIndex == 143)   recoveryIndex = 21;
    else if(buttonIndex == 144)   recoveryIndex = 22;
    else if(buttonIndex == 148)   recoveryIndex = 23;
    else if(buttonIndex == 149)   recoveryIndex = 24;
    else if(buttonIndex == 150)   recoveryIndex = 25;
    else if(buttonIndex == 151)   recoveryIndex = 26;
    else if(buttonIndex == 152)   recoveryIndex = 27;
    else if(buttonIndex == 156)   recoveryIndex = 28;
    else if(buttonIndex == 154)   recoveryIndex = 29;
    else if(buttonIndex == 155)   recoveryIndex = 30;
    else if(buttonIndex == 157)   recoveryIndex = 31;
    else if(buttonIndex == 158)   recoveryIndex = 32;
    else if(buttonIndex == 159)   recoveryIndex = 33;
    else if(buttonIndex == 160)   recoveryIndex = 34;
    else if(buttonIndex == 161)   recoveryIndex = 35;
    else if(buttonIndex == 162)   recoveryIndex = 36;
    else if(buttonIndex == 165)   recoveryIndex = 37;
    else if(buttonIndex == 166)   recoveryIndex = 38;
    else if(buttonIndex == 167)   recoveryIndex = 39;
    else if(buttonIndex == 168)   recoveryIndex = 40;
    else if(buttonIndex == 169)   recoveryIndex = 41;
    else if(buttonIndex == 170)   recoveryIndex = 42;
    else if(buttonIndex == 173)   recoveryIndex = 43;
    else if(buttonIndex == 174)   recoveryIndex = 44;

    routine = recoveryTable[recoveryIndex][0];
    recoveryState = recoveryTable[recoveryIndex][1];
}