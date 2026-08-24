#include <Wire.h>

#define OLED_SDA 4
#define OLED_SCL 5

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n--- ESP32-C6 Diagnostic I2C Scanner ---");

  // Force I2C initialization on GPIO 4 and GPIO 5
  Wire.begin(OLED_SDA, OLED_SCL);
  Wire.setClock(100000); // Set slow 100 kHz speed for maximum noise tolerance

  byte count = 0;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.printf("SUCCESS! Found I2C device at address 0x%02X\n", address);
      count++;
    }
  }

  if (count == 0) {
    Serial.println("NO DEVICES FOUND! Verify GND/VCC and try swapping SDA and SCL.");
  } else {
    Serial.printf("Done. Total devices detected: %d\n", count);
  }
}

void loop() {}
