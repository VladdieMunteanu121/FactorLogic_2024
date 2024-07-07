//Rail Pos: 1 = flat, 2 = oscillate, 3 = extract, 4 = fill, 5 = Drain
int railFlat;   //from extract light switch
int railFlatFill = 10;
int railFlatDrain = 25;
int railFillDrain = railFlatDrain - railFlatFill;
int railExtractDrain = railFlat + railFlatDrain;
int railExtractFill = railFlat + railFlatFill;


int setRail(int railDesiredPos)
{
    Serial.print("railDesiredPos = ");  Serial.println(railDesiredPos);
    
    if(railDesiredPos == 10)    //increment up 1
    {
      rail.setSpeed(100);
      rail.step(rail_pulse_per_rev);
    }
    else if(railDesiredPos == 11)   //increment down 1
    {
      rail.setSpeed(100);
      rail.step(-rail_pulse_per_rev);
    }
    else if (railPos != railDesiredPos)
    {
        if(Site = 0)  railFlat = 6;
        else if(Site = 1)   railFlat = 8;

        //initial homing 
        if (railPos == 0 && railDesiredPos == 1) 
        {
            rail.setSpeed(200); delay(10);
            while(digitalRead(LS_extract) == HIGH)    rail.step(-rail_pulse_per_rev);
            rail.step(rail_pulse_per_rev*railFlat);
        }

        //Flat to Fill
        else if (railPos == 1  && railDesiredPos == 4)
        {
          rail.setSpeed(200); delay(10);
          rail.step(rail_pulse_per_rev*railFlatFill);
        }
    
        //Fill to Flat
        else if (railPos == 4 && railDesiredPos == 1)
        {
          rail.setSpeed(200); delay(10);
          rail.step(-rail_pulse_per_rev*railFlatFill);
        }

  
        //Flat to Drain
        else if(railPos == 1  && railDesiredPos == 5)
        {
            rail.setSpeed(200); delay(10);
            rail.step(rail_pulse_per_rev*railFlatDrain);
        }

        //Drain to Flat
        else if(railPos == 5 && railDesiredPos == 1)
        {
            rail.setSpeed(200); delay(10);
            rail.step(-rail_pulse_per_rev*railFlatDrain);
        }

        //Fill to Drain
        else if(railPos == 4 && railDesiredPos == 5)
        {
            rail.setSpeed(200); delay(10);
            rail.step(rail_pulse_per_rev*railFillDrain);
        }

        //Drain to Fill
        else if(railPos == 5 && railDesiredPos == 4)
        {
            rail.setSpeed(200); delay(10);
            rail.step(-rail_pulse_per_rev*railFillDrain);
        }


        //Extract to Flat
        else if (railDesiredPos == 1  && digitalRead(LS_extract) == LOW)
        {
          rail.setSpeed(200); delay(10);
          rail.step(rail_pulse_per_rev*railFlat);
        }
 
        //Extract to Fill
        else if (digitalRead(LS_extract) == LOW && railDesiredPos == 4)
        {
            rail.setSpeed(200); delay(10);
            rail.step(rail_pulse_per_rev*railExtractFill);
        } 

        //Extract to Drain
        else if(railDesiredPos == 5 && railPos == 3)
        {
            rail.setSpeed(200); delay(10);
            rail.step(rail_pulse_per_rev*railExtractDrain);
        }
        
        //TO Extract
        else if (railDesiredPos == 3 && digitalRead(LS_extract) == HIGH)
        {
            rail.setSpeed(200); delay(10);
            while (digitalRead(LS_extract) == HIGH)   rail.step(-rail_pulse_per_rev);
        }

        else if (railDesiredPos == 2)   //gentle shake up-and-down
        {
            rail.setSpeed(200); delay(10);

            for(int i = 0; i < 2; i++)
            {
                while(digitalRead(LS_extract) == HIGH)    rail.step(-rail_pulse_per_rev);   //to extract
                rail.step(rail_pulse_per_rev*railExtractFill);    //to fill
            }
            delay(10);

            rail.step(-rail_pulse_per_rev*railFlatFill);
            railPos = 1;
            return;   //else railPos is redefined as 2 below
        }
    }

    railPos = railDesiredPos;
    Serial.print("\nRailPos = "); Serial.println(railPos);
}