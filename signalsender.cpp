#include "signalsender.h"

SignalSender::SignalSender() {}

void SignalSender::sendItemMovedSignal()
{
    emit itemMoved();
}
