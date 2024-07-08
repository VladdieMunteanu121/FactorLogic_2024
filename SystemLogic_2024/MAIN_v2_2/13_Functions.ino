int userNameTrigger, passwordTrigger, userNamePointer, passwordPointer = 0;

void Keyboard(int value)
{
    if(value == 0 && userNameTrigger == 0)        userNameTrigger++;    //Username button
    else if(value == 1 && passwordTrigger == 0)   passwordTrigger++;    //Password button
    else if(value == 2)    //Back button
    {
        if(userNameTrigger == 1 && userNamePointer > 0)    //entering username
        {
            UserName[userNamePointer - 1] = 0x00;
            userNamePointer--;
            genie.WriteStr(32, UserName);
        }
        else if(passwordTrigger == 1 && passwordPointer > 0)   //entering password
        {
            Password[passwordPointer - 1] = 0x00;
            passwordPointer--;
            genie.WriteStr(50, Password);
        }
    }
    else if(value == 3)   //Enter button
    {
        if(userNameTrigger == 1)        userNameTrigger++;    //Username entered but not verified
        else if(passwordTrigger == 1)   passwordTrigger++;    //Password entered but not verified

        if(userNameTrigger == 2 && passwordTrigger == 2)    verifyPassword();
    }
    else if(value == 4)
    {
        changeForm(21);
    }
    else if(userNameTrigger == 1 && userNamePointer < sizeof(UserName) - 1)   //entering username
    {
        UserName[userNamePointer] = value;
        UserName[userNamePointer + 1] = 0x00;
        userNamePointer++;

        genie.WriteStr(32, UserName);
    }
    else if(passwordTrigger == 1 && passwordPointer < sizeof(Password) - 1)    //entering password
    {
        Password[passwordPointer] = value;
        Password[passwordPointer + 1] = 0x00;
        passwordPointer++;

        genie.WriteStr(50, Password);
    }  
}

void verifyPassword()
{
    if(strcmp(UserName, "DCVAX") == 0 && strcmp(Password, "DCVAX") == 0)
    {
        userNameTrigger++;  //verified
        passwordTrigger++;  //verified
        changeForm(1);
    }
    else
    {
        userNameTrigger = passwordTrigger = userNamePointer = passwordPointer = 0;
        genie.WriteStr(32, "               ");
        genie.WriteStr(50, "               ");
    }
}




void changeForm(int form)
{
    if(form == 16 && (currentForm == 0 || currentForm == 16))
    {
        return;
    }

    previousForm = currentForm;

    currentForm = form;
    genie.WriteObject(GENIE_OBJ_FORM, form, 0);
    snprintf(messageArray, sizeof(messageArray) - 1, "F%i,", form);
    Serial.print(messageArray);

    titleString(form);
    messageString(form);
    instructionString(form);
}

void changeState(int state)
{
    stateIndex = state;
    snprintf(messageArray, sizeof(messageArray) - 1, "S%i,", state);
    Serial.print(messageArray);
}

void clearConfiguration()
{
    routine = 0;

    pos1_config = 0;
    pos2_config = 0;
    pos3_config = 0;
}

