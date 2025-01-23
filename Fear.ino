//Fear

#include <math.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
}

void loop() {
  static int frameCount = 1;
  if (frameCount == 1) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawStr(15, 20, "Don't");
    u8g2.drawStr(15, 30, "Worry..");

    u8g2.drawStr(70, 30, "I'm here");
    u8g2.drawStr(70, 40, "with you");
    u8g2.sendBuffer();
    delay(2000);
  }
  u8g2.clearBuffer();  // Clear entire screen buffer for static elements

  drawFearElements();
  animateFall(frameCount);
  animateEyes(frameCount);
  animateMouth(frameCount);
  u8g2.sendBuffer();  // Send static elements to display
  delay(300);
  frameCount++;
  if (frameCount == 17) {
    u8g2.clearBuffer();
    frameCount = 1;
    drawCheer();
    u8g2.sendBuffer();
    delay(3000);
  }
}

void drawFearElements() {
  drawRectBox();
  u8g2.drawCircle(64, 32, 24);  //Face
  u8g2.drawDisc(54, 24, 2);
  u8g2.drawDisc(74, 24, 2);  //Eye pupils
}

void animateFall(int frameCount) {
  u8g2.drawLine(12, 1, 12, frameCount * 4);
  u8g2.drawLine(16, 1, 16, frameCount * 4);
  u8g2.drawLine(118, 1, 118, frameCount * 4);
  u8g2.drawLine(114, 1, 114, frameCount * 4);

  if (frameCount == 16) {
    u8g2.setDrawColor(0);
    u8g2.drawLine(12, 1, 12, 63);
    u8g2.drawLine(16, 1, 16, 63);

    u8g2.drawLine(118, 1, 118, 63);
    u8g2.drawLine(114, 1, 114, 63);

    u8g2.sendBuffer();
  }
}

void animateEyes(int frameCount) {
  if (frameCount % 2 != 0) {
    /*u8g2.setDrawColor(0);
    u8g2.drawFilledEllipse(54, 24, 4, 3);
    u8g2.drawFilledEllipse(74, 24, 4, 3);
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();*/

    u8g2.drawDisc(54, 24, 3);
    u8g2.drawDisc(74, 24, 3);  //Eye pupils
    u8g2.sendBuffer();

  } else {
    /*u8g2.setDrawColor(0);
    u8g2.drawDisc(54, 24, 3);
    u8g2.drawDisc(74, 24, 3);  //Eye pupils
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();*/

    u8g2.drawFilledEllipse(54, 24, 4, 3);
    u8g2.drawFilledEllipse(74, 24, 4, 3);
    u8g2.sendBuffer();
  }
}


void animateMouth(int frameCount) {
  if (frameCount % 4 == 1) {
    u8g2.drawEllipse(64, 44, 5, 7);
    delay(50);
  } else if (frameCount % 4 == 2) {
    u8g2.drawEllipse(64, 44, 6, 9);
    delay(50);
  } else if (frameCount % 4 == 3) {
    u8g2.drawEllipse(62, 44, 6, 9);
    delay(50);
  } else {
    u8g2.drawEllipse(66, 44, 6, 9);
    delay(50);
  }
}

void drawCheer() {

  drawRectBox();
  drawEyes(44, 26);
  u8g2.drawCircle(35, 32, 24);  // Face
  for (int j = 0; j <= 5; j++) {
    drawMouth(36, 32, 15, 40 + 5 * j);
    u8g2.sendBuffer();
    delay(300);
  }
  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(65, 20, "Be Calm..");
  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.drawStr(65, 30, "Focus on ");
  u8g2.drawStr(65, 38, "what you can");
  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(65, 48, "CONTROL");
}

void drawRectBox() {
  u8g2.drawLine(1, 1, 128, 1);
  u8g2.drawLine(1, 63, 128, 63);
  u8g2.drawLine(2, 1, 2, 64);
  u8g2.drawLine(127, 1, 127, 64);
}

void drawEyes(int x, int y) {
  for (int i = 0; i <= 1; i++) {
    if (i == 0) x -= 18;
    else x += 18;
    u8g2.drawPixel(x, y);
    u8g2.drawPixel(x - 1, y - 1);
    u8g2.drawPixel(x + 1, y - 1);
    u8g2.drawPixel(x - 2, y - 1);
    u8g2.drawPixel(x + 2, y - 1);
    u8g2.drawPixel(x - 3, y - 2);
    u8g2.drawPixel(x + 3, y - 2);
  }
}

void drawMouth(int x, int y, int radius, int degree) {
  // Draw a small arc from approximately 45 degrees to 135 degrees
  for (int angle = 90 - degree; angle <= 90 + degree; angle++) {
    int xPos = x + radius * cos(angle * M_PI / 180);
    int yPos = y + radius * sin(angle * M_PI / 180);
    u8g2.drawPixel(xPos, yPos);
  }
}
