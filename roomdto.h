#ifndef ROOMDTO_H
#define ROOMDTO_H

#include "blockdto.h"
#include "robotdto.h"
#include "Serializable.h"

class RoomDto : Serializable
{
public:
    RoomDto(QVector<RobotDto*> robots, QVector<BlockDto*> blocks);

    QVector<RobotDto*> getRobots();
    QVector<BlockDto*> getBlocks();

    QJsonObject toJsonObject() const override;
    static RoomDto* fromJsonObject(QJsonObject jsonObject);
    static const QString robotsName;
    static const QString blocksName;
private:
    QVector<RobotDto*> robots;
    QVector<BlockDto*> blocks;
};

#endif // ROOMDTO_H
