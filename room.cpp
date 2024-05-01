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


bool Room::validateState(QPolygon *qpolygon) {
    return true;
}


bool Room::isPointInRoom(double x, double y) {
    if (x < 0 || y < 0)
        return false;

    if (x > width() || y > height())
        return false;

    return true;
}

void Room::fixedUpdate(long long deltaMilliseonds) {
    if (isPaused()) return;
    for (auto &r : this->robots) {
        r->fixedUpdate(deltaMilliseonds);
    }
}

void Room::update(long long deltaMilliseconds) {
    for (auto &r : this->robots) {
        r->update(deltaMilliseconds);
    }
    for (auto &b : this->blocks) {
        b->update(deltaMilliseconds);
    }
}

Room::Room(int w, int h) : QGraphicsScene(0, 0, w, h), GameEntity() {
    this->w = w;
    this->h = h;
};

QVector<Robot *> &Room::getRobots() {
    return this->robots;
}

QVector<Block *> &Room::getBlock() {
    return this->blocks;
}

bool Room::addRobot(Robot *robot) {
    bool toAdd = validateState(nullptr); //TODO
    if (toAdd) {
        robots.append(robot);
        this->addItem(robot);
    }
    return toAdd;
}

bool Room::addBlock(Block *block) {
    bool toAdd = validateState(nullptr); //TODO
    if (toAdd) {
        blocks.append(block);
        this->addItem(block);
    }
    return toAdd;
}

void Room::reset(){
    for(auto block : blocks){
        this->removeItem(block);
    }
    for(auto robot : robots){
        this->removeItem(robot);
    }
    blocks.clear();
    robots.clear();
}

void Room::removeRobot(Robot *robot) {
    for (int i = 0; i < robots.size(); i++) {
        if (robots[i] == robot) {
            robots.removeAt(i);
            i--;
        }
    }
}

void Room::removeBlock(Block *block) {
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == block) {
            blocks.remove(i);
            i--;
        }
    }
}
