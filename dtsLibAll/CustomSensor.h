#pragma once
#include <Arduino.h>
#include "Types.h"
#include "TClass.h"
#include "DEF_Message.h"
#include "Messages.h"



class TCustomSensor : public TClass {
protected:
	
	uint32_t	FLastReadTime;		// время (millis()), когда сенсор читали последний раз 
	uint16_t	FReadInterval;		// минимальный интервал физического чтения сенсора

	virtual void init(void) = 0;
	
	virtual void internalRead(void)  = 0;

	TCustomSensor(TCustomSensor&) = delete;
	TCustomSensor(TCustomSensor&&) = delete;

public:

	TCustomSensor() {
		FError = false;
		FInitNeed = true;
		SetReadInterval(1000);
		classname = F("CustomSensor");
	}

	void SetReadInterval(const uint16_t ANewReadInterval) {
		FReadInterval = ANewReadInterval;
		FLastReadTime = 0 - FReadInterval - 1;
	}


	void Read(void) {
		if (isNeedInit()) init();

		if (isError())  return;

		uint32_t now = millis();
		if (now - FLastReadTime < FReadInterval) return;

		FLastReadTime = now;

		internalRead();

	}

};