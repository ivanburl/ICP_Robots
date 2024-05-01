#ifndef ROOM_H
#define ROOM_H

#include "block.h"
#include "robot.h"
#include "roomdto.h"
#include "DtoMap.h"
#include <QGraphicsView>

class Room : DtoMap<RoomDto>
{
private:
    int h, w;
    QVector<Robot*> robots;
    QVector<Block*> blocks;
public:
    Room();
    Room(QVector<Robot*> robots, QVector<Block*> blocks);
    RoomDto* GetDtoObject() const override;
    static Room* fromDtoObject(RoomDto dtoObject);
};

#endif // ROOM_H
