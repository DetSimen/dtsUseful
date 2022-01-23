#include <Arduino.h>
#include <util/atomic.h>
#include "src\HardTimers.h"


void THardTimers::Init(void) {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			TCCR0A = 0b00000000;  // ������ � ������ Normal
			OCR0A = TIMER_ONE_MS;		// �������� ������� ����������
			TIMSK0 |= 0x3;				// ���������� OCIE0A � TOIE0, �������� ���������� � � ������������
			TIFR0 |= 0x2;				// ������� ���� OCF0A ���� �� ����� �� ��� ����������, ��� ��������� ����������
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
