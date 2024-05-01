#include "room.h"
#include <QDebug>


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

Room::Room(int w, int h) : QGraphicsScene(0, 0, w, h) {
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
