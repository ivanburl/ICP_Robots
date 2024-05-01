#include "block.h"

Block::Block() {}

BlockDto* Block::GetDtoObject() const{
    return new BlockDto(x, y, w, h);
}

Block* Block::fromDtoObject(BlockDto dtoObject){
    return new Block(dtoObject.getX(), dtoObject.getY(), dtoObject.getWidth(), dtoObject.getHeight());
}
