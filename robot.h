#ifndef ROBOT_H
#define ROBOT_H

#include "updatable_entity.h"

#include <QBrush>
#include <QGraphicsItem>

class Room;

class Robot : public QGraphicsItemGroup, UpdatableEntity
{
public:
    static QBrush DEFAULT_ROBOT_BRUSH;
    static QBrush DEFAULT_ROBOT_ARC_BRUSH;
    static QBrush DEFAULT_ROBOT_INTERSECTION_BRUSH;
private:
    double radius;
    double arcRadius;
    double arcDegree;
    double currentAngleInDegrees;
    double movementSpeed;
    double rotationDegreeSample, rotationSpeedInDegree;
private:
    QGraphicsEllipseItem* robotShape;
    QGraphicsEllipseItem* arcShape;
private:
    Room* room;
private:
    double leftToTurn;
    Q_PROPERTY(int DEFAULT_ROBOT_COLOR READ getDEFAULT_ROBOT_COLOR CONSTANT FINAL)

public:
    Robot(Room* room,
            double x, double y, double radius,
            double arcRadius, double arcDegree,
            double angleInDeegrees, double movementSpeed,
            double rotationSmaple, double rotationSpeedPerSecond) {
        this->currentAngleInDegrees = angleInDeegrees;
        this->rotationDegreeSample = rotationSmaple;
        this->movementSpeed = movementSpeed;
        this->rotationSpeedInDegree = rotationSpeedPerSecond;
        this->radius = radius;
        this->arcRadius = arcRadius;

        this->room = room;
        robotShape = new QGraphicsEllipseItem(x - radius ,y - radius, radius * 2, radius * 2);
        arcShape = new QGraphicsEllipseItem(x - arcRadius,y - arcRadius, arcRadius * 2, arcRadius * 2);
        arcShape->setStartAngle(currentAngleInDegrees * 16 - arcDegree * 8);
        arcShape->setSpanAngle(arcDegree * 16);

        robotShape->setBrush(DEFAULT_ROBOT_BRUSH);
        arcShape->setBrush(DEFAULT_ROBOT_ARC_BRUSH);
        arcShape->setOpacity(0.8);

        this->addToGroup(robotShape);
        this->addToGroup(arcShape);
    }

    ~Robot() {
        delete robotShape;
        delete arcShape;
    }

    bool move(long deltaNanos);

    void rotate(long deltaNanos);

    bool hasDetected();
    bool isOutOfRoom();
    bool isColliding();

    void update(long deltaNanos) override;
    static int getDEFAULT_ROBOT_COLOR();
public:
    QGraphicsEllipseItem* getRobotFrameItem() {
        return this->robotShape;
    }
    QGraphicsEllipseItem* getRobotArcItem() {
        return this->arcShape;
    }
};

#endif // ROBOT_H
