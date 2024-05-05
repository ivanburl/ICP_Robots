#ifndef ROBOT_H
#define ROBOT_H

#include "gameentity.h"

#include <QBrush>
#include <QGraphicsItem>
#include "robotdto.h"
#include "DtoMap.h"
#include "signalsender.h"

class Room;


class Robot : public QObject, public QGraphicsItemGroup, public GameEntity, DtoMap<RobotDto> {
public:
    static const QBrush DEFAULT_ROBOT_BRUSH;
    static const QBrush DEFAULT_ROBOT_ARC_BRUSH;
    static const QBrush DEFAULT_ROBOT_INTERSECTION_BRUSH;
    static const QBrush DEFAULT_ROBOT_CONTROLLED_BRUSH;
    static const QBrush DEFAULT_ROBOT_ROTATING_BRUSH;
private:
    double radius;
    double arcRadius;
    double arcDegree;
    double movementSpeed;
    double rotationDegreeSample, rotationSpeedInDegree;
    bool isControlled;
    int currentPressedKey;
private:
    int roflDirection = 0;

private:
    QGraphicsEllipseItem *robotFrameItem;
    QGraphicsEllipseItem *arcItem;

private:
    Room *room;

private:
    double leftToTurn;
    SignalSender* signalSender;

public:
    Robot(Room *room,
          double x, double y, double radius,
          double arcRadius, double arcDegree,
          double angleInDeegrees, double movementSpeed,
          double rotationSmaple, double rotationSpeedPerSecond);
    ~Robot() override;

public:
    bool moveOnDistance(double distance);
    void rotateOnAngle(double degree);

    bool hasDetected() const;

    bool isOutOfRoom() const;

    bool isColliding() const;

    bool isRotating() const;
public:
    void update(long long deltaMilliseconds) override;
    void fixedUpdate(long long deltaMilliseonds) override;

public:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public:
    void takeControl();
    void toggleControl();
    void releaseControl();

public:
    double getRobotRadius() const;
    double getRobotMovementSpeed() const;
    double getRobotRotationSpeed() const;
    double getRobotRotationSample() const;
    double getArcRadius() const;
    double getArcExtent() const;
    double getRobotCenterX() const;
    double getRobotCenterY() const;
    double getRotationAngle() const;
public:
    void setRobotCenterX(double x);

    void setRobotCenterY(double y);

    void setArcRadius(double radius);

    void setRobotRadius(double robotRadius);

    void setArcExtent(double arcExtent);

    void setRobotMovementSpeed(double speedPerSec);

    void setRobotRotationSpeed(double degreePerSec);

    void setRobotRotationSample(double degree);

    void setRotationAngle(double angle);

public:
    RobotDto* GetDtoObject() override;
    static Robot* fromDtoObject(RobotDto dtoObject, Room* room);
public:
    void pause() override;
    void play() override;
public:
    QGraphicsEllipseItem *getRobotFrameItem() const;

    QGraphicsEllipseItem *getRobotArcItem() const;

    [[deprecated("Use getRobotCenterX() instead")]]
    double getBaseX(){
        return getRobotCenterX();
    }

    [[deprecated("Use getRobotCenterY() instead")]]
    double getBaseY(){
        return getRobotCenterY();
    }

    SignalSender* getSignalSender() const;
};

#endif // ROBOT_H
