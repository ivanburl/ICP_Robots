#include "robot.h"
#include "qdebug.h"
#include "room.h"

#define USE_MATH_DEFINES
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <cmath>

const QBrush Robot::DEFAULT_ROBOT_BRUSH = QBrush(Qt::blue);
const QBrush Robot::DEFAULT_ROBOT_ARC_BRUSH = QBrush(Qt::yellow);
const QBrush Robot::DEFAULT_ROBOT_INTERSECTION_BRUSH = QBrush(Qt::red);
const QBrush Robot::DEFAULT_ROBOT_CONTROLLED_BRUSH = QBrush(Qt::green);
const QBrush Robot::DEFAULT_ROBOT_ROTATING_BRUSH = QBrush(Qt::magenta);

void Robot::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    auto savePoint = this->pos();
    signalSender->sendItemMovedSignal();
    QGraphicsItemGroup::mouseMoveEvent(event);
    if (isOutOfRoom()) {
        this->setPos(savePoint);
    }
}

void Robot::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (isPaused()) return;
    toggleControl();
    QGraphicsItemGroup::mouseDoubleClickEvent(event);
}

void Robot::keyPressEvent(QKeyEvent *event) {
    currentPressedKey = event->key();
    QGraphicsItemGroup::keyPressEvent(event);
}

void Robot::keyReleaseEvent(QKeyEvent *event) {
    currentPressedKey = -1;
    QGraphicsItemGroup::keyReleaseEvent(event);
}

void Robot::takeControl() {
    this->setFocus();
    this->isControlled = true;
    this->currentPressedKey = -1;
}

void Robot::toggleControl() {
    if (this->isControlled) {
        releaseControl();
    } else {
        takeControl();
    }
}

void Robot::releaseControl() {
    this->isControlled = false;
    this->clearFocus();
    this->currentPressedKey = -1;
}

double Robot::getRobotRadius() const {
    return this->radius;
}

double Robot::getRobotMovementSpeed() const {
    return this->movementSpeed;
}

double Robot::getRobotRotationSpeed() const {
    return this->rotationSpeedInDegree;
}

double Robot::getRobotRotationSample() const {
    return this->rotationDegreeSample;
}

double Robot::getArcRadius() const {
    return this->arcRadius;
}

double Robot::getArcExtent() const {
    return this->arcDegree;
}

double Robot::getRobotCenterX() const {
    return this->scenePos().x();
}

double Robot::getRobotCenterY() const {
    return this->scenePos().y();
}

void Robot::setRobotCenterX(double x) {
    //this->setPos(200, 200);
    this->setPos(x, getRobotCenterY());
}

void Robot::setRobotCenterY(double y) {
    //this->setPos(200, 200);
    this->setPos(getRobotCenterX(), y);
}

void Robot::setArcRadius(double radius) {
    this->arcRadius = radius;
    this->arcItem->setRect(
        -getArcRadius(), -getArcRadius(),
        2 * getArcRadius(), 2 * getArcRadius());
}

void Robot::setRobotRadius(double robotRadius) {
    this->radius = robotRadius;
    this->robotFrameItem->setRect(
        -getRobotRadius(),-getRobotRadius(),
        getRobotRadius() * 2, getRobotRadius() * 2);
}

void Robot::setArcExtent(double arcExtent) {
    this->arcDegree = arcExtent;
    arcItem->setStartAngle(getArcExtent() * 8);
    arcItem->setSpanAngle(getArcExtent() * 16);
}

void Robot::setRobotMovementSpeed(double speedPerSec) {
    this->movementSpeed = speedPerSec;
}

void Robot::setRobotRotationSpeed(double degreePerSec) {
    this->rotationSpeedInDegree = degreePerSec;
}

void Robot::setRobotRotationSample(double degree) {
    this->rotationDegreeSample = degree;
}

void Robot::setRotationAngle(double angle) {
    double rotateAngle = angle - getRotationAngle();
    rotateOnAngle(rotateAngle);
}


QGraphicsEllipseItem *Robot::getRobotFrameItem() const {
    return this->robotFrameItem;
}

QGraphicsEllipseItem *Robot::getRobotArcItem() const {
    return this->arcItem;
}

SignalSender *Robot::getSignalSender() const
{
    return signalSender;
}

void Robot::rotateOnAngle(double angleInDegree) {
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
    this->isControlled = false;
    this->currentPressedKey = -1;
    this->rotationDegreeSample = rotationSmaple;
    this->movementSpeed = movementSpeed;
    this->rotationSpeedInDegree = rotationSpeedPerSecond;
    this->radius = radius;
    this->arcRadius = arcRadius;
    this->arcDegree = arcDegree;
    this->leftToTurn = 0;
    this->releaseControl();
    this->signalSender = new SignalSender();

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
    this->setPos(x, y);

    this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);

    this->robotFrameItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->arcItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

