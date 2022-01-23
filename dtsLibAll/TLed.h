#pragma once 
#include <Arduino.h>
#include "DigitalDevice.h"
#include "TClass.h"

class TLed;
using PLed = TLed*;


class TLed : public TDigitalDevice {

private:
	TLed()		 = delete;
	TLed(TLed&)  = delete;
	TLed(TLed&&) = delete;


public:
	using TDigitalDevice::operator=;
	using TClass::operator bool;

//	TLed() : TLed(LED_BUILTIN) {};
	TLed(const uint8_t APin) : TLed(APin, ACTIVE_HIGH) {};

	TLed(const uint8_t APin, const bool AActiveLevel):TDigitalDevice::TDigitalDevice(APin, AActiveLevel) {
		classname = F("TLed");
		digitalWrite(FPin, !FActiveLevel);
	};

	void Toggle(void) {
		if (isError()) return;

		switch (FDeviceState)
		{
		case TDeviceState::On:
			Off();
			break;

		case TDeviceState::Off:
			On();
			break;

		default:
			break;
		}
	};

};
