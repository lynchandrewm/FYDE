char ssid[] = "fydetest";  // your network SSID (name)
char pass[] = "fYdEtEsT";  // your network password
char token[] = "FYDETEST";

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
  if (Serial1.available() > 0) {
    int inByte = Serial1.read();
    Serial.write(inByte); 
  }
}
