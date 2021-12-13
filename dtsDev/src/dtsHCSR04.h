#pragma once
#include <Arduino.h>
#include <CustomSensor.h>

class THCSR04 : public TCustomSensor {

	static constexpr uint16_t SR04_NO_DATA = 0xFFFF;

protected:
	uint8_t     FTriggerPin;
	uint8_t     FEchoPin;
	uint16_t	FLastValue;

	void init(void) override {
		pinMode(FTriggerPin, OUTPUT);
		pinMode(FEchoPin, INPUT);
		digitalWrite(FTriggerPin, LOW);
		FInitNeed = false;
	}

	void internalRead() override {
		digitalWrite(FTriggerPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(FTriggerPin, LOW);
		uint32_t duration = pulseIn(FEchoPin, HIGH);

		uint16_t newValue = 0;

		if ((duration < 20) || (duration > 4000))
			newValue = SR04_NO_DATA;
		else 
			newValue = 10UL * duration / 294UL / 2UL;

		if (FLastValue == newValue) return;

		FLastValue = newValue;

		PostMessage(msg_SensorValueChanged, GetValue());
	}

public:
	THCSR04(const uint8_t ATriggerPin, const uint8_t AEchoPin) {
		FTriggerPin = ATriggerPin;
		FEchoPin = AEchoPin;
		FReadInterval = 100;
		FInitNeed = true;
		FLastValue = SR04_NO_DATA;
		classname = F("HC - SR04");
	}

	uint16_t GetValue(void) const {
		return (uint16_t)(FLastValue);
	}

};