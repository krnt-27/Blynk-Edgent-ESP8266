#define BLYNK_TEMPLATE_ID "TMPL6ugfNVI__"
#define BLYNK_TEMPLATE_NAME "Potensiometer LED"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#define LED1 5 // menggunakan GPIO5 atau D1
#define LED2 4 // menggunakan GPIO4 atau D2

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

BlynkTimer timer;  // sebagai pengganti delay

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  BlynkEdgent.begin();

  timer.setInterval(2000L, myTimerEvent);  // setting interval utk 2 detik dan jalankan fungsi myTimerEvent
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}

void myTimerEvent() {
  Blynk.virtualWrite(V0, analogRead(A0));  // A0 = Potensiometer
}

BLYNK_WRITE(V1) {
  int valueVirtualPinLED = param.asInt(); // data yg diambil dari blynk
  digitalWrite(LED1, valueVirtualPinLED);
}

BLYNK_WRITE(V2) {
  int valueVirtualPinPWMLED = param.asInt(); // data yg diambil dari blynk
  analogWrite(LED2, valueVirtualPinPWMLED);
}