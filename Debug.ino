// Debug.ino
// Andrew Lynch
// January 30, 2018

// Set the number to whichever part you're currently useing
// i.e. for part two "STEP_NUMBER 2"
#define STEP_NUMBER 1

#if STEP_NUMBER == 1

void sensor_init(void);
void actuator_init(void);
void wifi_init(void);
bool check_failure(int);
int psuedo_random(void);
void failure(void);
void success(void);

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

bool check_failure(int num)
{
  if(!(psuedo_random() % num))
  {
    return true;
  }
  return false;
}

bool init_flag = false;
int psuedo_random(void)
{
  return analogRead(0);
}

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

#elif STEP_NUMBER == 2

#elif STEP_NUMBER == 3

#endif

