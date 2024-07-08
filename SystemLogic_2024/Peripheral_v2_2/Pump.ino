long clockSpeed = 16000000;
long timer_prescaler;
long motor_time;
long start_motor_time;
long high_speed_time;


void start_motor(int dir, long microsteps_per_second, long high_time)
{ 
    long frequency = microsteps_per_second; // multiply by 2 to give complete square steps or 50% duty cycle
    high_speed_time = high_time*1000;           // high speed duration in miliseconds
    start_motor_time = millis();                // motor starting timer
    motor_time = 0;                             //initializing motor time, start_motor_time and motor_time will help with getting higher flowarte for high_speed_time duration and 0 for rest of the minute.
    
    digitalWrite(WMDISABLEpin, LOW);
    digitalWrite(WMDIRpin, dir);           //pump direction (0 = CW; 1 = CCW)
    start_timer(frequency);  //commented out because was getting an error s 
}


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


//INTERRUPT HANDLERS
ISR(TIMER3_COMPA_vect)
{
    motor_time = millis() - start_motor_time;        // update motor on time

    //check if motor has been on till high_speed duration
    if(motor_time>=high_speed_time && high_speed_time>0 && motor_time<60000)
    {
        digitalWrite(WMSTEPpin,LOW);
    }

    // reset motor_time and start_motor_time when 1 minute has completed
    else if (motor_time>=60000)
    {
        motor_time = 0;
        start_motor_time = millis();
    }

    //sends PWM for required flowrate to Geckdrive
    digitalWrite(WMSTEPpin, digitalRead(WMSTEPpin)^1);  
}// end of timer interrupt