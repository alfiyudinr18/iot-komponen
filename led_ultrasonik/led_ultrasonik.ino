// C++ code
//
const int TRIGPIN = D5;
const int ECHOPIN = D6;
int led1 = D1;
int led2 = D2;
long timer, jarak;//berapa lama menerima sinyal

void setup()
{
  Serial.begin(9600);
  pinMode(TRIGPIN, OUTPUT); //mancar
  pinMode(ECHOPIN, INPUT); //menerima
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop()
{
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  
  timer = pulseIn(ECHOPIN, HIGH);
  jarak = (timer/2)/29;
  delay(1000);
  
  if (jarak >= 1 && jarak <=30) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  } 
  else if (jarak>=31 && jarak<=70) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
  else if (jarak>=71 && jarak<=90) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  else {
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
  
  Serial.print("Jarak = ");
  Serial.print(jarak);
  Serial.print(" cm ");
  Serial.println();
}