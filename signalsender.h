#ifndef SIGNALSENDER_H
#define SIGNALSENDER_H

#include <QObject>

class SignalSender : public QObject
{
Q_OBJECT
public:
    SignalSender();
    void sendItemMovedSignal();
    void sendUpdateExceptLocation();
signals:
    void itemMoved();
    void updateExceptLocation();
};

#endif // SIGNALSENDER_H
