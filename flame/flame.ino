int buzzer = D2;
int afire = A0;
int dfire = D0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  pinMode(dfire, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int firesensorAnalog = analogRead(afire);
  int firesensorDigital = digitalRead(dfire);

  Serial.print("Fire Sensor: ");
  Serial.print(firesensorAnalog);
  Serial.print("\t");
  Serial.print("Fire Class: ");
  Serial.print(firesensorDigital);
  Serial.print("\t");
  Serial.print("\t");
  
  if (firesensorAnalog < 1000) {
    Serial.println("Fire");
    digitalWrite (buzzer, HIGH) ; //send tone
    delay(1000);
    digitalWrite (buzzer, LOW) ;  //no tone
  }
  else {
    Serial.println("Tidak ada api");
  }
  delay(200);
}
