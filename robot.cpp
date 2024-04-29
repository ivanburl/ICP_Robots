#include "robot.h"
#include "qdebug.h"

#define _USE_MATH_DEFINES
#include <math.h>

QBrush Robot::DEFAULT_ROBOT_BRUSH = QBrush(Qt::blue);
QBrush Robot::DEFAULT_ROBOT_ARC_BRUSH = QBrush(Qt::yellow);

void  Robot::update(long deltaNanos) {
    if (leftToTurn!=0) {
        long requiredNanos = std::min(deltaNanos, (long) (leftToTurn*1e9/movementSpeed));
        rotate(requiredNanos);
        leftToTurn = leftToTurn - requiredNanos * rotationSpeedInDegree;
        return;
    }

    if (!move(deltaNanos)) {
        leftToTurn = rotationDegreeSample;
        update(deltaNanos);
        return;
    }
}

void Robot::rotate(long deltaNanos) {
    qreal angle  = this->rotationSpeedInDegree * deltaNanos / 1e9;
    auto center  = robotShape->boundingRect().center();
    QTransform transform = QTransform()
                               .translate(center.x(), center.y())
                               .rotate(angle)
                               .translate(-center.x(), -center.y());
    this->setTransform(transform, true);
    this->currentAngleInDegrees -= angle;
}

bool Robot::move(long deltaNanos) {
    if (this->hasDetected()) return false;

    double radians = currentAngleInDegrees/180 * M_PI;
    double delta = movementSpeed * deltaNanos / 1e9;
    QTransform transform = QTransform()
                               .translate(-delta * cos(radians),
                                          delta * sin(radians));
    this->setTransform(transform, true);
    return true;
}

bool Robot::hasDetected()
{
    return false;
}


