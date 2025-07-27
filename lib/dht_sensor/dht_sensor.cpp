// lib/dht_sensor/dht_sensor.cpp

#include "dht_sensor.h"
#include <DHT.h>

static DHT* _dht = nullptr;

void dht_sensor_init(uint8_t pin, uint8_t type) {
  // Allocate and begin the DHT sensor
  _dht = new DHT(pin, type == 22 ? DHT22 : DHT11);
  _dht->begin();
}

bool dht_sensor_read(float* temperature, float* humidity) {
  if (!_dht) return false;
  float h = _dht->readHumidity();
  float t = _dht->readTemperature(); // default is °C
  if (isnan(h) || isnan(t)) {
    return false;
  }
  *humidity = h;
  *temperature = t;
  return true;
}
