// PlantHealthMonitor.ino
// Main sketch for Plant Health Monitoring System (Refined)

// Avoid using Arduino String for efficiency
#include <Arduino.h>
#include "lcd_display.h"
#include "moisture_sensor.h"
#include "dht_sensor.h"
#include "light_sensor.h"
#include "alarm.h"

// Pin definitions
static const uint8_t MOISTURE_PIN = A0;
static const uint8_t LDR_PIN      = A1;
static const uint8_t DHT_PIN      = 2;
static const uint8_t BUZZER_PIN   = 7;
static const uint8_t LED_PIN      = 13;

// Thresholds (adjust after calibration)
static const int SOIL_DRY_THRESHOLD   = 30;   // percent
static const int LIGHT_LOW_THRESHOLD  = 20;   // percent
static const int TEMP_LOW_THRESHOLD   = 18;   // °C
static const int TEMP_HIGH_THRESHOLD  = 30;   // °C
static const int HUM_LOW_THRESHOLD    = 40;   // %
static const int HUM_HIGH_THRESHOLD   = 70;   // %

static const unsigned long SAMPLE_INTERVAL = 3000; // ms
unsigned long lastSampleTime = 0;

void setup() {
  Serial.begin(9600);

  // Initialize display
  lcd_init();
  lcd_clear();
  lcd_print(0, 0, "Plant Health Mon");
  lcd_print(1, 0, "Initializing...");
  delay(2000);
  lcd_clear();

  // Initialize sensors & alarm
  moisture_sensor_init(MOISTURE_PIN);
  dht_sensor_init(DHT_PIN, 11);   // DHT11
  light_sensor_init(LDR_PIN);
  alarm_init(BUZZER_PIN, LED_PIN);

  // Ready message
  lcd_print(0, 0, "Monitoring...");
  lcd_print(1, 0, "");
}

void loop() {
  unsigned long now = millis();
  if (now - lastSampleTime < SAMPLE_INTERVAL) return;
  lastSampleTime = now;

  // Read sensor values
  uint8_t soilPct = moisture_sensor_read_percent();   // 0–100%
  uint8_t lightPct = light_sensor_read_percent();     // 0–100%
  float temperature, humidity;
  bool dhtOk = dht_sensor_read(&temperature, &humidity);

  // Determine alerts
  bool soilAlert = (soilPct < SOIL_DRY_THRESHOLD);
  bool lightAlert = (lightPct < LIGHT_LOW_THRESHOLD);
  bool tempAlert = (!dhtOk) || (temperature < TEMP_LOW_THRESHOLD) || (temperature > TEMP_HIGH_THRESHOLD);
  bool humAlert  = (!dhtOk) || (humidity < HUM_LOW_THRESHOLD)   || (humidity > HUM_HIGH_THRESHOLD);
  bool anyAlert = soilAlert || lightAlert || tempAlert || humAlert;

  // Serial debug
  Serial.printf("Soil:%d%%  Light:%d%%\n", soilPct, lightPct);
  if (dhtOk) {
    Serial.printf("Temp:%.1fC  Hum:%.1f%%\n", temperature, humidity);
  } else {
    Serial.println("DHT read failed");
  }
  Serial.printf("Alerts: soil=%d light=%d temp=%d hum=%d\n",
                soilAlert, lightAlert, tempAlert, humAlert);

  // Prepare display lines
  char line1[17], line2[17];
  // Line 1: Soil & Light
  snprintf(line1, sizeof(line1), "Soil:%3d%% %s", soilPct, lightAlert ? "L!" : "OK");
  // Line 2: Temp & Hum
  if (dhtOk) {
    snprintf(line2, sizeof(line2), "%2.0fC %2.0f%% %s",
             temperature, humidity, (tempAlert||humAlert) ? "A!" : "OK");
  } else {
    snprintf(line2, sizeof(line2), "DHT ERR        ");
  }

  // Update LCD
  lcd_print(0, 0, line1);
  lcd_print(1, 0, line2);

  // Alarm control
  if (anyAlert) {
    alarm_on();
  } else {
    alarm_off();
  }
}