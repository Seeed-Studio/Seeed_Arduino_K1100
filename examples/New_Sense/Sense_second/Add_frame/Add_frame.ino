#include <TFT_eSPI.h>
#include "Free_Fonts.h"
#include "LIS3DHTR.h"

LIS3DHTR<TwoWire> lis;

TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);

#define SCREEN_WIDTH 320 // Wio Terminal Maximum Width
#define SCREEN_HIGH 240  // Wio Terminal Maximum Height
#define PIXEL 4          // Width of one letter
#define LEFT_SIDE 70
#define HIGHT_SIDE 47
const static unsigned int FONT_ROW_HEIGHT = 22; // The height of a letter

void DISPLAY_INIT() // Display initialization, black background rotation
{
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
}

void top(int _CHOOSE)
{
    spr.createSprite(SCREEN_WIDTH, 2 * FONT_ROW_HEIGHT + 1);

    if (_CHOOSE == 1)
        spr.fillRect(4 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, tft.color565(135, 206, 235));
    else
        spr.fillRect(4 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, TFT_WHITE);
    if (_CHOOSE == 2)
        spr.fillRect(30 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, tft.color565(135, 206, 235));
    else
        spr.fillRect(30 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, TFT_WHITE);
    if (_CHOOSE == 3)
        spr.fillRect(56 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, tft.color565(135, 206, 235));
    else
        spr.fillRect(56 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, TFT_WHITE);

    spr.setFreeFont(FSSB9);
    spr.setTextColor(TFT_BLACK);
    spr.drawString("Sense", 32, 11, GFXFF);
    spr.drawString("Process", 127, 11, GFXFF);
    spr.drawString("Network", 231, 11, GFXFF);

    spr.drawLine(0, 2 * FONT_ROW_HEIGHT, SCREEN_WIDTH, 2 * FONT_ROW_HEIGHT, TFT_WHITE);

    spr.pushSprite(0, 0);
    spr.deleteSprite();
}

void Sound_Display(int sound)
{
    spr.createSprite(24 * PIXEL, 3.7 * FONT_ROW_HEIGHT);

    spr.setFreeFont(FSS9);
    spr.setTextColor(TFT_WHITE);
    spr.drawString("Sound", 20, 0, GFXFF);

    spr.setFreeFont(FSS24);
    spr.setTextColor(TFT_WHITE);
    spr.drawNumber(sound, 0, 2 * FONT_ROW_HEIGHT, GFXFF);
    spr.pushSprite(10, 3.8 * FONT_ROW_HEIGHT);
    spr.deleteSprite();
}

void IMU_Display(float x, float y, float z)
{
    spr.createSprite(27 * PIXEL, 7 * FONT_ROW_HEIGHT);

    spr.setFreeFont(FSS9);
    spr.setTextColor(TFT_WHITE);
    spr.fillRect(0, 0, 16 * PIXEL, FONT_ROW_HEIGHT, tft.color565(100, 100, 100));
    spr.drawString("Sensor", 2, 2, GFXFF);

    spr.setFreeFont(FSS9);
    spr.setTextColor(TFT_WHITE);
    spr.drawString("IMU", 20, 12 + FONT_ROW_HEIGHT, GFXFF);

    spr.setFreeFont(FSS12);
    spr.setTextColor(TFT_WHITE);
    spr.drawFloat(x, 2, 16, 2.5 * FONT_ROW_HEIGHT, GFXFF); // Display the value of IMU X-axis
    spr.drawFloat(y, 2, 16, 3.5 * FONT_ROW_HEIGHT, GFXFF); // Display the value of IMU Y-axis
    spr.drawFloat(z, 2, 16, 4.5 * FONT_ROW_HEIGHT, GFXFF); // Display the value of IMU Z-axis
    spr.setFreeFont(FSS9);
    spr.drawString("X,Y,Z", 16, 5.5 * FONT_ROW_HEIGHT, GFXFF);

    spr.fillCircle(17, 6.8 * FONT_ROW_HEIGHT, 3, tft.color565(0, 193, 255));
    spr.fillCircle(34, 6.8 * FONT_ROW_HEIGHT, 3, tft.color565(220, 220, 220));

    spr.pushSprite(10 + 30 * PIXEL, 2.2 * FONT_ROW_HEIGHT);
    spr.deleteSprite();
}

