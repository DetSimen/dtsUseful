#include <Arduino.h>
#include <util/atomic.h>
#include "src\HardTimers.h"


void THardTimers::Init(void) {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			TCCR0A = 0b00000000;  // Таймер в режиме Normal
			OCR0A = TIMER_ONE_MS;		// загрузим регистр совпадения
			TIMSK0 |= 0x3;				// установить OCIE0A и TOIE0, разрешим совпадение А и переполнение
			TIFR0 |= 0x2;				// очистим флаг OCF0A если до этого он был установлен, ждём следущего совпадения
		}
}

ISR(TIMER0_COMPA_vect) {
	OCR0A += TIMER_ONE_MS;
	if (TimersSingleton != NULL) TimersSingleton->Tick();
}


THardTimers::THardTimers(const uint8_t ACount): TCustomTimers::TCustomTimers(ACount)
{
	classname = F("THardTimers");
}
