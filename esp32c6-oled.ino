#include <Wire.h>

#define OLED_SDA 4
#define OLED_SCL 5

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n--- ESP32-C6 Forced Pull-Up I2C Scanner ---");

  // Force GPIO mode with explicit internal pull-ups enabled
  pinMode(OLED_SDA, INPUT_PULLUP);
  pinMode(OLED_SCL, INPUT_PULLUP);
  delay(10);

  Wire.begin(OLED_SDA, OLED_SCL);
  Wire.setClock(100000);

  byte count = 0;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.printf("SUCCESS! Device found at address: 0x%02X\n", address);
      count++;
    }
  }

  if (count == 0) {
    Serial.println("STILL NO DEVICE FOUND.");
  } else {
    Serial.printf("Scan complete. Devices found: %d\n", count);
  }
}

void loop() {}
