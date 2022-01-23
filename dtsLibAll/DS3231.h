#pragma once
#include <Arduino.h>
#include "I2CSensor.h"
#include <time.h>
#include <alloca.h>

//#include <Generics.h>
//#include <Consts.h>

using uint8_t = unsigned char;

class TDS3231_v2;
using PDS3231_v2 = TDS3231_v2*;

using TDateTime = tm;
using TPackedDateTime = time_t;
using TPackedTime = uint32_t;

enum class TDateTimeFormat : bool { Short = false, Long = true };

const char str_ShortTimeFormat[] PROGMEM = "%02u:%02u";
const char str_LongTimeFormat[]  PROGMEM = "%02u:%02u:%02u";

const char str_ShortDateFormat[] PROGMEM = "%02u.%02u.%02u";
const char str_LongDateFormat[]  PROGMEM = "%02u.%02u.%04u";

// - - - - - - DS3231 REGISTERS  BANK - - - - 

static const uint8_t REG_SECONDS = 0x00;		// регистр секунд
static const uint8_t REG_MINUTES = 0x01;		// минут
static const uint8_t REG_HOURS = 0x02;		// часов
static const uint8_t REG_DAYOFWEEK = 0x03;		// дн¤ недели
static const uint8_t REG_DATE = 0x04;		// дней
static const uint8_t REG_MONTH = 0x05;		// мес¤цев
static const uint8_t REG_YEAR = 0x06;		// лет

static const uint8_t REG_CONTROL = 0x0E;		// управл¤ющий регистр
static const uint8_t REG_STATUS = 0x0F;			// регистр статуса

static const uint8_t REG_TEMP_HIGH = 0x11;		// старший байт температуры
static const uint8_t REG_TEMP_LOW = 0x12;		// младший байт температуры



class TDS3231 : public TI2CCustomSensor {
private:
	static const uint8_t	DS3231_DEFAULT_ADDRESS = 0x68;  // адрес устройства на шине по умолчанию
	static const uint32_t	DS3231_POLLING_TIME = 100;	 // минимальное врем¤ опроса 100 мс
	static const uint8_t	DS3231_MEMORY_SIZE = 0x13;

	static const uint8_t    OUTSTRING_SIZE = 32;
	
	char		*FOutString;

	int8_t		FLastTemperature;
	uint8_t		FDevMemory[DS3231_MEMORY_SIZE];


	static uint8_t dec2bcd(const uint8_t AdecValue) {
		return ((AdecValue / 10) << 4) + (AdecValue % 10);
	}

	static uint8_t bcd2dec(const uint8_t AbcdValue, const uint8_t AMask = 0x7F) {
		uint8_t val = AbcdValue & AMask;
		return 10 * (val >> 4) + (val & 0x0F);
	}

	TDateTime DecodeTime(void) const {
		TDateTime result;
		result.tm_sec = bcd2dec(FDevMemory[REG_SECONDS]);
		result.tm_min = bcd2dec(FDevMemory[REG_MINUTES]);
		result.tm_hour = bcd2dec(FDevMemory[REG_HOURS], 0x3F);
		result.tm_wday = bcd2dec(FDevMemory[REG_DAYOFWEEK]) - 1;
		result.tm_mday = bcd2dec(FDevMemory[REG_DATE], 0x3F);
		result.tm_mon = bcd2dec(FDevMemory[REG_MONTH], 0x1F) - 1;
		result.tm_year = 100 + bcd2dec(FDevMemory[REG_YEAR], 0xFF);
		return result;
	}

	void Check(const uint8_t AOld[]) {
		TDateTime time = DecodeTime();

		if (FDevMemory[REG_SECONDS] != AOld[REG_SECONDS]) PostMessage(msg_SecondsChanged, time.tm_sec);
		if (FDevMemory[REG_MINUTES] != AOld[REG_MINUTES]) PostMessage(msg_TimeChanged, time.tm_hour, time.tm_min);
		if (FDevMemory[REG_DATE] != AOld[REG_DATE]) PostMessage(msg_DateChanged, time.tm_mday, time.tm_mon+1);

		if (FDevMemory[REG_TEMP_HIGH] != AOld[REG_TEMP_HIGH]) {
			FLastTemperature = int8_t(FDevMemory[REG_TEMP_HIGH]);
			PostMessage(msg_TemperatureChanged, FLastTemperature);
		}

	}

	void internalRead(void) override {
		uint8_t* SaveMemory = (uint8_t *)(alloca(DS3231_MEMORY_SIZE+1));
		memcpy(SaveMemory, FDevMemory, DS3231_MEMORY_SIZE);
		
		Wire.beginTransmission(FDevAddress);
		Wire.write(REG_SECONDS);
		if (Wire.endTransmission() > 0) {
			Error(err_i2c_DeviceNotFound);
			return;
		}

		Wire.requestFrom(FDevAddress, DS3231_MEMORY_SIZE);
		if (Wire.readBytes(FDevMemory, DS3231_MEMORY_SIZE) != DS3231_MEMORY_SIZE) {
			Error(err_i2c_ReadError);
			return;
		}

		Check(SaveMemory);

	}

