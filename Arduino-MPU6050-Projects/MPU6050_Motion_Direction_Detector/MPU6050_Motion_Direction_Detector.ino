#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int16_t AcX, AcY, AcZ;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Wake up MPU6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  // Read MPU6050 Accelerometer Data
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(0x68, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  String direction = "STILL";

  // Detect Direction
  if (AcX > 6000)
    direction = "FORWARD";
  else if (AcX < -6000)
    direction = "BACKWARD";
  else if (AcY > 6000)
    direction = "RIGHT";
  else if (AcY < -6000)
    direction = "LEFT";

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(18, 0);
  display.println("Motion Direction");

  // Draw Arrow Based on Direction
  if (direction == "FORWARD") {

    display.drawLine(64, 18, 64, 38, WHITE);
    display.drawLine(64, 18, 58, 26, WHITE);
    display.drawLine(64, 18, 70, 26, WHITE);

  }
  else if (direction == "BACKWARD") {

    display.drawLine(64, 18, 64, 38, WHITE);
    display.drawLine(64, 38, 58, 30, WHITE);
    display.drawLine(64, 38, 70, 30, WHITE);

  }
  else if (direction == "LEFT") {

    display.drawLine(48, 28, 80, 28, WHITE);
    display.drawLine(48, 28, 56, 22, WHITE);
    display.drawLine(48, 28, 56, 34, WHITE);

  }
  else if (direction == "RIGHT") {

    display.drawLine(48, 28, 80, 28, WHITE);
    display.drawLine(80, 28, 72, 22, WHITE);
    display.drawLine(80, 28, 72, 34, WHITE);

  }
  else {

    // Center Circle for STILL
    display.drawCircle(64, 28, 8, WHITE);
  }

  // Direction Text
  display.setTextSize(2);

  if (direction == "FORWARD")
    display.setCursor(12, 45);
  else if (direction == "BACKWARD")
    display.setCursor(0, 45);
  else if (direction == "RIGHT")
    display.setCursor(28, 45);
  else if (direction == "LEFT")
    display.setCursor(35, 45);
  else
    display.setCursor(25, 45);

  display.println(direction);

  display.display();

  Serial.print("Direction: ");
  Serial.println(direction);

  delay(100);
}