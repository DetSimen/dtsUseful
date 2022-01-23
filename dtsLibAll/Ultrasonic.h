#pragma once
#include <Arduino.h>
#include "TClass.h"
#include "CustomSensor.h"

class TUltrasonic : public TCustomSensor {		//HCSR04
protected:
	static constexpr  uint16_t MIN_RANGE = 5U;
	static constexpr  uint16_t MAX_RANGE = 400U;
	static constexpr  uint32_t SOUND_SPEED = 343UL;
	static constexpr  uint32_t DIVIDER = 20000UL;
	static constexpr  uint32_t TIMEOUT = 60000;

	const uint8_t FSendPin;
	const uint8_t FEchoPin;
	int8_t FTemp;
	uint16_t FValue;

	void init(void) override {
		pinMode(FSendPin, OUTPUT);
		digitalWrite(FSendPin, LOW);
		pinMode(FEchoPin, INPUT_PULLUP);
		FInitNeed = false;
	}

	void internalRead(void) override {
		uint16_t dur = 0;

		uint8_t sreg = SREG;
		cli();

		digitalWrite(FSendPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(FSendPin, LOW);

		dur = pulseIn(FEchoPin, HIGH, TIMEOUT);

		uint32_t l = SOUND_SPEED*dur/DIVIDER;

		if (FValue != l) {

			FValue = l;

			PostMessage(msg_SensorValueChanged, FValue);
		}

		SREG = sreg;
	}

/*
uint16_t HCSR04::getEchoPulseLength(void)
{
  uint16_t pLength = 0;                           //in ?s

	digitalWrite(_triggerPin, HIGH);
	delayMicroseconds(10);                          //length of triger pulse, 100?s maximum
	digitalWrite(_triggerPin, LOW);                 //300..500?s after trigger low, module during next 200?s sends 8 pulses at 40 kHz & measures echo

	pLength = pulseIn(_echoPin, HIGH, _timeOutMax); //must be called at least a few dozen ?s before expected pulse, avarage tHOLLDOFF=700?s

	if ((pLength == 0) || (pLength <= _timeOutMin) || (pLength >= _timeOutMax)) return HCSR04_OUT_OF_RANGE;
	return pLength;
}

*/


public:
	TUltrasonic(const uint8_t ASendPin, const uint8_t AEchoPin, const int8_t ATemp=25) : FSendPin(ASendPin), FEchoPin(AEchoPin) {
		SetTemperature(ATemp);
		FReadInterval = 500;
		classname = F("HC-SR04");
	}

	uint16_t GetValue(void) const {
		return FValue;
	}

	void SetTemperature(const int8_t ATemp) {
		FTemp = ATemp;
	}

};