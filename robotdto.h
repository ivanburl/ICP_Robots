#ifndef ROBOTDTO_H
#define ROBOTDTO_H

#include "Serializable.h"

using namespace std;

class RobotDto : Serializable
{
public:
    RobotDto(double x, double y,
             double radius, double arcRadius,
             double arcDegree, double currentAngleInDegrees,
             double movementSpeed, double rotationSample,
             int rotationDirection);

    double getX();
    double getY();
    double getRadius();
    double getArcRadius();
    double getArcDegree();
    double getCurrentAngleInDegrees();
    double getMovementSpeed();
    double getRotationSample();
    int getRotationDirection();

    QJsonObject toJsonObject() const override;
    static RobotDto* fromJsonObject(QJsonObject jsonObject);

    static const QString xName;
    static const QString yName;
    static const QString radiusName;
    static const QString arcRadiusName;
    static const QString arcDegreeName;
    static const QString currentAngleInDegreesName;
    static const QString movementSpeedName;
    static const QString rotationSampleName;
    static const QString rotationDirectionName;
private:
    double x, y;
    double radius;
    double arcRadius;
    double arcDegree;
    double currentAngleInDegrees;
    double movementSpeed;
    double rotationSample;
    int rotationDirection;
};

#endif // ROBOTDTO_H
