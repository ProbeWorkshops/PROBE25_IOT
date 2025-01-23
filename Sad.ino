//Sad

#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
}

void loop() {
  
  u8g2.clearBuffer();  // Clear entire screen buffer for static elements

  static int frameCount = 1;

  drawSadElements();
  animateTear(frameCount);
  animateMouth(frameCount);

  u8g2.sendBuffer();  // Send static elements to display
  delay(500);

  frameCount++;
  if (frameCount == 17) {
    u8g2.clearBuffer();
    frameCount = 1;
    drawJoke();
    u8g2.sendBuffer();
    delay(3000);
  }
}

void drawSadElements() {
  drawRectBox();
  u8g2.drawCircle(64, 32, 24);  //Face
  u8g2.drawDisc(54, 24, 4 );
  u8g2.drawDisc(74, 24, 4);  //Eye pupils
}

void animateTear(int frameCount){
  u8g2.setDrawColor(0);
  u8g2.drawLine(54,24+((frameCount-1)*3),54,24+(frameCount*3));
  u8g2.drawLine(74,24+((frameCount-1)*3),54,24+(frameCount*3));
  u8g2.setDrawColor(1);
  u8g2.sendBuffer();

  u8g2.drawLine(54,24+(frameCount*3),54,24+((frameCount+1)*3));
  u8g2.drawLine(74,24+(frameCount*3),54,24+((frameCount+1)*3));
  u8g2.sendBuffer();
  delay(100);

  if(frameCount == 16){
    
    u8g2.setDrawColor(0);
    u8g2.drawLine(54,24,54,64);
    u8g2.drawLine(74,24,54,64);
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();
    delay(100);

  }
}


void animateMouth(int frameCount) {
  if (frameCount % 4 == 1) {
    u8g2.drawEllipse(64, 44, 10,8);
    u8g2.setDrawColor(0);
    u8g2.drawEllipse(64, 46, 10,8);
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();
    delay(150);
  } else if (frameCount % 4 == 2) {
    u8g2.drawEllipse(64, 42, 10,8);
    u8g2.setDrawColor(0);
    u8g2.drawEllipse(64, 44, 10,8);
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();
    delay(150);
  } else if (frameCount % 4 == 3) {
    u8g2.drawEllipse(64, 40, 10,8);
    u8g2.setDrawColor(0);
    u8g2.drawEllipse(64, 42, 10,8);
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();
    delay(150);
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
