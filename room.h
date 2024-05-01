#ifndef ROOM_H
#define ROOM_H

#include "block.h"
#include "robot.h"
#include "roomdto.h"
#include "DtoMap.h"
#include <QGraphicsView>

class Room : public QGraphicsScene, public GameEntity, DtoMap<RoomDto> {
private:
    int h, w;
    QVector<Robot *> robots;
    QVector<Block *> blocks;

public:
    Room(int w, int h);

    RoomDto* GetDtoObject() override;
    static Room* fromDtoObject(RoomDto dtoObject);

    QVector<Robot *> &getRobots();

    QVector<Block *> &getBlock();

    bool addRobot(Robot *robot);

    bool addBlock(Block *block);

    void removeRobot(Robot *robot);

    void removeBlock(Block *block);

    bool isPointInRoom(double x, double y);

    void fixedUpdate(long long deltaMilliseonds) override;
    void update(long long deltaMilliseconds) override;

private:
    bool validateState(QPolygon *qpolygon);
};

#endif // ROOM_H
