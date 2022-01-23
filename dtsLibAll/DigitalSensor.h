#pragma once
#include <Arduino.h>
#include "CustomSensor.h"
#include "Consts.h"


class TDigitalSensor : public TCustomSensor {
protected: 
	static constexpr uint8_t NUM_ATTEMPTS = 8;

protected:
	bool		FActiveLevel;
	bool		FCurrentValue;
	uint8_t		FPin;

	TDigitalSensor() = delete;
	TDigitalSensor(TDigitalSensor&) = delete;
	TDigitalSensor(TDigitalSensor&&) = delete;

	virtual void init(void) override {
		FInitNeed = false;
		FCurrentValue = ReadDigitalPin(FPin, FActiveLevel);
		if (FCurrentValue) PostMessage(msg_SensorStateChanged, FCurrentValue);
	}

	void internalRead(void) override {

		bool value = ReadDigitalPin(FPin, FActiveLevel);

		if (FCurrentValue == value) return;

		FCurrentValue = value; 

		PostMessage(msg_SensorStateChanged, value);
	};

	static bool ReadDigitalPin(const uint8_t APin, const bool AActiveLevel) {
		for (uint8_t i = 0; i < NUM_ATTEMPTS; ++i) {
			if (digitalRead(APin) != AActiveLevel) return false;
		}
		return true;
	}

public:

	TDigitalSensor(const uint8_t APin, const bool AActiveLevel = ACTIVE_LOW) {
		FPin = APin;
		FActiveLevel = AActiveLevel;
		FCurrentValue = false;
		pinMode(APin, (AActiveLevel==ACTIVE_LOW) ? INPUT_PULLUP : INPUT);
		classname = F("DigitalSensor");
	}

};



