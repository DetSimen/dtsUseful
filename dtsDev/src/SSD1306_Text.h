#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Print.h>

enum class TDeviceStatus: uint8_t {Unknown = 0, Normal, Error};


class TSSD1306TXT : public Print {
public:
	static constexpr uint8_t DEF_DEV_ADDR = 0x3C;  // адрес устройства по умолчанию
	static constexpr uint8_t ALT_DEV_ADDR = 0x3F;

	enum class TScreenSize: uint8_t {Unknown, Size_128x32, Size_128x64 };

protected:
	uint8_t			FDevAddr;
	TDeviceStatus	FStatus;
	uint8_t			FWidth;
	uint8_t			FHeight;

	uint8_t			FCurrentCol;
	uint8_t			FCurrentRow;

	TSSD1306TXT(TSSD1306TXT&) = delete;
	TSSD1306TXT(TSSD1306TXT&&) = delete;

	void HardwareInit();

public:
	TSSD1306TXT() : TSSD1306TXT(DEF_DEV_ADDR) {};
	TSSD1306TXT(const uint8_t ADevAddr);

	void Init(const TScreenSize AScreenSize);

	size_t	write(uint8_t c) override;

};