void SMInputwrite()
{
    for(int i = 0; Serial.available() > 0 && i < sizeof(SMInput) - 2; i++)
    {
        SMInput[i] = Serial.read(); 
        SMInput[i+1] = 0x00; delay(1);
    }

    Serial.print("Serial Input: "); Serial.println(SMInput);

    if(strcmp("time", SMInput) == 0)    //Set remaining time to 2 seconds
    {
        if(remainingTotalSec1 > 5 || remainingTotalSec2 > 5 || remainingTotalSec3 > 5)
        {
            unsigned long max1 = max(remainingTotalSec1, remainingTotalSec2);
            unsigned long max2 = max(max1, remainingTotalSec3);

            timeSkip = (max2 * 1000) - 5000;   //in milliseconds
        }         
    }
    else if(strcmp("state", SMInput) < 5)
    {
        char state[3];

        state[0] = SMInput[5];
        state[1] = SMInput[6];
        state[2] = 0x00;

        stateIndex = atoi(state);
        Serial.print("\nInput state = "); Serial.println(stateIndex);
        
        command = RUN;
    }
    else
    {
        //Mitsubishi Servo
        if(strcmp("ihr", SMInput) == 0)   //INITIAL HOMING ROUTINE (MUST BE EXECUTED AT EVERY STARTUP)
        {
            servoFunctions(1);
        }
        else if(strcmp("STOP", SMInput) == 0)   //stop shaking
        {
            shake_stop();
            shake_home(1);
        }
        else if(strcmp("shm", SMInput) == 0)    //Shake Homing Routine
        {
          shake_home(1);
        }
        else if(strcmp("rst", SMInput) == 0)    //Variable Reset
        {
          servo_reset();
        }
        else if(strcmp("eq", SMInput) == 0)   //Equilibration Program Selection (p2)
        {
            servoFunctions(2);
        }
        else if(strcmp("dr", SMInput) == 0)   //Drain Program Selection (p3)
        {
            servoFunctions(3);
        }
        else if (strcmp("hm", SMInput) == 0)    //Equilibrate and Drain Homing Program Selection (p4)
        {
            servoFunctions(4);
        }

            //Shake Program Selection
            else if (strcmp("p5", SMInput) == 0) // vigorous shake config 1
            {    
              servoFunctions(5);
            }
            else if (strcmp("p6", SMInput) == 0) // gentle shake config 1
            {
              servoFunctions(6);
            }
            else if (strcmp("p7", SMInput) == 0) // vigorous shake config 2
            {
              servoFunctions(7);
            }
            else if (strcmp("p8", SMInput) == 0) // vigorous shake config 3
            {
              servoFunctions(8);
            }

            //Indirect Addressing Method (Change Parameters on the fly)
            else if(strcmp("30", SMInput) == 0)
            { 
              servoFunctions(9);        
            }
            else if(strcmp("60", SMInput) == 0)
            {
              servoFunctions(10);
            }
            else if(strcmp("90", SMInput) == 0)
            {
              servoFunctions(11);
            }
            else if(strcmp("120", SMInput) == 0)
            {
              servoFunctions(12);
            }

            //EM2 
            else if(strcmp("q", SMInput) == 0) digitalWrite(EM2, !pin_status);       
            else if(strcmp("w", SMInput) == 0) digitalWrite(EM2, pin_status); 

            //SON 
            else if(strcmp("e", SMInput) == 0) digitalWrite(SON, !pin_status);       
            else if(strcmp("r", SMInput) == 0) digitalWrite(SON, pin_status); 

            //MD0 
            else if(strcmp("t", SMInput) == 0) digitalWrite(MD0, !pin_status);       
            else if(strcmp("y", SMInput) == 0) digitalWrite(MD0, pin_status);

            //ST1 
            else if(strcmp("u", SMInput) == 0) digitalWrite(ST1, !pin_status);       
            else if(strcmp("i", SMInput) == 0) digitalWrite(ST1, pin_status); 

            //DI_4 
            else if(strcmp("o", SMInput) == 0) digitalWrite(DI_4, !pin_status);       
            else if(strcmp("p", SMInput) == 0) digitalWrite(DI_4, pin_status); 

            //DOG 
            else if(strcmp("a", SMInput) == 0) digitalWrite(DOG, !pin_status);       
            else if(strcmp("s", SMInput) == 0) digitalWrite(DOG, pin_status); 

            //LSP 
            else if(strcmp("d", SMInput) == 0) 
            {
              digitalWrite(LSP, !pin_status);
              delay(300);
              digitalWrite(LSP, pin_status);
              LSP_status = 0; 
            }       

            //LSN 
            else if(strcmp("g", SMInput) == 0) 
            {
              digitalWrite(LSN, !pin_status);
              delay(300);
              digitalWrite(LSN, pin_status);
              LSN_status = 0;  
            }      
            //DI_0
            else if(strcmp("0", SMInput) == 0) digitalWrite(DI_0, !pin_status);       
            else if(strcmp("1", SMInput) == 0) digitalWrite(DI_0, pin_status);       

            //DI_1  
            else if(strcmp("2", SMInput) == 0) digitalWrite(DI_1, !pin_status);       
            if(strcmp("3", SMInput) == 0) digitalWrite(DI_1, pin_status);

            //DI_2  
            else if(strcmp("4", SMInput) == 0) digitalWrite(DI_2, !pin_status);       
            else if(strcmp("5", SMInput) == 0) digitalWrite(DI_2, pin_status); 

            //DI_3  
            else if(strcmp("6", SMInput) == 0) digitalWrite(DI_3, !pin_status);       
            else if(strcmp("7", SMInput) == 0) digitalWrite(DI_3, pin_status);  
    }
} //SMInputwrite()

