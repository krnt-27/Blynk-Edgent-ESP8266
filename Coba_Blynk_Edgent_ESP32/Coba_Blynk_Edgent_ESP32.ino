/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL6oBJWI8Wl"
#define BLYNK_TEMPLATE_NAME "Prototype Pemantau Suhu Ruangan"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG
#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temp, humi;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  delay(100);

  dht.begin();
  lcd.begin();
  lcd.backlight();

  BlynkEdgent.begin();
  timer.setInterval(2000L, myTimer);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}

void myTimer() {
  temp = dht.readTemperature();
  humi = dht.readHumidity();

  if (isnan(humi) || isnan(temp)) {
    Serial.println(F("gagal membaca sensor"));
    return;
  }
  Serial.print(F("Temp: "));
  Serial.print(temp);
  Serial.print(F("°C     "));
  Serial.print(F("Humidity: "));
  Serial.println(humi);

  lcd.setCursor(0,0);
  lcd.print("Humi: ");
  lcd.setCursor(6,0);
  lcd.print(humi);
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.setCursor(6, 1);
  lcd.print(temp);

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, humi);
}
