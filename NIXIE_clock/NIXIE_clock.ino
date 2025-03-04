#include <WiFi.h>
#include "time.h"
#include "esp_sntp.h"


// Your WiFi settings for clock to synchronize with global server
const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSCODE";

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

const char *time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";

// Pin configuration
const int PIN_LAMP = 7;
const int PIN_RELAY = 8;
const int PIN_DATA = 9;
const int PIN_CLOCK = 10;

// Delay time influences time change animation speed (minimum 8)
const int DELAY_TIME = 15;

// State variables
bool RELAY = false;
int number = -1;
int previousTime = -1;
int previousSec = -1;
unsigned long now = 0;

// Binary decoding (if numbers are not displayed or are switched in your case, you have different nixie tubes pinout, change these tables according to your datasheet)
bool key[10][4] = {
  { 0, 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 1, 0 }, { 0, 0, 1, 1 }, { 0, 1, 0, 0 }, { 0, 1, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1, 1, 1 }, { 1, 0, 0, 0 }, { 1, 0, 0, 1 }
};

// Display a number on a specific lamp
void display(int number) {
  if (number < 0 || number >= 10) return;  // Validate input

  for (int i = 0; i < 4; i++) {
    step(key[number][i]);
  }
}


void step(bool dataState) {
  digitalWrite(PIN_DATA, dataState);
  delay(DELAY_TIME);
  digitalWrite(PIN_CLOCK, HIGH);
  delay(DELAY_TIME);
  digitalWrite(PIN_CLOCK, LOW);
}


//Print time on a clock
void printLocalTime() {
  static unsigned long lastUpdateMillis = 0;  // Last time the function ran
  const unsigned long interval = 1000;        // 1 second interval

  // Ensure this function runs at most once per second
  if (millis() - lastUpdateMillis < interval) {
    return;
  }
  lastUpdateMillis = millis();

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return;
  }

  // Update the display if the minute changes
  if (previousTime != timeinfo.tm_min) {
    for (int j = 0; j < 4; j++) {
      switch (j) {
        case 0:
          number = timeinfo.tm_hour / 10;
          break;
        case 1:
          number = timeinfo.tm_hour % 10;
          break;
        case 2:
          number = timeinfo.tm_min / 10;
          break;
        case 3:
          number = timeinfo.tm_min % 10;
          break;
      }
      display(number);
    }
    step(0);
    previousTime = timeinfo.tm_min;
  }
}



void timeavailable(struct timeval *t) {
  printLocalTime();
}

void setup() {

  pinMode(PIN_LAMP, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);

  digitalWrite(PIN_RELAY, RELAY);

  WiFi.begin(ssid, password);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  esp_sntp_servermode_dhcp(1);  // (optional)

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  sntp_set_time_sync_notification_cb(timeavailable);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}

void loop() {
  if (millis() >= now + 1000) {
    now = millis();
    digitalWrite(PIN_RELAY, RELAY);
    RELAY = !RELAY;
    printLocalTime();
  }
}
