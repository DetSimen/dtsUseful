// Tuner5807.h
#pragma once

#include <Arduino.h>

constexpr uint8_t info_TUNED	= 0x01;
constexpr uint8_t info_RSSI		= 0x02;
constexpr uint8_t info_STEREO	= 0x03;

class TTuner5807 {
public:
	static constexpr	uint8_t		DEFAULT_ADDRESS = 0x11;
	static constexpr	uint16_t	MIN_FREQ = 880;
	static constexpr	uint16_t	MAX_FREQ = 1080;

protected:
	uint8_t		FDevAddr;
	bool		FError;
	uint32_t	FLastReadTime;
	uint16_t	FLastStatusA;
	uint16_t	FLastStatusB;

	uint16_t reg02h, reg03h, reg05h,  reg0Bh, freq;

	void	WriteRegister(const uint8_t ARegNum, const uint16_t ARegValue);

	uint16_t ReadRegister(const uint8_t ARegNum);

	void	CheckStatus(const uint16_t AStatusA, const uint16_t AStatusB);
public:
	TTuner5807() : TTuner5807(DEFAULT_ADDRESS) {}
	TTuner5807(const uint8_t ADevAddr);

	void	Init(const uint16_t AStartFreq = 0);

	void	SetFreq(const uint16_t ANewFreq);

	void	SetVolume(const uint16_t AVolume);

	void	SetExtraBass(const bool AExtra = true);

	void	SetMono(const bool AForcedMono = true);

	void	ReadStatus(void);

	void	Write07(const uint16_t AValue = 0);
};
