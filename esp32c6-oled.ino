#include <Arduino.h>
#include <U8g2lib.h>

#define OLED_SDA 4
#define OLED_SCL 5

// Use Software Bit-Bang I2C (Immune to hardware peripheral hangs)
U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(
  U8G2_R0, 
  /* clock=*/ OLED_SCL, 
  /* data=*/ OLED_SDA, 
  /* reset=*/ U8X8_PIN_NONE
);

void setup() {
  Serial.begin(115200);
  delay(2000); // Give power supply time to stabilize on boot
  Serial.println("Starting Stable Software I2C OLED...");

  pinMode(OLED_SDA, INPUT_PULLUP);
  pinMode(OLED_SCL, INPUT_PULLUP);

  u8g2.begin();
  u8g2.setContrast(255);
  
  Serial.println("Init complete.");
}

void loop() {
  static unsigned long counter = 0;

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 14, "ESP32-C6 STABLE");
  u8g2.drawHLine(0, 18, 128);

  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 36, "Driver: SH1106 SW");

  char buf[20];
  snprintf(buf, sizeof(buf), "Uptime: %lu s", counter++);
  u8g2.drawStr(0, 56, buf);

  u8g2.sendBuffer();

  delay(1000);
}
