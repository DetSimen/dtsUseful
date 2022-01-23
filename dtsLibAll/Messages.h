#pragma  once
#include <Arduino.h>
#include "Types.h"


struct TMessage;


class  TMessageList;
using  PMessageList = TMessageList*;


#pragma pack(push,1)

struct TMessage
{
protected:
 TMessage() = delete;// :TMessage(msg_Empty) {};
public:
	uint16_t		Message;
	NativeInt		LoParam;
	NativeInt		HiParam;
	NativeUInt	    Sender;

	TMessage(int16_t AMsg, NativeInt ALoParam = 0, NativeInt AHiParam = 0, NativeUInt ASender = 0) {
		Message = AMsg;
		LoParam = ALoParam;
		HiParam = AHiParam;
		Sender = ASender;
	}
};
#pragma pack(pop)

using PMessage = TMessage*;  // pointer to TMessage


class TMessageList
{
protected:
	PMessage	*Items;

	uint8_t		FSize;
	uint8_t		FCount;
	
	void     DeleteFirst(void){
		if (FCount > 0) {
			for (uint8_t i = 1; i < FCount; ++i) Items[i - 1] = Items[i];
			Items[--FCount] = NULL;
			
		}
	}


public:

	TMessageList() :TMessageList(15) {};

	TMessageList(uint8_t ASize) {

		Items = new PMessage[FSize = ASize];
		for (uint8_t i = 0; i < FSize; ++i) Items[i] = NULL;

		FCount = 0;
	}


	operator bool(void) const {
		return (FCount > 0);
	}

	TMessage GetMessage(void)
	{
		TMessage msg = *Items[0];
		free(Items[0]);
		DeleteFirst();
		return msg;
	}

	void Add(const PMessage pmsg){

		
		if (pmsg != NULL) {

			if (FCount < FSize)
				Items[FCount++] = pmsg;
			else
				free(pmsg);
		}

	}

	void Add(uint16_t AMsg, NativeInt ALoParam = 0, NativeInt AHiParam = 0, NativeUInt AClass = 0) {
		Add(new TMessage(AMsg, ALoParam, AHiParam, AClass));
	}

	bool Available() const {
		return (FCount > 0);
	}

};

extern void SendMessage(const uint16_t, const NativeInt = 0, const NativeInt = 0);
extern void SendClassMessage(const uint16_t, const NativeInt = 0, const NativeInt = 0, NativeUInt = 0U);
