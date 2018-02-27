// Lab4.ino
// Andrew Lynch
// February 8, 2018

/*
    Skeleton file for FYDE class project
*/

//#include "PATH_TO_SENSOR1_DRIVERS"
//#include "PATH_TO_SENSOR2_DRIVERS" //optional sensor 2
//#include "PATH_TO_ACTUATOR1_DRIVERS"
//#include "PATH_TO_ACTUATOR2_DRIVERS" //optional actuator 2
//#include "msp8266_driver.h" //ensure file is in the same directory
                            //or change path to where driver is
#include <assert.h>

// Define statements 

#define COMPILE_MODE 0  // 0 - Release
                        // 1 - Test sensor 1
                        // 2 - Test sensor 2
                        // 3 - Test actuator 1
                        // 4 - Test actuator 2
                        // 5 - Test wifi
                        // 6 - Full system DEBUG
#define WIFI_SSID "MyCellPhonesHotspot"
#define WIFI_WEP2_PASSWORD "MyCellPhonesHotspotPassword"
#define NUMBER_OF_ERRORS_PROJECT_TRACKS 1
#define BAUD_RATE 9600

// Macros at your own risk


// Private Function Declarations
bool errorPresent(int * errorCodeArray, int arrayLen);

// Global Variables


// Test Cases (main functions)

#if COMPILE_MODE == 1 // Test sensor 1
void setup(void)
{}

void loop(void)
{}

#elif COMPILE_MODE == 2 // Test sensor 2
void setup(void)
{}

void loop(void)
{}

#elif COMPILE_MODE == 3 // Test actuator 1
void setup(void)
{}

void loop(void)
{}

#elif COMPILE_MODE == 4 // Test actuator 2
void setup(void)
{}

void loop(void)
{}

#elif COMPILE_MODE == 5 // Test wifi
void setup(void)
{}

void loop(void)
{}

#elif COMPILE_MODE == 6 // Full system DEBUG
void setup(void)
{
    int errorCode[5] = {0, 0, 0, 0, 0};
    Serial.begin(BAUD_RATE);
    // errorCode[0] = sensor1_init();
    // errorCode[1] = sensor2_init();
    // errorCode[2] = actuator1_init();
    // errorCode[3] = actuator2_init();
    // errorCode[4] = msp8266_init(WIFI_SSID, WIFI_WEP2_PASSWORD);
    assert(!errorPresent(errorCode, 5));
    Serial.println("Initializations success");
}

void loop(void)
{
    int errorCode[NUMBER_OF_ERRORS_PROJECT_TRACKS]; 
    runFSM(errorCode);      // this should only return due to error
                            // report error and restart
    Serial.println("Error detected");
    for(int i = 0; i < NUMBER_OF_ERRORS_PROJECT_TRACKS; i++)
    {
        Serial.print("ErrorCode %d: %d\n", errorCode[i]);
        errorCode[i] = 0; // reset errorCode
    }
    assert(false);
}

#endif

// Run case 
#if COMPILE_MODE == 0 // Release
void setup(void)
{
    int errorCode[5] = {0, 0, 0, 0, 0};
    Serial.begin(BAUD_RATE);
    while(errorPresent(errorCode, 5))
    {
        // errorCode[0] = sensor1_init();
        // errorCode[1] = sensor2_init();
        // errorCode[2] = actuator1_init();
        // errorCode[3] = actuator2_init();
        // errorCode[4] = msp8266_init(WIFI_SSID, WIFI_WEP2_PASSWORD);
        if(errorPresent(errorCode, 5))
        {
            Serial.println("Initialization failure...");
            Serial.print("Sensor 1 error code: ");
            Serial.println(errorCode[0]);
            Serial.print("Sensor 2 error code: ");
            Serial.println(errorCode[1]);
            Serial.print("Actuator 1 error code: ");
            Serial.println(errorCode[2]);
            Serial.print("Actuator 2 error code: ");
            Serial.println(errorCode[3]);
            Serial.print("Wifi error code: ");
            Serial.println(errorCode[4]);
            Serial.println("Reattempting initializations...");
        }
    }
    Serial.println("Initializations success");
}

void loop(void)
{
    int errorCode[NUMBER_OF_ERRORS_PROJECT_TRACKS]; 
    runFSM(errorCode);      // this should only return due to error
                            // report error and restart
    Serial.println("Error detected");
    for(int i = 0; i < NUMBER_OF_ERRORS_PROJECT_TRACKS; i++)
    {
        Serial.print("ErrorCode: ");
        Serial.println(errorCode[i]);
        errorCode[i] = 0; // reset errorCode
    }
    Serial.println("Restarting...");
}

#endif

// Private function definitions

/*  errorPresent
    Args:  -errorCodeArray is a pointer to an array of error codes
            It is assumed that a 0 is not an error, and anything else is
           -arrayLen is the number of potential errorCodes
    Return: true is error is present
            false if error is not present
*/
bool errorPresent(int * errorCodeArray, int arrayLen)
{
    for(int i = 0; i < arrayLen; i++)
    {
        if(errorCodeArray[i])
        {
            return true;
        }
    }
    return false;
}

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
    // transmit diagnostic informations through serial link. 
    Serial.println(__func);
    Serial.println(__file);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    Serial.flush();
    // abort program execution.
    abort();
}
