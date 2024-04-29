#include "robot.h"

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
    }
}

void Robot::turn(long deltaNanos) {
    currentAngleInDegrees += (rotationSpeedInDegree*deltaNanos)/1e9;
}


bool Robot::move(long deltaNanos) {
    return false;
}
