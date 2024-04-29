#ifndef ROOM_H
#define ROOM_H

#include "block.h"
#include "robot.h"

#include <QGraphicsView>

class Room
{
private:
    int h, w;
    QVector<Robot*> robots;
    QVector<Block*> blocks;
public:
    Room();
};

#endif // ROOM_H
