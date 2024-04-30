#include "robot.h"
#include "qdebug.h"
#include "room.h"

#define _USE_MATH_DEFINES
#include <math.h>

QBrush Robot::DEFAULT_ROBOT_BRUSH = QBrush(Qt::blue);
QBrush Robot::DEFAULT_ROBOT_ARC_BRUSH = QBrush(Qt::yellow);
QBrush Robot::DEFAULT_ROBOT_INTERSECTION_BRUSH  = QBrush(Qt::red);


void  Robot::update(long deltaNanos) {
    if (leftToTurn>=0) {
        long requiredNanos = std::min(deltaNanos, (long) (leftToTurn*1e9/movementSpeed + 1));
        rotate(requiredNanos);
        leftToTurn = leftToTurn - requiredNanos * rotationSpeedInDegree;
        return;
    }

    if (hasDetected()) {
        arcShape->setBrush(DEFAULT_ROBOT_INTERSECTION_BRUSH);
        leftToTurn = rotationDegreeSample;
        update(deltaNanos);
        return;
    }


    if (!move(deltaNanos)) {
        robotShape->setBrush(DEFAULT_ROBOT_INTERSECTION_BRUSH);
        leftToTurn = rotationDegreeSample;
        update(deltaNanos);
        return;
    }

    arcShape->setBrush(DEFAULT_ROBOT_ARC_BRUSH);
    robotShape->setBrush(DEFAULT_ROBOT_BRUSH);
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
    double radians = currentAngleInDegrees/180 * M_PI;
    double delta = movementSpeed * deltaNanos / 1e9;
    QTransform transform = QTransform()
                               .translate(-delta * cos(radians),
                                          delta * sin(radians));
    this->setTransform(transform, true);

    if (isColliding()) {
        this->setTransform(transform.inverted(), true);
        return false;
    }

    if (isOutOfRoom()) {
        this->setTransform(transform.inverted(), true);
        return false;
    }
    return true;
}

bool Robot::hasDetected()
{
    if (room == nullptr) return false;
    auto shape = arcShape->shape();
    QVector<QPainterPath> pathes;
    for (const auto b: qAsConst(room->getBlock())) {
        pathes.append(b->shape());
    }
    for (const auto r: qAsConst(room->getRobots())) {
        if (r == this) continue;
        pathes.append(r->getRobotFrameItem()->shape());
    }
    for (const auto &p: pathes) {
        if (shape.intersects(p))
            return true;
    }
    return false;
}

bool Robot::isOutOfRoom()
{
    if (room == nullptr)
        return false;
    int width = room->width();
    int height = room->height();

    if (robotShape->x() + robotShape->boundingRect().width() > width ||
        robotShape->y() + robotShape->boundingRect().height() > height) {
        return true;
    }

    return false;
 }

bool Robot::isColliding()
{
    if (room == nullptr) return false;
    auto shape = robotShape->shape();
    QVector<QPainterPath> pathes;
    for (const auto b: qAsConst(room->getBlock())) {
        pathes.append(b->shape());
    }
    for (const auto r: qAsConst(room->getRobots())) {
        if (r == this) continue;
        pathes.append(r->getRobotFrameItem()->shape());
    }
    for (const auto &p: pathes) {
        if (shape.intersects(p))
            return true;
    }
    return false;
}


