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
    if (isPaused()) return;
}

int Block::x(){
    return pos().x();
}
int Block::y(){
    return pos().y();
}
int Block::width(){
    return rect().width();
}
int Block::height(){
    return rect().height();
}

void Block::setX(int value){
    setPos(value, pos().y());
}
void Block::setY(int value){
    setPos(pos().x(), value);
}
void Block::setWidth(int value){
    auto prev_rect = rect();
    prev_rect.setHeight(value);
    setRect(prev_rect);
}
void Block::setHeight(int value)
{
    auto prev_rect = rect();
    prev_rect.setHeight(value);
    setRect(prev_rect);
    //emit xChanged(pos().x());
}

SignalSender *Block::getSignalSender()
{
    return signalSender;
}

void Block::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //emit xChanged(pos().x());
    //emit yChanged(pos().y());
    signalSender->sendItemMovedSignal();
    QGraphicsItem::mouseMoveEvent(event);

}
