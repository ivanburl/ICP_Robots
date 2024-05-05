/*! VUT FIT ICP
 * @file blockcomposer.h
 * @brief Block game entity binding class for property view  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef BLOCKCOMPOSER_H
#define BLOCKCOMPOSER_H

#include "block.h"
#include "graphicsitemcomposer.h"

#include <QObject>

class BlockComposer : public GraphicsItemComposer
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
public:
    explicit BlockComposer(Block* block);
private:
    Block* block;
public:
    int x();
    int y();
    int width();
    int height();
    QGraphicsItem* getOriginalGraphicsItem() const override;

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
    /**
     * Listens for signal when source block graphics item is moved
     */
    void itemMoved();
    /**
     * Listens for signal when all source robot graphics item's properties are updated except location
     */
    void updateExceptLocation();
};

#endif // BLOCKCOMPOSER_H
