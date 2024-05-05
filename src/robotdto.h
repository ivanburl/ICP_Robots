/*! VUT FIT ICP
 * @file robotdto.h
 * @brief Robot game entity dto class  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

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
             double rotationSpeedInDegree);

    double getX();
    double getY();
    double getRadius();
    double getArcRadius();
    double getArcDegree();
    double getCurrentAngleInDegrees();
    double getMovementSpeed();
    double getRotationSample();
    double getRotationSpeedInDegree();

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
    static const QString rotationSpeedInDegreeName;
private:
    double x, y;
    double radius;
    double arcRadius;
    double arcDegree;
    double currentAngleInDegrees;
    double movementSpeed;
    double rotationDegreeSample, rotationSpeedInDegree;
};

#endif // ROBOTDTO_H
