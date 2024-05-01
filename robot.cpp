#include "robot.h"
#include "qdebug.h"
#include "room.h"

#define USE_MATH_DEFINES
#include <QGraphicsSceneMouseEvent>
#include <cmath>

QBrush Robot::DEFAULT_ROBOT_BRUSH = QBrush(Qt::blue);
QBrush Robot::DEFAULT_ROBOT_ARC_BRUSH = QBrush(Qt::yellow);
QBrush Robot::DEFAULT_ROBOT_INTERSECTION_BRUSH = QBrush(Qt::red);


// void Robot::update(long deltaNanos) {
//     if (leftToTurn >= 0) {
//         long requiredNanos = std::min(deltaNanos, (long) (leftToTurn * 1e9 / movementSpeed + 1));
//         rotate(requiredNanos);
//         leftToTurn = leftToTurn - requiredNanos * rotationSpeedInDegree;
//         return;
//     }
//
//     if (hasDetected()) {
//         arcItem->setBrush(DEFAULT_ROBOT_INTERSECTION_BRUSH);
//         leftToTurn = rotationDegreeSample;
//         update(deltaNanos);
//         return;
//     }
//
//
//     if (!move(deltaNanos)) {
//         robotFrameItem->setBrush(DEFAULT_ROBOT_INTERSECTION_BRUSH);
//         leftToTurn = rotationDegreeSample;
//         update(deltaNanos);
//         return;
//     }
//
//     arcItem->setBrush(DEFAULT_ROBOT_ARC_BRUSH);
//     robotFrameItem->setBrush(DEFAULT_ROBOT_BRUSH);
// }

void Robot::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    auto savePoint = this->pos();
    QGraphicsItemGroup::mouseMoveEvent(event);
    if (isOutOfRoom()) {
        this->setPos(savePoint);
    }
}

QGraphicsEllipseItem *Robot::getRobotFrameItem() const {
    return this->robotFrameItem;
}

QGraphicsEllipseItem *Robot::getRobotArcItem() const {
    return this->arcItem;
}

void Robot::rotate(long long deltaMilliseconds) {
    qreal angle = this->rotationSpeedInDegree * deltaMilliseconds / 1e3;
    rotateOnAngle(angle);
}

void Robot::rotateOnAngle(double angleInDegree)
{
    auto center = robotFrameItem->boundingRect().center();
    QTransform transform = QTransform()
                               .translate(center.x(), center.y())
                               .rotate(angleInDegree)
                               .translate(-center.x(), -center.y());
    this->setTransform(transform, true);
}

Robot::Robot(Room *room,
             double x, double y, double radius,
             double arcRadius, double arcDegree,
             double angleInDeegrees, double movementSpeed,
             double rotationSmaple, double rotationSpeedPerSecond) {
    this->rotationDegreeSample = rotationSmaple;
    this->movementSpeed = movementSpeed;
    this->rotationSpeedInDegree = rotationSpeedPerSecond;
    this->radius = radius;
    this->arcRadius = arcRadius;
    this->leftToTurn = 0;

    this->room = room;
    robotFrameItem = new QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2);
    arcItem = new QGraphicsEllipseItem(-arcRadius, -arcRadius, arcRadius * 2, arcRadius * 2);
    arcItem->setStartAngle(-arcDegree * 8);
    arcItem->setSpanAngle(arcDegree * 16);


    robotFrameItem->setBrush(DEFAULT_ROBOT_BRUSH);
    arcItem->setBrush(DEFAULT_ROBOT_ARC_BRUSH);
    arcItem->setOpacity(0.8);

    this->addToGroup(robotFrameItem);
    this->addToGroup(arcItem);

    this->rotateOnAngle(-angleInDeegrees);
    this->setPos(x - radius, y - radius);

    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

Robot::~Robot() {
    delete arcItem;
    delete robotFrameItem;
}

bool Robot::move(long long deltaMilliseconds) {
    double delta = movementSpeed * ((double)deltaMilliseconds) / 1e3;
    return moveOnDistance(delta);
}

bool Robot::moveOnDistance(double distance) {
    QTransform transform = QTransform().translate(distance,0);
    this->setTransform(transform, true);

    if (isColliding() || isOutOfRoom()) {
        this->setTransform(transform.inverted(), true);
        return false;
    }

    return true;
}

bool Robot::hasDetected() const {
    if (room == nullptr) return false;
    auto thisPath = arcItem->mapToScene(arcItem->shape());

    QVector<QPainterPath> pathes;
    for (const auto b: qAsConst(room->getBlock())) {
        pathes.append(b->mapToScene(b->shape()));
    }
    for (const auto r: qAsConst(room->getRobots())) {
        if (r == this) continue;
        pathes.append(r->mapToScene(r->getRobotFrameItem()->shape()));
    }
    for (const auto &p: pathes) {
        if (thisPath.intersects(p)) {
            return true;
        }
    }
    return false;
}

bool Robot::isOutOfRoom() const {
    if (room == nullptr)
        return false;

    auto pos = this->scenePos();

    if (!this->room->isPointInRoom(pos.x() - radius, pos.y() - radius) ||
        !this->room->isPointInRoom(pos.x() + radius, pos.y() + radius)) {
        return true;
    }

    return false;
}

bool Robot::isColliding() const {
    if (room == nullptr) return false;
    auto thisPath = robotFrameItem->mapToScene(robotFrameItem->shape());

    QVector<QPainterPath> pathes;
    for (const auto b: qAsConst(room->getBlock())) {
        pathes.append(b->mapToScene(b->shape()));
    }
    for (const auto r: qAsConst(room->getRobots())) {
        if (r == this) continue;
        pathes.append(r->mapToScene(r->getRobotFrameItem()->shape()));
    }
    for (const auto &p: pathes) {
        if (thisPath.intersects(p)) {
            return true;
        }
    }
    return false;
}

void Robot::update(long long deltaMilliseconds) {

    if (isOutOfRoom() || isColliding()) {
        this->robotFrameItem->setBrush(DEFAULT_ROBOT_INTERSECTION_BRUSH);
    } else {
        if (leftToTurn>0) {
            qDebug() << "changed color?? " << leftToTurn;
            this->robotFrameItem->setBrush(Qt::magenta);
        } else {
            this->robotFrameItem->setBrush(DEFAULT_ROBOT_BRUSH);
        }
    }

    if (hasDetected()) {
        this->arcItem->setBrush(DEFAULT_ROBOT_INTERSECTION_BRUSH);
    } else {
        this->arcItem->setBrush(DEFAULT_ROBOT_ARC_BRUSH);
    }


}

void Robot::fixedUpdate(long long deltaMilliseonds) {
    
    if (leftToTurn >= 0) {
        auto requiredMilliseconds = std::min(deltaMilliseonds, (long long) (leftToTurn * 1e3 / rotationSpeedInDegree + 1));
        rotate(requiredMilliseconds);
        leftToTurn = leftToTurn - ((double)requiredMilliseconds) / 1e3 * rotationSpeedInDegree;
        return;
    }

    if (hasDetected() || !move(deltaMilliseonds)) {
        leftToTurn = rotationDegreeSample;
        update(deltaMilliseonds);
        return;
    }
}
