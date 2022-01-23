#pragma once

#define CONSTS_H

#include "Arduino.h"
#include "Types.h"


const uint16_t MIN_ANALOG_VALUE = 0;

#if defined(__AVR__)
const uint16_t MAX_ANALOG_VALUE = 1023;
#endif

const bool ACTIVE_HIGH = true;
const bool ACTIVE_LOW = false;

const uint8_t INVALID_HUMIDITY = 0xFF;
const int8_t  INVALID_TEMPERATURE = -127;
const uint8_t INVALID_PIN = 0xFF;


const int16_t INVALID_INDEX = -1;
const int8_t  INVALID_HANDLE = -1;


const char eoln = '\n';
