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
    /**
     * Sends signal that item was moved
     */
    void sendItemMovedSignal();
    /**
     * Sends signal that all item's fields were updated except location
     */
    void sendUpdateExceptLocation();
    /**
     * Sends signal that item was rotated
     */
    void sendUpdateRotationAngle();
signals:
    /**
     * Signal informs that item was moved
     */
    void itemMoved();
    /**
     * Signal informs that all item's fields were updated except location
     */
    void updateExceptLocation();
    /**
     * Signal informs that item was rotated
     */
    void updateRotationAngle();
};

#endif // SIGNALSENDER_H
