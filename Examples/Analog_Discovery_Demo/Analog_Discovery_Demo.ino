// Analog_Discovery_Demo.ino
// Andrew Lynch
// 2/6/18

void outputNextNumber(void);

void setup(void)
{
    for(int i = 0; i < 4; i++)
    {
        pinMode(i, OUTPUT);
    }
}

void loop(void)
{
    for(int i = 0; i < 50; i++)
    {
        delay(10);
        digitalWrite(13, HIGH);
        delay(10);
        digitalWrite(13, LOW);
    }
    outputNextNumber();
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
