/*! VUT FIT ICP
 * @file room.h
 * @brief Class that contains game entites  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef ROOM_H
#define ROOM_H

#include "block.h"
#include "robot.h"
#include "roomdto.h"
#include "DtoMap.h"
#include "scene.h"
#include <QGraphicsView>

/**
 * Entity represents the room (container for robots and blocks)
 */
class Room : public GameEntity, DtoMap<RoomDto> {
    Q_OBJECT;
private:
    int h, w;
    Scene* graphicsScene;
    QVector<Robot *> robots;
    QVector<Block *> blocks;

public:
    /**
     * Room constructor
     * @param w - width of the room
     * @param h - height of the room
     */
    Room(int w, int h);
    ~Room() override;
public:
    RoomDto* GetDtoObject() override;
    static Room* fromDtoObject(RoomDto dtoObject);
public:
    /**
     * Get all roobots in the room
     * @return robots in the room
     */
    QVector<Robot *> &getRobots();

    /**
     *  Return all blocks in the room
     * @return block in the room
     */
    QVector<Block *> &getBlocks();

    /**
     *
     * @return room scene
     */
    Scene* scene();
public:
    /**
     * Add robot to the room
     * @param robot
     */
    void addRobot(Robot *robot);

    /**
     * Add block to the room
     * @param block
     */
    void addBlock(Block *block);

    /**
     * Find specific robot in the room and remove it from the room
     * @param robot - specifc robot
     */
    void removeRobot(Robot *robot);

    /**
     * Find specific block in the room and remove it from the room
     * @param block
     */
    void removeBlock(Block *block);

    /**
     * Clean and reset room to default state (empty state)
     */
    void reset();

    /**
     * Whether coordinate (x,y) inside room
     * @param x - coordinate x
     * @param y - coordinate y
     * @return  - true if coordiante inside room, otherwise false
     */
    bool isPointInRoom(double x, double y);

public:
    void fixedUpdate(long long deltaMilliseonds) override;
    void update(long long deltaMilliseconds) override;
signals:
    void itemSelected(QGraphicsItem* selectedItem);
public:
    void pause() override;
    void play() override;
private slots:
    void processClickedItem(QGraphicsItem* item);
public slots:
    void processItemToDelete(QGraphicsItem* item);
public:
    /**
     * Checks whether room has meaningful and valid state
     * @return true if room is in valid state, otherwise false
     */
    bool isValidState();
};

#endif // ROOM_H
