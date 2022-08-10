#include <TFT_eSPI.h>
#include "Free_Fonts.h"

TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);

#define SCREEN_WIDTH 320                        // Wio Terminal Maximum Width
#define SCREEN_HIGH 240                         // Wio Terminal Maximum Height
#define PIXEL 4                                 // Width of one letter
const static unsigned int FONT_ROW_HEIGHT = 22; // The height of a letter

void DISPLAY_INIT() // Display initialization, black background rotation
{
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
}

void BindDev_Display() // Select Frequency band interface
{
    spr.createSprite(SCREEN_WIDTH, SCREEN_HIGH);

    // put your main code here
    spr.setFreeFont(FSSB9);
    spr.setTextColor(TFT_BLACK);

    spr.fillRect(4 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, TFT_WHITE);
    spr.fillRect(30 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, TFT_WHITE);
    spr.fillRect(56 * PIXEL, 0, 21 * PIXEL, FONT_ROW_HEIGHT + 15, tft.color565(135, 206, 235));

    spr.fillRect(156, 54, 40, 4, tft.color565(220, 220, 220));

    spr.drawString("Sense", 32, 11, GFXFF);
    spr.drawString("Process", 127, 11, GFXFF);

    spr.setTextColor(TFT_BLACK);
    spr.drawString("Network", 231, 11, GFXFF);

    spr.drawLine(0, 2 * FONT_ROW_HEIGHT, SCREEN_WIDTH, 2 * FONT_ROW_HEIGHT, TFT_WHITE);
    // spr.drawLine(0, 3.5 * FONT_ROW_HEIGHT, SCREEN_WIDTH, 3.5 * FONT_ROW_HEIGHT, TFT_WHITE);

    spr.setFreeFont(FSS9);

    spr.setTextColor(TFT_WHITE, tft.color565(112, 112, 112));
    spr.drawString("LoRa(SenseCAP)", 92, 48, GFXFF);

    spr.setTextColor(TFT_WHITE);
    spr.drawString("Please download and register an account", 30, 3.4 * FONT_ROW_HEIGHT, 2);
    spr.drawString("on our SenseCAP Mate APP, then scan the", 30, 4.2 * FONT_ROW_HEIGHT, 2);
    spr.drawString("QR code on the back of Grove-Wio E5", 30, 5.0 * FONT_ROW_HEIGHT, 2);
    spr.drawString("(which is included in the kit) to bind", 30, 5.8 * FONT_ROW_HEIGHT, 2);
    spr.drawString("your device to the cloud.", 30, 6.6 * FONT_ROW_HEIGHT, 2);

    spr.fillRect(122, 164, 21 * PIXEL, 33, tft.color565(70, 130, 160));
    spr.setFreeFont(FSS12);
    spr.drawString("OK", 146, 170, GFXFF);

    spr.setFreeFont(FSS9);
    spr.drawString("Network :", 5, 218, GFXFF);

    spr.setTextColor(TFT_RED); // Networking status indication：OFF
    spr.drawString("OFF", 82, 218, GFXFF);

    //    spr.setTextColor(TFT_GREEN, TFT_BLACK);             //Networking status indication：ON
    //    spr.drawString("LoRa(SenseCAP)", 82, 218 , GFXFF);  //Show the network you are in

    spr.pushSprite(0, 0);
    spr.deleteSprite();
}

void setup()
{
    DISPLAY_INIT();
}

void loop()
{
    BindDev_Display();
}
