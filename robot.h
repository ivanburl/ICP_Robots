#ifndef ROBOT_H
#define ROBOT_H

#include "updatable_entity.h"

#include <QGraphicsItem>

class Room;

class Robot : public QGraphicsItemGroup, UpdatableEntity
{
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
        robotShape = new QGraphicsEllipseItem(x,y, radius, radius);
        arcShape = new QGraphicsEllipseItem(x,y, arcRadius, arcRadius);
        arcShape->setStartAngle(currentAngleInDegrees/2);
        arcShape->setSpanAngle(arcDegree);

        this->addToGroup(robotShape);
        this->addToGroup(arcShape);
    }

    ~Robot() {
        delete robotShape;
        delete arcShape;
    }

    bool move(long deltaNanos);

    void turn(long deltaNanos);

    bool hasDetected();

    void update(long deltaNanos) override;
};

#endif // ROBOT_H
