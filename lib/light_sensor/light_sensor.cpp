// lib/light_sensor/light_sensor.cpp

#include "light_sensor.h"
#include <Arduino.h>

static uint8_t _sensorPin = A1;
static int     _darkRaw   = 800;
static int     _brightRaw = 200;
static const int _samples = 5;  // number of readings to average

void light_sensor_init(uint8_t pin, int darkRaw, int brightRaw) {
  _sensorPin = pin;
  _darkRaw   = darkRaw;
  _brightRaw = brightRaw;
  pinMode(_sensorPin, INPUT);
}

int light_sensor_read_raw() {
  long sum = 0;
  for (int i = 0; i < _samples; i++) {
    sum += analogRead(_sensorPin);
    delay(5);
  }
  int raw = sum / _samples;
  return raw;
}

uint8_t light_sensor_read_percent() {
  int raw = light_sensor_read_raw();
  // Clamp raw between brightRaw..darkRaw
  if (raw <= _brightRaw) return 100;
  if (raw >= _darkRaw)   return   0;
  // Map brightRaw→100% to darkRaw→0%
  int pct = map(raw, _brightRaw, _darkRaw, 100, 0);
  return (uint8_t)constrain(pct, 0, 100);
}
