// Author -- Kalpit Prabhu--
//Project -- Smart IOT based plant watering system using ESP32

#define BLYNK_PRINT Serial
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "time.h"
#include <stdlib.h>
#include <stdio.h>
int time_H,time_M,mode,manual,Moisturepercentage,a,b,c,m;



#define soil 35
#define Motor_A 26
#define Motor_B 27
#define LED 2
#define BLYNK_AUTH_TOKEN "IAPdDFjEsecr-xN2h3JQ7Yn394U-HNNN"


float threshold_moisture = 85;
float max_threshold_moisture = 88;
Adafruit_SSD1306 oled(128,64, &Wire, -1);

BlynkTimer timer;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "BabaYaga";
char pass[] = "Kalpit2547";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 3600;


void plant() {
  int analog = analogRead(soil);
  int Moisturepercentage = ( 100 - ( (analog/4095.00) * 100 ) );
  Serial.print("Moisture = ");
  Serial.print(Moisturepercentage);
  Blynk.virtualWrite(V3,Moisturepercentage);

   Serial.println("%");

  }
  

  



 BLYNK_WRITE(V1){
  int a = param.asInt();
  time_H = a;
 
  
  }
  BLYNK_WRITE(V0){
  int b = param.asInt();
  time_M = b;

  }
  BLYNK_WRITE(V2){
  int c = param.asInt();
  manual = c;
  }
  BLYNK_WRITE(V4){
  int m   = param.asInt();
   mode = m;

  }
 

void setup() {  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  Serial.println(F("SSD1306 allocation failed"));
  while (true);
}


  


  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, plant);
  pinMode(soil,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(Motor_A,OUTPUT);
  pinMode(Motor_B,OUTPUT);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display
  oled.setTextColor(WHITE);

      oled.setTextSize(1);      
            
 }



void loop() {
  Blynk.run();
  timer.run();
  int analog = analogRead(soil);
  int Moisturepercentage = ( 100 - ( (analog/4095.00) * 100 ) );

  
    struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
  }
  Serial.print("Hour: ");

  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  int timeHour_int = atoi(timeHour);
  Serial.println(timeHour_int);

  Serial.print("Minute: ");
  char timeMin[3];
  strftime(timeMin,3, "%M", &timeinfo);
  int timeMin_int = atoi(timeMin);
  Serial.println(timeMin_int);

  if (mode == 0){
    oled.clearDisplay();
    oled.setCursor(0, 0);      
  oled.print("Mode set to: "); 
  oled.setCursor(0, 10);       
  oled.println("No mode set"); 
  oled.display(); 
  }
  if (mode == 1){
      oled.setTextColor(WHITE);
    oled.clearDisplay();
      oled.setCursor(0, 0);      
  oled.print("Mode set to: "); 
  oled.setCursor(0, 10);       
  oled.println("Automatic"); 
  oled.display(); 
  }
  if (mode == 2){
    oled.clearDisplay();
      oled.setCursor(0, 0);      
  oled.print("Mode set to: "); 
  oled.setCursor(0, 10);       
  oled.println("Clock timer");
  oled.setCursor(0,30);
  oled.print("watering time: ");
  oled.setCursor(0,40);
  oled.print(time_H);
  oled.setCursor(20,40);
  oled.print("H");
  oled.setCursor(30,40);
  oled.print(time_M);
  oled.setCursor(50,40);
  oled.print("M");

  oled.display(); 
  }
  if (mode == 3){
    oled.clearDisplay();
         oled.setCursor(0, 0);      
  oled.print("Mode set to: ");  
  oled.setCursor(0, 10);       
  oled.println("Manual");


  oled.display(); 
  }

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
      Blynk.logEvent("enough_water");
    }
  }
  else{
    digitalWrite(Motor_A,HIGH);
    digitalWrite(Motor_B,HIGH);
    digitalWrite(LED,LOW);
    if (mode == 3 && Moisturepercentage < threshold_moisture){
      Serial.println("water_please");
      Blynk.logEvent("water_please");
    }
  
}
delay(3000);
}
