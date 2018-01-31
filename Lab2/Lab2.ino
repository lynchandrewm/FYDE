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

/*
 * For step 1, use the LED to signal which init is failing
 */

void sensor_init(void);
void actuator_init(void);
void wifi_init(void);

void sensor_init(void)
{
  if(check_failure(3))
  {
    //your code here

    failure();
  }
}

void actuator_init(void)
{
  if(check_failure(5))
  {
    //your code here

    failure();
  }
}

void wifi_init(void)
{
  if(check_failure(7))
  {
    //your code here

    failure();
  }
}

void setup(void)
{
  sensor_init();
  actuator_init();
  wifi_init(); 
}

void loop(void){
  success();  
}

#elif STEP_NUMBER == 2

/*
 * For step 2, use the serial monitor to debug. 
 * TOOLS > SERIAL MONITOR
 */

void setup(void)
{
    Serial.begin(9600);
    Serial.println("Serial monitor is working!");
}

void loop(void)
{
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

/*
 * For step three, use the Analog Discovery to see the effects of the serial monitor
 * Now think of a way to fix the problem.
 */

void setup(void)
{
    Serial.begin(9600);
    Serial.println("Serial monitor is working!");
}

void loop(void)
{
    int num;
    for(int i = 0; i < 500; i++)
    {
        num = psuedo_random();
        digitalWrite(13, HIGH);
        num = psuedo_random();
        Serial.println(num);
        digitalWrite(13, LOW);
    }
    for(;;){}
}

#endif

/*
 ********************************************************************************
 ********               DO NOT EDIT BELOW THIS LINE                      ********
 ********************************************************************************
 */

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
  for(;;)
  {
    digitalWrite(13, HIGH);
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

int psuedo_random(void)
{
  return analogRead(0);
}
