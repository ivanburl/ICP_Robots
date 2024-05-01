#include "robot.h"

RobotDto::RobotDto(double x, double y,
                   double radius, double arcRadius,
                   double arcDegree, double currentAngleInDegrees,
                   double movementSpeed, double rotationSample, int rotationDirection) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->arcRadius = arcRadius;
    this->arcDegree = arcDegree;
    this->currentAngleInDegrees = currentAngleInDegrees;
    this->movementSpeed = movementSpeed;
    this->rotationSample = rotationSample;
    this->rotationDirection = rotationDirection;
}

RobotDto* Robot::GetDtoObject() const{
    return new RobotDto(x, y, radius,
                    arcRadius, arcDegree,
                    currentAngleInDegrees,
                    movementSpeed, rotationSample,
                    rotationDirection);
}

Robot* Robot::fromDtoObject(RobotDto dtoObject){
    return new Robot(dtoObject.getX(), dtoObject.getY(),
                     dtoObject.getRadius(), dtoObject.getArcRadius(),
                     dtoObject.getArcDegree(), dtoObject.getCurrentAngleInDegrees(),
                     dtoObject.getMovementSpeed(), dtoObject.getRotationSample(),
                     dtoObject.getRotationDirection());
}
