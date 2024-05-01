#ifndef BLOCKDTO_H
#define BLOCKDTO_H

#include "Serializable.h"

class BlockDto : Serializable
{
public:
    BlockDto(int x, int y, int w, int h);
    int getX();
    int getY();
    int getHeight();
    int getWidth();
    QJsonObject toJsonObject() const override;
    static BlockDto* fromJsonObject(QJsonObject jsonObject);
    static const QString xName;
    static const QString yName;
    static const QString wName;
    static const QString hName;
private:
    int x, y;
    int w, h;
};

#endif // BLOCKDTO_H
