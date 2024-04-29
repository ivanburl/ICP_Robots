#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsRectItem>

class Room;

class Block: public QGraphicsRectItem
{
private:
    int x, y;
    int h, w;
private:
    Room* room;
public:
    Block(Room* room, int x, int y, int w, int h) : QGraphicsRectItem(x, y, w, h) {
        this->room = room;
    }
};

#endif // BLOCK_H
