#include "block.h"
#include <qbrush.h>

QBrush Block::DEFAULT_BLOCK_BRUSH = QBrush(Qt::lightGray);

BlockDto* Block::GetDtoObject(){
    return new BlockDto(x, y, w, h);
}

Block* Block::fromDtoObject(BlockDto dtoObject, Room* room){
    return new Block(room, dtoObject.getX(), dtoObject.getY(), dtoObject.getWidth(), dtoObject.getHeight());
void Block::update(long long deltaMilliseconds) {
}

void Block::fixedUpdate(long long deltaMilliseonds) {
}
