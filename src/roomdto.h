/*! VUT FIT ICP
 * @file roomdto.h
 * @brief Room dto class  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef ROOMDTO_H
#define ROOMDTO_H

#include "blockdto.h"
#include "robotdto.h"
#include "Serializable.h"

class RoomDto : Serializable
{
public:
    RoomDto(int w, int h, QVector<RobotDto*> robots, QVector<BlockDto*> blocks);

    QVector<RobotDto*> getRobots();
    QVector<BlockDto*> getBlocks();

    int getWidth();
    int getHeight();

    QJsonObject toJsonObject() const override;
    static RoomDto* fromJsonObject(QJsonObject jsonObject);
    static const QString robotsName;
    static const QString blocksName;
    static const QString wName;
    static const QString hName;
private:
    QVector<RobotDto*> robots;
    QVector<BlockDto*> blocks;
    int w, h;
};

#endif // ROOMDTO_H
