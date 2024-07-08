void setup()
{
    Serial.begin (115200);  // Serial Monitor Communication
    Serial1.begin(115200);   //3rd Arduino
    Serial2.begin(115200);  //2nd Arduino
    Serial3.begin (115200); // 4D Systems and Arduino Communication
    genie.Begin (Serial3); // 4D Systems and Arduino Communication
    delay(8000);
    genie.AttachEventHandler(myGenieEventHandler);

    genie.WriteContrast(15);
    
  
    //WM 
    pinMode(WMDIRpin, OUTPUT);
    pinMode(WMSTEPpin, OUTPUT);
    pinMode(WMDISABLEpin, OUTPUT);
    digitalWrite(WMDISABLEpin, HIGH);

    //Valves
    pinMode(valve1PIN, OUTPUT);
    pinMode(valve2PIN, OUTPUT);
    pinMode(valve3PIN, OUTPUT);

    valveControl(1, 0);   //NC
    valveControl(2, 0);   //NC
    valveControl(3, 0);   //NO

    stopWM(1); stopWM(2); stopWM(3);

    //Linear Rail
    pinMode(railDIRpin, OUTPUT);
    pinMode(railSTEPpin, OUTPUT);
    pinMode(LS_extract, INPUT_PULLUP);
    
    //Mitsubishi Servo
    pinMode(EM2, OUTPUT);
    pinMode(SON, OUTPUT);
    pinMode(MD0, OUTPUT);
    pinMode(ST1, OUTPUT);
    pinMode(DOG, OUTPUT);
    pinMode(LSP, OUTPUT);
    pinMode(LSN, OUTPUT);
    pinMode(DI_0, OUTPUT);
    pinMode(DI_1, OUTPUT);
    pinMode(DI_2, OUTPUT);
    pinMode(DI_3, OUTPUT);
    pinMode(DI_4, OUTPUT);

    digitalWrite(DI_0, pin_status);
    digitalWrite(DI_1, pin_status);
    digitalWrite(DI_2, pin_status);
    digitalWrite(DI_3, pin_status);
    digitalWrite(DI_4, pin_status);

        //Initial Homing
        digitalWrite(LSP, pin_status); //ON (NC)
        digitalWrite(LSN, pin_status); //ON (NC)
        digitalWrite(ST1, pin_status); //OFF
        digitalWrite(EM2, pin_status); //ON (NC)
        digitalWrite(DOG, !pin_status); //ON (NO)
        digitalWrite(MD0, !pin_status);


    //Initializing Checks
    changeForm(33);   

    stringBuilder(2, 1, 0, 51, 1, 0);
    writeDisplayString(74); 
    setRail(stateMachine[0][2]);

    stringBuilder(2, 0, 0, 52, 1, 0);
    writeDisplayString(74);
    servoFunctions(1);    //Initial Homing
    servoPos = 0;

    
    stringBuilder(2, 0, 0, 53, 1, 0);
    writeDisplayString(74);
    stringBuilder(2, 0, 0, 54, 1, 0);
    writeDisplayString(74);
    //check peripheral Arduino responses
    arduinoResponse(2);
    //arduinoResponse(3);

    //if(arduino2 == 1)
    //{
        if(login) changeForm(20);
        else      changeForm(1);

        Serial.println("Setup Complete.");
    //}
    //else
    //{
      //while(1);
    //}
}


