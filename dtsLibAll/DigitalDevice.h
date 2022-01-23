#pragma once
#include <Arduino.h>
#include "Consts.h"
#include "CustomDevice.h" 



class TDigitalDevice : public TCustomDevice {
protected:
	uint8_t			FPin;
	bool			FActiveLevel;

	TDigitalDevice() = delete;
	TDigitalDevice(TDigitalDevice&) = delete;
	TDigitalDevice(TDigitalDevice&&) = delete;


public:
	TDigitalDevice(const uint8_t APin) : TDigitalDevice(APin, ACTIVE_HIGH) {};
	
	TDigitalDevice(const uint8_t APin, const bool AActiveLevel, const bool AEnableSendMessage = false) {
		FPin = APin;
		FActiveLevel = AActiveLevel;
		pinMode(FPin, OUTPUT);
		FEnableChangeMsg = false;
		Off();
		FEnableChangeMsg = AEnableSendMessage;
		classname = F("DigitalDevice");
	}

	void On(void) {
		if (isError()) return;

		digitalWrite(FPin, FActiveLevel);
		SetDeviceState(TDeviceState::On);

	}

	inline bool isOn(void) const {
		return FDeviceState == TDeviceState::On;;
	}

	void Off(void) {
		digitalWrite(FPin, !FActiveLevel);
		SetDeviceState(TDeviceState::Off);
	}

	inline bool isOff(void) const {
		return FDeviceState==TDeviceState::Off;
	}

	bool operator =(const bool AValue) {
		if (AValue)
			On();
		else
			Off();
		return AValue;
	}



};