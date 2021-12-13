#include <Arduino.h>
#include "DownTimer.h"

TDownTimer::TDownTimer(const uint8_t AHours, const uint8_t AMinutes, const TTimerState AState)
{
	FInitTime = AHours * MINUTES_PER_HOUR + AMinutes;
	FPackedTime = FInitTime;
	FSeconds = 0;
	FActive = AState;
	FLastMillis = millis();
}

void TDownTimer::SetNewInterval(const uint8_t AHours, const uint8_t AMinutes)
{
	TTimerState active = FActive;
	Stop();
	FInitTime = AHours * MINUTES_PER_HOUR + AMinutes;
	FPackedTime = FInitTime;
	if (active == TTimerState::Running) Start();
}

uint8_t TDownTimer::GetMinutes(void)
{
	return (FPackedTime % MINUTES_PER_HOUR);
}

uint8_t TDownTimer::GetHours(void)
{
	return (FPackedTime / MINUTES_PER_HOUR);
}

void TDownTimer::Run(void)
{
	uint16_t now = uint16_t(millis());
	if ((now - FLastMillis) < SECUND_INTERVAL) return;
	FLastMillis = now;
	
	if (FActive==TTimerState::Running) {
		if (FSeconds > 0) {	
			FSeconds--; 
			return;	
		}

		FSeconds = MINUTES_PER_HOUR - 1;
		FPackedTime--;

		PostMessage(msg_TimeChanged, GetHours(), GetMinutes());

		if (FPackedTime == 0) {
			Stop();
			PostMessage(msg_TimerEnd);
		}

	}
}
