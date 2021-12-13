#include "ROM_Array.h"
#include <avr\eeprom.h>
#include <Consts.h>

int ArrayIndexOf(const uint8_t AValue)
{
	for (uint8_t i = 0; i < ARRAY_BYTE_SIZE; ++i) {
		if (eeprom_read_byte(ARRAY_DATA_PTR + i) == AValue) return (int)(i);
	}
	return INVALID_INDEX;
}

void ClearROMArray(void)
{
	for (uint8_t i = 0; i < ARRAY_BYTE_SIZE; ++i) eeprom_update_byte(ARRAY_DATA_PTR + i, EMPTY_ROM_VALUE);
}

int GetFreeAddress(void)
{
	for (uint8_t i = 0; i < ARRAY_BYTE_SIZE; ++i) {
		if (eeprom_read_byte(ARRAY_DATA_PTR + i) == EMPTY_ROM_VALUE) return int(ARRAY_DATA_PTR + i);
	}
	return INVALID_INDEX;
}

int SaveValue(const uint8_t AValue)
{
	int result = ArrayIndexOf(AValue);
	if (result < 0) {
		int addr = GetFreeAddress();
		if (addr != INVALID_INDEX) {
			eeprom_update_byte(TBytePtr(addr), AValue);
			result = addr - (int)(ARRAY_DATA_PTR);
		}
	}
	return result;
}

uint8_t FindNear(const uint8_t AFreq, const uint8_t AGap)
{
	for (uint8_t i = 0; i < ARRAY_BYTE_SIZE; ++i) {
		uint8_t value = eeprom_read_byte(ARRAY_DATA_PTR + i);
		if (value == EMPTY_ROM_VALUE) break;
		if (abs(int(value) - int(AFreq)) <= AGap) return(value);
	}
	return EMPTY_ROM_VALUE;
}
