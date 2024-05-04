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
    void sendUpdateRotationAngle();
signals:
    void itemMoved();
    void updateExceptLocation();
    void updateRotationAngle();
};

#endif // SIGNALSENDER_H
