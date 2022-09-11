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
#include <NeoPixelConnect.h>
#define MAXIMUM_NUM_NEOPIXELS 16

// Create an instance of NeoPixelConnect and initialize it
// to use GPIO pin 4 (D12) as the control pin, for a string
// of 8 neopixels. Name the instance p

NeoPixelConnect p(4, MAXIMUM_NUM_NEOPIXELS, pio0, 0);
//----------------------------LED---------------------------------


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
