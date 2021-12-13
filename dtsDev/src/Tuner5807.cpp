// 
// 
// 

#include <Arduino.h>
#include <DEF_Message.h>
#include <Messages.h>
#include <Wire.h>
#include "Tuner5807.h"


#define RDA5807M_REG_CONFIG 0x02
#define RDA5807M_REG_TUNING 0x03
#define RDA5807M_REG_VOLUME 0x05
#define RDA5807M_REG_RSSI   0x0B
// флаги
#define RDA5807M_FLG_DHIZ 0x8000
#define RDA5807M_FLG_DMUTE 0x4000
#define RDA5807M_FLG_BASS 0x3000
#define RDA5807M_FLG_ENABLE word(0x0001)
#define RDA5807M_FLG_TUNE word(0x0010)
#define RDA5807M_FLG_MONO word(0x2000)

//маски
#define RDA5807M_CHAN_MASK 0xFFC0
#define RDA5807M_CHAN_SHIFT 6
#define RDA5807M_VOLUME_MASK word(0x000F)
#define RDA5807M_VOLUME_SHIFT 0
#define RDA5807M_RSSI_MASK 0xFE00
#define RDA5807M_RSSI_SHIFT 9


void TTuner5807::WriteRegister(const uint8_t ARegNum, const uint16_t ARegValue)
{
		Wire.beginTransmission(FDevAddr);
		Wire.write(ARegNum);
		Wire.write(highByte(ARegValue));
		Wire.write(lowByte(ARegValue));
		Wire.endTransmission();
}

uint16_t TTuner5807::ReadRegister(const uint8_t ARegNum)
{
	uint16_t result;
	
	Wire.beginTransmission(FDevAddr);
	Wire.write(ARegNum);
	Wire.endTransmission();

	Wire.requestFrom(FDevAddr, 2U);
	
	result = Wire.read();
	result <<= 8;
	result |= (Wire.read());

	return result;
}

void TTuner5807::CheckStatus(const uint16_t AStatusA, const uint16_t AStatusB)
{
	uint8_t val = (AStatusB >> 9) & 0x7F;      // RSSI Check
	uint8_t old = (FLastStatusB >> 9) & 0x7F;
	if (val != old) SendMessage(msg_StatusChanged, info_RSSI, val);

	val = (AStatusB >> 8) & 0x01;     // Tuned flag
	old = (FLastStatusB >> 8) & 0x01;
	if (val != old) SendMessage(msg_StatusChanged, info_TUNED, val);

	val = (AStatusA >> 10) & 0x01;
	old = (FLastStatusA >> 10) & 0x01;
	if (val != old) SendMessage(msg_StatusChanged, info_STEREO, val);
}

TTuner5807::TTuner5807(const uint8_t ADevAddr)
{
	FDevAddr = ADevAddr;
	FLastReadTime = 0;
	FLastStatusA = 0;
	FLastStatusB = 0;
}

void TTuner5807::Init(const uint16_t AStartFreq)
{
	Wire.begin();

	// Регистр 02h - включение, настройки
	reg02h = RDA5807M_FLG_ENABLE | RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE;
	WriteRegister(2, reg02h);

	SetFreq(AStartFreq);
}

void TTuner5807::SetFreq(const uint16_t ANewFreq)
{
	if ((ANewFreq < MIN_FREQ) || (ANewFreq > MAX_FREQ)) return;

	if (freq == ANewFreq) return;

	freq = ANewFreq;

	// Регистр 03h - выбор радиостанции
	// После сброса в регистре 03h значение по умолчанию - 0
	// Таким образом BAND = 00 (87..108МГц), STEP = 00 (100кГц). Оставим их как есть
	
	reg03h = (freq - 870) << RDA5807M_CHAN_SHIFT; // chan = (freq - band) / space
	WriteRegister(RDA5807M_REG_TUNING, reg03h | RDA5807M_FLG_TUNE);

}

void TTuner5807::SetVolume(const uint16_t AVolume)
{
	reg05h=ReadRegister(5);

	reg05h &= 0xFFF0;
	reg05h |= (AVolume & 0x0F);
	WriteRegister(5, reg05h);
}

void TTuner5807::SetExtraBass(const bool AExtra)
{
	reg02h = ReadRegister(2);
	if (AExtra)
		reg02h |= RDA5807M_FLG_BASS;
	else
		reg02h &= ~RDA5807M_FLG_BASS;

	WriteRegister(2, reg02h);
}

void TTuner5807::SetMono(const bool AForcedMono)
{
	reg02h = ReadRegister(2);
	if (AForcedMono)
		reg02h |= RDA5807M_FLG_MONO;
	else
		reg02h &= ~RDA5807M_FLG_MONO;
	WriteRegister(2, reg02h);
}

void TTuner5807::ReadStatus(void)
{
	uint32_t now = millis();
	if (now - FLastReadTime < 1000) return;

	FLastReadTime = now;
	uint16_t valueA = ReadRegister(0x0A);
	uint16_t valueB = ReadRegister(0x0B);

	if ((FLastStatusA != valueA) || (FLastStatusB != valueB)) {
		CheckStatus(valueA, valueB);
		FLastStatusA = valueA;
		FLastStatusB = valueB;
	}
}
