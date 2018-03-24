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


#define led 13


int     Pin_Number  = 255;
int     Pin_Integer = 0;
float   Pin_Float   = 0.0;

// **********************************
void DebugPrint(void) {

  Serial.print(Pin_Number);
  Serial.print(",");
  Serial.print(Pin_Integer);
  Serial.print(",");
  Serial.println(Pin_Float); 
 
}

// **********************************
void SerialInput_to_Mega(void) {

  while (Serial1.available() > 0) {
    //Serial.println("In serial input");
    // look for the next valid integer in the incoming serial stream:

    Pin_Number  = Serial1.parseInt();
    Pin_Integer = Serial1.parseInt();
    Pin_Float = Serial1.parseFloat();
     
    // look for the newline.
    if (Serial1.read() == '\n') {
      //DebugPrint();
    }
  Parser();
  }
}

int Val = 50;
int led_val = 4;
int brightness = 255;

// **********************************
void Parser(void) {
  //Serial.println("In the parser");
  
  if((Pin_Number == 1) && (Pin_Integer == 1))  {
    
    DebugPrint();
    digitalWrite(led, HIGH);
    
    Serial1.print(Val);
    Serial1.print(",");
    Serial1.print(Pin_Integer);
    Serial1.print(",");
    Serial1.print(Val*Val);
    Serial1.print("\n");

    Serial1.print(led_val);
    Serial1.print(",");
    Serial1.print(brightness);
    Serial1.print(",");
    Serial1.print(Pin_Integer);
    Serial1.print("\n");
  }
  
  if((Pin_Number == 1) && (Pin_Integer == 0))  {
    DebugPrint();
    digitalWrite(led, LOW);

    Serial1.print(Val);
    Serial1.print(",");
    Serial1.print(Pin_Integer);
    Serial1.print(",");
    Serial1.print(Val*Val*8.39);
    Serial1.print("\n");

    Serial1.print(led_val);
    Serial1.print(",");
    Serial1.print(Pin_Integer);
    Serial1.print(",");
    Serial1.print(Val);
    Serial1.print("\n");
    
  }

  if (Pin_Number == 5) { 
    brightness = Pin_Integer; 
    
    DebugPrint();

    Serial1.print(led_val);
    Serial1.print(",");
    Serial1.print(brightness);
    Serial1.print(",");
    Serial1.print(Pin_Integer);
    Serial1.print("\n");
  }
 
}

int sensorPin = A0;    // select the input pin for the potentiometer
float sensorValueOld = 0.0;  // variable to store the value coming from the sensor
float sensorValueNew = 0.0; 

// **********************************
void ReadSensors(void) {
  
  sensorValueNew = analogRead(sensorPin);
  
  if (abs(sensorValueNew - (sensorValueOld)) > 0) {
    Serial1.print(49);
    Serial1.print(",");
    Serial1.print(0);
    Serial1.print(",");
    Serial1.print((sensorValueNew/1023)*5);
    Serial1.print("\n");
    sensorValueOld = sensorValueNew;
  
    Serial.print("Analog pin value = ");
    Serial.print(sensorValueNew);
    Serial.print("\n");
  }
}

void setup() {
  pinMode(led, OUTPUT);
  
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.begin(9600);
  
  digitalWrite(led, HIGH);
}


void loop() {
  
  SerialInput_to_Mega();
  //Execute();
  delay(200);
  ReadSensors();
  delay(200);  
}