void Add_Display()
{
    spr.createSprite(27 * PIXEL, 5 * FONT_ROW_HEIGHT);
    spr.fillRect(0, 0, 20 * PIXEL, 5 * FONT_ROW_HEIGHT, tft.color565(0, 139, 0));
    spr.setFreeFont(FSSB9);
    spr.setTextColor(TFT_WHITE);
    spr.drawString("Add", 20, 0, GFXFF);

    spr.fillRect(20, 1.5 * FONT_ROW_HEIGHT, 40, 40, TFT_WHITE);
    spr.fillRect(38, 1.5 * FONT_ROW_HEIGHT + 6, 3, 26, TFT_BLACK);
    spr.fillRect(27, 1.5 * FONT_ROW_HEIGHT + 18, 26, 3, TFT_BLACK);

    spr.pushSprite(10 + 55 * PIXEL, 3.8 * FONT_ROW_HEIGHT);
    spr.deleteSprite();
}

void Network_state(int s_key)
{
    spr.createSprite(SCREEN_WIDTH, 25);
    spr.setFreeFont(FSSB9);
    spr.fillSprite(TFT_BLACK);

    switch (s_key)
    {
    case 0:
        spr.setTextColor(TFT_RED);
        spr.drawString("OFF", 90, 0, 2);
        break;
    case 1:
        spr.setTextColor(TFT_GREEN, TFT_BLACK); // Networking status indication：ON
        spr.drawString("LoRa", 60, 0, 2);       // Show the network you are in
        break;
    case 2:
        spr.setTextColor(TFT_GREEN, TFT_BLACK); // Networking status indication：ON
        spr.drawString("WIFI", 60, 0, 2);       // Show the network you are in
        break;
    default:;
    }
    spr.setTextColor(TFT_WHITE);
    spr.drawString("Network:", 5, 0, 2);
    spr.setFreeFont(FSS9);

    spr.pushSprite(0, 215);
    spr.deleteSprite();
}

void Grove_Tip()
{
    spr.createSprite(SCREEN_WIDTH, 25);
    spr.fillSprite(TFT_BLACK);
    spr.setFreeFont(FSS9);
    spr.setTextColor(TFT_YELLOW);
    spr.drawString("Plug in a Grove sensor", 0, 0, 2);
    spr.pushSprite(170, 215);
    spr.deleteSprite();
}

void TFcard_Tip()
{
    spr.createSprite(SCREEN_WIDTH, 25);
    spr.setFreeFont(FSS9);
    spr.drawTriangle(0, 18, 11, 0, 22, 18, TFT_YELLOW);
    spr.setTextColor(TFT_YELLOW);
    spr.drawString("! ", 10, 4, 2);
    spr.drawString("TF card storage is full", 28, 2, 2);
    spr.pushSprite(140, 215);
    spr.deleteSprite();
}

void Below_Right_State_Content(int gg_state) // SD 插拔状态 Grove 插拔状态
{

    spr.createSprite(320, 25);

    spr.setFreeFont(FSSB9);
    spr.fillSprite(TFT_BLACK);
    // int s_key = 1;
    switch (gg_state)
    {
    case 0:
        spr.setFreeFont(FSS9);
        spr.setTextColor(TFT_YELLOW);
        spr.drawString("Plug in a Grove sensor", 0, 0, 2);
        spr.pushSprite(170, 215);
        break;
    case 1:
        spr.setFreeFont(FSS9);
        spr.drawTriangle(0, 18, 11, 0, 22, 18, TFT_YELLOW);
        spr.setTextColor(TFT_YELLOW);
        spr.drawString("! ", 10, 4, 2);
        spr.drawString("TF card storage is full", 28, 0, 2);
        spr.pushSprite(140, 215);
        break;
    case 2:
        spr.setFreeFont(FSS9);
        spr.setTextColor(TFT_GREEN);
        spr.drawString("Vision AI Sensor connected", 22, 0, 2);
        spr.pushSprite(120, 215);
        break;
    case 3:
        spr.setFreeFont(FSS9);
        spr.setTextColor(TFT_GREEN);
        spr.drawString("Saving has been started", 22, 0, 2);
        spr.pushSprite(140, 215);
        break;
    case 4:
        spr.setFreeFont(FSS9);
        spr.setTextColor(TFT_YELLOW);
        spr.drawString("Please insert TF card", 22, 0, 2);
        spr.pushSprite(148, 215);
        break;

    default:;
    }
    spr.setTextColor(TFT_WHITE);
    spr.drawString("Network :", 5, 0, GFXFF);

    spr.deleteSprite();
}

void setup()
{
    DISPLAY_INIT();
    pinMode(WIO_MIC, INPUT);
    lis.begin(Wire1);
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);
}

int gg = 0;

void loop()
{
    Network_state(1);
    top(1);
    Sound_Display(analogRead(WIO_MIC));
    IMU_Display(lis.getAccelerationX(), lis.getAccelerationY(), lis.getAccelerationZ());
    Add_Display();
    // Grove_Tip();
    // TFcard_Tip();
    Below_Right_State_Content(gg % 2 + 1);
    delay(500);
}
