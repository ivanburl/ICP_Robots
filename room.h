#ifndef ROOM_H
#define ROOM_H

#include "block.h"
#include "robot.h"

#include <QGraphicsView>

class Room: public QGraphicsScene
{
private:
    int h, w;
    QVector<Robot*> robots;
    QVector<Block*> blocks;
public:
    Room();

    QVector<Robot*> getRobots() {
        return robots;
    }

    QVector<Block*> getBlock() {
        return blocks;
    }

    bool addRobot(Robot* robot) {
        robots.append(robot);
    }

    bool addBlock(Block* block) {
        blocks.append(block);
    }

private:
    bool validateState();
};

#endif // ROOM_H
