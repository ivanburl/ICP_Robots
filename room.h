#ifndef ROOM_H
#define ROOM_H

#include "block.h"
#include "robot.h"

#include <QGraphicsView>

class Room : public QGraphicsScene {
private:
    int h, w;
    QVector<Robot *> robots;
    QVector<Block *> blocks;

public:
    Room(int w, int h);

    QVector<Robot *> &getRobots();

    QVector<Block *> &getBlock();

    bool addRobot(Robot *robot);

    bool addBlock(Block *block);

    void removeRobot(Robot *robot);

    void removeBlock(Block *block);

    bool isPointInRoom(double x, double y);

private:
    bool validateState(QPolygon *qpolygon);
};

#endif // ROOM_H
