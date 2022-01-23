#pragma once
#include <Arduino.h>
#include "Types.h"
#include "Messages.h"
#include "DEF_Message.h"


class TClass;
using PClass = const TClass*;

extern TMessageList MessageList;


class TClass {
private:
protected:
	bool		FError:1;
	bool		FInitNeed : 1;

	PFlashString classname;
	
	virtual void Error(const int AErrorCode) {
		PostMessage(msg_Error, AErrorCode);
		FError = true;
	}

	inline bool isNeedInit(void) const { return FInitNeed; }

public:

	TClass() { 
		FError = false; 
		FInitNeed = false;
		classname = F("TClass");
	}

	virtual ~TClass() {}

	inline bool isError(void) const { return FError; }

	void PostMessage(const uint16_t AMessage, const NativeInt ALoParam = 0, const NativeInt AHiParam = 0) {
		SendClassMessage(AMessage, ALoParam, AHiParam, GetID());
	}

	inline PFlashString GetClassName(void) const {	return classname;}

	inline operator bool() const {return !FError;}

	inline NativeUInt GetID(void) const { return reinterpret_cast<size_t>(this); }

	operator NativeUInt() { return GetID(); }

};

