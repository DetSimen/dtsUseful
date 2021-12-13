#pragma once

#include <Arduino.h>
#include <I2CSensor.h>


class TBMPE280 : public TI2CCustomSensor {
public:
	enum class TDeviceType: uint8_t {Unknown, BMP280, BME280} DevType;

	enum class TSampling : uint8_t {
		None = 0x00,
		X1 = 0x01,
		X2 = 0x02,
		X4 = 0x03,
		X8 = 0x04,
		X16 = 0x05
	};

    enum class TMode : uint8_t {
        Sleep       = 0x00,
        Forced      = 0x01,
        Normal      = 0x02,
        SoftReset   = 0x03
    };

    enum class TFiltering : uint8_t {
        Off = 0x00,
        X2  = 0x01,
        X4  = 0x02,
        X8  = 0x03,
        X16 = 0x04
    };

    enum class TStandby : uint8_t {
        MS1     = 0x00,
        MS62    = 0x01,
        MS125   = 0x02,
        MS250   = 0x03,
        MS500   = 0x04,
        MS1000  = 0x05,
        MS2000  = 0x06, 
        MS4000  = 0x07
    };



	static constexpr uint8_t DEV_DEFAULT_ADDRESS	= 0x77;
	static constexpr uint8_t DEV_ALTERNATE_ADDRESS	= 0x76;

	static constexpr uint8_t DEV_CHIPID = 0x58;

protected:
	TDeviceType FDevType;
	TSampling	FSampling = TSampling::None;

	void init(void) override {

	}

public:
	TBMPE280(const uint8_t ADevAddr = DEV_DEFAULT_ADDRESS, const TDeviceType ADevType = TDeviceType::BMP280)
        : TI2CCustomSensor::TI2CCustomSensor(ADevAddr) 
    {
        FDevType = ADevType;
	}


};
