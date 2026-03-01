
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c // I2C address for the OLED
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin, -1 if sharing Arduino reset pin

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int maxCharsPerRow = SCREEN_WIDTH / 6;  // 128 / 6 = 21 characters per row
const int maxRows = SCREEN_HEIGHT / 8;        // 64 / 8 = 8 rows (each row is 8 pixels high)

int currentRow = 0;
int charsInRow = 0;

void setup() {
  Serial.begin(9600);
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.display();
}

void loop() {
  if (Serial.available()) {
    String text = Serial.readString();  // Read the incoming string

    // Split the text into words using a space as the delimiter
    String word = "";
    int textLength = text.length();

    for (int i = 0; i < textLength; i++) {
      char currentChar = text[i];

      // Add characters to the word until we reach a space or the end of the text
      if (currentChar != ' ' && i != textLength - 1) {
        word += currentChar;
      } else {
        // If the last character is reached, append it to the word
        if (i == textLength - 1 && currentChar != ' ') {
          word += currentChar;
        }

        // Check if the word fits in the current row
        if (charsInRow + word.length() > maxCharsPerRow) {
          // Move to the next row if the word exceeds the row limit
          currentRow++;
          charsInRow = 0;
        }

        // If the screen is full, clear the display
        if (currentRow >= maxRows) {
          display.clearDisplay();
          currentRow = 0;
          charsInRow = 0;  // Reset to the top of the screen
        }

        // Set the cursor to the current row and column, then print the word
        display.setCursor(charsInRow * 6, currentRow * 8);  // Set cursor based on row and column
        display.print(word);

        // Move the cursor for the next word
        charsInRow += word.length();

        // Add a space after the word (unless it's the end of the string)
        if (currentChar == ' ') {
          display.print(' ');
          charsInRow++;
        }

        display.display();  // Update the display

        // Clear the word for the next iteration
        word = "";
      }
    }
  }
}



