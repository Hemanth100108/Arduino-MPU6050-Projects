#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BUTTON_PIN 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int16_t AcX, AcY, AcZ;

int page = 0;
bool lastButton = HIGH;

int stepCount = 0;
int fallCount = 0;

bool stepDetected = false;
bool fallDetected = false;

unsigned long lastStepTime = 0;

void setup() {

  Serial.begin(9600);
  Wire.begin();

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Wake MPU6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  // Button Page Change
  bool currentButton = digitalRead(BUTTON_PIN);

  if (lastButton == HIGH && currentButton == LOW) {
    page++;
    if (page > 3) page = 0;
    delay(250);
  }

  lastButton = currentButton;

  // Read MPU6050 Accelerometer
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(0x68, 6, true);

  if (Wire.available() >= 6) {
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
  }

  // Tilt Angles
  float pitch = atan2(AcY, AcZ) * 180.0 / PI;
  float roll  = atan2(AcX, AcZ) * 180.0 / PI;

  // Acceleration Magnitude
  float accMag = sqrt(
                   (long)AcX * AcX +
                   (long)AcY * AcY +
                   (long)AcZ * AcZ
                 );

  // Step Counter
  if (accMag > 22000 &&
      !stepDetected &&
      millis() - lastStepTime > 300) {

    stepCount++;
    stepDetected = true;
    lastStepTime = millis();
  }

  if (accMag < 18000)
    stepDetected = false;

  // Fall Counter
  if (!fallDetected && accMag > 30000) {
    fallCount++;
    fallDetected = true;
  }

  if (accMag < 18000)
    fallDetected = false;

  String status = "IDLE";

  if (millis() - lastStepTime < 1000)
    status = "MOVE";

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.drawRect(0, 0, 128, 64, WHITE);

  // PAGE 1
  if (page == 0) {

    display.setCursor(35, 2);
    display.println("ACC DATA");

    display.drawLine(0, 12, 128, 12, WHITE);

    display.setCursor(5, 20);
    display.print("X:");
    display.println(AcX);

    display.setCursor(5, 35);
    display.print("Y:");
    display.println(AcY);

    display.setCursor(5, 50);
    display.print("Z:");
    display.println(AcZ);

    display.setCursor(100, 2);
    display.print("1/4");
  }

  // PAGE 2
  else if (page == 1) {

    display.setCursor(42, 2);
    display.println("MOTION");

    display.drawLine(0, 12, 128, 12, WHITE);

    display.setCursor(5, 25);
    display.print("ACC:");

    display.setCursor(45, 25);
    display.print((int)accMag);

    display.setCursor(5, 45);

    if (accMag > 18000)
      display.println("ACTIVE");
    else
      display.println("STABLE");

    display.setCursor(100, 2);
    display.print("2/4");
  }

  // PAGE 3
  else if (page == 2) {

    display.setCursor(45, 2);
    display.println("TILT");

    display.drawLine(0, 12, 128, 12, WHITE);

    display.setCursor(5, 25);
    display.print("Pitch:");
    display.print((int)pitch);

    display.setCursor(5, 45);
    display.print("Roll :");
    display.print((int)roll);

    display.setCursor(100, 2);
    display.print("3/4");
  }

  // PAGE 4
  else {

    display.setCursor(30, 2);
    display.println("ACTIVITY");

    display.drawLine(0, 12, 128, 12, WHITE);

    display.setCursor(5, 22);
    display.print("Steps:");
    display.println(stepCount);

    display.setCursor(5, 38);
    display.print("Falls:");
    display.println(fallCount);

    display.setCursor(5, 54);
    display.print(status);

    display.setCursor(100, 2);
    display.print("4/4");
  }

  display.display();

  delay(50);
}