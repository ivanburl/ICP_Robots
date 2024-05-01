#ifndef BLOCK_H
#define BLOCK_H

#include "DtoMap.h"
#include "blockdto.h"
#include "gameentity.h"

#include <QGraphicsRectItem>

class Room;

class Block: public QGraphicsRectItem, GameEntity, DtoMap<BlockDto>
{
public:
    static QBrush DEFAULT_BLOCK_BRUSH;

private:
    Room *room;

public:
    Block(Room *room, int x, int y, int w, int h) : QGraphicsRectItem(x, y, w, h), GameEntity() {
        this->room = room;
        this->setBrush(DEFAULT_BLOCK_BRUSH);
    }
    BlockDto* GetDtoObject() override;
    static Block* fromDtoObject(BlockDto dtoObject, Room* room);

    void update(long long deltaMilliseconds) override;

    void fixedUpdate(long long deltaMilliseonds) override;
};

#endif // BLOCK_H
