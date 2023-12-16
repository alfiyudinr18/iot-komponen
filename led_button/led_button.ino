int redLedPin = D1;
int yellowLedPin = D2; 
int buttonPin = D3;

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Menggunakan resistor pull-up internal
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    digitalWrite(redLedPin, HIGH);
    delay(1000);  // LED merah menyala selama 3 detik

    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    delay(1000);  // LED kuning menyala selama 1 detik

    digitalWrite(yellowLedPin, LOW);
  }
}
