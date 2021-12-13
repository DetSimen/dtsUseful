#pragma once

#include <Arduino.h>
#include "CustomTimers.h"

class TSoftTimers;
using PSoftTimers = TSoftTimers*;


class TSoftTimers: public TCustomTimers
{
protected:
	uint32_t FLastMicros;
	TSoftTimers() = delete;
public:
	TSoftTimers(const uint8_t ASize);
	void Run(void);
};

