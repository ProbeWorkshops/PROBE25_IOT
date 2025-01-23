//Angry

#include <math.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(){
  u8g2.begin();

}

void loop() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(25, 20, "Let's take a");
  u8g2.drawStr(25, 40, "Deep breath..");
  u8g2.sendBuffer();
  delay(2000);
  
  u8g2.clearBuffer(); // Clear entire screen buffer for static elements
  drawAngryElements();
  u8g2.sendBuffer(); // Send static elements to display
  delay(2000); // Pause before the next frame

  u8g2.clearBuffer();
  delay(300);
  drawAfterCheer();
  u8g2.sendBuffer();
  delay(2500);
  
}

void drawAngryElements() {
  drawRectBox();
  drawvEyes(53, 24);
  u8g2.drawCircle(44, 32, 24); // Face

  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(78, 17, "Stay");
  u8g2.drawStr(78, 32, "Calm..:)");

  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(42, 44, "o");

  for (int offset = 0; offset <= 3; offset++) {
    animateBreathe(offset); // Animate breathing
    delay(500); // Small delay for animation effect
  }
}

void drawAfterCheer(){
  drawRectBox();
  drawvEyes(63, 24);
  u8g2.drawCircle(54, 32, 24); // Face
  drawMouth();

  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(85, 17, "You're");
  u8g2.drawStr(85, 27, "doing");
  u8g2.drawStr(85, 37, "GREAT!");

}

void drawRectBox() {
  u8g2.drawLine(1, 1, 128, 1);
  u8g2.drawLine(1, 63, 128, 63);
  u8g2.drawLine(2, 1, 2, 64);
  u8g2.drawLine(127, 1, 127, 64);
}

void drawvEyes(int x, int y) {
  for (int i = 0; i <= 1; i++) {
    if (i == 0) x -= 18;
    else x += 18;
    u8g2.drawPixel(x, y);
    u8g2.drawPixel(x - 1, y + 1);
    u8g2.drawPixel(x + 1, y + 1);
    u8g2.drawPixel(x - 2, y + 1);
    u8g2.drawPixel(x + 2, y + 1);
    u8g2.drawPixel(x - 3, y + 2);
    u8g2.drawPixel(x + 3, y + 2);
  }
}

void drawMouth(){
  u8g2.drawFilledEllipse(54, 40, 12, 8);
  u8g2.setDrawColor(0);
  u8g2.drawFilledEllipse(54, 34, 12, 8);
  u8g2.setDrawColor(1);
}

void animateBreathe(int x) {
  int xPos = 48 + x * 20; // Starting from the mouth and moving right

  // Clear the previous position of "0)"
  if (x > 0 ) {
    u8g2.setDrawColor(0); // Set color to black for clearing
    u8g2.drawBox(48 + (x - 1) * 20, 40, 8,6);
    u8g2.setDrawColor(1); // Reset color to white
    u8g2.sendBuffer();
    delay(300);
  }
  // Draw the new "0)" at the updated position
  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(xPos, 46, "0)");
  u8g2.sendBuffer(); // Send updated frame to display
  delay(300);
}


