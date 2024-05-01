#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsRectItem>

class Room;

class Block : public QGraphicsRectItem {
public:
    static QBrush DEFAULT_BLOCK_BRUSH;

private:
    Room *room;

public:
    Block(Room *room, int x, int y, int w, int h) : QGraphicsRectItem(x, y, w, h) {
        this->room = room;
        this->setBrush(DEFAULT_BLOCK_BRUSH);
    }

    void update(long long deltaMilliseconds);

    void fixedUpdate(long long deltaMilliseonds);
};

#endif // BLOCK_H
