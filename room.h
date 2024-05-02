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
    ~Room() override;
public:
    RoomDto* GetDtoObject() override;
    static Room* fromDtoObject(RoomDto dtoObject);
public:
    QVector<Robot *> &getRobots();

    QVector<Block *> &getBlock();
public:
    void addRobot(Robot *robot);
    void addBlock(Block *block);

    void removeRobot(Robot *robot);
    void removeBlock(Block *block);

    void reset();

    bool isPointInRoom(double x, double y);

public:
    void fixedUpdate(long long deltaMilliseonds) override;
    void update(long long deltaMilliseconds) override;
public:
    void pause() override;
    void play() override;
public:
    bool isValidState();
};

#endif // ROOM_H
