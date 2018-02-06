// Analog_Discovery_Demo.ino
// Andrew Lynch
// 2/6/18

#include "TimerOne.h"

void setup(void)
{
    for(int i = 0; i < 4; i++)
    {
        pinMode(i, OUTPUT);
    }
    Timer1.initialize(100000);
    Timer1.pwm(9, 512);
    Timer1.attachInterrupt(Timer1_handler);
}

void loop(void)
{
    
}

int Timer1_count = 0;
void Timer1_handler(void)
{
    Timer1_count = (Timer1_count + 1) & 0xF;
    if(!Timer1_count)
    {
        outputNextNumber();
    }
}

int currentNumberOut = -1;
void outputNextNumber(void)
{
    currentNumberOut = (currentNumberOut + 1) & 0xf;
    for(int i = 0; i < 4; i++)
    {
        if(currentNumberOut&(1<<i))
        {
            digitalWrite(i, HIGH);
        }
        else
        {
            digitalWrite(i, LOW);
        }
    }
}
