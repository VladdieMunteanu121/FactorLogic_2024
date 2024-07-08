//Servo Pos: 0 = home (flat), 1 = equilibrate (90), 2 = drain (145), 3 = fill (angled)

void setServo(int servo_desiredPos, int shakeType)
{
    if(servo_desiredPos != servoPos)
    {
        posServo(servo_desiredPos);   // 0 = home, 1 = equilibrate, 2 = drain, 3 = fill

        if((servoPos == 0 && servo_desiredPos == 1) || (servoPos == 1 && servo_desiredPos == 0))        delay(3500);
        else if((servoPos == 0 && servo_desiredPos == 2) || (servoPos == 2 && servo_desiredPos == 0))   delay(5500);
        else if((servoPos == 0 && servo_desiredPos == 3) || (servoPos == 3 && servo_desiredPos == 0))   delay(500);   
        else if((servoPos == 2 && servo_desiredPos == 1) || (servoPos == 1 && servo_desiredPos == 2))   delay(8500);
        else if((servoPos == 3 && servo_desiredPos == 2) || (servoPos == 2 && servo_desiredPos == 3))   delay(6000);
        
        servoPos = servo_desiredPos;    //update current servoPos
    }

    if(shakeType)   startServoShake(shakeType);
} //setServo


//POSITION PROGRAMS
void posServo(int pos_cmd)
{
    if(pos_cmd == 0) //Equilibrate-Drain Homing Program - p4
    {
        bool DI_0_status = digitalRead(DI_0);     
        bool DI_1_status = digitalRead(DI_1);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        delay(10);    //added 11192023
        digitalWrite(ST1, !pin_status); 
    }
    else if (pos_cmd == 1) //Equilibration - p2
    {
        bool DI_0_status = digitalRead(DI_0);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        delay(100);
        digitalWrite(ST1, !pin_status);
    }
    else if (pos_cmd == 2) //Drain - p3
    {
        bool DI_1_status = digitalRead(DI_1);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
    }
    else if(pos_cmd == 3) //Fill - p14
    {
        bool DI_0_status = digitalRead(DI_0);
        bool DI_3_status = digitalRead(DI_3);
        bool DI_2_status = digitalRead(DI_2);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_3_status == pin_status) digitalWrite(DI_3,!pin_status);
        if(DI_2_status == pin_status) digitalWrite(DI_2,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(300);
        servo_reset();
    }

    delay(300);
    servo_reset();
} //posServo()


