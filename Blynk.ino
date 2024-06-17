#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#define DATA_PIN 7   
#define CLOCK_PIN 5   
#define LATCH_PIN 6 
#define BLYNK_GREEN     "#23C48E"
#define BLYNK_RED       "#D3435C"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "";
char pass[] = "";

void sendData(byte data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA_PIN, (data >> i) & 0x01);
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

void clearRegisters() {
  sendData(0b00000000);
  sendData(0b00000000);
  sendData(0b00000000);
  sendData(0b00000000);
  sendData(0b00000000);
  sendData(0b00000000);
  sendData(0b00000000);
  sendData(0b00000000);
}

void setup()
{
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  Serial.begin(9600);
  clearRegisters(); 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V1) 
{
  int pinValue = param.asInt(); 

  if (pinValue == 1) {
    sendData(0b10000000); 
    Blynk.setProperty(V1, "color", BLYNK_GREEN);
  } else {
    sendData(0b00000000); 
    Blynk.setProperty(V1, "color", BLYNK_RED); 
  }
}

