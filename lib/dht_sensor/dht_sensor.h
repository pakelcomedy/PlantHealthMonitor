// lib/dht_sensor/dht_sensor.h

#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>

/**
 * @brief Initialize the DHT sensor.
 * 
 * Must be called once in setup().
 * 
 * @param pin       Digital pin connected to DHT data line.
 * @param type      Sensor type: 11 for DHT11, 22 for DHT22.
 */
void dht_sensor_init(uint8_t pin, uint8_t type);

/**
 * @brief Read temperature & humidity from DHT sensor.
 * 
 * @param[out] temperature  Pointer to store temperature in °C.
 * @param[out] humidity     Pointer to store relative humidity in %.
 * @return true if read succeeded, false on failure.
 */
bool dht_sensor_read(float* temperature, float* humidity);

#endif // DHT_SENSOR_H
