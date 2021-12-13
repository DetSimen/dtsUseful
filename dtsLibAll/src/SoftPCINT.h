#pragma once

#include <Arduino.h>
#include <Consts.h>
#include <TClass.h>


class TSoftPCINT: public TClass {
protected:
	const uint8_t	FPin;
	const bool		FActiveLevel;

	uint16_t		FLastReadTime;
	bool			FActive;

	void internalRead() {
		bool value = digitalRead(FPin);
		value ? onActive() : onPassive();
	}

	void onActive() {
		if (FActive) return;
		FLastReadTime = uint16_t(millis());
		FActive = true;
		PostMessage(msg_PCINTChanged, FPin, 1);
		puts("Active");
	}

	void onPassive() {
		if (!FActive) return;
		FLastReadTime = 0;
		FActive = false;
		PostMessage(msg_PCINTChanged, FPin,0);
	}

	TSoftPCINT() = delete;
	TSoftPCINT(TSoftPCINT&) = delete;
	TSoftPCINT(TSoftPCINT&&) = delete;
public:
	TSoftPCINT(const uint8_t APin, const bool AActiveLevel = ACTIVE_LOW) 
		:FPin(APin), FActiveLevel(AActiveLevel) {
		FLastReadTime = 0;
		FActive = false;
//		pinMode(FPin, FActiveLevel ? INPUT : INPUT_PULLUP);
	};

	void  Read(void) {
		internalRead();
	}
};