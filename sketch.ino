#define BLYNK_TEMPLATE_ID "TMPL6jXU10icr"
#define BLYNK_TEMPLATE_NAME "SISTEM KEAMANAN AREA TERLARANG"
#define BLYNK_AUTH_TOKEN "v-AsSht06cfHb7c1954C6c6LZFeI8Qor"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define PIR_PIN      13
#define BUZZER_PIN   25
#define GREEN_LED    26
#define RED_LED      27

BlynkTimer timer;

int counter = 0;
bool lastState = LOW;

void sendSensor() {

  bool motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {

    // BAHAYA
    digitalWrite(GREEN_LED, HIGH);  
    digitalWrite(RED_LED, LOW);      
    digitalWrite(BUZZER_PIN, HIGH);

    if (lastState == LOW) {

      counter++;

      Serial.println("GERAKAN TERDETEKSI!");

      Blynk.virtualWrite(V0, "BAHAYA");
      Blynk.virtualWrite(V1, 1);
      Blynk.virtualWrite(V2, counter);

      lastState = HIGH;
    }

  } else {

    // AMAN
    digitalWrite(GREEN_LED, LOW);    
    digitalWrite(RED_LED, HIGH);     
    digitalWrite(BUZZER_PIN, LOW);

    Blynk.virtualWrite(V0, "AMAN");
    Blynk.virtualWrite(V1, 0);

    lastState = LOW;
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Kondisi awal: AMAN
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(500L, sendSensor);
}

void loop() {

  Blynk.run();
  timer.run();

}