Robot::~Robot() {
    delete arcItem;
    delete robotFrameItem;
}

bool Robot::moveOnDistance(double distance) {
    QTransform transform = QTransform().translate(distance, 0);
    this->setTransform(transform, true);

    signalSender->sendItemMovedSignal();

    if (isColliding() || isOutOfRoom()) {
        this->setTransform(transform.inverted(), true);
        return false;
    }
    qDebug() << getRobotCenterX() << " " << getRobotCenterY();
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

bool Robot::isRotating() const {
    if (abs(leftToTurn) <= 0.1) {
        return false;
    }

    return true;
}

RobotDto *Robot::GetDtoObject() {
    return new RobotDto(this->getBaseX(), this->getBaseY(), radius,
                        arcRadius, arcDegree,
                        -getRotationAngle(),
                        movementSpeed, rotationDegreeSample,
                        rotationSpeedInDegree);
}

double Robot::getRotationAngle() const {
    double angleRadians = std::atan2(this->transform().m12(), this->transform().m11());
    double angleDegrees = angleRadians * (180 / M_PI);
    return angleDegrees;
}

Robot *Robot::fromDtoObject(RobotDto dtoObject, Room *room) {
    return new Robot(room, dtoObject.getX(), dtoObject.getY(),
                     dtoObject.getRadius(), dtoObject.getArcRadius(),
                     dtoObject.getArcDegree(), dtoObject.getCurrentAngleInDegrees(),
                     dtoObject.getMovementSpeed(), dtoObject.getRotationSample(),
                     dtoObject.getRotationSpeedInDegree());
}

void Robot::update(long long deltaMilliseconds) {
    auto defaultBrush = isControlled ? DEFAULT_ROBOT_CONTROLLED_BRUSH : DEFAULT_ROBOT_BRUSH;

    if (isOutOfRoom() || isColliding()) {
        this->robotFrameItem->setBrush(DEFAULT_ROBOT_INTERSECTION_BRUSH);
    } else {
        if (leftToTurn > 0) {
            this->robotFrameItem->setBrush(Qt::magenta);
        } else {
            this->robotFrameItem->setBrush(defaultBrush);
        }
    }

    if (hasDetected()) {
        this->arcItem->setBrush(DEFAULT_ROBOT_INTERSECTION_BRUSH);
    } else {
        this->arcItem->setBrush(DEFAULT_ROBOT_ARC_BRUSH);
    }

    if (isControlled && !isPaused()) {
        if (isRotating()) return;
        switch (currentPressedKey) {
            case Qt::Key_Right:
                leftToTurn = abs(rotationDegreeSample);
                break;
            case Qt::Key_Left:
                leftToTurn = -abs(rotationDegreeSample);
                break;
            case Qt::Key_Up:
                moveOnDistance(deltaMilliseconds * movementSpeed / 1e3);
                break;
            case Qt::Key_Down:
                moveOnDistance(deltaMilliseconds * -movementSpeed / 1e3);
                break;
        }
    }


    if (isSelected() && isPaused()) {
        switch (currentPressedKey) {
            case Qt::Key_Right:
                rotateOnAngle(5);
                break;
            case Qt::Key_Left:
                rotateOnAngle(-5);
                break;
            case Qt::Key_Up:
                this->radius += this->radius * 0.05;
                break;
            case Qt::Key_Down:
                this->radius -= this->radius * 0.05;
                break;
        }

        switch (currentPressedKey) {
            case Qt::Key_W:
                this->arcRadius += this->arcRadius * 0.05;
                break;
            case Qt::Key_S:
                this->arcRadius -= this->arcRadius * 0.05;
                break;
            case Qt::Key_D:
                this->arcDegree += 5;
                break;
            case Qt::Key_A:
                this->arcDegree -= 5;
                break;
        }

        this->arcItem->setRect(-this->arcRadius, -this->arcRadius, this->arcRadius * 2, this->arcRadius * 2);
        this->robotFrameItem->setRect(-this->radius, -this->radius, this->radius * 2, this->radius * 2);

        arcItem->setStartAngle(-arcDegree * 8);
        arcItem->setSpanAngle(arcDegree * 16);

        this->currentPressedKey = -1;
    }
}

void Robot::fixedUpdate(long long deltaMilliseonds) {
    if (isPaused()) return;

    if (isRotating()) {
        double rotationAngle = std::min(deltaMilliseonds * rotationSpeedInDegree / 1e3, abs(leftToTurn));
        rotationAngle = leftToTurn < 0 ? -rotationAngle : rotationAngle;
        rotateOnAngle(rotationAngle);
        leftToTurn = leftToTurn - rotationAngle;
        return;
    }

    if (isControlled) return;
    if (hasDetected() || !moveOnDistance(deltaMilliseonds * movementSpeed / 1e3)) {
        leftToTurn = rotationDegreeSample;
        update(deltaMilliseonds);
        return;
    }
}
