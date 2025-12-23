#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "animation.h"

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, 16);

bool blank = true;

String animation;
int width;
int shift;
int step = -1;

void whiteOut()
{
    u8g2.clearBuffer();
    u8g2.drawBox(0, 0, 128, 32);
    u8g2.sendBuffer();

    delay(400);
}

void blackOut()
{
    u8g2.clearBuffer();
    u8g2.sendBuffer();

    delay(100);
}

void Animation::startAnimation(const String &message)
{
    animation = message;
    step = 0;
}

void Animation::animate()
{
    if (step >= 0)
        // Each iteration has 13 steps:
        //   0- 9   attention blink
        //     10   init text shift - if necessary
        //     11   shift text
        //     12   show text
        switch ((step++) % 13)
        {
        case 0:
        case 2:
        case 4:
        case 6:
        case 8:
            whiteOut();

            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
            blackOut();

            break;
        case 10:
            width = max(0, u8g2.getUTF8Width(animation.c_str()) - 128);
            shift = 0;

            break;
        case 11:
            u8g2.clearBuffer();
            u8g2.drawUTF8(-shift, 23, animation.c_str());
            u8g2.sendBuffer();

            delay(shift ? 10 : 1000);

            // More to shift - keep step.
            if (++shift < width)
                --step;

            break;
        case 12:
            // Final wait - maybe we can not receive new commands for five seconds but this will not matter.
            delay(5000 - max(1500, 990 + 10 * width));

            blank = false;

            // Go back to idle after three repetitions.
            if (step == 39)
            {
                writeText("");

                step = -1;
            }

            break;
        }
    else if (blank)
        return;
    else
    {
        delay(1000);

        u8g2.clearBuffer();
        u8g2.sendBuffer();

        blank = true;
    }
}

void Animation::writeText(const String &message)
{
    u8g2.clearBuffer();
    u8g2.drawUTF8(0, 23, message.c_str());
    u8g2.sendBuffer();

    blank = false;
}

void Animation::setup()
{
    u8g2.begin();
    u8g2.setFont(u8g2_font_helvB14_tf);
}