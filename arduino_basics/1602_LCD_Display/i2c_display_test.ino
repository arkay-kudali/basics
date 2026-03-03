#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn on backlight
  
  lcd.setCursor(0, 0); // Column 0, Row 0
  lcd.print("Hello World");
  
  lcd.setCursor(0, 1); // Column 0, Row 1
  lcd.print("I2C LCD Test");
}

void loop() {
  // Nothing needed here
}
