
#define BLINKER_WIFI
#include <Blinker.h>
char auth[] = "xxxxxxxxxxxx";//Blinker平台获取
char ssid[] = "Test";       //WIFI名称
char pswd[] = "66666666";  //WIFI密码
bool sta,swa,swb;
BlinkerButton Button1("btn1");
BlinkerButton Button2("btn2");
BlinkerButton Button3("btn3");
void button1_callback(const String & state) {
  BLINKER_LOG("get button1 state: ", state);
  if(state=="off"){
    digitalWrite(4,HIGH);
    digitalWrite(12,HIGH);
    swa=0;
  }if(state=="on"){
    digitalWrite(4,LOW);
    digitalWrite(12,LOW);
    swa=1;
  }  
  t1();
  Blinker.vibrate(); 
}
void button2_callback(const String & state) {
  BLINKER_LOG("get button1 state: ", state);
  if(state=="off"){
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    swa=swb=0;
  }if(state=="on"){
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    swa=swb=1;
  }  
  t1();
  Blinker.vibrate();  
}
void button3_callback(const String & state) {
  BLINKER_LOG("get button1 state: ", state);
  if(state=="off"){
    digitalWrite(5,HIGH);
    digitalWrite(13,HIGH);
    swb=0;
  }if(state=="on"){
    digitalWrite(5,LOW);
    digitalWrite(13,LOW);
    swb=1;
  }  
  t1();
  Blinker.vibrate(); 
}
void heartbeat() {
  t1();
  
}
void t1(){
  if(swa){
        Button1.color("#fddb00");
        Button1.text("A端已打开");    
        Button1.print("on");         
      }else{
        Button1.text("A端已关闭");    
        Button1.print("off");     
      }
    if(swb){
      Button3.color("#fddb00");
      Button3.text("B端已打开");    
      Button3.print("on");  
      }else{
        Button3.text("B端已关闭");    
        Button3.print("off");
        
      }
    if(swa and swb){
      Button2.color("#fddb00");
      Button2.text("AB端已打开");    
      Button2.print("on");   
      }else{
        Button2.text("AB端已关闭");    
        Button2.print("off");      
      } 
}
void setup() {
  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);
  Blinker.begin(auth, ssid, pswd);
  Button1.attach(button1_callback);
  Button2.attach(button2_callback);
  Button3.attach(button3_callback);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(4,HIGH);
  Blinker.attachHeartbeat(heartbeat);
  sta=swa=swb=0;
}
void loop() {
  Blinker.run();
  if(sta==0){   
      if(Blinker.init()){
        digitalWrite(5,HIGH); 
        digitalWrite(4,HIGH);          
        sta=1;
        }else{
          digitalWrite(5,LOW);
          digitalWrite(4,HIGH);
          Blinker.delay(10);
          digitalWrite(5,HIGH); 
          digitalWrite(4,LOW);  
          Blinker.delay(50);   
        }  
   }
}
