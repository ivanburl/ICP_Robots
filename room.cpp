#include "room.h"
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>

RoomDto* Room::GetDtoObject() const{
    QVector<BlockDto*> blockDtos;
    for(auto* block : blocks){
        blockDtos.append(block->GetDtoObject());
    }

    QVector<RobotDto*> robotDtos;
    for(auto* robot : robots){
        robotDtos.append(robot->GetDtoObject());
    }

    return new RoomDto(robotDtos, blockDtos);
}

Room* Room::fromDtoObject(RoomDto dtoObject){
    auto blockDtos = dtoObject.getBlocks();

    QVector<Block*> blocks;

    for(auto* blockDto : blockDtos){
        blocks.append(Block::fromDtoObject(*blockDto));
    }

    auto robotDtos = dtoObject.getRobots();

    QVector<Robot*> robots;

    for(auto* robotDto : robotDtos){
        robots.append(Robot::fromDtoObject(*robotDto));
    }

    return new Room(robots, blocks);
}

bool Room::validateState(QPolygon *qpolygon)
{
    return true;
}
