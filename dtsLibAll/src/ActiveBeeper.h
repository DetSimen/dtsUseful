#pragma once
#include <Arduino.h>
#include <DigitalDevice.h>

class TActiveBeeper : public TDigitalDevice {
	TActiveBeeper() = delete;
	
	void initDevice(void) override {
		digitalWrite(FPin, !FActiveLevel);
		FState = enumDeviceState::Off;
	}

public:
	TActiveBeeper(const uint8_t APin, const bool AActiveLevel) :TDigitalDevice(APin, AActiveLevel) {
		FSendMessageChange = false;
		classname = F("ActiveBeeper");
	}
};
