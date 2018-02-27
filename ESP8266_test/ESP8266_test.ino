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
 - Connect RX to TX on the programmer
 - Connect TX to RX on the programmer
 - Connect GND to GND
 - Connect GPIO2 to 3.3V with a resistor between 1K and 50K ohms 
 (If you can't find a resistor, you can use some from your EE302/319K kit or ask the equipment 
 checkout desk in EER for one)

 2) Install Module Drivers and Select the Board:
 Go to File -> Preferences and paste this link into aditional board manager url's:
 http://arduino.esp8266.com/stable/package_esp8266com_index.json
 Then, go to Tools -> Boards: -> Boards Manager and search "ESP8266" and install the first item
 Go once more to Tools -> Boards but scroll down and select "Generic ESP8266 module"

 4) Change the network name and password on line 50 and 51 for your hardware
 
 5) To program, unplug your board and connect the GPIO2 to GND with another wire (while it is 
 still pulled up by resistor) then plug the programmer back in, turing on the board. Next, unplug the 
 jumper to ground you just added, select the programmer's COM port, and click the upload button!

 6) Open a serial monitor by going to
 Tools -> Serial Monitor and set to 115200 baud once open to see output

 7) Test and make sure it is working! If you see '......' on the serial
 monitor, you are not connecting to your wifi network correctly.
 
 ******************************************************/
 
// Library defs
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "fydetest";  // your network SSID (name)
char pass[] = "fydetest";  // your network password


unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}

void loop()
{
  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP); 

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = " );
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
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
  }
  // wait ten seconds before asking for the time again
  delay(10000);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
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
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}
