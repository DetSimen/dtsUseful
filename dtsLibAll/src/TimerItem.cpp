
#include "TimerItem.h"
#include <util/atomic.h>

TTimerItem::TTimerItem(const uint32_t AInterval, const TTimerState AState)
{
	FActive = static_cast<bool>(AState);
	SetInterval(AInterval);
}

void TTimerItem::SetInterval(const uint32_t AInterval)
{
	FInitCounter = AInterval;
	Reset();
}

void TTimerItem::Reset(void)
{
	Stop();
	FWorkCounter = FInitCounter;
	Start();
}


bool TTimerItem::Tick(void)
{
	bool result = false;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if (FActive) {
			result = (--FWorkCounter == 0);
			if (result) FWorkCounter = FInitCounter;
		}
	}

	return result;
}
