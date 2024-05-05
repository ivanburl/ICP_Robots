#ifndef ROBOTCOMPOSER_H
#define ROBOTCOMPOSER_H

#include "graphicsitemcomposer.h"
#include "robot.h"
#include <QObject>

class RobotComposer : public GraphicsItemComposer
{
    Q_OBJECT
    Q_PROPERTY(double X READ getRobotCenterX WRITE setRobotCenterX NOTIFY robotCenterXChanged)
    Q_PROPERTY(double Y READ getRobotCenterY WRITE setRobotCenterY NOTIFY robotCenterYChanged)
    Q_PROPERTY(double Radius READ getRobotRadius WRITE setRobotRadius NOTIFY robotRadiusChanged)
    Q_PROPERTY(double MovementSpeed READ getRobotMovementSpeed WRITE setRobotMovementSpeed NOTIFY robotMovementSpeedChanged)
    Q_PROPERTY(double RotationSpeed READ getRobotRotationSpeed WRITE setRobotRotationSpeed NOTIFY robotRotationSpeedChanged)
    Q_PROPERTY(double RotationSample READ getRobotRotationSample WRITE setRobotRotationSample NOTIFY robotRotationSampleChanged)
    Q_PROPERTY(double ArcRadius READ getArcRadius WRITE setArcRadius NOTIFY arcRadiusChanged)
    Q_PROPERTY(double ArcExtent READ getArcExtent WRITE setArcExtent NOTIFY arcExtentChanged)
    Q_PROPERTY(double RotationAngle READ getRobotRotation WRITE setRobotRotation NOTIFY robotRotationChanged)

public:
    explicit RobotComposer(Robot *robot);
    double getRobotRadius() const;
    double getRobotMovementSpeed() const;
    double getRobotRotationSpeed() const;
    double getRobotRotationSample() const;
    double getArcRadius() const;
    double getArcExtent() const;
    double getRobotCenterX() const;
    double getRobotCenterY() const;
    double getRobotRotation() const;
    QGraphicsItem* getOriginalGraphicsItem() const override;

    void setRobotCenterX(double x);
    void setRobotCenterY(double y);
    void setArcRadius(double radius);
    void setRobotRadius(double robotRadius);
    void setArcExtent(double arcExtent);
    void setRobotMovementSpeed(double speedPerSec);
    void setRobotRotationSpeed(double degreePerSec);
    void setRobotRotationSample(double degree);
    void setRobotRotation(double degree);

private:
    Robot* robot;

private slots:
    void itemMoved();
    void updateExceptLocation();
    void updateRotationAngle();

signals:
    void robotCenterXChanged(double x);
    void robotCenterYChanged(double y);
    void arcRadiusChanged(double radius);
    void robotRadiusChanged(double robotRadius);
    void arcExtentChanged(double arcExtent);
    void robotMovementSpeedChanged(double speedPerSec);
    void robotRotationSpeedChanged(double degreePerSec);
    void robotRotationSampleChanged(double degree);
    void robotRotationChanged(double degree);
};

#endif // ROBOTCOMPOSER_H
