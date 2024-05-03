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

// void Room::focusItemChanged(QGraphicsItem* newFocus, QGraphicsItem* oldFocus, Qt::FocusReason focusReason){
//     QGraphicsScene::focusItemChanged(newFocus, oldFocus, focusReason);
//     if(!newFocus){
//         // Focus is lost
//         // Hide properties window
//         return;
//     }

//     if(auto* block = dynamic_cast<Block*>(newFocus); block){

//     }
//     else if(auto* robot = dynamic_cast<Robot*>(newFocus); robot){

//     }


// }

bool Room::validateState(QPolygon *qpolygon) {
    return true;
}


bool Room::isPointInRoom(double x, double y) {
    if (x < 0 || y < 0)
        return false;

    if (x > graphicsScene->width() || y > graphicsScene->height())
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

void Room::pause() {
    for (auto r : robots) {
        r->pause();
    }
    for (auto b : blocks) {
        b->pause();
    }
    GameEntity::pause();
}

void Room::play() {
    for (auto r: robots) {
        r->play();
    }
    for (auto b: blocks) {
        b->play();
    }
    GameEntity::play();
}

Room::Room(int w, int h) : GameEntity() {
    this->w = w;
    this->h = h;
    graphicsScene = new QGraphicsScene(0, 0, w, h);
    QGraphicsScene::connect(graphicsScene, &QGraphicsScene::focusItemChanged, this, &Room::processClickedItem);
};

QVector<Robot *> &Room::getRobots() {
    return this->robots;
}

QVector<Block *> &Room::getBlock() {
    return this->blocks;
}

QGraphicsScene* Room::scene(){
    return graphicsScene;
}

bool Room::addRobot(Robot *robot) {
    bool toAdd = validateState(nullptr); //TODO
    if (toAdd) {
        robots.append(robot);
        graphicsScene->addItem(robot);
    }
    return toAdd;
}

bool Room::addBlock(Block *block) {
    bool toAdd = validateState(nullptr); //TODO
    if (toAdd) {
        blocks.append(block);
        graphicsScene->addItem(block);
    }
    return toAdd;
}

void Room::reset(){
    for(auto block : blocks){
        graphicsScene->removeItem(block);
    }
    for(auto robot : robots){
        graphicsScene->removeItem(robot);
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


void Room::processClickedItem(QGraphicsItem* newItem, QGraphicsItem* prevItem, Qt::FocusReason focusReason){
    qDebug() << "Item clcked";
    emit itemSelected(newItem);
}
