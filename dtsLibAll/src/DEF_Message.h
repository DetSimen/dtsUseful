#pragma once

/*    LCD 1602  Volume Meter Symbols
*
uint8_t Sim[] = { 0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x1F };
uint8_t Sim[] = { 0x1F,0x00,0x1F,0x1F,0x1F,0x1F,0x00,0x1F };
uint8_t Sim[] = { 0x1F,0x04,0x04,0x04,0x04,0x04,0x04,0x1F };
uint8_t Sim[] = { 0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x1F };
uint8_t Sim[] = { 0x1F,0x10,0x17,0x17,0x17,0x17,0x10,0x1F };
uint8_t Sim[] = { 0x1F,0x01,0x1D,0x1D,0x1D,0x1D,0x01,0x1F };
*
*/

#define DEF_MESSAGE_UNIT

// system messages

#define  msg_Empty				0x00
#define  msg_Error				0x01
#define  msg_CriticalError		0x02
#define  msg_OutOfMemory		0x03
#define  msg_WrongIndex			0x04
constexpr uint8_t msg_WDT		= 0x05;

#define  msg_Paint				0x06


#define  msg_PCINTChanged		0x07		// изменился уровень на ноге PCINT
#define  msg_VCC_Changed		0x08		// напряжение питания изменилось
#define  msg_Sleep				0x09		// отправить CPU в сон
#define	 msg_WakeUp				0x0A		// CPU проснулося

// сообщения приложения

#define  msg_AppStateChanged	0x17		// состояние приложения изменено
#define  msg_Command			0x18		// приложение: выполнить команду

// user messages

#define msg_SerialRead			0x20	// читать из сериал
#define msg_SerialLineEnd		0x21
#define msg_SerialClear			0x22
#define msg_SerialSend			0x23

#define msg_SoftSerialRead		0x24
#define msg_SoftSerialLineEnd	0x25
#define msg_SoftSerialClear		0x26
#define msg_SofterialSend		0x27


#define msg_Alarm				0x2A
#define msg_AlarmUnderflow		0x2B
#define msg_AlarmOverflow		0x2C


#define msg_OneSecondTick		0x30	// тик раз в секунду
#define msg_HalfSecondTick		0x31	// тик раз в полсекунды

#define msg_SecondsChanged		0x32	// секунды изменились
#define msg_TimeChanged			0x33    // минуты изменились
#define msg_TemperatureChanged  0x34	// температура изменилась
#define msg_TempChanged         0x34    
#define msg_HumidityChanged		0x35	// влажность изменилась

#define msg_DateChanged			0x36	// дата изменилась

#define msg_TimerEnd			0x37    // таймер дощитал до 0
#define msg_TimeAlarmOn			0x38	// Включился будильнег времени
#define msg_TimeAlarmOff		0x39	// Выключился будильник времени

#define msg_Timeout				0x3A    // заданный интервал времени истёк
#define msg_CounterTick			0x3B    // таймер тикнул один раз
#define msg_CounterEnd			0x3C	// счетчик кончился
#define msg_SoftTimerEnd		0x3D	// Soft Timer тикнул


#define msg_ReadKeyboard		0x40	// опросить клаву
#define msg_KeyDown				0x41
#define msg_Key_Up				0x42
#define msg_KeyPress			0x43
#define msg_LongPress			0x44	// долгое нажатие

#define msg_MenuChoice			0x50    // выбран пункт меню

#define msg_SensorValueChanged	0x60
#define msg_SensorStateChanged	0x61	//
#define msg_SelectorChanged		0x62    // положение селектора изменилось
#define msg_ShakeDetected		0x63	// датчик удара чуть потрясся

// encoder 
#define msg_EncoderLeft			0x70
#define msg_EncoderRight		0x71
#define msg_EncoderBtnPress		0x72
#define msg_EncoderBtnLong		0x73

#define msg_ModuleStateChanged  0x80
#define msg_StatusChanged		0x81



#define msg_DeviceStateChanged  0xA0    // состояние исполнительного устройства изменилось
#define msg_MotorRunning		0xA1


