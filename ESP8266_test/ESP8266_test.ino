//  _____ ___________ _____  _____   ____   ____ 
// |  ___/  ___| ___ \  _  |/ __  \ / ___| / ___|
// | |__ \ `--.| |_/ /\ V / `' / /'/ /___ / /___ 
// |  __| `--. \  __/ / _ \   / /  | ___ \| ___ \
// | |___/\__/ / |   | |_| |./ /___| \_/ || \_/ |
// \____/\____/\_|   \_____/\_____/\_____/\_____/
//                                             

/******************************************************

 This example connects to a WPA-secured Wifi network
 using the ESP8266 module, then it pulls the current
 time and date from time.NIST.gov and prints the info 
 on the serial terminal at 115200 baud.

 1) Wire Module:
 Wire according to this picture: https://www.forward.com.au/pfod/ESP8266/GPIOpins/ESP8266_01.jpg
 - Connect VCC and CH_PD to 3.3V on the arduino
 - Connect RX to RX1 (Digital 0 on the arduino) !!! but may need voltage shifting (see below) !!!
 - Connect TX to TX1 (Digital 1 on the arduino)
 - Connect GND to GND
 The RX pin is 3.3V logic while the Arudino is 5V, so you may need to make
 a voltage divider to drop the voltage. To do so, use the formula
 VOUT = VIN(R2/(R1+R2)) so choosing like R1 = 1K and R2 = 2K will work
 You can use resistors from your EE302/319K kits or see the gear checkout desk in EER
 to get required supplies. You neeed to have 5V turn into 3 - 3.3V, so calculate accordingly!
 Diagram of voltage divider: https://cdn.sparkfun.com/r/300-300/assets/c/8/8/7/7/514208cbce395f1c12000000.png

 2) Install Module Drivers and Select the Board:
 Go to File -> Preferences and paste this link into aditional baord manager url's:
 http://arduino.esp8266.com/stable/package_esp8266com_index.json
 Then, go to Tools -> Boards: -> Boards Manager and search "ESP8266" and install the first item
 Go once more to Tools -> Boards but scroll down and select "Generic ESP8266 module"

 3) Install Library:
 Go to Sketch -> Include Library -> Manage Libraries
 and search 'WiFiEsp' in the popup window
 and click install on the first result (should be by bportaluri)
 Go to your Arduino folder on your computer (usually in Documents for windows)
 and navigate to Arduino -> libraries -> WiFiEsp -> src -> utility -> EspDrv.cpp
 and change '#include <avr/pgmspace.h>' to '#include <pgmspace.h>' in the file

 4) Change the network name and password on line 59 and 60 for your hardware
 
 5) Program your Code onto the arduino

 6) Open a serial monitor by going to
 Tools -> Serial Monitor and set to 115200 baud once open

 7) Run! 
 
 ******************************************************/
 
// Library defs
#include "WiFiEsp.h"
#include "WiFiEspUdp.h"

// !!!!!!!!!!!!!!!Update for network being used!!!!!!!!!!!!!!!!!!!!!!!!!!!
char ssid[] = "yourNetwork";     // your network SSID (name) within quotes
char pass[] = "secretPassword";  // your network password within quotes

// Emulate Serial2 on pins 6/7 if not present
#ifndef HAVE_HWSerial2
#include "SoftwareSerial.h"
SoftwareSerial Serial2(6, 7); // RX, TX
#endif

int status = WL_IDLE_STATUS;     // the Wifi radio's status

char timeServer[] = "time.nist.gov";  // NTP server
unsigned int localPort = 2390;        // local port to listen for UDP packets

const int NTP_PACKET_SIZE = 48;  // NTP timestamp is in the first 48 bytes of the message
const int UDP_TIMEOUT = 2000;    // timeout in miliseconds to wait for an UDP packet to arrive

byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiEspUDP Udp;

void setup()
{
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial2.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial2);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
  Udp.begin(localPort);
}

void loop()
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  
  // wait for a reply for UDP_TIMEOUT miliseconds
  unsigned long startMs = millis();
  while (!Udp.available() && (millis() - startMs) < UDP_TIMEOUT) {}

  Serial.println(Udp.parsePacket());
  if (Udp.parsePacket()) {
    Serial.println("packet received");
    // We've received a packet, read the data from it into the buffer
    Udp.read(packetBuffer, NTP_PACKET_SIZE);

    // the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = ");
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);


    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if (((epoch % 3600) / 60) < 10) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ((epoch % 60) < 10) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
  }
  // wait ten seconds before asking for the time again
  delay(10000);
}

// send an NTP request to the time server at the given address
void sendNTPpacket(char *ntpSrv)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)

  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(ntpSrv, 123); //NTP requests are to port 123

  Udp.write(packetBuffer, NTP_PACKET_SIZE);

  Udp.endPacket();
}

