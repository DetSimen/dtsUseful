#pragma once

#define UNIT_ERRORS


static const int err_NoError			= 0x00;

static const int err_CriticalError		= -1;

static const int err_StackUnderflow		= 0x11;
static const int err_StackFull			= 0x12;
static const int err_WrongIndex			= 0x13;
static const int err_WrongMenu			= 0x14;
static const int err_RangeError			= 0x15;
static const int err_OutOfMemory		= 0x16;
static const int err_MemoryFull			= 0x19;
static const int err_UnhandledMsg		= 0x1A;
static const int err_InvalidHandle		= 0x1B;
static const int err_AppRunError		= 0x1C;
static const int err_AppAborted			= 0x1D;

// Devices errors
static const int err_DeviceNotInit		= 0x20;
static const int err_DeviceInitError	= 0x21;
static const int err_DeviceNotFound		= 0x22;
static const int err_CRCError			= 0x23;



//----------- I2C Errors

static const int err_i2c_NoAck			=	0x30;
static const int err_i2c_BufferOverload =	0x31;

static const int err_i2c_SendError		=	0x32;
static const int err_i2c_WriteError		=	0x32;

static const int err_i2c_ReceiveError	=	0x33;
static const int err_i2c_ReadError		=	0x33;

static const int err_i2c_AckError		=	0x34;
static const int err_i2c_CRCError		=	0x35;
static const int err_i2c_DeviceNotFound =	0x36;
static const int err_i2c_Timeout		=	0x37;
static const int err_i2c_ROMOutOfMemory =	0x38;


// other device error

static const int err_OneWire_DeviceNotFound = 0x40;
static const int err_OneWire_CRCError		= 0x42;
static const int err_OneWire_InvalidDevice	= 0x43;
static const int err_OneWire_ReadError		= 0x44;
 
// User errors

static const int err_InvalidTime = 0x87;
static const int err_InvalidAlarm = 0x88;

// Program errors

static const int err_ProgExecute = 0x90;

