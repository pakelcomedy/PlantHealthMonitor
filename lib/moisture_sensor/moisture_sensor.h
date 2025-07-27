// lib/moisture_sensor/moisture_sensor.h

#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H

#include <Arduino.h>

/**
 * @brief Initialize the soil moisture sensor.
 * 
 * @param pin         Analog pin number (e.g., A0).
 * @param wetRaw      Raw ADC value corresponding to fully wet soil (e.g., 300).
 * @param dryRaw      Raw ADC value corresponding to completely dry soil (e.g., 800).
 *                     raw readings above dryRaw will clamp to 0% moisture.
 */
void moisture_sensor_init(uint8_t pin, int wetRaw = 300, int dryRaw = 800);

/**
 * @brief Read a single raw ADC sample from the moisture sensor.
 * 
 * @return ADC reading (0–1023).
 */
int moisture_sensor_read_raw();

/**
 * @brief Read the soil moisture as a percentage (0–100%).
 * 
 * Uses calibrated wetRaw/dryRaw to map raw reading to percentage.
 * 
 * @return Moisture percentage (0 = dry, 100 = wet).
 */
uint8_t moisture_sensor_read_percent();

#endif // MOISTURE_SENSOR_H
