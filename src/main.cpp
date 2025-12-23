#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "animation.h"

const char *getHomePage(void);

ESP8266WebServer server(80);

WiFiClient client;

bool startMDNS = true;

void setup()
{
  Serial.begin(115200);

  pinMode(GPIO_AS_PIN_SOURCE, INPUT_PULLUP);

  Animation::setup();

  WiFi.mode(WIFI_STA);

  auto ssid = WiFi.SSID();
  auto pass = WiFi.psk();

  if (ssid.length() > 0 && pass.length() > 0)
    WiFi.begin(ssid, pass);
}

void connect()
{
  Animation::writeText("WPS");

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

  Animation::startAnimation(cmd);

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
    Animation::writeText(WiFi.SSID().isEmpty() ? "kein WiFi" : "...");

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

  server.handleClient();

  MDNS.update();

  Animation::animate();
}
