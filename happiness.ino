#include <U8g2lib.h>
#include <Wire.h>

// Initialize U8G2 for SSD1306 OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int zzzOffset = 0;
int frameCount = 0;
int eyeY = 28;        // Initial Y position of the eyes
int direction = 1;    // Direction of movement: 1 = down, -1 = up
int starY[5];          // Array to store the Y position of the stars
int starX[5];          // Array to store the X position of the stars

int mouthRadius = 8;  // Initial radius for the mouth
int zoomDirection = 1; // Direction of zoom: 1 = zoom in, -1 = zoom out
int maxMouthRadius = 12; // Maximum radius for the mouth
int minMouthRadius = 6;  // Minimum radius for the mouth


void setup() {
  // Initialize the U8g2 library
  u8g2.begin();
    for (int i = 0; i < 5; i++) {
    starX[i] = random(0, 128); // Random X position for each star
    starY[i] = random(-64, 0); // Random Y position above the screen
  }

}

void loop() {
  u8g2.clearBuffer();                  // Clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);  // Choose a suitable font
u8g2.drawCircle(64, 32, 25);
    // Draw the left eye (arc approximation using lines)
  u8g2.drawLine(53, eyeY, 56, eyeY - 2); // Left part of the arc
  u8g2.drawLine(56, eyeY - 2, 59, eyeY); // Right part of the arc

  // Draw the right eye (arc approximation using lines)
  u8g2.drawLine(69, eyeY, 72, eyeY - 2); // Left part of the arc
  u8g2.drawLine(72, eyeY - 2, 75, eyeY); // Right part of the arc // Draw a semi-circle mouth (flat side up)
  

 // Draw the text "Let's Celebrate :)...."
  u8g2.setFont(u8g2_font_ncenB08_tr);         // Set the font
  u8g2.drawStr(28, 10, "Let's Celebrate :)...");    // Draw the text at (28, 10)

  // Draw the rectangle frame at the borders
  u8g2.drawFrame(0, 0, 128, 64);             // Draw a frame around the screen
    // Draw falling stars
  for (int i = 0; i < 5; i++) {
    u8g2.drawPixel(starX[i], starY[i]);      // Draw each star
    starY[i]++;                              // Move the star down
    if (starY[i] > 64) {                     // If the star moves off the screen, reset its position
      starY[i] = random(-10, 0);             // Reset to a random position above the screen
      starX[i] = random(0, 128);             // Random X position
    }
  }
// Shade the upper portion of the mouth (leave the bottom part visible)
  u8g2.drawBox(64 - mouthRadius, 44 - mouthRadius, 2 * mouthRadius, mouthRadius); // Shading the top portion



u8g2.sendBuffer();
  // Update the Y position of the eyes
  eyeY += direction;

  // Reverse direction if the eyes reach the upper or lower limit
  if (eyeY >= 30 || eyeY <= 26) {
    direction = -direction;
  }
      // Adjust the mouth radius for zoom effect
  mouthRadius += zoomDirection;

  // Reverse zoom direction when reaching max/min size
  if (mouthRadius >= maxMouthRadius || mouthRadius <= minMouthRadius) {
    zoomDirection = -zoomDirection;
  }

    delay(100);

  }