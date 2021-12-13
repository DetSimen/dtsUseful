#pragma once
#include <Arduino.h>
#include "TClass.h"
#include "CustomSensor.h"


class TAnalogSensor : public TCustomSensor {
protected:
	static constexpr uint16_t DEFAULT_READ_INTERVAL	= 1000;		// время между опросами 1 секунда по умолчанию
	static constexpr uint16_t INVALID_VALUE			= 0xFFFF;	// Magic Number
	static constexpr uint16_t NUM_READ_ATTEMPTS		= 16;

	uint8_t		FPin;
	uint16_t	FValue;
	uint16_t	FGap;
	
	TAnalogSensor() = delete;
	TAnalogSensor(TAnalogSensor&) = delete;
	TAnalogSensor(TAnalogSensor&&) = delete;




static 	uint16_t readAnalogPin(const uint8_t APin) {
		uint16_t result = 0;
		uint16_t value = 0;
		for (uint8_t i = 0; i < NUM_READ_ATTEMPTS; i++) {
			value = analogRead(APin);
			if (value < 10) return 0;
			if (value > 1013) return 1023;
			result += value;
			delayMicroseconds(500);
		}

		return (result/NUM_READ_ATTEMPTS);

	}

void init(void) override {
	internalRead();
	}

	void internalRead(void) override {
		uint16_t value = readAnalogPin(FPin);
		if ((FGap & 0x01) > 0) FGap++;
		uint8_t delta = FGap / 2;
		uint16_t min = value - delta;
		uint16_t max = value + delta;

		if ((FValue>=min)&&(FValue<=max)) return;

		FValue = value;

		PostMessage(msg_SensorValueChanged, FValue);

	}
public:

	TAnalogSensor(const uint8_t APin, const bool APullUp = true) {
		FPin = APin;
		pinMode(FPin, APullUp ? INPUT_PULLUP : INPUT);
		SetReadInterval(DEFAULT_READ_INTERVAL);
		FValue = INVALID_VALUE;
		FGap = 10;
		classname = F("AnalogSensor");
	}

	inline uint16_t GetValue(void) const {
		return FValue;
	}

	inline void SetGap(const uint16_t ANewGap) {
		FGap = ANewGap;
	}
};
