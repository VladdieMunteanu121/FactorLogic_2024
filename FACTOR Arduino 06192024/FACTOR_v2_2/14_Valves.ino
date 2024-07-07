void closeValves()
{
    valveControl(1, false);
    valveControl(2, false);
    valveControl(3, true);
    delay(100);
}

void valveControl(int valve, bool status)
{
    if(valve == 1)
    {
        digitalWrite(valve1PIN, status);
        valve1Status = status;
    }
    else if(valve == 2)
    {
        digitalWrite(valve2PIN, status);
        valve2Status = status;
    }
    else if(valve == 3)
    {
        digitalWrite(valve3PIN, status);
        valve3Status = status;
    }
}