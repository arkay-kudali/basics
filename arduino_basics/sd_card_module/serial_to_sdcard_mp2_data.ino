#include <SPI.h>
#include <SD.h>

const int chipSelectPin = 4;  // SS pin for SD card module

File dataFile;

void setup() {
  Serial.begin(9600);
  
  // Initialize SD card
  if (!SD.begin(chipSelectPin)) {
    Serial.println("SD initialization failed!");
    return;
  }
  
  Serial.println("SD card initialized.");
  
  // Open file for writing
  dataFile = SD.open("data.txt", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error opening file!");
    return;
  }
  
  Serial.println("Type something and press Enter to save to SD card:");
}

void loop() {
  // Read data from Serial Monitor
  if (Serial.available()) {
    String inputString = Serial.readStringUntil('\n');  // Read a line from Serial Monitor
    
    // Write data to SD card
    dataFile.println(inputString);  // Write the entire line to SD card
    dataFile.flush();  // Flush data to SD card
    
    Serial.println("Data saved to SD card.");
  }
}
