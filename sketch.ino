#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ESP32-C6 Default I2C Pins
#define OLED_SDA 6
#define OLED_SCL 7
#define OLED_RESET -1 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define I2C_ADDRESS 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  delay(2000); 

  Serial.println("Starting ESP32-C6 OLED Diagnostics...");

  // Initialize I2C Bus on GPIO 6 (SDA) and GPIO 7 (SCL)
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS)) {
    Serial.println("OLED allocation failed! Check wiring on GPIO 6 and 7.");
    for (;;); 
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.println("ESP32-C6 + 1.3 OLED");
  display.drawFastHLine(0, 12, 128, SSD1306_WHITE);
  
  display.setCursor(0, 20);
  display.println("SDA: GPIO 6");
  display.setCursor(0, 32);
  display.println("SCL: GPIO 7");
  
  display.display();
}

void loop() {
  static unsigned long counter = 0;

  display.fillRect(0, 48, 128, 16, SSD1306_BLACK);
  display.setCursor(0, 50);
  display.printf("Uptime: %lu s", counter++);
  display.display();
  
  delay(1000);
}
