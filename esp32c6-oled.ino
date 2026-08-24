#include <Arduino.h>
#include <U8g2lib.h>

#define OLED_SDA 6
#define OLED_SCL 7

// SW_I2C (Software Bit-Bang) drives GPIO pins directly without relying on hardware registers
U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(
  U8G2_R0, 
  /* clock=*/ OLED_SCL, 
  /* data=*/ OLED_SDA, 
  /* reset=*/ U8X8_PIN_NONE
);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting Software I2C SH1106 Test...");

  u8g2.begin();
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 15, "ESP32-C6 READY!");
  u8g2.drawStr(0, 35, "1.3 SH1106 OLED");
  u8g2.drawStr(0, 55, "Software I2C OK");
  u8g2.sendBuffer();

  Serial.println("Display buffer sent.");
}

void loop() {
  static unsigned long count = 0;
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 15, "ESP32-C6 READY!");
  
  char buf[20];
  snprintf(buf, sizeof(buf), "Uptime: %lu s", count++);
  u8g2.drawStr(0, 40, buf);
  
  u8g2.sendBuffer();
  delay(1000);
}
