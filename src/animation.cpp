#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "animation.h"

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, 16);

bool blank = true;

void Animation::writeText(const String &message)
{
    if (message.isEmpty())
    {
        if (blank)
            return;

        delay(1000);
    }

    u8g2.clearBuffer();
    u8g2.drawUTF8(0, 21, message.c_str());
    u8g2.sendBuffer();

    blank = message.isEmpty();
}

void Animation::setup()
{
    u8g2.begin();
    u8g2.setFont(u8g2_font_helvB10_tf);
}