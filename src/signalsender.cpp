/*! VUT FIT ICP
 * @file signalsender.cpp
 * @brief signalsender.h implementation 
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "signalsender.h"

SignalSender::SignalSender() {}

void SignalSender::sendItemMovedSignal(){
    emit itemMoved();
}

void SignalSender::sendUpdateExceptLocation(){
    emit updateExceptLocation();
}

void SignalSender::sendUpdateRotationAngle(){
    emit updateRotationAngle();
}
