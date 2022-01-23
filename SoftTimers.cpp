#include "src\SoftTimers.h"
#include "src\Messages.h"

TSoftTimers::TSoftTimers(const uint8_t ASize): TCustomTimers(ASize)
{
	FLastMicros = 0;
	classname = F("TSoftTimers");
}

void TSoftTimers::Run(void)
{
	uint32_t now = micros();
	if (now - FLastMicros < 1000) return;
	FLastMicros = now;
	Tick();
}
