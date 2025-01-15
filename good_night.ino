void setup() {
  Serial.begin(9600);
  u8g2.begin();
}

void loop() {
  frameCount++;
  zzzOffset = (frameCount / 2) % 4;  // Slower ZZZ movement
  
  u8g2.clearBuffer();
  drawSleepingFace();
  drawAdvancedFeatures();
  u8g2.clear();
  delay(500);
  goodMorning();
  u8g2.sendBuffer();
  
  delay(100);
}

void drawSleepingFace() {
  // Face outline with smooth circle
  u8g2.drawCircle(64, 32, 20);
  u8g2.drawCircle(64, 32, 21);

  /*u8g2.drawRBox(54, 25, 6, 2, 1);  // Left eye
  u8g2.drawRBox(68, 25, 6, 2, 1);  // Right eye*/

  // Sleepy eyes - now with rounded ends
  u8g2.drawDisc(55, 25, 3);
  u8g2.drawDisc(73, 25, 3);

  u8g2.drawCircle(64, 34, 2);  // Main nose circle
  
  // Calm mouth with slight curve
  u8g2.drawLine(58, 42, 70, 42);
  
  // ZZZ with fancy font
  u8g2.setFont(u8g2_font_profont12_tf);
  u8g2.drawStr(90 - zzzOffset, 10 + zzzOffset, "z");
  u8g2.drawStr(98 - zzzOffset, 8 + zzzOffset, "Z");
  u8g2.drawStr(106 - zzzOffset, 6 + zzzOffset, "Z");
}

void drawAdvancedFeatures() {
  u8g2.drawRFrame(0, 0, 128, 64, 3);  // Rounded rectangle frame
  
  for(int i = 0; i < 5; i++) {
    int y = 5 + ((frameCount * (i+1)) % 108);
    int x = 110 + (sin(frameCount * 0.1 + i) * 3);
    u8g2.drawDisc(x, y, 1);
  }

  for(int i = 0; i < 5; i++) {
    int y = 5 + ((frameCount * (i+1)) % 108);
    int x = 19 + (sin(frameCount * 0.1 + i) * 3);
    u8g2.drawDisc(x, y, 1);
  }
  
  int pulseSize = 22 + (sin(frameCount * 0.1) * 2);
  u8g2.drawCircle(64, 32, pulseSize);
  
  u8g2.setFont(u8g2_font_micro_tr);
  u8g2.drawStr(2, 10, "Sleeping...");
  
}

void goodMorning(){
  drawSleepingFace();
  u8g2.drawCircle(100, 40, 10); // Sun at position (100, 40) with radius 10
  u8g2.drawLine(100, 30, 100, 50); // Sun rays vertical
  u8g2.drawLine(90, 40, 110, 40); // Sun rays horizontal
    u8g2.setFont(u8g2_font_ncenB08_tr);  // Select a suitable font
  u8g2.drawStr(80, 25, "Good");
  u8g2.drawStr(80, 35, "Morning");
}

}