//www.elegoo.com
//2016.06.13

#define ADD 0x00
int IR_S =  12;    

// IR receiver stuff.
#include <IRremote.h>
 
int RECV_PIN = 11;
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
void setup() 
{ 
  pinMode(IR_S, OUTPUT);

// IRrecvDemo stuff.
// IRRecvDemo Stuff
  Serial.begin(9600);
  irrecv.enableIRIn(); //初始化红外遥控
  pinMode(13,1);
}
void loop() 
{
  uint8_t dat,temp=("123456");

     
    IR_Send38KHZ(280,1);
    IR_Send38KHZ(140,0);
     
    IR_Sendcode(ADD);
    dat=~ADD;
    IR_Sendcode(dat);
     
    IR_Sendcode(temp);
    dat=~temp;
    IR_Sendcode(dat);
     
    IR_Send38KHZ(21,1);

  delay(200);
}
void IR_Send38KHZ(int x,int y) 
{ 
for(int i=0;i<x;i++)
{ 
           if(y==1)
           {
     digitalWrite(IR_S,1);
     // IRRecvDemo Stuff
     
  if (irrecv.decode(&results)) {
if(results.value==16753245)      //确认接收到的第一排按键1的编码，此码是预先读出来的按键编码。
  {
  digitalWrite(13,1);                //点亮LED
   Serial.println("turn on LED"); //串口显示开灯
  }
  else if(results.value==16736925)   //确认接收到的第一排按键2的编码
  {
   digitalWrite(13,0);            //熄灭LED
    Serial.println("turn off LED");    //串口显示关灯
  }
    irrecv.resume(); // 接收下一个值
  }
}

            delayMicroseconds(9);
     digitalWrite(IR_S,0);
            delayMicroseconds(9);
           }
           else
           {
     digitalWrite(IR_S,0);
            delayMicroseconds(20);
           }            
}
}
void IR_Sendcode(uint8_t x) 
{
    for(int i=0;i<8;i++)
     {
       if((x&0x01)==0x01)
        {
           IR_Send38KHZ(23,1);
           IR_Send38KHZ(64,0);             
        }
        else
         {
            IR_Send38KHZ(23,1);
            IR_Send38KHZ(21,0);  
         }
       x=x>>1;
     }  
}
