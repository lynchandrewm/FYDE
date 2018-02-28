/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define VirtualPin_Handler(pin_num) \
BLYNK_WRITE(pin_num)                \
{                                   \
  Serial.print(#pin_num "~");       \
  Serial.print(param.asInt());      \
  Serial.print("~");                \
  Serial.print(param.asStr());      \
  Serial.print("~");                \
  Serial.println(param.asDouble()); \
}                         

BlynkTimer timer;

char buf[500];
char auth[] = "3267e5ebd9a14724862a96767a5f73b1";
char ssid[] = "Beaubien";
char pass[] = "bullybully";

VirtualPin_Handler(V1)

void SerialInput_to_BlynkApp(void)
{
  if(Serial.available() > 0)
  {
    Blynk.virtualWrite(V2, Serial.readString());
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  // This code attempts to get credentials from the MEGA
  // currently with bugs
  /*
  while(Serial.available() <= 0) { ; }
  Serial.readString().toCharArray(buf, 500);
  Serial.println(buf);
  std::string s = buf;
  std::string delimiter = "~";
  size_t pos = 0;
  pos = s.find(delimiter);
  std::string auth = s.substr(0, pos);
  s.erase(0, pos + delimiter.length());
  pos = s.find(delimiter);
  std::string ssid = s.substr(0, pos);
  s.erase(0, pos + delimiter.length());
  std::string pass = s;
  Serial.println(auth.c_str());
  Serial.println(ssid.c_str());
  Serial.println(pass.c_str());
  

  Blynk.begin(auth.c_str(), ssid.c_str(), pass.c_str());
  */
  Serial.println("Serial connection success!");

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
  timer.setInterval(1000L, SerialInput_to_BlynkApp);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

