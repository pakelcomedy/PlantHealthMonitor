// lib/moisture_sensor/moisture_sensor.cpp

#include "moisture_sensor.h"
#include <Arduino.h>

static uint8_t   _sensorPin = A0;
static int       _wetRaw    = 300;
static int       _dryRaw    = 800;
static const int _samples   = 5;  // number of readings to average

void moisture_sensor_init(uint8_t pin, int wetRaw, int dryRaw) {
  _sensorPin = pin;
  _wetRaw    = wetRaw;
  _dryRaw    = dryRaw;
  pinMode(_sensorPin, INPUT);
}

int moisture_sensor_read_raw() {
  long sum = 0;
  for (int i = 0; i < _samples; i++) {
    sum += analogRead(_sensorPin);
    delay(10);
  }
  int raw = sum / _samples;
  return raw;
}

uint8_t moisture_sensor_read_percent() {
  int raw = moisture_sensor_read_raw();
  // Clamp raw between wetRaw..dryRaw
  if (raw <= _wetRaw)    return 100;
  if (raw >= _dryRaw)    return   0;
  // Map wetRaw→100% to dryRaw→0%
  int pct = map(raw, _wetRaw, _dryRaw, 100, 0);
  // Constrain and return
  return (uint8_t)constrain(pct, 0, 100);
}
