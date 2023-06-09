//Libraries
#include <SD.h>//https://www.arduino.cc/en/reference/SD
#include <Adafruit_GFX.h>//https://github.com/adafruit/Adafruit-GFX-Library
#include <MCUFRIEND_kbv.h>//https://github.com/prenticedavid/MCUFRIEND_kbv
#include <TouchScreen.h> //https://github.com/adafruit/Adafruit_TouchScreen
//Constants
#define SD_CS 10
#define BLACK 0
#define GREY 21845
#define BLUE 31
#define RED 63488
#define GREEN 2016
#define DARKGREEN 1472
#define CYAN 2047
#define MAGENTA 63519
#define YELLOW 65504
#define GOLD 56768
#define WHITE 65535
//Touch screen configuration
#define MINPRESSURE 200
#define MAXPRESSURE 1000
// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
//3.5 Parameters
const int XP = 8, XM = 16, YP = 17, YM = 9; //320x480 ID=0x9486
const int TS_LEFT = 144, TS_RT = 887, TS_TOP = 936, TS_BOT = 87;
//2.8 Parameters
//const int XP = 8, XM = 16, YP = A3, YM = 9; //240x320 ID=0x9341
//const int TS_LEFT = 907, TS_RT = 120, TS_TOP = 74, TS_BOT = 913;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint p;
bool down;
int pixel_x, pixel_y;         //Touch_getXY() updates global vars
//Variables
int currentPage   = 0, oldPage = -1;
//Objects
MCUFRIEND_kbv tft;
// Button calibration
Adafruit_GFX_Button page1_btn, page2_btn;
int margin = 5;
int btnWidth = 100;
int btnHeight = 40;
int btnY = 200;
void setup() {
  //Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  //Init tft screen
  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9486;  //for 3.5" TFT LCD Shield , 0x9341 for 2.8" TFT LCD Shield  
  tft.begin(ID);
  tft.setRotation(1);//0-PORTRAIT 1-PAYSAGE 2-REVERSE PORTRAIT 3-REVERSE PAYSAGE
  //Uncomment if you are using SD
  /*if (!SD.begin(SD_CS)) {
      Serial.println(F("initialization failed!"));
      return;
  }*/
  currentPage = 0; // Indicates that we are at Home Screen
}
void loop() {
  down = Touch_getXY();
  switch (currentPage) {
      case 0:
          if (currentPage != oldPage) {
              Serial.println(F("Page 1"));
              drawPage1();
          }
          page2_btn.press(down && page2_btn.contains(pixel_x, pixel_y));
          //if (page2_btn.justReleased()) page2_btn.drawButton();
          if (page2_btn.justPressed()) {
              currentPage = 1;
          }
          break;
      case 1:
          if (currentPage != oldPage) {
              Serial.println(F("Page 2"));
              drawPage2();
          }
          page1_btn.press(down && page1_btn.contains(pixel_x, pixel_y));
          //if (page1_btn.justReleased()) page1_btn.drawButton();
          if (page1_btn.justPressed()) {
              currentPage = 0;
          }
          break;
  }
}
void drawPage1() { /* function drawHomePage */
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  //Title
  tft.setCursor(0, 10);
  tft.setTextSize(3);
  tft.setTextColor(WHITE, BLACK);
  tft.print("This is page 1"); // Prints the string on the screen
  tft.drawLine(0, 32, 319, 32, DARKGREEN); // Draws the red line
  //text
  tft.setTextSize(3);
  tft.setTextColor(RED, BLACK);
  tft.setCursor(tft.width() / 2. -  14 * 3 * 3, 80);
  tft.print(" Go to page 2 ");
  //Button
  page2_btn.initButton(&tft, tft.width() / 2., 200, 2 * btnWidth, btnHeight, WHITE, GREEN, BLACK, "Page 2", 2);
  page2_btn.drawButton(false);
  oldPage = currentPage;
}
void drawPage2() { /* function drawHomePage */
  tft.setRotation(1);
  tft.fillScreen(GREY);
  //Title
  tft.setCursor(0, 10);
  tft.setTextSize(3);
  tft.setTextColor(WHITE, GREY);
  tft.print("This is page 2"); // Prints the string on the screen
  tft.drawLine(0, 32, 319, 32, DARKGREEN); // Draws the red line
  //text
  tft.setTextSize(3);
  tft.setTextColor(GREEN, BLACK);
  tft.setCursor(tft.width() / 2. - 14 * 3 * 3, 80);
  tft.print(" Go to page 1 ");
  //Button
  page1_btn.initButton(&tft, tft.width() / 2., 200, 2 * btnWidth, btnHeight, WHITE, RED, BLACK, "Page 1", 2);
  page1_btn.drawButton(false);
  oldPage = currentPage;
}
/************************************************************************************
      UTILITY FUNCTION
*************************************************************************************/
bool Touch_getXY(void)
{
  p = ts.getPoint();
  pinMode(YP, OUTPUT);          //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed) {
      if (tft.width() <= tft.height()) { //Portrait
          pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
          pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
      } else {
          pixel_x = map(p.y, TS_TOP, TS_BOT, 0, tft.width());
          pixel_y = map(p.x, TS_RT, TS_LEFT, 0, tft.height());
      }
  }
  return pressed;
}
