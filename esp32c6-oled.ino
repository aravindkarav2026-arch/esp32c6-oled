#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ============================================================
// ESP32-C6 N16 + I2C OLED
//
// OLED wiring:
//   VCC -> 3.3V
//   GND -> GND
//   SDA -> GPIO 6
//   SCL -> GPIO 7
//
// OLED:
//   Resolution: 128 x 64
//   I2C address: 0x3C
// ============================================================

#define OLED_SDA 6
#define OLED_SCL 7

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32-C6 N16 OLED Test");
  Serial.println("==============================");
  Serial.println("SDA: GPIO 6");
  Serial.println("SCL: GPIO 7");
  Serial.println("I2C address: 0x3C");

  // Start I2C using the actual pins connected to the OLED.
  Wire.begin(OLED_SDA, OLED_SCL);

  // Initialize SSD1306 OLED.
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED initialization FAILED!");

    while (true) {
      delay(1000);
    }
  }

  Serial.println("OLED initialization OK!");

  // Clear screen.
  display.clearDisplay();

  // Text settings.
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  // Title.
  display.setCursor(0, 0);
  display.println("ESP32-C6 N16");

  display.drawLine(
    0, 10,
    127, 10,
    SSD1306_WHITE
  );

  // OLED information.
  display.setCursor(0, 18);
  display.println("OLED: SSD1306");

  display.setCursor(0, 30);
  display.println("SDA : GPIO 6");

  display.setCursor(0, 42);
  display.println("SCL : GPIO 7");

  display.setCursor(0, 54);
  display.println("I2C : 0x3C");

  // Send buffer to OLED.
  display.display();

  delay(1000);
}

void loop() {
  static unsigned long seconds = 0;

  // Update the bottom line.
  display.fillRect(
    0,
    54,
    128,
    10,
    SSD1306_BLACK
  );

  display.setCursor(0, 54);
  display.print("UPTIME: ");
  display.print(seconds);
  display.print("s");

  display.display();

  seconds++;

  delay(1000);
}
