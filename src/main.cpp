#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <Wire.h>

const char *getHomePage(void);

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, 16);

ESP8266WebServer server(80);

WiFiClient client;

bool blank = false;
bool startMDNS = true;

void writeText(const String &message)
{
  u8g2.clearBuffer();
  u8g2.drawStr(0, 21, message.c_str());
  u8g2.sendBuffer();

  blank = message.isEmpty();
}

void setup()
{
  Serial.begin(115200);

  pinMode(GPIO_AS_PIN_SOURCE, INPUT_PULLUP);

  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);

  WiFi.mode(WIFI_STA);

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

void befehl(String cmd)
{
  if (server.hasArg("text"))
  {
    auto text = server.arg("text");

    if (!text.isEmpty())
      cmd = text;
  }

  writeText(cmd);

  server.send(204);
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

  if (startMDNS)
  {
    startMDNS = false;

    MDNS.begin("esp8266");

    server.on("/RR", []
              { befehl("RR"); });

    server.on("/RG", []
              { befehl("RG"); });

    server.on("/RY", []
              { befehl("RY"); });

    server.on("/GR", []
              { befehl("GR"); });

    server.on("/GG", []
              { befehl("GG"); });

    server.on("/GY", []
              { befehl("GY"); });

    server.on("/YR", []
              { befehl("YR"); });

    server.on("/YG", []
              { befehl("YG"); });

    server.on("/YY", []
              { befehl("YY"); });

    server.on("/OFF", []
              { befehl("OFF"); });

    server.onNotFound([]
                      { server.send(200, "text/html", getHomePage()); });

    server.begin();
  }

  if (!blank)
  {
    delay(1000);

    writeText("");
  }

  server.handleClient();

  MDNS.update();
}
