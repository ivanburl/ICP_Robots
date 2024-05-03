#ifndef SIGNALSENDER_H
#define SIGNALSENDER_H

#include <QObject>

class SignalSender : public QObject
{
Q_OBJECT
public:
    SignalSender();
    void sendItemMovedSignal();
signals:
    void itemMoved();
};

#endif // SIGNALSENDER_H
