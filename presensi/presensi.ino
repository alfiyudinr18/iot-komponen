#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Ticker.h>

const char* ssid = "Error"; //ssid
const char* pass = "error404"; //password wifi
const uint16_t port = 80;
const char* host = "192.168.42.32"; //ip address
String BASE_URL = "http://" + String(host) + "/presensi_csa/public";

// String BASE_URL = "http://web-csa.wuaze.com";

#define RST D3
#define SDA D4
#define LED D1
#define Button D2
#define Buzer D8

MFRC522 mfrc522(SDA, RST);
Ticker ticker;

// Fungsi untuk reconnect WiFi
void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Menghubungkan ulang ke WiFi...");
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("WiFi terhubung kembali");
  }
}

// Fungsi untuk reset NodeMCU jika terjadi masalah
void resetModule() {
  ESP.restart();
}

void setup() {
  Serial.begin(115200);

  // Inisialisasi WiFi
  WiFi.hostname("NodeMCU");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  reconnectWiFi(); // Pastikan koneksi terhubung

  Serial.println("WiFi terhubung");
  Serial.println("Alamat IP:");
  Serial.println(WiFi.localIP());

  // Inisialisasi EEPROM untuk menyimpan RFID terakhir
  EEPROM.begin(512);

  pinMode(LED, OUTPUT);
  pinMode(Buzer, OUTPUT);
  pinMode(Button, INPUT);
  noTone(Buzer);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Silahkan scan kartu anda...");
  Serial.println();

  // Inisialisasi Watchdog Timer
  ticker.attach(30, resetModule);  // Reset NodeMCU setiap 30 detik
}

void loop() {
  HTTPClient http;
  WiFiClient client;
  String url;

  ticker.detach();  // Nonaktifkan ticker jika semuanya baik-baik saja
  reconnectWiFi();  // Pastikan WiFi terhubung
  ticker.attach(30, resetModule);  // Aktifkan kembali ticker jika perlu
  
  if (digitalRead(Button) == 1) {
    tone(Buzer, 2000);
    digitalWrite(LED, HIGH);
    delay(400);
    noTone(Buzer);
    tone(Buzer, 2000);
    delay(400);
    noTone(Buzer);

    delay(2000);
    digitalWrite(LED, LOW);
    
    url = BASE_URL + "/api/mode";
    http.begin(client, url);

    int httpCode = http.GET();
    String payload = http.getString();
    Serial.println(payload);
    http.end();
  }

  digitalWrite(LED, LOW);

  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String IDTAG = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    IDTAG += String(mfrc522.uid.uidByte[i], HEX);
  }

  // Simpan IDTAG ke EEPROM
  if (IDTAG.length() > 0) {
    for (int i = 0; i < IDTAG.length(); i++) {
      EEPROM.write(i, IDTAG[i]);
    }
    EEPROM.commit();
  }

  // Nyalakan lampu LED dan buzzer
  digitalWrite(LED, HIGH);
  tone(Buzer, 2000);
  delay(400);
  noTone(Buzer);
  digitalWrite(LED, LOW);

  if (!client.connect(host, port)) {
    Serial.println("Connection Failed");
    return;
  }

  url = BASE_URL + "/api/rfid/" + IDTAG;
  http.begin(client, url);

  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println(payload);
  http.end();

  Serial.println(url);
  delay(1000);
}