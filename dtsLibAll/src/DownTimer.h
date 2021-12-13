#pragma once
#include <Arduino.h>
#include "TClass.h"


enum class TTimerState: bool {Stopped = false, Running};

class TDownTimer : public TClass
{
protected:
	const uint16_t  SECUND_INTERVAL = 1000U;
	const uint8_t   MINUTES_PER_HOUR = 60U;
	const uint8_t	SECONDS_PER_HOUR = 60U;

	uint16_t	FPackedTime;
	uint16_t	FInitTime;
	uint8_t		FSeconds;
	TTimerState	FActive;
	uint16_t	FLastMillis;

	TDownTimer() = delete;
public:
	TDownTimer(const uint8_t AHours, const uint8_t AMinutes, const TTimerState AState = TTimerState::Stopped);

	inline void Start(void) { if (FPackedTime > 0) FActive = TTimerState::Running; }
	inline void Stop(void) { FActive = TTimerState::Stopped; }

	void SetNewInterval(const uint8_t AHours, const uint8_t AMinutes);

	uint8_t GetMinutes(void);
	uint8_t	GetHours(void);
	
	inline void Reset(void) {
		Stop();
		FPackedTime = FInitTime;
		Start();
	}

	void Run(void);
};

