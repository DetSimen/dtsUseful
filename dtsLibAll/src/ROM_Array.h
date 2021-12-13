#pragma once

#include <Arduino.h>
//#include <avr\eeprom.h>

using TBytePtr = uint8_t*;
 

static const TBytePtr ARRAY_DATA_PTR = TBytePtr(0x10U);
static const uint8_t  ARRAY_BYTE_SIZE = 64U;
static const uint8_t  EMPTY_ROM_VALUE = 0xFF;

extern int ArrayIndexOf(const uint8_t AValue);

extern void ClearROMArray(void);

extern int GetFreeAddress(void);

extern int SaveValue(const uint8_t AValue);

extern uint8_t FindNear(const uint8_t AFreq, const uint8_t AGap = 2);