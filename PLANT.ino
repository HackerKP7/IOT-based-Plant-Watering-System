#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "time.h"



#define soil 23
#define Motor_A 21   //your motor pin number
#define Motor_B 22   // your motor pin number
#define LED 12
float threshold_moisture = 10;
float max_threshold_moisture = 40;


BlynkTimer timer;
char auth[] = "YOUR_AUTH_CODE";
char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 3600;


void blynk() {

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");

  
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  int timeHour_int = timeHour - '0';
  Serial.println(timeHour_int);


  char timeMin[3];
  strftime(timeMin,3, "%M", &timeinfo);
  int timeMin_int = timeMin - '0';
  Serial.println(timeMin_int);


  int time_H = Blynk.virtualRead(V1);
  int time_M = Blynk.virtualRead(V0);
  int manual = Blynk.virtualRead(V2);
  int mode   = Blynk.virtualRead(V4);
  float Moisturepercentage = (100 - ((analogRead(soil)/1023)*100));

 
  
  Serial.print("Moisture in percent: ");
  Serial.println(Moisturepercentage);
  Blynk.virtualWrite(V3,Moisturepercentage);
  Blynk.virtualWrite(V3,t);




  if (timeMin_int == time_M && timeHour_int == time_H && Moisturepercentage < threshold_moisture && mode == 2){
    digitalWrite(Motor_A,HIGH);
    digitalWrite(Motor_B,LOW);
    digitalWrite(LED,HIGH);
    Serial.println("watering");
    Blynk.logEvent("watering");
  }
  else if(Moisturepercentage < threshold_moisture && mode == 1){
    digitalWrite(Motor_A,HIGH);
    digitalWrite(Motor_B,LOW);
    digitalWrite(LED,HIGH);
    Serial.println("watering");
    Blynk.logEvent("watering");
  }
  else if(manual == 1 && mode == 3){
    digitalWrite(Motor_A,HIGH);
    digitalWrite(Motor_B,LOW);
    digitalWrite(LED,HIGH);
    Serial.println("watering");
    Blynk.logEvent("watering");
    if (Moisturepercentage > max_threshold_moisture){
      Serial.println("enough_water");
      Blynk.logEvent("enough_water")
    }
  }
  else{
    digitalWrite(Motor_A,HIGH);
    digitalWrite(Motor_B,HIGH);
    digitalWrite(LED,LOW);
    Serial.println("OFF");
    if (mode == 3 && Moisturepercentage < threshold_moisture){
      Serial.println("water_please");
      Blynk.logEvent("water_please");
    }
  }
}


void setup() {  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, sendSensor);
  pinMode(DHT,INPUT);
  pinMode(soil,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(Motor_A,OUTPUT);
  pinMode(Motor_B,OUTPUT);


  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
 }
 dht.begin();
}


void loop() {

  Blynk.run();
  timer.run();
  blynk();
  
}