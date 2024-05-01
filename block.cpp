#include "block.h"
#include <qbrush.h>
#include <QDebug>

QBrush Block::DEFAULT_BLOCK_BRUSH = QBrush(Qt::lightGray);

BlockDto* Block::GetDtoObject(){
    qDebug() << "Im here";

    auto position = this->scenePos();

    return new BlockDto(position.x(), position.y(), this->rect().width(), this->rect().height());
}

Block* Block::fromDtoObject(BlockDto dtoObject, Room* room){
    return new Block(room, dtoObject.getX(), dtoObject.getY(), dtoObject.getWidth(), dtoObject.getHeight());
}
void Block::update(long long deltaMilliseconds) {
}

void Block::fixedUpdate(long long deltaMilliseonds) {

}
