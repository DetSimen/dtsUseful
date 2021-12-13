#pragma once

#include <Arduino.h>


enum class TTimerState : bool { Stopped = false, Running = true };

struct	TTimerItem;
using	PTimerItem = TTimerItem*;

struct TTimerItem {
protected:
	bool		FActive;
	uint32_t	FInitCounter;
	uint32_t	FWorkCounter;

	TTimerItem() = delete;
public:
	TTimerItem(const uint32_t AInterval, const TTimerState AState = TTimerState::Running);

	inline bool	isActive(void) const { return FActive; }
	
	inline void Stop(void) { FActive = false; }
	inline void Start(void) { FActive = true; }

	void		SetInterval(const uint32_t AInterval);

	void		Reset(void);

	bool		Tick(void);

	inline bool operator--(int) { return Tick(); }
};