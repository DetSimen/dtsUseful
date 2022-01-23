#include "src\Messages.h"
#include "src\SoftTimers.h"


extern TMessageList MessageList;


void SendMessage(const uint16_t AMessage, const NativeInt LoParam, const NativeInt HiParam)
{
	MessageList.Add(AMessage, LoParam, HiParam, 0U);
}

void SendClassMessage(const uint16_t Msg, const NativeInt LoParam, const NativeInt HiParam, NativeUInt Sender)
{
	MessageList.Add(Msg, LoParam, HiParam, Sender);
}
