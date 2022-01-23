#include <Arduino.h>
#include "src\CustomTimers.h"
#include "src\TimerItem.h"
#include "src\Consts.h"

PCustomTimers TimersSingleton;

void TCustomTimers::Clear(void)
{
	if (FItems == NULL) return;

	for (uint8_t i = 0; i < FSize; ++i) {
		if (FItems[i] != NULL) delete FItems[i];
		FItems = NULL;
	}

	FCount = 0;
}

bool TCustomTimers::isValidHandle(const THandle AHnd)
{
	return ((AHnd < FSize) && (FItems[AHnd] != NULL));
}

THandle TCustomTimers::FindFreeIndex(void)
{
	for (THandle idx = 0; idx < FSize; ++idx) {
		if (FItems[idx] == NULL) return idx;
	}
	return INVALID_HANDLE;
}

TCustomTimers::TCustomTimers(const uint8_t AListSize)
{
	FCount = 0;
	FItems = new PTimerItem[FSize = AListSize];
	for (uint8_t i = 0; i < FSize; ++i) FItems[i] = NULL;

	if (TimersSingleton != NULL) delete(TimersSingleton);
	TimersSingleton = this;
}

TCustomTimers::~TCustomTimers()
{
	Clear();
	delete[] FItems;
}

THandle TCustomTimers::Add(const uint32_t AInterval, const TTimerState AState)
{
	if ((FCount == 0)) {
		Init();
		Start();
	}

	THandle idx = FindFreeIndex();
	if (idx != INVALID_HANDLE) {
		FItems[idx] = new TTimerItem(AInterval, AState);
		FCount++;
	}
	return idx;
}

void TCustomTimers::Delete(const THandle AHnd)
{
	if (isValidHandle(AHnd)) {
		if (FItems[AHnd] != NULL) {
			delete FItems[AHnd];
			FCount--;
		}
	}
}

void TCustomTimers::SetNewInterval(const THandle AHnd, const uint32_t ANewInterval)
{
	if (isValidHandle(AHnd)) { FItems[AHnd]->SetInterval(ANewInterval); }
}

void TCustomTimers::Stop(const THandle AHnd){
	if (isValidHandle(AHnd)) FItems[AHnd]->Stop();

}

void TCustomTimers::Start(const THandle AHnd)
{
	if (isValidHandle(AHnd)) FItems[AHnd]->Start();
}

void TCustomTimers::Reset(const THandle AHnd)
{
	if (isValidHandle(AHnd)) FItems[AHnd]->Reset();
}

bool TCustomTimers::isActive(const THandle AHnd)
{
	if (isValidHandle(AHnd))
		return FItems[AHnd]->isActive();
	else
		return false;
}

void TCustomTimers::Tick()
{
	if (!FActive) return;
	for (uint8_t idx=0; idx<FSize; ++idx){
		if (FItems[idx] == NULL) continue;
		if ((*FItems[idx])--) PostMessage(msg_TimerEnd, idx);
	}
}
