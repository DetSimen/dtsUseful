#pragma once
#include "arduino.h"
#include <LiquidCrystal.h>
#include <TLed.h>
#include <AnalogKeys.h>

//#include <Generics.h>
//#include <Print.h>



class TKeyShield;
using PKeyShield = TKeyShield *;



class TKeyShield : public LiquidCrystal
{
protected:
	PLed		FBackLight;
	PAnalogKeys FKeys;
	
public:


	TKeyShield():LiquidCrystal::LiquidCrystal(8, 9, 4, 5, 6, 7){

		begin(16, 2);

		FBackLight = new TLed(10, ACTIVE_HIGH);

		FKeys = new TAnalogKeys(KEY_SHIELD, A0);

		clear();
		FBackLight->On();

	};

	~TKeyShield() {
		if (FBackLight != NULL) delete(FBackLight);
	};


	inline void BackOff() const { FBackLight->Off(); };
	inline void BackOn() const { FBackLight->On(); };

	void printColon(uint8_t acol, uint8_t arow, bool avisible) {
		setCursor(acol, arow);
		char ch = avisible ? ':' : ' ';
		print(ch);
	}

	void ReadKeys(void) {
		if (FKeys != NULL) FKeys->Read();
	}



};


