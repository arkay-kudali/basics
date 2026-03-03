#include <Wire.h>

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  while (!Serial);   // wait for serial (if needed)
  
  Serial.println("\n--- I2C Bus Scanner ---");
}

void loop()
{
  uint8_t statusCode;
  uint8_t i2cAddr;
  uint8_t devicesFound = 0;

  Serial.println("Starting bus sweep...");

  for (i2cAddr = 1; i2cAddr < 127; i2cAddr++)
  {
    Wire.beginTransmission(i2cAddr);
    statusCode = Wire.endTransmission();

    if (statusCode == 0)
    {
      Serial.print("[OK] Device detected @ 0x");
      if (i2cAddr < 16) Serial.print("0");
      Serial.println(i2cAddr, HEX);
      devicesFound++;
    }
    else if (statusCode == 4)
    {
      Serial.print("[ERR] Bus error @ 0x");
      if (i2cAddr < 16) Serial.print("0");
      Serial.println(i2cAddr, HEX);
    }
  }

  if (devicesFound == 0)
  {
    Serial.println("Result: No active I2C devices.");
  }
  else
  {
    Serial.print("Result: ");
    Serial.print(devicesFound);
    Serial.println(" device(s) responding.");
  }

  Serial.println("Scan cycle complete.\n");
  delay(4000);
}
