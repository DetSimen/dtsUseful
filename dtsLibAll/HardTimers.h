#pragma once
#include <Arduino.h>
#include <util\atomic.h>
#include "CustomTimers.h"

constexpr uint8_t TIMER_ONE_MS = 245;



class THardTimers : public TCustomTimers {
protected:
	void Init(void) override;

	THardTimers(THardTimers&) = delete;
	THardTimers(THardTimers&&) = delete;
public:
	THardTimers(const uint8_t ACount = 8);
};


