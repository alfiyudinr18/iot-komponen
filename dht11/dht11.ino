#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#define DHTPIN D4
#define DHTTYPE DHT11

const char* ssid = "Error";
const char* pass = "error404";
const uint16_t port = 80;
const char* host = "192.168.172.32";

String BASE_URL = "http://" + String(host) + "/nodemcu/public/Dht11/uploaddata";
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.print(F("DHTxx test!"));
  WiFi.begin(ssid, pass);
  dht.begin();
}

void loop() {
  WiFiClient client;
  HTTPClient http;

  if(!client.connect(host, port)){
    Serial.println("Connection to server FAILED !");
    Serial.println(client.connect(host, port));
    delay(1000);
  }

  String url;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  url = BASE_URL + "/" + String(t) + "/" + String(h);
  http.begin(client, url);
  int httpResponse = http.GET();
  Serial.println(t);
  Serial.println(h);
  Serial.println(url);
  delay(1000);
}
