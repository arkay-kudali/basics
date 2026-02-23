#include <SD.h>
#include <SPI.h>

File satFile ;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(7)) {
    Serial.println("initialization failed!");
    while (1);
  }

  satFile=SD.open("sat_data.txt", FILE_WRITE);
  satFile.println("hello arkay");
  satFile.close();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
