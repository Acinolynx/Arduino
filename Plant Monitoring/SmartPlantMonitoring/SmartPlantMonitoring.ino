
// code dari Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
// IOT Smart Plant Monitoring System dari arduino dan blynk
#define BLYNK_TEMPLATE_ID "TMPL645H07bRL";
#define BLYNK_TEMPLATE_NAME "Automatic Watering Device";
#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2
#include <Blynk.h>

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


char auth[] = "hftW0n19U8RFGE1A0R5oMdOZ4B8OzSTO";               //Kode template dari blynk
char ssid[] = "Tes";                       //WiFi SSID
char pass[] = "11223344";                      //WiFi Password

WiFiClient client;

#define sensorPin D3 
int sensorState = 0;
int lastState = 0;
#define DHTPIN 2    
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal Membaca Dari Sensor DHT!");
    return;
  }
 
  Blynk.virtualWrite(V5, h);  //V5 untuk kelembapan
  Blynk.virtualWrite(V6, t);  //V6 untuk suhu
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
   pinMode(sensorPin, INPUT);
  dht.begin();

  timer.setInterval(1000L, sendSensor);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
   sensors.begin();
}
int sensor=0;
void sendTemps()
{
sensor=analogRead(A0);
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0); 
Serial.println(temp);
Serial.println(sensor);
Blynk.virtualWrite(V1, temp);
Blynk.virtualWrite(V2,sensor);
delay(1000);
}
void loop()
{
  Blynk.run(); 
  timer.run(); 
  sendTemps();
  sensorState = digitalRead(sensorPin);
Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) {
  Serial.println("Butuh Disiram!");
  lastState = 1;
  delay(1000);
//kirim notifikasi
    
  } 
  else if (sensorState == 1 && lastState == 1) {
    //jangan lakukan apa apa, belum disiram
  Serial.println("Belum Disiram");
  delay(1000);
  }
  else {
    //st
    Serial.println("Tidak Perlu Disiram");
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
}
