#ifndef BLOCKCOMPOSER_H
#define BLOCKCOMPOSER_H

#include "block.h"

#include <QObject>

class BlockComposer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
public:
    explicit BlockComposer(Block* block, QObject *parent = nullptr);
private:
    Block* block;
public:
    int x();
    int y();
    int width();
    int height();

    void setX(int value);
    void setY(int value);
    void setWidth(int value);
    void setHeight(int value);

signals:
    void xChanged(int value);
    void yChanged(int value);
    void widthChanged(int value);
    void heightChanged(int value);

private slots:
    void itemMoved();
};

#endif // BLOCKCOMPOSER_H
