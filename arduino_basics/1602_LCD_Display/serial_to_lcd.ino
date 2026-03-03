#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change address if needed (0x27 or 0x3F are common)
LiquidCrystal_I2C lcd(0x27, 16, 2);

String inputText = "";

void setup() {
  Serial.begin(9600);
  
  lcd.init();      
  lcd.backlight(); 
  
  lcd.setCursor(0, 0);
  lcd.print("Send Text:");
}

void loop() {
  
  while (Serial.available()) {
    char c = Serial.read();
    
    if (c == '\n') {   // When Enter is pressed
      
      lcd.clear();
      lcd.setCursor(0, 0);
      
      // Print first 16 characters on line 1
      lcd.print(inputText.substring(0, 16));
      
      // If text >16 chars, print remaining on line 2
      if (inputText.length() > 16) {
        lcd.setCursor(0, 1);
        lcd.print(inputText.substring(16, 32));
      }
      
      inputText = "";  // Clear buffer
    }
    else {
      inputText += c;
    }
  }
}
