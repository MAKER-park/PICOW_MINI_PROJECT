//insert 관련
//http://cloud.park-cloud.co19.kr/project/insert.php?temp=45&hum=25&pm1=150&pm2=200&pm3=20 다음과 같은 주소 형식으로 데이터를 보낼 예정

//status 관련
//INSERT INTO `project_status` (`status`, `R`, `G`, `B`) VALUES ('0', '255', '255', '255');
//UPDATE `project_status` SET `status`=1,`R`=255,`G`=250,`B`=250 WHERE 1
//http://cloud.park-cloud.co19.kr/project/update_status.php?status=0&R=200&G=100&B=20

//view 관련
//http://cloud.park-cloud.co19.kr/project/view.php
//http://cloud.park-cloud.co19.kr/project/view_status.php

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#ifndef STASSID
#define STASSID "iptime_projecter"
#define STAPSK "134625wo"
#endif

const char *ssid = STASSID;
const char *pass = STAPSK;

WiFiMulti WiFiMulti;

String sta, R, G, B;
int count = 0;
int mode_number = 0;

//----------------------------LED---------------------------------
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        2 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 13 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//----------------------------LED---------------------------------
//----------------------------dust sensor---------------------------------
#include <pms.h>
Pmsx003 pms(14, 16); //미세먼지 센서

int pm1, pm2, pm3;
//----------------------------dust sensor---------------------------------
//----------------------------dht---------------------------------
#include "DHT.h"
#define DHTPIN 5 
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = 0;
  // Read temperature as Celsius (the default)
  int t = 0;
//----------------------------dht---------------------------------

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFiMulti.addAP(ssid, pass);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin("http://cloud.park-cloud.co19.kr/project/view_status.php")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}
