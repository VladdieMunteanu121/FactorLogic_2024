void arduinoResponse(int arduino)
{
    int i = 0;

    if(arduino == 2)    //Arduino 2
    {
        for(i; Serial2.available() > 0 && i < sizeof(arduinoMessage) - 2; i++)
        {
            arduinoMessage[i] = Serial2.read(); delay(1);
        }
        arduinoMessage[i] = 0x00;

        if(strcmp(arduinoMessage, "Arduino 2 OK") == 13)   arduino2 = 1;
        else  arduino2 = 0;


        Serial.println(arduinoMessage);
        Serial.println(strcmp(arduinoMessage, "Arduino 2 OK"));
    }
}


void airPurge(int type)
{
    //Type 0: PBMC Seed & DC Medium Fill (CS flat so just start pumps)
    if(type == 1)    //Drain states (CS in Drain position so change Servo and Rail to both flat then start pumps)
    {
        setServo(0, 0);
        setRail(1);
    }

    setTimer(1);
    command = TIMER;
    purge = 1;

    startWM(0, stateMachine[stateIndex][3], purgeFlowRate);
}













void reverseFlow(int pump)
{
    if(pump == 1 && pos1_config == 1 && purge == 0)
    {
        if(pos2_config == 2 || pos3_config == 2)
        {
            startPause();
            delay(100);    //to not mix signals to valves
            if(stateIndex == 1)         valveControl(2, 1);
            else if(stateIndex == 18)   valveControl(1, 1);
            startWM(1, 1, purgeFlowRate);
            delay(purgeTime * 1000);
            stopWM(1);
            if(pos2_config == 2 && pos3_config == 2)        endPause();
            else if(pos2_config == 2 && pos3_config == 3)   endPause();
            else if(pos2_config == 3 && pos3_config == 2)   endPause();
            
        }
    }
    else if(pump == 2 && pos2_config == 1 && purge == 0)
    {
        if(pos1_config == 2 || pos3_config == 2)
        {
            if(!pause) startPause();
            delay(100);
            if(stateIndex == 1)         valveControl(2, 1);
            else if(stateIndex == 18)   valveControl(1, 1);
            startWM(2, 1, purgeFlowRate);
            delay(purgeTime * 1000);
            stopWM(2);
            if(pos1_config == 2 && pos3_config == 2)        endPause();
            else if(pos1timer == 1 && pos3_config == 2)     endPause();
            else if(pos1_config == 2 && pos3_config == 3)   endPause();
        }
    }
    else if(pump == 3 && pos3_config == 1 && purge == 0)
    {
        if(pos1_config == 2 || pos2_config == 2)
        {
            if(!pause) startPause();
            delay(100);
            if(stateIndex == 1)         valveControl(2, 1);
            else if(stateIndex == 18)   valveControl(1, 1);
            startWM(3, 1, purgeFlowRate);
            delay(purgeTime * 1000);
            stopWM(3);
            endPause();
        }
    }
}