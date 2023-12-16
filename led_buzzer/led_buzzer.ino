const int ledPin1 = D1;
const int buzzer = D2;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin1, HIGH);
  delay(1000);

  digitalWrite(ledPin1, LOW);
  delay(2000);

  tone(buzzer, 100, 1000);
  delay(1000);
  tone(buzzer, 250, 1000);
  delay(1000);
}
