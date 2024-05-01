#ifndef BLOCK_H
#define BLOCK_H

#include "gameentity.h"

#include <QGraphicsRectItem>

class Room;

class Block : public QGraphicsRectItem, public GameEntity {
public:
    static QBrush DEFAULT_BLOCK_BRUSH;

private:
    Room *room;

public:
    Block(Room *room, int x, int y, int w, int h) : QGraphicsRectItem(x, y, w, h), GameEntity() {
        this->room = room;
        this->setBrush(DEFAULT_BLOCK_BRUSH);
    }

    void update(long long deltaMilliseconds) override;

    void fixedUpdate(long long deltaMilliseonds) override;
};

#endif // BLOCK_H
