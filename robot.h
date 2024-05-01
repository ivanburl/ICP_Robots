#ifndef ROBOT_H
#define ROBOT_H

#include "gameentity.h"

#include <QBrush>
#include <QGraphicsItem>
#include "robotdto.h"
#include "DtoMap.h"

class Room;

class Robot : public QGraphicsItemGroup, GameEntity, DtoMap<RobotDto> {
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
    QGraphicsEllipseItem *robotFrameItem;
    QGraphicsEllipseItem *arcItem;

private:
    Room *room;

private:
    double leftToTurn;

public:
    Robot(Room *room,
          double x, double y, double radius,
          double arcRadius, double arcDegree,
          double angleInDeegrees, double movementSpeed,
          double rotationSmaple, double rotationSpeedPerSecond);
    ~Robot() override;

    bool move(long deltaNanos);

    void rotate(long deltaNanos);

    bool hasDetected() const;

    bool isOutOfRoom() const;

    bool isColliding() const;

    void update(long long deltaMilliseconds) override;
    void fixedUpdate(long long deltaMilliseonds) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

public:
    QGraphicsEllipseItem *getRobotFrameItem() const;

    QGraphicsEllipseItem *getRobotArcItem() const;

    double getBaseX(){
        return getRobotArcItem()->x() + radius;
    }

    double getBaseY(){
        return getRobotArcItem()->y() + radius;
    }
};

#endif // ROBOT_H
