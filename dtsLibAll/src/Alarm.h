#pragma once
#include <Arduino.h>
#include <TClass.h>
#include <DEF_Message.h>

enum class TAlarmType : uint8_t { Off = 0, Min, Max, Both = 3 };

template<typename T>
class TAlarm: public TClass {
protected:
	struct {
		TAlarmType	OldState  : 2;
		TAlarmType	AlarmType : 2;
	};
	T	FMinValue;
	T   FMaxValue;

	void CheckMin(const T AValue) {
		if (AValue < FMinValue) PostMessage(msg_AlarmUnderflow);
	}

	void CheckMax(const T AValue) {
		if (AValue > FMaxValue) PostMessage(msg_AlarmOverflow);
	}

public:
	TAlarm() {
		AlarmType = TAlarmType::Off;
		FMinValue = T();
		FMaxValue = T();
	}

	TAlarm(const T AMinValue, const T AMaxValue) {
		OldState = TAlarmType::Off;
		SetAlarm(AMinValue, AMaxValue);
	}

	void SetAlarmMin(const T AMinValue) {
		AlarmType = TAlarmType::Min;
		FMinValue = AMinValue;
		FMaxValue = T();
	}

	void SetAlarmMax(const T AMaxValue) {
		AlarmType = TAlarmType::Max;
		FMaxValue = AMaxValue;
		FMinValue = T();
	}

	void SetAlarmEqual(const T AValue) {
		AlarmType = TAlarmType::Both;
		FMinValue = FMaxValue = AValue;
	}

	void SetAlarm(const T AMinValue, const T AMaxValue) {
		AlarmType = TAlarmType::Both;
		FMinValue = AMinValue;
		FMaxValue = AMaxValue;
	}

	void AlarmStop(void) {
		OldState = AlarmType;
		AlarmType = TAlarmType::Off;
	}

	void AlarmStart(void) {
		AlarmType = OldState;
	}

	void Check(const T AValue) {
		if (AlarmType == TAlarmType::Off) return;

		if ((AlarmType == TAlarmType::Min) || (AlarmType == TAlarmType::Both)) CheckMin(AValue);
		if ((AlarmType == TAlarmType::Max) || (AlarmType == TAlarmType::Both)) CheckMax(AValue);

		if ((FMinValue == FMaxValue) && (AValue == FMinValue)) PostMessage(msg_Alarm, int16_t(AValue));
	}

};
