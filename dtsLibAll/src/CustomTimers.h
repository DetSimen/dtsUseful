#pragma once
#include <Arduino.h>
#include "TClass.h"
#include "TimerItem.h"


class TCustomTimers : public TClass {
protected:
	bool		FActive;
	PTimerItem* FItems;
	uint8_t		FCount;
	uint8_t		FSize;

	TCustomTimers() = delete;
	
	void	Clear(void);

	bool isValidHandle(const THandle AHnd);
	THandle FindFreeIndex(void);

public:
	TCustomTimers(const uint8_t AListSize = 8);
	~TCustomTimers();

	THandle Add(const uint32_t AInterval, const TTimerState AState = TTimerState::Running);
	void	Delete(const THandle AHnd);
	void	SetNewInterval(const THandle AHnd, const uint32_t ANewInterval);

	inline void Stop(void) { FActive = false; }
	inline void Start(void) { FActive = true; }
	inline bool isActive(void) { return FActive; }

	void	Stop(const THandle AHnd);
	void	Start(const THandle AHnd);
	void	Reset(const THandle AHnd);
	bool	isActive(const THandle AHnd);

	void	Tick();
};