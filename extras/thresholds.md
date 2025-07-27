# Threshold Configuration for Plant Health Monitoring

This document defines threshold values used by the system to determine plant health conditions.

## 1. Soil Moisture (0–1023 analog)
- **DRY_THRESHOLD**: > 600 (soil is too dry → trigger watering)
- **WET_THRESHOLD**: < 400 (soil is wet)

## 2. Light Intensity (0–1023 analog)
- **LOW_LIGHT_THRESHOLD**: < 300 → Not enough sunlight
- **GOOD_LIGHT_THRESHOLD**: > 600 → Ideal

## 3. Temperature (°C)
- **MIN_TEMP**: < 18°C → Too cold
- **MAX_TEMP**: > 32°C → Too hot

## 4. Humidity (%)
- **MIN_HUMIDITY**: < 30% → Too dry
- **MAX_HUMIDITY**: > 70% → Too humid

## Alarm Logic
- Alarm is triggered when:
  - Soil is too dry
  - Light is too low
  - Temperature is outside the ideal range
  - Humidity is outside the ideal range