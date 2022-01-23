#include <Arduino.h>
#include "src\DigitalButton.h"
#include "src\DEF_Message.h"
#include "src\DEF_Keys.h"


TDigitalButton::TDigitalButton(const uint8_t APin, const uint8_t AAssignKey, const bool AActiveLevel)
	: TDigitalButton(APin, AActiveLevel) {

	AssignKey(AAssignKey);
}


void TDigitalButton::internalRead(void) {
	
	if (ReadDigitalPin(FPin, FActiveLevel)) 
		onPress();
	else
		onRelease();
}

void TDigitalButton::AssignKey(const uint8_t AKey)
{
	FKey = AKey;
}

void TDigitalButton::onPress(void)
{
	uint16_t now = (uint16_t)(millis());

	if (FPressTime == 0) {
		FPressed = true;
		FPressTime = now;
		FSendLong = false;
	}
	else {
		if (now - FPressTime > LONG_PRESS_TIME) {
			if (!FSendLong) PostMessage(msg_LongPress, FKey);
			FPressTime = now;
			FSendLong = true;
		}
	}
}

void TDigitalButton::onRelease(void)
{
	if (!FPressed) return;
	FPressed = false;
	uint16_t now = (uint16_t)(millis());
	if ((now-FPressTime < LONG_PRESS_TIME) && (!FSendLong)) PostMessage(msg_KeyPress, FKey);
	FPressTime = 0;
}

TDigitalButton::TDigitalButton(const uint8_t APin, const bool AActiveLevel)
	:TDigitalSensor(APin, AActiveLevel) {
	
	FReadInterval = 10;

	FPressTime = 0;

	FPressed = false;

	FSendLong = false;

	classname = F("TDigitalButton");
};


