#include "room.h"
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>

RoomDto* Room::GetDtoObject(){
    QVector<BlockDto*> blockDtos;
    for(auto* block : blocks){
        blockDtos.append(block->GetDtoObject());
    }

    QVector<RobotDto*> robotDtos;
    for(auto* robot : robots){
        robotDtos.append(robot->GetDtoObject());
    }

    return new RoomDto(w, h, robotDtos, blockDtos);
}

Room* Room::fromDtoObject(RoomDto dtoObject){
    auto* room = new Room(dtoObject.getWidth(), dtoObject.getHeight());

    auto blockDtos = dtoObject.getBlocks();

    for(auto* blockDto : blockDtos){
        room->addBlock(Block::fromDtoObject(*blockDto, room));
    }

    auto robotDtos = dtoObject.getRobots();

    for(auto* robotDto : robotDtos){
        room->addRobot(Robot::fromDtoObject(*robotDto, room));
    }

    return room;
}

bool Room::validateState(QPolygon *qpolygon)
{
    return true;
}
