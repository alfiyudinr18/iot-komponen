#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("    Coba LCD   ");
  lcd.setCursor(0,1);
  lcd.print("Belajar LCD");
  delay(500);
}