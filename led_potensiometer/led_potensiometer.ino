// C++ code
int led1 = D1;
int led2 = D2;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  int potentiometerValue = analogRead(A0);
  Serial.print("Nilai : ");
  Serial.println(potentiometerValue);
  delay(1000);

  if (potentiometerValue >= 600) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  } 
  else if (potentiometerValue <= 599) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }

}
