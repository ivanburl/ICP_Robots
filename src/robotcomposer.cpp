/*! VUT FIT ICP
 * @file robotcomposer.cpp
 * @brief robotcomposer.h implementation
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "robotcomposer.h"

RobotComposer::RobotComposer(Robot* robot)
{
    this->robot = robot;
    connect(this->robot->getSignalSender(), &SignalSender::itemMoved, this, &RobotComposer::itemMoved);
    connect(this->robot->getSignalSender(), &SignalSender::updateExceptLocation, this, &RobotComposer::updateExceptLocation);
    connect(this->robot->getSignalSender(), &SignalSender::updateRotationAngle, this, &RobotComposer::updateRotationAngle);
}

double RobotComposer::getRobotRadius() const{
    return robot->getRobotRadius();
}
double RobotComposer::getRobotMovementSpeed() const{
    return robot->getRobotMovementSpeed();
}
double RobotComposer::getRobotRotationSpeed() const{
    return robot->getRobotRotationSpeed();
}
double RobotComposer::getRobotRotationSample() const{
    return robot->getRobotRotationSample();
}
double RobotComposer::getArcRadius() const{
    return robot->getArcRadius();
}
double RobotComposer::getArcExtent() const{
    return robot->getArcExtent();
}
double RobotComposer::getRobotCenterX() const{
    return robot->getRobotCenterX();
}
double RobotComposer::getRobotCenterY() const{
    return robot->getRobotCenterY();
}
double RobotComposer::getRobotRotation() const{
    return robot->getRotationAngle();
}
QGraphicsItem *RobotComposer::getOriginalGraphicsItem() const{
    return robot;
}

void RobotComposer::setRobotCenterX(double x){
    robot->setRobotCenterX(x);
}
void RobotComposer::setRobotCenterY(double y){
    robot->setRobotCenterY(y);
}
void RobotComposer::setArcRadius(double radius){
    robot->setArcRadius(radius);
}
void RobotComposer::setRobotRadius(double robotRadius){
    robot->setRobotRadius(robotRadius);
}
void RobotComposer::setArcExtent(double arcExtent){
    robot->setArcExtent(arcExtent);
}
void RobotComposer::setRobotMovementSpeed(double speedPerSec){
    robot->setRobotMovementSpeed(speedPerSec);
}
void RobotComposer::setRobotRotationSpeed(double degreePerSec){
    robot->setRobotRotationSpeed(degreePerSec);
}
void RobotComposer::setRobotRotationSample(double degree){
    robot->setRobotRotationSample(degree);
}
void RobotComposer::setRobotRotation(double degree){
    robot->setRotationAngle(degree);
}

void RobotComposer::itemMoved(){
    emit this->robotCenterXChanged(this->getRobotCenterX());
    emit this->robotCenterYChanged(this->getRobotCenterY());
}

void RobotComposer::updateExceptLocation(){
    emit arcRadiusChanged(this->getArcRadius());
    emit robotRadiusChanged(this->getRobotRadius());
    emit arcExtentChanged(this->getArcExtent());
    emit robotMovementSpeedChanged(this->getRobotMovementSpeed());
    emit robotRotationSpeedChanged(this->getRobotRotationSpeed());
    emit robotRotationSampleChanged(this->getRobotRotationSample());
}

void RobotComposer::updateRotationAngle(){
    emit robotRotationChanged(this->getRobotRotation());
}
