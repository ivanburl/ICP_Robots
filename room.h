#ifndef ROOM_H
#define ROOM_H

#include "block.h"
#include "robot.h"
#include "roomdto.h"
#include "DtoMap.h"
#include <QGraphicsView>

class Room: public QGraphicsScene, DtoMap<RoomDto>
{
private:
    int h, w;
    QVector<Robot*> robots;
    QVector<Block*> blocks;
public:
    Room(int w, int h) : QGraphicsScene(0, 0, w, h) {
        this->w = w;
        this->h = h;
    };

        RoomDto* GetDtoObject() const override;
    static Room* fromDtoObject(RoomDto dtoObject);

    QVector<Robot*>& getRobots() {
        return robots;
    }

    QVector<Block*>& getBlock() {
        return blocks;
    }

    bool addRobot(Robot* robot) {
        bool toAdd = validateState(nullptr); //TODO
        if (toAdd) {
            robots.append(robot);
            this->addItem(robot);
        }
        return toAdd;
    }

    bool addBlock(Block* block) {
        bool toAdd = validateState(nullptr); //TODO
        if (toAdd) {
            blocks.append(block);
            this->addItem(block);
        }
        return toAdd;
    }

    void removeRobot(Robot* robot) {
        for (int i=0;i<robots.size();i++) {
            if (robots[i] == robot) {
                robots.removeAt(i);
                i--;
            }
        }
        return;
    }


    void removeBlock(Block* block) {
        for (int i = 0;i < blocks.size(); i++) {
            if (blocks[i] == block) {
                blocks.remove(i);
                i--;
            }
        }
        return;
    }

private:
    bool validateState(QPolygon* qpolygon);
};

#endif // ROOM_H