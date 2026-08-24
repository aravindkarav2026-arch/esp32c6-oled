#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define OLED_SDA 6
#define OLED_SCL 7

// Initialize U8g2 for SH1106 128x64 I2C display (Non-rotated, Full Framebuffer)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting SH1106 OLED Test...");

  // Set ESP32-C6 custom I2C pins
  Wire.begin(OLED_SDA, OLED_SCL);

  // Pass Wire instance to U8g2
  u8g2.begin();
}

void loop() {
  static unsigned long counter = 0;

  u8g2.clearBuffer();          // Clear internal memory buffer

  // Header Text
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(0, 12, "ESP32-C6 + 1.3 OLED");
  u8g2.drawHLine(0, 16, 128);

  // Controller Details
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 32, "Driver: SH1106");
  u8g2.drawStr(0, 44, "Pins: SDA 6 / SCL 7");

  // Dynamic Counter
  char buf[20];
  snprintf(buf, sizeof(buf), "Uptime: %lu s", counter++);
  u8g2.drawStr(0, 60, buf);

  u8g2.sendBuffer();          // Transfer frame buffer to SH1106 screen

  delay(1000);
}
