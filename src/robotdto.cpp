/*! VUT FIT ICP
 * @file robotdto.cpp
 * @brief robotdto.h implementation 
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "robotdto.h"

const QString RobotDto::xName = "x";
const QString RobotDto::yName = "y";
const QString RobotDto::radiusName = "radius";
const QString RobotDto::arcRadiusName = "arcRadius";
const QString RobotDto::arcDegreeName = "arcDegree";
const QString RobotDto::currentAngleInDegreesName = "currentAngleInDegrees";
const QString RobotDto::movementSpeedName = "movementSpeed";
const QString RobotDto::rotationSampleName = "rotationSample";
const QString RobotDto::rotationSpeedInDegreeName = "rotationSpeedInDegree";

RobotDto::RobotDto(double x, double y,
                   double radius, double arcRadius,
                   double arcDegree, double currentAngleInDegrees,
                   double movementSpeed, double rotationSample, double rotationSpeedInDegree) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->arcRadius = arcRadius;
    this->arcDegree = arcDegree;
    this->currentAngleInDegrees = currentAngleInDegrees;
    this->movementSpeed = movementSpeed;
    this->rotationDegreeSample = rotationSample;
    this->rotationSpeedInDegree = rotationSpeedInDegree;
}

double RobotDto::getX(){
    return x;
}
double RobotDto::getY(){
    return y;
}
double RobotDto::getRadius(){
    return radius;
}
double RobotDto::getArcRadius(){
    return arcRadius;
}
double RobotDto::getArcDegree(){
    return arcDegree;
}
double RobotDto::getCurrentAngleInDegrees(){
    return currentAngleInDegrees;
}
double RobotDto::getMovementSpeed(){
    return movementSpeed;
}
double RobotDto::getRotationSample(){
    return rotationSpeedInDegree;
}
double RobotDto::getRotationSpeedInDegree(){
    return rotationSpeedInDegree;
}

QJsonObject RobotDto::toJsonObject() const{
    QJsonObject jsonObject;
    jsonObject.insert(xName, x);
    jsonObject.insert(yName, y);
    jsonObject.insert(radiusName, radius);
    jsonObject.insert(arcRadiusName, arcRadius);
    jsonObject.insert(arcDegreeName, arcDegree);
    jsonObject.insert(currentAngleInDegreesName, currentAngleInDegrees);
    jsonObject.insert(movementSpeedName, movementSpeed);
    jsonObject.insert(rotationSampleName, rotationDegreeSample);
    jsonObject.insert(rotationSpeedInDegreeName, rotationSpeedInDegree);
    return jsonObject;
}

RobotDto* RobotDto::fromJsonObject(QJsonObject jsonObject){
    auto xValue = jsonObject.value(xName);
    auto yValue = jsonObject.value(yName);
    auto radiusValue = jsonObject.value(radiusName);
    auto arcRadiusValue = jsonObject.value(arcRadiusName);
    auto arcDegreeValue = jsonObject.value(arcDegreeName);
    auto currentAngleInDegreesValue = jsonObject.value(currentAngleInDegreesName);
    auto movementSpeedValue = jsonObject.value(movementSpeedName);
    auto rotationSampleValue = jsonObject.value(rotationSampleName);
    auto rotationSpeedValue = jsonObject.value(rotationSpeedInDegreeName);

    if(!xValue.isDouble() || !yValue.isDouble()
        || !radiusValue.isDouble()
        || !arcRadiusValue.isDouble()
        || !arcDegreeValue.isDouble()
        || !currentAngleInDegreesValue.isDouble()
        || !movementSpeedValue.isDouble()
        || !rotationSampleValue.isDouble()
        || !rotationSpeedValue.isDouble()){
        return nullptr;
    }

    return new RobotDto(xValue.toDouble(), yValue.toDouble(),
                        radiusValue.toDouble(), arcRadiusValue.toDouble(),
                        arcDegreeValue.toDouble(), currentAngleInDegreesValue.toDouble(),
                        movementSpeedValue.toDouble(), rotationSampleValue.toDouble(),
                        rotationSpeedValue.toDouble());
}


