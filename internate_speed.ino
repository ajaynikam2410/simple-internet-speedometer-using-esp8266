//Do not forget to change SSID, Password section.
// install esp8266wifi and esp8266ping library

#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
//connect led to respective pin on node mcu
#define Red 16  //D0
#define Yellow 5 //D1
#define Green 4  //D2
#define indicator 13  //D7

const char* ssid     = "ap";  //enter your ssid
const char* password = "12345678";  //enter your wifi password

const char* remote_host = "www.google.com";


String avg_time_ms;
int i;

void setup() {
  Serial.begin(115200);
  
  pinMode(Red,OUTPUT);
  pinMode(Yellow,OUTPUT);
  pinMode(Green,OUTPUT);
  pinMode(indicator,OUTPUT);
  delay(10);
  
  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     digitalWrite(indicator,HIGH);
     delay(1000);
      digitalWrite(indicator,LOW);
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected with ip ");  // Just for troubleshot purpose.  
  Serial.println(WiFi.localIP());
  Serial.print("Pinging host ");  // Just for troubleshot purpose.
  Serial.println(remote_host);
  digitalWrite(indicator,HIGH);
}

void loop() {

    if(Ping.ping(remote_host)) 
    {
    Ping.ping(remote_host, 10);  //10 time ping to google, You can change value to higher or lower
    i= Ping.averageTime();
    avg_time_ms = Ping.averageTime(); // reading string and Int for easy display integration.
    Serial.println(i);

  if (i < 20)  // It is in general term, Please change as per your requirement
 {
  
  Serial.println("Excelent Speed");
  Serial.println("Green led on");
  digitalWrite(Red,LOW);
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,HIGH);
 }
  if (i > 20 && i < 50)  // It is in general term, Please change as per your requirement
 {
   
  Serial.println("Average Speed");
  Serial.println("Yellow led on");
  digitalWrite(Red,LOW);
  digitalWrite(Yellow,HIGH);
  digitalWrite(Green,LOW);
 }

if (i > 50 )  // It is in general term, Please change as per your requirement
 {
   
  Serial.println("Bad Speed");
  Serial.println("Red led on");
  digitalWrite(Red,HIGH);
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,LOW);
 }



 
    } 
    
    else 
    {
    Serial.println("Error :(");
  digitalWrite(Red,LOW);
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,LOW);
   digitalWrite(indicator,LOW);
   delay(500);
    digitalWrite(indicator,HIGH);
    }
  
 
 // delay(30000);  // Every minutes
 
}
