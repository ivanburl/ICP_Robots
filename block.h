#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsRectItem>

class Room;

class Block: public QGraphicsRectItem
{
public:
    static QBrush DEFAULT_BLOCK_BRUSH;
private:
    int x, y;
    int h, w;
private:
    Room* room;
public:
    Block(Room* room, int x, int y, int w, int h) : QGraphicsRectItem(x, y, w, h) {
        this->room = room;
        this->setBrush(DEFAULT_BLOCK_BRUSH);
    }
};

#endif // BLOCK_H
