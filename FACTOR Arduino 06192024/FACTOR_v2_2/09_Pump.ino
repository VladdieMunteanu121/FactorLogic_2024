//Pump 1 is on Arduino 1/Primary (Top Pump)
//Pump 2 is on Arduino 2 (Middle Pump) Serial 2
//Pump 3 is on Arduino 3 (Bottom Pump) Serial 1

void startWM(int mode, int direction, int flowRate)    //Routines: mode = 0; Manual Control: mode = 1 || 2 || 3 (top || middle || bottom pump)
{
    if((!mode && TotalSec2 > 0 && !pos2timer) || mode == 2)
    {
        if(flowRate == 20 && direction == 0)          Serial2.print("START0200");
        else if(flowRate == 20 && direction == 1)     Serial2.print("START0201");
        else if(flowRate == 50 && direction == 0)     Serial2.print("START0500");
        else if(flowRate == 50 && direction == 1)     Serial2.print("START0501");
        else if(flowRate == 100 && direction == 0)    Serial2.print("START1000");
        else if(flowRate == 100 && direction == 1)    Serial2.print("START1001");
        else if(flowRate == 200 && direction == 0)    Serial2.print("START2000");
        else if(flowRate == 200 && direction == 1)    Serial2.print("START2001");
        
        WM2_status = direction;
        WM2_flowRate = flowRate;
    }

    if((!mode && TotalSec3 > 0 && !pos3timer) || mode == 3)
    {
        if(flowRate == 20 && direction == 0)          Serial1.print("START0200");
        else if(flowRate == 20 && direction == 1)     Serial1.print("START0201");
        else if(flowRate == 50 && direction == 0)     Serial1.print("START0500");
        else if(flowRate == 50 && direction == 1)     Serial1.print("START0501");
        else if(flowRate == 100 && direction == 0)    Serial1.print("START1000");
        else if(flowRate == 100 && direction == 1)    Serial1.print("START1001");
        else if(flowRate == 200 && direction == 0)    Serial1.print("START2000");
        else if(flowRate == 200 && direction == 1)    Serial1.print("START2001");

        WM3_status = direction;
        WM3_flowRate = flowRate;
    }

    if((!mode && TotalSec1 > 0 && ! pos1timer) || mode == 1)
    {
        if(flowRate == 20)          WM1speed = WM1speed20;
        else if(flowRate == 50)     WM1speed = WM1speed50;
        else if(flowRate == 100)    WM1speed = WM1speed100;
        else if(flowRate == 200)    WM1speed = WM1speed200;

        start_motor(direction, WM1speed, 0);    
        WM1_status = direction;
        WM1_flowRate = flowRate;
    }
} //startWM()


void stopWM(int pump)
{
    if(pump == 1)
    {
        digitalWrite(WMDISABLEpin, HIGH);
        WM1_status = 2;  
        WM1_flowRate = 0;
        //Serial.println("\nSTOP WM1");
    }
    else if(pump == 2)
    {
        snprintf(messageArray, sizeof(messageArray) - 1, "STOP");
        Serial2.print(messageArray);
        WM2_status = 2;
        WM2_flowRate = 0;
        //Serial.println("\nSTOP WM2");
    }
    else if(pump == 3)
    {
        snprintf(messageArray, sizeof(messageArray) - 1, "STOP");
        Serial1.print(messageArray);
        WM3_status = 2;
        WM3_flowRate = 0;
        //Serial.println("\nSTOP WM3");
    }
}











long clockSpeed = 16000000;
long timer_prescaler;
long motor_time;
long start_motor_time;
long high_speed_time;

   
//********************************* start_motor *********************************************
void start_motor(int dir, long microsteps_per_second, long high_time)
{ 
    long frequency = microsteps_per_second; // multiply by 2 to give complete square steps or 50% duty cycle
    high_speed_time = high_time*1000;           // high speed duration in miliseconds
    start_motor_time = millis();                // motor starting timer
    motor_time = 0;                             //initializing motor time, start_motor_time and motor_time will help with getting higher flowarte for high_speed_time duration and 0 for rest of the minute.
    
    digitalWrite(WMDISABLEpin, LOW);
    digitalWrite(WMDIRpin, dir);           //pump direction (0 = CW; 1 = CCW)
    start_timer(frequency);  
}

 
//*********************************************************START TIMER

void start_timer(long frequency)
{
    timer_prescaler = 256;
    
    noInterrupts();   
    
    TCCR3A = 0;                                    
    TCCR3B = 0;                                      
    TCNT3 = 0; 
  
    // Timer 3 is 16-bit, so this number needs to be safely within 65536
    // with prescaler at 256, the range is ~ 1 - 20,000 microsteps per second
    OCR3A = clockSpeed / timer_prescaler / frequency;
  
    
    TCCR3B |= (1 << WGM32);                   
    TCCR3B |= (1 << CS32);                    
    TIMSK3 |= (1 << OCIE3A);
      
    interrupts();
}


//*********************************************************INTERRUPT HANDLERS
ISR(TIMER3_COMPA_vect)
{
  //Serial.println(digitalRead(WMSTEPpin));
  motor_time = millis() - start_motor_time;        // update motor on time

  
  // check if motor has been on till high_speed duration
  if(motor_time>=high_speed_time && high_speed_time>0 && motor_time<60000)
  {
        //motor_state = 0;
        digitalWrite(WMSTEPpin,LOW);
  }
  
  // reset motor_time and start_motor_time when 1 minute has completed
  else if (motor_time>=60000)
  {
        motor_time = 0;
        start_motor_time = millis();
  }

  // sends PWM for required flowrate to Geckdrive
      digitalWrite(WMSTEPpin, digitalRead(WMSTEPpin)^1);
}// end of timer interrupt 

