/******************************************************

 RUN ME ON YOUR MEGA!!!

 This program sends your network and blynk token information
 to the WiFi module over serial, then should recieve characters over
 serial from the WiFi module in return.

 1) Wire Module:
 Wire according to this picture: https://www.forward.com.au/pfod/ESP8266/GPIOpins/ESP8266_01.jpg
 - Connect VCC and CH_PD to 3.3V on the arduino
 - Connect RX1 on the mega to TX on the programmer
 - Connect TX1 on the mega to RX on the programmer
 - Connect GND to GND
 
 2) Go to Tools -> Board and select Arduino/Genuino Mega or Mega 2560

 3) Sign up for Blynk (https://www.blynk.cc/) and install the app on your phone.
 MAKE SURE TO CREATE AND WRITE DOWN YOUR TOKEN!!!
 Then, go to Sketch -> Include Library -> Manage Libraries and search 'Blynk' and
 install the library

 4) Change the network name, password, and blynk token in the code to reflect your own 
 
 5) Finish writing the serial recieve in the 'void loop()'
 It needs to:
 - Continuously look for serial input on Serial 1 
 - Take any character recieved on Serial 1 and print
 the data out through the main Serial 

 6) Open a serial monitor by going to
 Tools -> Serial Monitor and set to 9600 baud once open to see output
 and run!
 
 ******************************************************/


char ssid[] = "fydetest";  // your network SSID (name)
char pass[] = "fYdEtEsT";  // your network password
char token[] = "FYDETEST"; // your blynk password

#define led 13

void setup() {
  pinMode(led, OUTPUT);
  
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.begin(9600);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  delay(5000);  

  while (Serial1.available() <= 0) {
    delay(15);
    Serial1.print("~");
    Serial1.print(ssid);
    Serial1.print("~");
    Serial1.print(pass);
    Serial1.print("~");
    Serial1.print("token");
    Serial1.println("~");
  }
}

void loop() {
  //!!!!! EDIT ME !!!!!
  //Please read section 5 in the top for directions
}
