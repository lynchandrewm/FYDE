// Debug.ino
// Andrew Lynch
// January 30, 2018

// Set the number to whichever part you're currently useing
// i.e. for part two "STEP_NUMBER 2"
#define STEP_NUMBER 1

bool check_failure(int);
int psuedo_random(void);
void failure(void);
void success(void);

#if STEP_NUMBER == 1

void sensor_init(void);
void actuator_init(void);
void wifi_init(void);

void sensor_init(void)
{
  if(check_failure(3))
  {
    //your changes here

    failure();
  }
}

void actuator_init(void)
{
  if(check_failure(5))
  {
    //your changes here

    failure();
  }
}

void wifi_init(void)
{
  if(check_failure(7))
  {
    //your changes here

    failure();
  }
}

int main(void)
{
  sensor_init();
  actuator_init();
  wifi_init();
  while(1)
  {
    success();  
  }
}

#elif STEP_NUMBER == 2

int main(void)
{
    Serial.begin(9600);
    for(int i = 5; i < 100; i++)
    {
        if(check_failure(i))
        {
            //insert your code here

            failure();
        }
    }
    success();
}

#elif STEP_NUMBER == 3

int main(void)
{
    int num;
    Serial.begin(9600);
    for(int i = 0; i < 500; i++)
    {
        num = psuedo_random();
        digitalWrite(13, HIGH);
        num = psuedo_random();
        Serial.write(num);
        digitalWrite(13, LOW);
    }
    for(;;){}
}

#endif

void success(void)
{
  for(;;)
  {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}

void failure(void)
{
  digitalWrite(13, HIGH);
}

bool check_failure(int num)
{
  if(!(psuedo_random() % num))
  {
    return true;
  }
  return false;
}

int psuedo_random(void)
{
  return analogRead(0);
}


