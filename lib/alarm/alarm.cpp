// lib/alarm/alarm.cpp

#include "alarm.h"

// Internal state
static uint8_t _buzzerPin = 255;
static uint8_t _ledPin    = 255;
static bool    _isOn      = false;

void alarm_init(uint8_t buzzerPin, uint8_t ledPin) {
  _buzzerPin = buzzerPin;
  _ledPin    = ledPin;
  pinMode(_buzzerPin, OUTPUT);
  pinMode(_ledPin, OUTPUT);
  digitalWrite(_buzzerPin, LOW);
  digitalWrite(_ledPin, LOW);
  _isOn = false;
}

void alarm_on() {
  if (!_isOn && _buzzerPin != 255 && _ledPin != 255) {
    digitalWrite(_buzzerPin, HIGH);
    digitalWrite(_ledPin, HIGH);
    _isOn = true;
  }
}

void alarm_off() {
  if (_isOn && _buzzerPin != 255 && _ledPin != 255) {
    digitalWrite(_buzzerPin, LOW);
    digitalWrite(_ledPin, LOW);
    _isOn = false;
  }
}

void alarm_beep(uint8_t count, uint16_t onTime, uint16_t offTime) {
  if (_buzzerPin == 255 || _ledPin == 255) return;
  for (uint8_t i = 0; i < count; i++) {
    digitalWrite(_buzzerPin, HIGH);
    digitalWrite(_ledPin, HIGH);
    delay(onTime);
    digitalWrite(_buzzerPin, LOW);
    digitalWrite(_ledPin, LOW);
    if (i + 1 < count) {
      delay(offTime);
    }
  }
  _isOn = false;
}
