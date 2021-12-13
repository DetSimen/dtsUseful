#include <Arduino.h>
#include "SSD1306_Text.h"

void TSSD1306TXT::HardwareInit()
{
	;
}

TSSD1306TXT::TSSD1306TXT(const uint8_t ADevAddr)
{
	FDevAddr = ADevAddr;
	FStatus = TDeviceStatus::Unknown;
}

void TSSD1306TXT::Init(const TScreenSize AScreenSize)
{
	FWidth = 128;
	switch (AScreenSize)
	{
	case TSSD1306TXT::TScreenSize::Unknown:
		FHeight = 0;
		break;
	case TSSD1306TXT::TScreenSize::Size_128x32:
		FHeight = 32;
		break;
	case TSSD1306TXT::TScreenSize::Size_128x64:
		FHeight = 64;
		break;
	default:
		break;
	}
	FCurrentCol = FCurrentRow = 0;

	if (FHeight > 0) HardwareInit();
}


size_t TSSD1306TXT::write(uint8_t c)
{
	return size_t(c);
}
