
#include "src\TimerItem.h"
#include <util/atomic.h>

TTimerItem::TTimerItem(const uint32_t AInterval, const TTimerState AState)
{
	SetInterval(AInterval);
	FActive = static_cast<bool>(AState);
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
			result = ((--FWorkCounter) == 0);
			if (result) FWorkCounter = FInitCounter;
		}
	}

	return result;
}
