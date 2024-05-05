#ifndef GRAPHICSITEMCOMPOSER_H
#define GRAPHICSITEMCOMPOSER_H

#include "qgraphicsitem.h"
class GraphicsItemComposer : public QObject{
    Q_OBJECT;
public:
    virtual QGraphicsItem* getOriginalGraphicsItem() const = 0;
};

#endif // GRAPHICSITEMCOMPOSER_H
