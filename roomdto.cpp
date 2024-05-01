#include "roomdto.h"
#include <QJsonArray>

const QString RoomDto::blocksName = "blocks";
const QString RoomDto::robotsName = "robots";
const QString RoomDto::wName = "w";
const QString RoomDto::hName = "h";

RoomDto::RoomDto(int w, int h, QVector<RobotDto*> robots, QVector<BlockDto*> blocks){
    this->blocks = blocks;
    this->robots = robots;
    this->w = w;
    this->h = h;
}

QVector<RobotDto*> RoomDto::getRobots(){
    return robots;
};
QVector<BlockDto*> RoomDto::getBlocks(){
    return blocks;
}
int RoomDto::getWidth(){
    return w;
}
int RoomDto::getHeight(){
    return h;
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
        || !jsonObject.value(robotsName).isArray()
        || !jsonObject.value(wName).isDouble()
        || jsonObject.value(hName).isDouble()){
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

    return new RoomDto(jsonObject.value(wName).toInt(),
                       jsonObject.value(hName).toInt(),
                       robotDtos, blockDtos);
}
