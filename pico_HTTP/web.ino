void get_data() {
  Serial.println("connect to web!");
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin("http://cloud.park-cloud.co19.kr/pico_project/view_status.php")) {  // HTTP


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
          //Serial.println(payload);//get result
          //[{"status":"1","R":"255","G":"0","B":"0"}]
          String mode_status = payload.substring(12, 13);
          Serial.println("mode : " + mode_status);

          if (mode_status == "0") {
            //air update mode
            Serial.println("air mode!");

            if (PM2_5_val != 0) {//PM2_5_val only update
              if (http.begin("http://cloud.park-cloud.co19.kr/pico_project/insert.php?&pm1=" + String(PM1_0_val) + "&pm2=" + String(PM2_5_val) + "&pm3=" + String(PM10_val))) {  // HTTP

                //PM2.5 - led sync
                /*
                  good 0 - 15 blue
                  normal 16 - 35 green
                  warring 36 - 75 yellow
                  bed over 76 red
                */
                if (PM2_5_val <= 15) { //blue
                  ring_led(0, 0, 50);
                } else if ((PM2_5_val > 15) && (PM2_5_val <= 35)) { // green
                  ring_led(0, 50, 0);
                } else if ((PM2_5_val > 35) && (PM2_5_val <= 75) ) { // yellow
                  ring_led(50, 50, 0);
                } else if (PM2_5_val > 75) { //red
                  ring_led(50, 0, 0);
                }

                Serial.print("[HTTP] GET...\n");
                // start connection and send HTTP header
                int httpCode = http.GET();

                // httpCode will be negative on error
                if (httpCode > 0) {
                  // HTTP header has been send and Server response header has been handled
                  Serial.printf("[HTTP] GET... code: %d\n", httpCode);
                }

                // file found at server
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                  String payload = http.getString();
                  Serial.println(payload);//get result
                  //init PM_data
                  PM2_5_val = 0;
                }

              }
            }

          } else {
            //LED mode
            Serial.println("LED mode!");
            int r, g, b, index_r_s, index_r_e, index_g_s, index_g_e, index_b_s, index_b_e;
            index_r_s = payload.indexOf("R", 10);
            index_r_e = payload.indexOf(",", index_r_s);
            //            Serial.println("test_r_s : " + String(index_r_s));
            //            Serial.println("test_r_e : " + String(index_r_e));
            r = payload.substring(index_r_s + 4, index_r_e - 1).toInt();
            Serial.println("RED : " + String(r));

            index_g_s = payload.indexOf("G", index_r_e);
            index_g_e = payload.indexOf(",", index_g_s);
            g = payload.substring(index_g_s + 4, index_g_e - 1).toInt();
            Serial.println("GREEN : " + String(g));

            index_b_s = payload.indexOf("B", index_g_e);
            index_b_e = payload.indexOf("}", index_b_s);
            //            Serial.println("index_b_s : " + String(index_b_s));
            //            Serial.println("index_b_e : " + String(index_b_e));
            b = payload.substring(index_b_s + 4, index_b_e - 1).toInt();
            Serial.println("BLUE : " + String(b));
            ring_led(r, g, b);
          }

        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  } else {
    Serial.println("wifi not connect!");
  }
}
