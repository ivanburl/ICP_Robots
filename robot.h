#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include "robotdto.h"
#include "DtoMap.h"


class Robot : DtoMap<RobotDto>
{
private:
    double x, y;
    double radius;
    double arcRadius;
    double arcDegree;
    double currentAngleInDegrees;
    double movementSpeed;
    double rotationSample;
    int rotationDirection;
public:
    Robot(double x, double y,
          double radius,
          double arcRadius,
          double arcDegree,
          double currentAngleInDegrees,
          double movementSpeed,
          double rotationSample,
          int rotationDirection);
    RobotDto* GetDtoObject() const override;
    static Robot* fromDtoObject(RobotDto dtoObject);
};

#endif // ROBOT_H
