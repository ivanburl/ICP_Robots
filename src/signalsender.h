/*! VUT FIT ICP
 * @file signalsender.h
 * @brief Class for sending signals when game entities are somehow transformed 
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

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