//SHAKING PROGRAMS
void startServoShake(int shake_cmd)
{
    if(shake_cmd == 1) //GentleShake_1 - p6
    {
        bool DI_0_status = digitalRead(DI_0);
        bool DI_2_status = digitalRead(DI_2);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_2_status == pin_status) digitalWrite(DI_2,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(300);
        servo_reset();
    }
    else if (shake_cmd == 2) //GentleShake_2 - p13
    {
        bool DI_3_status = digitalRead(DI_3);
        bool DI_2_status = digitalRead(DI_2);
        if(DI_3_status == pin_status) digitalWrite(DI_3,!pin_status);
        if(DI_2_status == pin_status) digitalWrite(DI_2,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(300);
        servo_reset();
    }
    else if (shake_cmd == 3) //Day7_VigorousShake_1 - p5
    {
        bool DI_2_status = digitalRead(DI_2);
        if(DI_2_status == pin_status) digitalWrite(DI_2,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
    else if (shake_cmd == 4) //Day7_VigorousShake_2 - p7
    {
        bool DI_1_status = digitalRead(DI_1);
        bool DI_2_status = digitalRead(DI_2);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        if(DI_2_status == pin_status) digitalWrite(DI_2,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
    else if (shake_cmd == 5) //Day7_VigorousShake_3 - p8
    {
        bool DI_0_status = digitalRead(DI_0);
        bool DI_1_status = digitalRead(DI_1);
        bool DI_2_status = digitalRead(DI_2);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        if(DI_2_status == pin_status) digitalWrite(DI_2,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
   else if (shake_cmd == 6) //Day8_VigorousShake_1_CS - p10
    {
        bool DI_0_status = digitalRead(DI_0);
        bool DI_3_status = digitalRead(DI_3);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_3_status == pin_status) digitalWrite(DI_3,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
    else if (shake_cmd == 7) //Day8_VigorousShake_2_CS - p11
    {
        bool DI_1_status = digitalRead(DI_1);
        bool DI_3_status = digitalRead(DI_3);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        if(DI_3_status == pin_status) digitalWrite(DI_3,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
    else if (shake_cmd == 8) //Day8_VigorousShake_3_CS - p12
    {
        bool DI_0_status = digitalRead(DI_0);
        bool DI_1_status = digitalRead(DI_1);
        bool DI_3_status = digitalRead(DI_3);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        if(DI_3_status == pin_status) digitalWrite(DI_3,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
    else if (shake_cmd == 9) //Day8_VigorousShake_1_TF- p15
    {
        bool DI_2_status = digitalRead(DI_2);
        bool DI_1_status = digitalRead(DI_1);
        bool DI_3_status = digitalRead(DI_3);
        if(DI_2_status == pin_status) digitalWrite(DI_2,!pin_status);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        if(DI_3_status == pin_status) digitalWrite(DI_3,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
    else if (shake_cmd == 10) //Day8_VigorousShake_2_TF- p16
    {
        bool DI_0_status = digitalRead(DI_0);
        bool DI_2_status = digitalRead(DI_2);
        bool DI_1_status = digitalRead(DI_1);
        bool DI_3_status = digitalRead(DI_3);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_2_status == pin_status) digitalWrite(DI_2,!pin_status);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        if(DI_3_status == pin_status) digitalWrite(DI_3,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
    else if (shake_cmd == 11) //Day8_VigorousShake_3_TF- p17
    {
        bool DI_4_status = digitalRead(DI_4);
        if(DI_4_status == pin_status) digitalWrite(DI_4,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(1000);
        servo_reset();
    }
    else if(shake_cmd == 12) //GentleShake_2 - p18
    {
        bool DI_0_status = digitalRead(DI_0);
        bool DI_4_status = digitalRead(DI_4);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_4_status == pin_status) digitalWrite(DI_4,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(300);
        servo_reset();
    }
    else if(shake_cmd == 13) //Day8_VigorousShake_4_CS - p19
    {
        bool DI_1_status = digitalRead(DI_1);
        bool DI_4_status = digitalRead(DI_4);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        if(DI_4_status == pin_status) digitalWrite(DI_4,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(300);
        servo_reset();
    }
    else if(shake_cmd == 14) //Day8_VigorousShake_4_TF - p20
    {
        bool DI_0_status = digitalRead(DI_0);
        bool DI_1_status = digitalRead(DI_1);
        bool DI_4_status = digitalRead(DI_4);
        if(DI_0_status == pin_status) digitalWrite(DI_0,!pin_status);
        if(DI_1_status == pin_status) digitalWrite(DI_1,!pin_status);
        if(DI_4_status == pin_status) digitalWrite(DI_4,!pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(300);
        servo_reset();
    }

} //startServoShake()



void servoFunctions(int type)
{
    if(type == 1)    //Initial Homing
    {
        digitalWrite(SON, !pin_status);
        delay(1000);
        digitalWrite(ST1, pin_status);
        delay(240);
        digitalWrite(ST1, !pin_status);
        delay(240);
        digitalWrite(ST1, pin_status);
        delay(240);
        digitalWrite(DOG, pin_status);
        delay(240);
        digitalWrite(DOG, !pin_status);
        delay(3000);    
        servo_reset();
    }
    else if(type == 2)    //PD 30 sec
    {
        for (int i = 0; i <= servo_Run30; i++ )
        {
            Serial.println(i);
            bool DI_3_status = digitalRead(DI_3); 
            if(DI_3_status == pin_status) digitalWrite(DI_3,!pin_status);
            delay(10);
            digitalWrite(ST1, !pin_status);
            delay(1000);
          }
          delay(300);
          shake_stop();
          delay(300);
          shake_home(1);
    }
} //servoFunctions()


void servo_home()
{
    bool DI_0_status = digitalRead(DI_0);      
    bool DI_1_status = digitalRead(DI_1);
    Serial.println(DI_1_status);
    if(DI_1_status == pin_status) digitalWrite(DI_0,!pin_status);
    if(DI_0_status == pin_status) digitalWrite(DI_1,!pin_status);
    delay(10);
    digitalWrite(ST1, !pin_status);
    delay(1000);
    servo_reset();
}


void servo_reset()
{
  digitalWrite(DI_0,pin_status);
  digitalWrite(DI_1,pin_status);
  digitalWrite(DI_2,pin_status);
  digitalWrite(DI_3,pin_status);
  digitalWrite(DI_4,pin_status);
  digitalWrite(ST1, pin_status);
}

//SHAKE TERMINATION BLOCK
void shake_stop()
{
  servo_reset();
  delay(300);
  digitalWrite(LSP, !pin_status);
  delay(300);
  digitalWrite(LSP, pin_status);
  LSP_status = 0;
}


void shake_home(int shakeMode_hm) //shakeMode variable only necessary when using timers
{
  if (!LSP_status && shakeMode_hm == 1) //vigorous shake values
      {
        digitalWrite(SON, !pin_status);
        delay(1000);

        digitalWrite(ST1, pin_status);
        delay(950);
        digitalWrite(ST1, !pin_status);
        delay(950);
        digitalWrite(ST1, pin_status);
        delay(950);
        digitalWrite(DOG, pin_status);
        delay(950);
        digitalWrite(DOG, !pin_status);
        delay(1500);
        servo_reset();
        delay(1500);
        servo_home();
      }
      if (!LSP_status && shakeMode_hm == 2) // gentle shake values
      {
        digitalWrite(SON, !pin_status);
        delay(1000);

        digitalWrite(ST1, pin_status);
        delay(300);
        digitalWrite(ST1, !pin_status);
        delay(300);
        digitalWrite(ST1, pin_status);
        delay(300);
        digitalWrite(DOG, pin_status);
        delay(300);
        digitalWrite(DOG, !pin_status);
        delay(1500);
        servo_reset();
        delay(1500);
        servo_home();
      }
      else if (!LSN_status)
      {
        digitalWrite(SON, !pin_status);
        delay(1000);
        servo_reset();
        delay(1000);
        digitalWrite(ST1, pin_status);
        delay(10);
        digitalWrite(ST1, !pin_status);
        delay(10);
        digitalWrite(ST1, pin_status);
        delay(10);
        digitalWrite(DOG, pin_status);
        delay(10);
        digitalWrite(DOG, !pin_status);
        delay(1500);
        servo_reset();
        delay(1500);
        servo_home();
      }
      LSP_status = 1;
      LSN_status = 1;
      shakeMode = 0;
}
//***************************************************************************************SHAKE TERMINATION BLOCK END!!!!