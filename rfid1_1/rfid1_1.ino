#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D1;
constexpr uint8_t SS_PIN = D2;

byte readCard[4];
String MasterTag = " 53 EA F6 0F";
String tagID = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
}

boolean getUID(){
  if(!mfrc522.PICC_IsNewCardPresent()){
    return false;
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    return false;
  }

  tagID = "";
  for (uint8_t i = 0; i < 4; i++) {
    tagID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA();
  return true;
}

void loop() {
  // put your main code here, to run repeatedly:
  while(getUID())
  {
    if ( tagID == MasterTag ){
      Serial.print("tag ID :");
      Serial.println(tagID);
      Serial.print("Master TAG :");
      Serial.println(MasterTag);
      Serial.println("Connected");
    }
    else{
      Serial.print("tag ID :");
      Serial.println(tagID);
      Serial.print("Master TAG :");
      Serial.println(MasterTag);
      Serial.println("Sorry card do'not Connected");
    }
    delay(2000);
  }
}