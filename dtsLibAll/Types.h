#pragma once 
#include <Arduino.h>
#include <inttypes.h>


#define UInt16Array(...) [](void)->uint16_t *{ static uint16_t _[] = {__VA_ARGS__}; return _; }()
#define IntArray(...) [](void)->int *{ static int _[] = {__VA_ARGS__}; return _; }()

using THandle = int8_t;				// тип аналог Handle Windows только для AVR


using pointer	= void *;			// указатель на ничто (нетипизированный указатель)

using char_p	= char *;			// указатель на однобайтовый char
using pchar_t	= char *;
using pchar		= char *;

using PErrorFunc	= void(*)(int);    // указатель на функцию обрабоччика ошибок, принимает int код ошибки
using pvfCallback	= void(*)(void);      // указатель на функцию без параметров, ничего не возвращающую: void AnyFunc(void) 
using pvfvCommand	= bool(*)(pointer);

#if defined(TINY)
  using ptrdiff_t = int16_t;
#endif


using NativeInt = ptrdiff_t;
using NativeUInt = size_t;

#ifdef __AVR__
using  PFlashString = const __FlashStringHelper*;  // указатель на строку в PROGMEM
#endif // __AVR__






