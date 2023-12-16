#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

String teks = "Tak perlu dikejar ";
int indeks = 0;

void setup()
{
  lcd.init(); // inisialisasi lcd
  lcd.backlight(); // Menyalakan lampu belakang
  lcd.clear();
  lcd.print("QOTD : "); 
  // Bentuk string yang panjang
  teks = teks +
        "Jika sudah tak sejajar ";
}

 

void loop()

{

  char st[17];  // String dengan maksimal 16 karakter
  st[16] = 0;   // Akhir string

  // Bentuk string

  for (int j = 0; j < 16; j++)
    if (indeks + j < teks.length())
      st[j] = teks[indeks + j];
    else 
      st[j] = 32; // Spasi
  // Tampilkan di baris kedua
  lcd.setCursor(0, 1);
  lcd.print(st);
  // Peroleh indeks berikutnya
  indeks++;
  if (indeks == teks.length() -  1)
    indeks = 0;
  delay(600); 
}