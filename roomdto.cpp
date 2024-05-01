#include "roomdto.h"
#include <QJsonArray>

const QString RoomDto::blocksName = "blocks";
const QString RoomDto::robotsName = "robots";

RoomDto::RoomDto(QVector<RobotDto*> robots, QVector<BlockDto*> blocks){
    this->blocks = blocks;
    this->robots = robots;
}

QVector<RobotDto*> RoomDto::getRobots(){
    return robots;
};
QVector<BlockDto*> RoomDto::getBlocks(){
    return blocks;
}

QJsonObject RoomDto::toJsonObject() const{
    QJsonObject roomObject;

    QJsonArray robotJsonArray;
    for(auto* robot : this->robots){
        auto jsonObject = robot->toJsonObject();
        robotJsonArray.append(jsonObject);
    }

    roomObject.insert("robots", robotJsonArray);

    QJsonArray blockJsonArray;
    for(auto* block : this->blocks){
        auto jsonObject = block->toJsonObject();
        blockJsonArray.append(jsonObject);
    }

    roomObject.insert("blocks", blockJsonArray);
    return roomObject;
}


RoomDto* RoomDto::fromJsonObject(QJsonObject jsonObject){
    if(!jsonObject.value(blocksName).isArray()
        || !jsonObject.value(robotsName).isArray()){
        return nullptr;
    }

    QVector<RobotDto*> robotDtos;

    auto robotsArray = jsonObject.value(robotsName).toArray();

    for(auto object : robotsArray){
        if(object.isObject()){
            robotDtos.append(RobotDto::fromJsonObject(object.toObject()));
        }
    }

    QVector<BlockDto*> blockDtos;

    auto blocksArray = jsonObject.value(robotsName).toArray();

    for(auto object : blocksArray){
        if(object.isObject()){
            blockDtos.append(BlockDto::fromJsonObject(object.toObject()));
        }
    }

    return new RoomDto(robotDtos, blockDtos);
}
