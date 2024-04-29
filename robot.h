#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>


class Robot
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
    Robot();
};

#endif // ROBOT_H
