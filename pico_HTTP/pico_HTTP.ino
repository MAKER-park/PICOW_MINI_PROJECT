//insert 관련
//http://cloud.park-cloud.co19.kr/project/insert.php?temp=45&hum=25&pm1=150&pm2=200&pm3=20 다음과 같은 주소 형식으로 데이터를 보낼 예정

//status 관련
//INSERT INTO `project_status` (`status`, `R`, `G`, `B`) VALUES ('0', '255', '255', '255');
//UPDATE `project_status` SET `status`=1,`R`=255,`G`=250,`B`=250 WHERE 1
//http://cloud.park-cloud.co19.kr/project/update_status.php?status=0&R=200&G=100&B=20
//INSERT INTO `dust_station`( `PM1.0`, `PM2.5`, `PM10`) VALUES (10,20,30)

//view 관련
//http://cloud.park-cloud.co19.kr/project/view.php
//INSERT INTO `pico_status`(`status`, `r`, `g`, `b`) VALUES (1,255,0,0)
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

//tiemr
#include <time.h>
#include <sys/time.h>

//wifi set
#ifndef STASSID
#define STASSID "iptime_projecter"
#define STAPSK "134625wo"
//#define STASSID "iot6"
//#define STAPSK "iot60000"
#endif

const char *ssid = STASSID;
const char *pass = STAPSK;

WiFiMulti WiFiMulti;

String sta, R, G, B;
int count = 0;
int mode_number = 0;

//----------------------------LED---------------------------------
#include <NeoPixelConnect.h>
#define MAXIMUM_NUM_NEOPIXELS 16 //number of led  led 갯수

// Create an instance of NeoPixelConnect and initialize it
// to use GPIO pin 4 (D12) as the control pin, for a string
// led 인스턴스 선언 과 갯수 설정 4(D12) 쪽 으로 출력 핀 설정

NeoPixelConnect p(2, MAXIMUM_NUM_NEOPIXELS, pio0, 0);
//----------------------------LED---------------------------------

//------------------------timer---------------
// These define's must be placed at the beginning before #include "TimerInterrupt_Generic.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     4

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "RPi_Pico_TimerInterrupt.h"

#define TIMER0_INTERVAL_MS        2000//2sec dust sensor update
#define TIMER0_DURATION_MS        10000 //10sec update 

//#define TIMER1_INTERVAL_MS        3000
//#define TIMER1_DURATION_MS        15000

// Init RPI_PICO_Timer, can use any from 0-15 pseudo-hardware timers
RPI_PICO_Timer ITimer0(0);
//RPI_PICO_Timer ITimer1(1);
//---------------------timer----------------------------

//dust_sensor_variable
unsigned char pmsbytes[32]; // array for 32 bytes stream from PMS7003
#define HEAD_1 0x42
#define HEAD_2 0x4d
int PM1_0_val=0; 
int PM2_5_val=0;
int PM10_val=0;

void setup() {

  Serial.begin(115200);
  Serial1.begin(9600);
  Serial.println("start churai project!");
  Serial.println();
  int start_red = 0;
  int start_green = 0;
  int start_blue = 0;


  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, pass);
  Serial.print("wifi connect");
  while ((WiFiMulti.run() != WL_CONNECTED)) { //wait for connect wifi!
    start_red = start_red + 15;
    start_green = start_green + 15;
    start_blue = start_blue + 15;
    Serial.print(".");
    ring_led(start_red,start_green,start_blue);
  }

  Serial.println("");
  Serial.println("wifi connect!");
  ring_led(0,0,0);
  //-----------------------set timer---------------------
  // Interval in microsecs
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else {
    Serial.println(F("Can't set ITimer0. Select another freq. or timer"));
  }

  Serial.flush();
}

void loop() {
  static unsigned long lastTimer0 = 0;

  if (millis() - lastTimer0 >= TIMER0_DURATION_MS)//10sec
  {
    Serial.println("timer! : " + String(millis() - lastTimer0));
    lastTimer0 = millis();
    //get data
    get_data();
  } 
}
