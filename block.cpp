#include "block.h"
#include <qbrush.h>
#include <QDebug>
#include <QKeyEvent>

QBrush Block::DEFAULT_BLOCK_BRUSH = QBrush(Qt::lightGray);

Block::Block(Room *room, double x, double y, double w, double h) : QGraphicsRectItem(0, 0, w, h) {
    this->room = room;
    this->currentPressedKey = -1;

    this->setBrush(DEFAULT_BLOCK_BRUSH);
    this->setPos(x, y);


    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->signalSender = new SignalSender;
}

BlockDto *Block::GetDtoObject() {
    auto position = this->scenePos();

    return new BlockDto(position.x(), position.y(), this->rect().width(), this->rect().height());
}

Block *Block::fromDtoObject(BlockDto dtoObject, Room *room) {
    return new Block(room, dtoObject.getX(), dtoObject.getY(), dtoObject.getWidth(), dtoObject.getHeight());
}

void Block::update(long long deltaMilliseconds) {
    if (isSelected() && isPaused()) {
        double width = this->rect().width();
        double height = this->rect().height();

        switch (currentPressedKey) {
            case Qt::Key_Right:
                width += width * 0.05;
                break;
            case Qt::Key_Left:
                width -= width * 0.05;
                break;
            case Qt::Key_Up:
                height += height * 0.05;
                break;
            case Qt::Key_Down:
                height -= height * 0.05;
                break;
        }

        this->setRect(0,0,width,height);
        if(currentPressedKey != -1){
            signalSender->sendUpdateExceptLocation();
        }
        this->currentPressedKey = -1;
    }
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
    signalSender->sendItemMovedSignal();
    QGraphicsItem::mouseMoveEvent(event);
}

void Block::pause() {
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    GameEntity::pause();
}

void Block::play() {
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    GameEntity::play();
}

void Block::keyPressEvent(QKeyEvent *event) {
    currentPressedKey = event->key();
    QGraphicsRectItem::keyPressEvent(event);
}

void Block::keyReleaseEvent(QKeyEvent *event) {
    currentPressedKey = -1;
    QGraphicsItem::keyReleaseEvent(event);
}
