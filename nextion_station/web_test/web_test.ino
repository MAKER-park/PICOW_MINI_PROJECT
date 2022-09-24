//----------------------------web---------------------------------
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "iptime_projecter";
const char* password = "134625wo";
String host = "http://cloud.park-cloud.co19.kr/project/view2.php";
String sta, temp, hmet, dust;
int count = 0;

WiFiServer server(80);
WiFiClient client;
HTTPClient http;
//----------------------------web---------------------------------
#include <Nextion.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialForNex(14, 16);

NexText t3 = NexText(0, 5, "t3");
NexText t4 = NexText(0, 7, "t4");
NexText t5 = NexText(0, 8, "t5");


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");

  //-------------------------------------------------------
  nexInit();

  t3_Callback(&t3);
  t4_Callback(&t4);
  t5_Callback(&t5);

}

auto lastRead = millis();
 
void loop() {
  // put your main code here, to run repeatedly:
  
  auto newRead = millis();
  if (newRead - lastRead > 3000) { //3초마다 센서 값 갱신 및 DB 업데이트
    lastRead = newRead;
    String phpHost = host;
    Serial.print("Connect to ");
    Serial.println(phpHost);

    http.begin(client, phpHost);
    http.setTimeout(1000);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("GET code : %d\n\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        //sta, R, G, B;

        for (int i = 0; i < payload.length(); i++) {

          if (payload.charAt(i) == ':' && payload.charAt(i + 1) == '"') {
            int index = i + 2;
            //Serial.println("found! : " + String(index));
            count++;
            if (count == 2) {
              //Serial.println("found number 2");
              while (payload.charAt(index) != '"') {
                //Serial.print(payload.charAt(index));
                index++;
              }//temp, hmet, dust;
              temp = payload.substring(i + 2, index);
            } else if (count == 3) {
              //Serial.println("found number 3");
              while (payload.charAt(index) != '"') {
                //Serial.print(payload.charAt(index));
                index++;
              }
              hmet = payload.substring(i + 2, index);
            } else if (count == 4) {
              //Serial.println("found number 4");
              while (payload.charAt(index) != '"') {
                //Serial.print(payload.charAt(index));
                index++;
              }
              dust = payload.substring(i + 2, index);
              count = 0;
            }
          }
        }
        Serial.print(temp + "\t");
        Serial.print(hmet + "\t");
        Serial.print(dust + "\t");
        Serial.println("");
        t3_Callback(&t3);
        t4_Callback(&t4);
        t5_Callback(&t5);
      }
    }
    else {
      Serial.printf("GET failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
