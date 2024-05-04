#include "blockcomposer.h"

BlockComposer::BlockComposer(Block* block, QObject *parent)
    : QObject{parent}
{
    this->block = block;
    connect(block->getSignalSender(), &SignalSender::itemMoved, this, &BlockComposer::itemMoved);
}

int BlockComposer::x(){
    return block->pos().x();
}
int BlockComposer::y(){
    return block->pos().y();
}
int BlockComposer::width(){
    return block->rect().width();
}
int BlockComposer::height(){
    return block->rect().height();
}

void BlockComposer::setX(int value){
    qDebug() << "Im here";
    block->setPos(value, block->pos().y());
}
void BlockComposer::setY(int value){
    block->setPos(block->pos().x(), value);
}
void BlockComposer::setWidth(int value){
    auto prev_rect = block->rect();
    prev_rect.setWidth(value);
    block->setRect(prev_rect);
}
void BlockComposer::setHeight(int value)
{
    auto prev_rect = block->rect();
    prev_rect.setHeight(value);
    block->setRect(prev_rect);
}

void BlockComposer::itemMoved()
{
    emit xChanged(x());
    emit yChanged(y());
}