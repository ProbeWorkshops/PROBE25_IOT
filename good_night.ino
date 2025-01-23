//Sleeping

#include <math.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(){
  // put your setup code here, to run once:
  u8g2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();

  drawSleepElements();

  //zzz animation
  for (int offset = 0; offset <= 7; offset++) {  // Move "ZZZ" upwards
    drawZZZ(offset); // Draw frame
    u8g2.sendBuffer();
    delay(200);      // Pause for animation effect
  }
  delay(200);
  u8g2.sendBuffer();
}

void drawSleepElements(){
  drawRectBox();
  drawEyes(73,26);
  u8g2.drawCircle(64, 32, 24);
  delay(1000);

  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.drawStr(93,32,"Sleeping");
  u8g2.drawStr(100,45,"..:)");
  
  u8g2.drawDisc(20, 16, 5);//Moon
  drawMouth(65,32,15);

}

void drawRectBox(){
  u8g2.drawLine(1,1,128,1);
  u8g2.drawLine(1,63,128,63);
  u8g2.drawLine(2,1,2,64);
  u8g2.drawLine(127,1,127,64);
}

void drawEyes(int x,int y){
  for(int i=0;i<=1;i++){
    if(i==0) x-=18;
    else x+=18;
    u8g2.drawPixel(x,y);
    u8g2.drawPixel(x-1,y-1);
    u8g2.drawPixel(x+1,y-1);
    u8g2.drawPixel(x-2,y-1);
    u8g2.drawPixel(x+2,y-1);
    u8g2.drawPixel(x-3,y-2);
    u8g2.drawPixel(x+3,y-2);
  }
}

void drawZZZ(int offset) {

  u8g2.setDrawColor(0); // Set draw color to black to clear
  u8g2.drawBox(88, 10 - offset, 30, 12);
  u8g2.drawPixel(20,offset*9);
  u8g2.drawPixel(40,(offset-1)*9);
  u8g2.drawPixel(100,(offset-2)*9);

  u8g2.setDrawColor(1); // Set draw color back to white

  // Set a small font for the "ZZZ"
  u8g2.setFont(u8g2_font_5x8_tr); 

  // Draw the "ZZZ" with an upward motion and slant
  u8g2.drawStr(90, 20 - offset, "Z");  // First Z (bottom)
  u8g2.drawStr(98, 15 - offset, "Z");  // Second Z (middle, slanted up)
  u8g2.drawStr(106, 10 - offset, "Z");  // Third Z (top, slanted up)

  //Stars
  u8g2.drawPixel(20,offset*9);
  u8g2.drawPixel(40,(offset-1)*9);
  u8g2.drawPixel(100,(offset-2)*9);
  delay(100);

  u8g2.drawPixel(20,offset*9);
  u8g2.drawPixel(40,(offset-1)*9);
  u8g2.drawPixel(100,(offset-2)*9);

}

void drawMouth(int x, int y, int radius) {
  // Draw a small arc from approximately 45 degrees to 135 degrees
  for (int angle = 40; angle <= 140; angle++) {
    int xPos = x + radius * cos(angle * M_PI / 180);
    int yPos = y + radius * sin(angle * M_PI / 180);
    u8g2.drawPixel(xPos, yPos);
  }
}