	void SaveRegisters(const uint8_t AFrom, const uint8_t ACount) {
		Wire.beginTransmission(FDevAddress);
		Wire.write(AFrom);
		Wire.write(&FDevMemory[AFrom], ACount);
		Wire.endTransmission();
	}

public:
	TDS3231() :TDS3231(DS3231_DEFAULT_ADDRESS) {}

	TDS3231(const uint8_t ADevAddr) :TI2CCustomSensor(ADevAddr) {
		FReadInterval = DS3231_POLLING_TIME;
		FOutString = new char[OUTSTRING_SIZE + 1];
		memset(FOutString, 0x00, OUTSTRING_SIZE);
		classname = F("TDS3231");
	}

	~TDS3231() {
		delete[] FOutString;
	}

	TDateTime GetTime(void) {
		Read();
		return DecodeTime();
	}

	const char* GetTimeStr(const TDateTimeFormat AFormat = TDateTimeFormat::Short) {
		const char *ptr;
		if (AFormat == TDateTimeFormat::Long)
			ptr = "%T";
		else
			ptr = "%R";


		Read();
		TDateTime t = DecodeTime();

		strftime(FOutString, OUTSTRING_SIZE, ptr, &t);

		return FOutString;

	}

	const char* GetTimeStr(const char* AFormatStr) {
		Read();
		TDateTime t = DecodeTime();

		strftime(FOutString, OUTSTRING_SIZE, AFormatStr, &t);
		return FOutString;
	}

	const char* GetDateStr(const TDateTimeFormat AFormat = TDateTimeFormat::Short) {
		Read();
		TDateTime t = DecodeTime();

		const char* ptr;
		if (AFormat == TDateTimeFormat::Short)
			ptr = "%d.%m.%y";
		else
			ptr = "%a, %e %h %Y";

		strftime(FOutString, OUTSTRING_SIZE, ptr, &t);

		return FOutString;
		
	}

	void SetDate(const uint8_t ADay, const uint8_t AMonth, const uint16_t AYear) {
		Read();
		if (ADay > 0 && ADay < 32) FDevMemory[REG_DATE] = dec2bcd(ADay);
		if (AMonth > 0 && AMonth < 13) FDevMemory[REG_MONTH] = dec2bcd(AMonth);
		uint8_t y = 0;
		if (AYear < 100) y = AYear;
		if (AYear>2000)	y = AYear - 2000;
		FDevMemory[REG_YEAR] = dec2bcd(y);

		SaveRegisters(REG_DATE, 3);
	}

	void SetDate(const char* ADateStr) {
		uint8_t d = atoi(&ADateStr[0]);
		uint8_t m = atoi(&ADateStr[3]);
		uint16_t y = atoi(&ADateStr[6]);
		SetDate(d, m, y);
	}

	void SetTime(const uint8_t AHour, const uint8_t AMinute, const uint8_t ASecond = 0) {
		Read();
		if (AHour < 24) FDevMemory[REG_HOURS] = dec2bcd(AHour);
		if (AMinute < 60) FDevMemory[REG_MINUTES] = dec2bcd(AMinute);
		if (ASecond < 60) FDevMemory[REG_SECONDS] = dec2bcd(ASecond);

		SaveRegisters(REG_SECONDS, 3);
	}

	void SetTime(const char* ATimeStr) {
		uint8_t h = atoi(&ATimeStr[0]);
		uint8_t m = atoi(&ATimeStr[3]);
		uint8_t s = atoi(&ATimeStr[6]);
		SetTime(h, m, s);
	}

	const char* GetDateStr(const char* AFormatStr) {
		return GetTimeStr(AFormatStr);
	}

	void SetDayOfWeek(const uint8_t ADOW) {
		if (ADOW < 7) {
			Read();
			FDevMemory[REG_DAYOFWEEK] = ADOW + 1;
			SaveRegisters(REG_DAYOFWEEK, 1);
		}
	}

	uint8_t GetRegister(const uint8_t ARegAddr) {
		if (ARegAddr < DS3231_MEMORY_SIZE) {
			Read();
			return FDevMemory[ARegAddr];
		}
		return 0;
	}

	void SetRegister(const uint8_t ARegAddr, const uint8_t AValue) {
		if (ARegAddr < DS3231_MEMORY_SIZE) {
			Read();
			FDevMemory[ARegAddr] = AValue;
			SaveRegisters(ARegAddr, 1);
		}
	}

	int8_t GetTemperature(void) const {
		return FLastTemperature;
	}

	uint8_t GetHour() { return GetTime().tm_hour; }
	uint8_t GetMinute() { return GetTime().tm_min; }
	uint8_t GetSeconds() { return GetTime().tm_sec; }

};