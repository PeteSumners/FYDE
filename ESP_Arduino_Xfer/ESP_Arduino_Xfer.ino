/******************************************************

 Run me on the ESP8266

 */

// Comment out the next line to disable verbose messages
// which will mess up the interface to the MEGA.

//#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <stdio.h>
#include <string.h>

int     Pin_Number  = 255;      // Invalid pin number
int     Pin_Integer = 0;
float   Pin_Float   = 0.0;


#define VirtualPin_Handler(pin_num) \
BLYNK_WRITE(pin_num)                \
{                                   \
  Pin_Number = pin_num;             \
  Pin_Integer = param.asInt();      \
  Pin_Float   = param.asDouble();   \
  Serial.print(Pin_Number);         \
  Serial.print(",");                \
  Serial.print(Pin_Integer);        \
  Serial.print(",");                \
  Serial.print(Pin_Float);          \
  Serial.print("\n");               \
}                         

 
BlynkTimer timer;

//char str[500];
char auth[] = "0ce05cf4d7f34766a37a22ea9777262c";
//char ssid[] = "mac";
char ssid[] = "Arduino-Blynk";
//char ssid[] = "Baldy";
char pass[] = "utfyde21";


VirtualPin_Handler(V1)
VirtualPin_Handler(V2)
VirtualPin_Handler(V3)
VirtualPin_Handler(V4)
VirtualPin_Handler(V5)
VirtualPin_Handler(V6)
VirtualPin_Handler(V7)
VirtualPin_Handler(V8)
VirtualPin_Handler(V9)
VirtualPin_Handler(V10)


void SerialInput_to_BlynkApp(void) {

  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:

    int Pin_Number  = Serial.parseInt();
    int Pin_Integer = Serial.parseInt();
    float Pin_Float = Serial.parseFloat();
 
    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      
      /*Serial.print("V");           
      Serial.print(Pin_Number);
      Serial.print(",");
      Serial.print(Pin_Integer);
      Serial.print(",");
      Serial.print(Pin_Float);
      Serial.print("\n");*/
      
      
      if(Pin_Number > 48) {
      Blynk.virtualWrite(Pin_Number, Pin_Float );
      }
      else {
      Blynk.virtualWrite(Pin_Number, Pin_Integer );
      }
    }
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  //Serial.println("Serial connection success!");

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
  timer.setInterval(1000L, SerialInput_to_BlynkApp);
  //timer.setInterval(1000L, Virtual_Pin_to_BlynkApp);

}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}





/*
void SerialInput_to_BlynkApp(void)
{
  if(Serial.available() > 0)
  {
    // ADD in Parser
    char *p = sz;
    char *str;
    while ((str = strtok_r(p, ",", &p)) != "\0") // delimiter is the comma
    Serial.println(str);
    p = NULL;
   }

    //Blynk.virtualWrite(V32, Serial.readString());
}
*/

/*
void Virtual_Pin_to_BlynkApp(void)

{
    //byte brightness = Pin_Integer ;
    //Serial.print(Pin_Number);

  if((Pin_Number == 1) && (Pin_Integer > 0))  {
    Serial.println(Pin_Number);
    Blynk.virtualWrite(V4, brightness );
    Pin_Integer = 255;
  }
  if(Pin_Integer == 0) {
    Serial.println(Pin_Number);
    Blynk.virtualWrite(V4, 0 );
    Pin_Integer = 255;
  }
}
*/
/*
void SerialInput_to_BlynkApp(void)
{
  if(Serial.available() > 0)
  {
    Blynk.virtualWrite(Serial.readString());
  }
}
*/

/*
String str;

void SerialInput_to_BlynkApp(void) {
  int serial_complete = 0;

  while (Serial.available()) {
      //delay(10);
      if (Serial.available() > 0) {
          char c = Serial.read(); // Gets one byte from serial buffer
          str += c; // Makes the string readString
      }
   serial_complete = 1;
  }

    if ((str.length() > 0) & (serial_complete == 1)) {
      Serial.print("V");
      Serial.println(str);   
    }
  
}
*/


/*
void SerialInput_to_BlynkApp(void) {

  char str[] ="1,23,34,This is a string\0";
  char * pch;
  Serial.print("V");
  //Serial.println(str);
  pch = strtok (str,",");
  while (pch != NULL)
  {
    
    Serial.print(pch);
    Serial.print(",");
    //Serial.println("\n");
    pch = strtok (NULL,",");
  }
  Serial.println("\0");
}
*/

/* char sz[] = "3500,270,890,70,4"; */

/*
void Parser(void) {

  if((Pin_Number == 1) && (Pin_Integer == 1))  {
    Serial.print(Pin_Number);
    Serial.print("~");
    Serial.println(Pin_Integer);
    Blynk.virtualWrite(V4, brightness );
    //Pin_Integer = 255;
  }
  
  if((Pin_Number == 1) && (Pin_Integer == 0))  {
    Serial.print(Pin_Number);
    Serial.print("~");
    Serial.println(Pin_Integer);    
    Blynk.virtualWrite(V4, 0 );
    //Pin_Integer = 255;
  }
    
  if (Pin_Number == 5) { 
    brightness = Pin_Integer;         
    Blynk.virtualWrite(V4, Pin_Integer );
  }
}
*/

/*
 * 
 * 
  // This code attempts to get credentials from the MEGA
  // currently with bugs
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

  /*
void Virtual_Pin_to_BlynkApp(void) {

    
    if((Pin_Number == 1) && (Pin_Integer > 0))  {
    Serial.println(Pin_Number);
    Blynk.virtualWrite(V4, brightness );
    Pin_Integer = 255;
  }
  if(Pin_Integer == 0) {
    Serial.println(Pin_Number);
    Blynk.virtualWrite(V4, 0 );
    Pin_Integer = 255;
  }
  
}
*/

