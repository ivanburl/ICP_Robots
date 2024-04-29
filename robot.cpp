#include "robot.h"
#include"room.h"

void  Robot::update(long deltaNanos) {
    if (leftToTurn!=0) {
        long requiredNanos = std::min(deltaNanos, (long) (leftToTurn*1e9/movementSpeed));
        turn(requiredNanos);
        leftToTurn = leftToTurn - requiredNanos * rotationSpeedInDegree;
        return;
    }

    if (!move(deltaNanos)) {
        leftToTurn = rotationDegreeSample;
        update(deltaNanos);
        return;
    }
}

void Robot::turn(long deltaNanos) {
    currentAngleInDegrees += (rotationSpeedInDegree*deltaNanos)/1e9;
}

bool Robot::move(long deltaNanos) {
    if (this->hasDetected()) return false;
    QTransfrom transform = QTransform().translate(1, 1);

}

bool Robot::hasDetected()
{
    return false;
}


