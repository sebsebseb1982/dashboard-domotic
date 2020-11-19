
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ESP8266HTTPClient.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>
#include <TimeLib.h>

#include "secret.h"
#include "quote-of-the-day.h"
#include "weather-forecast.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting");
  display.clearDisplay();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void setupDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
}

void setup() {
  Serial.begin(9600);
  setupDisplay();
  setupWifi();
}

void loop() {
  QuoteOfTheDay quoteOfTheDay = getQuoteOfTheDay();
  display.println(quoteOfTheDay.quote);
  display.println(quoteOfTheDay.author);
    /*TwoDaysWeatherForecasts twoDaysWeatherForecasts = getWeatherForecasts();
    displayWeatherForecast(twoDaysWeatherForecasts.today);
    displayWeatherForecast(twoDaysWeatherForecasts.tomorrow);*/

  display.display();
  ESP.deepSleep(5 * 1000);
}
