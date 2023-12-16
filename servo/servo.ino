// C++ code
//
#include <Servo.h>
Servo myservo; //buat objek servo
int a = D3;
void setup()
{
  myservo.attach(a);
}

void loop()
{
  myservo.write(180);//intrukis servo bergerak ke posisi 180
  delay(3000); // tunggu 3 detik untuk servo bergereak ke posisi yang di tentukan
  myservo.write(0);//intrukis servo bergerak ke posisi 0
  delay(3000); // tunggu 3 detik untuk servo bergereak ke posisi yang di tentukan
}