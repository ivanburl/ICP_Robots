#ifndef BLOCK_H
#define BLOCK_H

#include "DtoMap.h"
#include "blockdto.h"
#include <QGraphicsRectItem>


class Block : DtoMap<BlockDto>
{
private:
    int x, y;
    int h, w;
public:
    Block(int x, int y,
          int h, int w);
    BlockDto* GetDtoObject() const override;
    static Block* fromDtoObject(BlockDto dtoObject);
};

#endif // BLOCK_H
