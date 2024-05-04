#ifndef BLOCK_H
#define BLOCK_H

#include "DtoMap.h"
#include "blockdto.h"
#include "gameentity.h"
#include "signalsender.h"

#include <QGraphicsRectItem>

class Room;

class Block : public QGraphicsRectItem, public GameEntity, DtoMap<BlockDto> {

public:
    static QBrush DEFAULT_BLOCK_BRUSH;

private:
    Room *room;
    SignalSender* signalSender;

public:
    Block(Room *room, int x, int y, int w, int h) : QGraphicsRectItem(0, 0, w, h), GameEntity() {
        this->room = room;
        this->setBrush(DEFAULT_BLOCK_BRUSH);

        this->setPos(x, y);
        this->setFlag(QGraphicsItem::ItemIsSelectable, true);
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        this->setFlag(QGraphicsItem::ItemIsFocusable, true);
        signalSender = new SignalSender;
    }

public:
    BlockDto *GetDtoObject() override;

    static Block *fromDtoObject(BlockDto dtoObject, Room *room);

public:
    void update(long long deltaMilliseconds) override;

    void fixedUpdate(long long deltaMilliseonds) override;

    int x();
    int y();
    int width();
    int height();

    void setX(int value);
    void setY(int value);
    void setWidth(int value);
    void setHeight(int value);
    SignalSender* getSignalSender();
public:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BLOCK_H
