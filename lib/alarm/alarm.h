// lib/alarm/alarm.h

#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>

/**
 * @brief Initialize alarm outputs.
 * 
 * @param buzzerPin  Digital pin connected to buzzer (active HIGH).
 * @param ledPin     Digital pin connected to indicator LED (active HIGH).
 */
void alarm_init(uint8_t buzzerPin, uint8_t ledPin);

/**
 * @brief Activate the alarm (turn on buzzer and LED).
 */
void alarm_on();

/**
 * @brief Deactivate the alarm (turn off buzzer and LED).
 */
void alarm_off();

/**
 * @brief Sound a short beep pattern.
 * 
 * @param count   Number of beeps.
 * @param onTime  Duration of each beep (ms).
 * @param offTime Duration between beeps (ms).
 */
void alarm_beep(uint8_t count, uint16_t onTime = 200, uint16_t offTime = 200);

#endif // ALARM_H
