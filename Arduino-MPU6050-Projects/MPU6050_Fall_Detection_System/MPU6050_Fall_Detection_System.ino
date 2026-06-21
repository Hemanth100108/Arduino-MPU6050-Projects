#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BUZZER 8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int16_t AcX, AcY, AcZ;

bool fallDetected = false;
int fallCount = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

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

  // Calculate total acceleration magnitude
  float totalAcc = sqrt(
    (long)AcX * AcX +
    (long)AcY * AcY +
    (long)AcZ * AcZ
  );

  // Fall threshold
  if (!fallDetected && totalAcc > 25000) {
    fallDetected = true;
    fallCount++;
  }

  // Reset when stable
  if (fallDetected && totalAcc < 18000) {
    fallDetected = false;
    digitalWrite(BUZZER, LOW);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(18, 0);
  display.println("Fall Detection");

  display.drawRect(0, 14, 128, 34, WHITE);

  if (fallDetected) {

    digitalWrite(BUZZER, HIGH);

    display.setTextSize(2);
    display.setCursor(8, 22);
    display.println("FALL!");

  } else {

    digitalWrite(BUZZER, LOW);

    display.setTextSize(2);
    display.setCursor(18, 22);
    display.println("SAFE");
  }

  display.setTextSize(1);
  display.setCursor(0, 54);
  display.print("Falls: ");
  display.print(fallCount);

  display.display();

  Serial.print("Acceleration: ");
  Serial.print(totalAcc);
  Serial.print("  Falls: ");
  Serial.println(fallCount);

  delay(100);
}