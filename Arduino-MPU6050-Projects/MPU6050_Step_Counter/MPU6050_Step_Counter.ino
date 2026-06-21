  #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int16_t AcX, AcY, AcZ;

int steps = 0;
bool stepDetected = false;
unsigned long lastStepTime = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Wake MPU6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  // Read MPU6050
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(0x68, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Total acceleration magnitude
  float accMagnitude = sqrt(
    (long)AcX * AcX +
    (long)AcY * AcY +
    (long)AcZ * AcZ
  );

  String status = "Idle";

  // Step detection threshold
  if (accMagnitude > 22000 &&
      !stepDetected &&
      millis() - lastStepTime > 300) {

    steps++;
    stepDetected = true;
    lastStepTime = millis();
  }

  if (accMagnitude < 18000) {
    stepDetected = false;
  }

  if (millis() - lastStepTime < 1000) {
    status = "Walking...";
  }

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(22, 0);
  display.println("Step Counter");

  display.drawRect(0, 14, 128, 30, WHITE);

  display.setTextSize(2);
  display.setCursor(10, 22);
  display.print("Steps:");
  display.print(steps);

  display.setTextSize(1);
  display.setCursor(30, 52);
  display.println(status);

  display.display();

  Serial.print("Steps: ");
  Serial.print(steps);
  Serial.print("  Acceleration: ");
  Serial.println(accMagnitude);

  delay(50);
}