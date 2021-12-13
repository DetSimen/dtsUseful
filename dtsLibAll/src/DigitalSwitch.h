#pragma once
#include <DigitalSensor.h>

class TDigitalSwitch : public TDigitalSensor {
protected:
	void init(void) override {
		FInitNeed = false;
		FCurrentValue = ReadDigitalPin(FPin, FActiveLevel); 
		if (FCurrentValue) PostMessage(msg_SensorStateChanged, FCurrentValue);
	};

public:
	TDigitalSwitch(const uint8_t APin, const bool AActiveLevel = ACTIVE_LOW) :TDigitalSensor(APin, AActiveLevel) {
		FReadInterval = 100;
		FCurrentValue = false;
		classname = F("TDigitalSwitch");
	};

	bool SwitchState(void) const {
		return FCurrentValue;
	}
};