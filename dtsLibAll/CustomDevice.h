#pragma once
#include <Arduino.h>
#include "TClass.h"
#include "DEF_Message.h"


enum class TDeviceState: uint8_t {Unknown, On, Off};


class TCustomDevice : public TClass {
protected:
	bool         FEnableChangeMsg;
	TDeviceState FDeviceState;

	virtual void On(void) = 0;
	virtual void Off(void) = 0;

	void    SetDeviceState(const TDeviceState ANewState) {
		if (FDeviceState == ANewState) return;
		FDeviceState = ANewState;
		if (FEnableChangeMsg) PostMessage(msg_DeviceStateChanged, static_cast<uint16_t>(FDeviceState));
	}

public:
	TCustomDevice(const bool AEnableMsg=false) {
		FEnableChangeMsg = AEnableMsg;
		FDeviceState = TDeviceState::Unknown;
		classname = F("CustomDevice");
	}

	void SetEnableSendChangeMessage(const bool AEnableSend) {
		FEnableChangeMsg = AEnableSend;
	}


	
};
