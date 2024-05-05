/*! VUT FIT ICP
 * @file blockcomposer.cpp
 * @brief blockcomposer.h implementation
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "blockcomposer.h"

BlockComposer::BlockComposer(Block* block)
{
    this->block = block;
    connect(block->getSignalSender(), &SignalSender::itemMoved, this, &BlockComposer::itemMoved);
    connect(block->getSignalSender(), &SignalSender::updateExceptLocation, this, &BlockComposer::updateExceptLocation);
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
QGraphicsItem *BlockComposer::getOriginalGraphicsItem() const{
    return block;
}

void BlockComposer::setX(int value){
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

void BlockComposer::updateExceptLocation()
{
    emit widthChanged(width());
    emit heightChanged(height());
}
