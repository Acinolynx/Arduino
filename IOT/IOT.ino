#define BLYNK_TEMPLATE_ID "TMPL6cQEY8tKP"
#define BLYNK_TEMPLATE_NAME "IOT"
#define BLYNK_AUTH_TOKEN "Y8K-KtRdNH5oUMPnPVZGL4kvVsNFjDbC"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

char auth[] = "Y8K-KtRdNH5oUMPnPVZGL4kvVsNFjDbC";
char ssid[] = "Tes";
char pass[] = "11223344";

int relayPin = D1;
int soilPin = A0;

BlynkTimer timer;

int pompaStatus = 0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V3) { // soil sensor
  int soilMoisture = analogRead(soilPin);
  Blynk.virtualWrite(V3, soilMoisture);
}

BLYNK_WRITE(V4) { // relay / pompa
  int buttonState = param.asInt();
  if (buttonState == 1) {
    // Aktifkan pompa (relay)
    digitalWrite(relayPin, HIGH);
    pompaStatus == 1;
    Blynk.virtualWrite(V1, "Pompa: ON");
  } else {
    // Matikan pompa (relay)
    digitalWrite(relayPin, LOW);
    pompaStatus == 0;
    Blynk.virtualWrite(V1, "Pompa: OFF");
  }
}

BLYNK_READ(V3) { // A0
  int soilMoisture = analogRead(soilPin);
  Blynk.virtualWrite(V3, soilMoisture);
}