#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsRectItem>


class Block: public QGraphicsRectItem
{
private:
    int x, y;
    int h, w;
public:
    Block(int x, int y, int w, int h) : QGraphicsRectItem(x, y, w, h) {
    }
};

#endif // BLOCK_H
