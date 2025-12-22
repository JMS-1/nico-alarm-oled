#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, 16);

WiFiClient client;

bool blank = false;

void writeText(const String &message)
{
  u8g2.clearBuffer();
  u8g2.drawStr(0, 26, message.c_str());
  u8g2.sendBuffer();

  blank = message.isEmpty();
}

void setup()
{
  pinMode(GPIO_AS_PIN_SOURCE, INPUT_PULLUP);

  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB18_tr);
  u8g2.enableUTF8Print();

  auto ssid = WiFi.SSID();
  auto pass = WiFi.psk();

  if (ssid.length() > 0 && pass.length() > 0)
    WiFi.begin(ssid, pass);
}

void connect()
{
  writeText("WPS");

  WiFi.disconnect();
  WiFi.beginWPSConfig();
}

void loop()
{
  if (digitalRead(GPIO_AS_PIN_SOURCE) == LOW)
  {
    connect();

    delay(300);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    writeText(WiFi.SSID().isEmpty() ? "kein WiFi" : "...");

    return;
  }

  if (!blank)
    writeText("");
}
