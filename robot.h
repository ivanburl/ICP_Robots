#ifndef ROBOT_H
#define ROBOT_H

#include "gameentity.h"

#include <QBrush>
#include <QGraphicsItem>
#include "robotdto.h"
#include "DtoMap.h"
#include "signalsender.h"

class Room;

/**
 * Entity which represent the robot (mmoving object with ability to detect and collide)
 */
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
    SignalSender *signalSender;

public:
    Robot(Room *room,
          double x, double y, double radius,
          double arcRadius, double arcDegree,
          double angleInDeegrees, double movementSpeed,
          double rotationSmaple, double rotationSpeedPerSecond);

    ~Robot() override;

public:
    /**
     * Move robot on specific distance in his current dierection
     * @param distance - distance
     * @return true if move was done successfuly, otherwise false
     */
    bool moveOnDistance(double distance);

    /**
     * Rotate robot on specific angle
     * @param degree - angle in degree
     */
    void rotateOnAngle(double degree);

    /**
     * Robot detection
     * @return true if robot has detected any colider, otherwise false
     */
    bool hasDetected() const;

    /**
     * Check if robot is out of the room
     * @return true if robot is out of the room, otherwise false
     */
    bool isOutOfRoom() const;

    /**
     * Robot is colliding with collider
     * @return true if colliding, otherwise false
     */
    bool isColliding() const;

    /**
     * Robot is rotatting
     * @return true if rotating, otherwise false
     */
    bool isRotating() const;

public:
    void update(long long deltaMilliseconds) override;

    void fixedUpdate(long long deltaMilliseonds) override;

public:
    /**
     * Detection on movement
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * Reqeuest focus on robot, give more info about current robot
     * @param event
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * Control of the robot and changing of robot parameteres
     * @param event
     */
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

public:
    /**
     * take control over the robot to the user
     */
    void takeControl();

    /**
     * toggle control mode of the robot
     */
    void toggleControl();

    /**
     *
     */
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
    RobotDto *GetDtoObject() override;

    /**
     * Static constructor for robot
     * @param dtoObject
     * @param room
     * @return
     */
    static Robot *fromDtoObject(RobotDto dtoObject, Room *room);

public:
    void pause() override;

    void play() override;

public:
    /**
     * Return robot frame (circle)
     * @return robot frame
     */
    QGraphicsEllipseItem *getRobotFrameItem() const;

    /**
     * Return robot arc (pie arc)
     * @return robot arc
     */
    QGraphicsEllipseItem *getRobotArcItem() const;

    [[deprecated("Use getRobotCenterX() instead")]]
    double getBaseX() {
        return getRobotCenterX();
    }

    [[deprecated("Use getRobotCenterY() instead")]]
    double getBaseY() {
        return getRobotCenterY();
    }

    SignalSender *getSignalSender() const;
};

#endif // ROBOT_H
