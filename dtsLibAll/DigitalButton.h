#pragma once
#include <Arduino.h>
#include "Consts.h"
#include "DigitalSensor.h"
#include "DEF_Keys.h"



class TDigitalButton : public TDigitalSensor {
protected:
	static const uint16_t LONG_PRESS_TIME = 750; // ms

	uint16_t	FPressTime;
	uint8_t		FKey;
	bool		FPressed, FSendLong;


	void internalRead(void) override;

	TDigitalButton() = delete;
	TDigitalButton(TDigitalButton&) = delete;
	TDigitalButton(TDigitalButton&&) = delete;
	
	void  onPress(void);
	void  onRelease(void);

public:
	
	void AssignKey(const uint8_t AKey);
	
	TDigitalButton(const uint8_t APin, const bool AActiveLevel = ACTIVE_LOW);
	TDigitalButton(const uint8_t APin, const uint8_t AAssignKey = key_Null, const bool AActiveLevel = ACTIVE_LOW);

//	void Read(void);
};