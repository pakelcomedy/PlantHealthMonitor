// lib/light_sensor/light_sensor.h

#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>

/**
 * @brief Initialize the light sensor (LDR) pin.
 *
 * @param pin           Analog pin connected to LDR voltage divider (e.g., A1).
 * @param darkRaw       Raw ADC value in complete darkness (e.g., 1023).
 * @param brightRaw     Raw ADC value in bright light (e.g., 0).
 *                       Values outside [brightRaw..darkRaw] will clamp.
 */
void light_sensor_init(uint8_t pin, int darkRaw = 800, int brightRaw = 200);

/**
 * @brief Read the raw ADC value from the light sensor.
 *
 * @return Averaged ADC reading (0–1023), where lower = brighter.
 */
int light_sensor_read_raw();

/**
 * @brief Read the ambient light as a percentage (0–100%).
 *
 * Maps brightRaw→100% to darkRaw→0%.
 *
 * @return Light intensity percentage (0 = dark, 100 = bright).
 */
uint8_t light_sensor_read_percent();

#endif // LIGHT_SENSOR_H
