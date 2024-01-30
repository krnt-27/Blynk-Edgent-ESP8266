/*************************************************************
  Program Blynk IoT Monitoring Suhu dan Kontrol Servo
  dan Deteksi Keberadaan Manusia 
 *************************************************************/
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6oBJWI8Wl"
#define BLYNK_TEMPLATE_NAME "Prototype Pemantau Suhu Ruangan"
#define BLYNK_AUTH_TOKEN "T0Cq5YD69BZNW88QCBytjdKPUGa6GUD7"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>                // sensor suhu
#include <Wire.h>               // untuk LCD
#include <LiquidCrystal_I2C.h>  // untuk LCD
#include <Servo.h>

char ssid[] = "HUAWEI-uX8s";
char pass[] = "vAk3hwC4";

#define servoPin 32
#define DHTPIN 4
#define DHTTYPE DHT22

Servo servo;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

float temp, humi;

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin);
  dht.begin();
  lcd.begin();
  lcd.backlight();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimer);
}

void loop() {
  Blynk.run();
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

  lcd.setCursor(0, 0);
  lcd.print("Humi: ");
  lcd.setCursor(6, 0);
  lcd.print(humi);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.setCursor(6, 1);
  lcd.print(temp);

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, humi);
}


BLYNK_WRITE(V2) {
  int valueServo = param.asInt();  // data slider di blynk
  servo.write(valueServo);
}


BLYNK_WRITE(V3) {
  int onOffServo = param.asInt();
  if (onOffServo == 1) {
    servo.write(180);
  } else {
    servo.write(0);
  }
}