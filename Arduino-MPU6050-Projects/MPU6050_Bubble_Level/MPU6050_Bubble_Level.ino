#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

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

  // Read MPU6050 accelerometer data
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(0x68, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Calculate tilt angles
  float angleX = atan2(AcY, AcZ) * 180.0 / PI;
  float angleY = atan2(AcX, AcZ) * 180.0 / PI;

  // Determine orientation
  String status = "LEVEL";

  if (angleX > 10)
    status = "RIGHT TILT";
  else if (angleX < -10)
    status = "LEFT TILT";
  else if (angleY > 10)
    status = "FORWARD";
  else if (angleY < -10)
    status = "BACKWARD";

  // Bubble box dimensions
  const int boxX = 14;
  const int boxY = 36;
  const int boxW = 100;
  const int boxH = 24;
  const int bubbleRadius = 4;

  // Bubble movement constrained inside box
  int bubbleX = map(constrain(angleX, -30, 30),
                    -30, 30,
                    boxX + bubbleRadius,
                    boxX + boxW - bubbleRadius);

  int bubbleY = map(constrain(angleY, -30, 30),
                    -30, 30,
                    boxY + boxH - bubbleRadius,
                    boxY + bubbleRadius);

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.println("Digital Spirit Level");

  display.setCursor(0, 12);
  display.print("X:");
  display.print((int)angleX);
  display.print((char)247);

  display.setCursor(64, 12);
  display.print("Y:");
  display.print((int)angleY);
  display.print((char)247);

  display.setCursor(0, 24);
  display.println(status);

  // Draw bubble chamber
  display.drawRect(boxX, boxY, boxW, boxH, WHITE);

  // Center vertical line
  display.drawLine(boxX + boxW / 2,
                   boxY,
                   boxX + boxW / 2,
                   boxY + boxH,
                   WHITE);

  // Center horizontal line
  display.drawLine(boxX,
                   boxY + boxH / 2,
                   boxX + boxW,
                   boxY + boxH / 2,
                   WHITE);

  // Center target circle
  display.drawCircle(boxX + boxW / 2,
                     boxY + boxH / 2,
                     6,
                     WHITE);

  // Bubble
  display.fillCircle(bubbleX,
                     bubbleY,
                     bubbleRadius,
                     WHITE);

  display.display();

  // Serial Monitor Output
  Serial.print("X Angle: ");
  Serial.print(angleX);
  Serial.print("   Y Angle: ");
  Serial.print(angleY);
  Serial.print("   Status: ");
  Serial.println(status);

  delay(100);
}