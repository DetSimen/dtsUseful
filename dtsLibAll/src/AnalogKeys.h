#pragma once
#include <Arduino.h>

#include <DEF_Keys.h>
#include <Messages.h>
#include <DEF_Message.h>
#include <AnalogSensor.h>
#include <Generics.h>

#pragma pack(push,1)
/*
const uint8_t key_Left  = 0x01;
const uint8_t key_Right = 0x02;
const uint8_t key_Up	= 0x03;
const uint8_t key_Down	= 0x04;
const uint8_t key_Set   = 0x05;
*/



struct TAnalogKeysStruct
{
public:
	uint16_t Value;
	uint8_t  Key;
};

TAnalogKeysStruct KEY_SHIELD[] = { 
	{503,key_Left},
	{15,key_Right},
	{153,key_Up},
	{332,key_Down},
	{738,key_Set}
};

class TAnalogKeys : public TAnalogSensor {
protected:
	const TAnalogKeysStruct *FKeyArray;
	const uint8_t			FKeySize;
	uint8_t					FLastKey = key_Null;

	void internalRead(void) override {
		uint16_t Val = readAnalogPin(FPin);
		if (FValue == Val) return;
		FValue = Val;
		uint8_t key = GetKey(FValue);
		if (FLastKey == key) return;
		if (key == key_Null) PostMessage(msg_KeyPress, FLastKey, 0);
		FLastKey = key;
	}

	uint8_t GetKey(const uint16_t AValue) {
		uint16_t minval = AValue - FGap;
		uint16_t maxval = AValue + FGap;

		for (uint8_t i = 0; i < FKeySize; ++i) {
			if (Between(FKeyArray[i].Value, minval, maxval)) return FKeyArray[i].Key;
		}

		return key_Null;
	}

public:
	template <uint8_t ASize> 
	TAnalogKeys(const TAnalogKeysStruct (&AKeyMatrix)[ASize], const uint8_t APin)
		: TAnalogSensor::TAnalogSensor(APin, true), FKeyArray(AKeyMatrix), FKeySize(ASize)
	{
		FGap = 5;
		FReadInterval = 125;
	}

	uint8_t SetGap(const uint8_t ANewGap) {
		uint8_t oldGap = FGap;
		if (ANewGap != FGap) FGap = ANewGap;
		return oldGap;
	}

};

using PAnalogKeys = TAnalogKeys*;

#pragma pack(pop)
