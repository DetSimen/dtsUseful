#pragma once
#include <Arduino.h>
#include "OneWire.h"
#include "Consts.h"
#include "DEF_Errors.h"
#include "CustomSensor.h"
#include "TClass.h"
#include "Messages.h"
#include "DEF_Errors.h"

//
//   константы
//
const uint8_t  ID_DS18B20			= 0x28;   // Идентификатор Далласа начинается с 0x28
const uint8_t  DALLAS_MEMORY_SIZE	= 9;      // Размер памяти датчика, включая CRC

//
//   команды
//
const uint8_t	CMD_SKIP_ROM  = 0xCC;  // обратиться ко всем даччикам на одной шине
const uint8_t	CMD_READ_RAM  = 0xBE;
const uint8_t	CMD_READ_ID   = 0x33;  // прочитать идентификатор Далласа, все 8 байт
const uint8_t	CMD_WRITE_MEM = 0x4E;  // записывает 3 байта в память Далласа
const uint8_t	CMD_COPY_MEM  = 0x48;
const uint8_t	CMD_RESET     = 0xB8;

const uint8_t	CMD_START_CONVERSION = 0x44; // начать преобразование температуры
//const uint8_t	CMD_READ_POWER_MODE  = 0xB4; // чтение режима питания


enum class T18B20Resolution :uint8_t { Res9bit = 0, Res10bit = 1, Res11bit = 2, Res12bit = 3 };
static constexpr uint16_t ResReadTimes[] PROGMEM = { 150, 250, 450, 900 };


//
//   сам  класик для одного Dallas на проводе
//
class TDS18B20: public TCustomSensor {
protected:


	OneWire		*FOneWire;
	uint8_t		*FDallasMemory;
	int8_t		FTemperature;

	void startConversion(void) {
		FOneWire->reset();
		FOneWire->write(CMD_SKIP_ROM);
		FOneWire->write(CMD_START_CONVERSION);
		FOneWire->reset();
		FLastReadTime = millis();
	}

	void internalRead() override {

		if (ReadData()) {

			int8_t temp = (FDallasMemory[1] << 4) | (FDallasMemory[0] >> 4);

			if (temp == FTemperature) return;

			FTemperature = temp;
			PostMessage(msg_TemperatureChanged, FTemperature);
		}
		else 	
			Error(err_OneWire_CRCError);

	}


	bool CheckDevicePresent(void) {
		if (FOneWire == NULL) return false;

		FOneWire->reset();
		FOneWire->write(CMD_READ_ID);

		uint8_t id = FOneWire->read();
		
		FOneWire->reset();
		
		return (id == ID_DS18B20);
	}

	void init(void) override {
	
		FInitNeed = false;

		if (CheckDevicePresent()) {
//			SetResolution(T18B20Resolution::Res12bit);
			startConversion();
		}
		else {	
			Error(err_DeviceNotFound);
		}
	}

	bool ReadData(void) {

		FOneWire->reset();
		FOneWire->write(CMD_SKIP_ROM);
		FOneWire->write(CMD_READ_RAM);
		FOneWire->read_bytes(FDallasMemory, DALLAS_MEMORY_SIZE);
		FOneWire->reset();
		startConversion();

		uint8_t crc = OneWire::crc8(FDallasMemory, DALLAS_MEMORY_SIZE - 1);

		return (crc == FDallasMemory[DALLAS_MEMORY_SIZE - 1]);
	}


public:
	TDS18B20(uint8_t ADallasPin) {
		FOneWire = new OneWire(ADallasPin);
		FDallasMemory = new uint8_t[DALLAS_MEMORY_SIZE];
		FError = (FDallasMemory == NULL) || (FOneWire == NULL);
		FTemperature = INVALID_TEMPERATURE;
		FReadInterval = ResReadTimes[3];
		FLastReadTime = 0 - FReadInterval - 1;
		classname = F("DS18B20");

	}

	~TDS18B20() {
		delete[] FDallasMemory;
		delete FOneWire;
	}


	inline int8_t GetTemperature(void) const { 
		return FTemperature; 
	};
/*
	void SetResolution(const T18B20Resolution AValue) {

		Read();
		uint8_t mask = static_cast<uint8_t>(AValue);
		FReadInterval = (uint32_t)(ResReadTimes[mask]);
		FDallasMemory[4] =  (mask << 5) | 0b00011111;
		
		FOneWire->reset();					// сохраним
		FOneWire->write(CMD_WRITE_MEM);
		FOneWire->write(FDallasMemory[2]);
		FOneWire->write(FDallasMemory[3]);
		FOneWire->write(FDallasMemory[4]);  // здесь сохраняется разрешение даччика
		FOneWire->reset();
	}
*/

};
