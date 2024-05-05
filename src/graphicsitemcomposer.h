/*! VUT FIT ICP
 * @file graphicsitemcomposer.h
 * @brief Abstract class for classes that are bindable to property view  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef GRAPHICSITEMCOMPOSER_H
#define GRAPHICSITEMCOMPOSER_H

#include "qgraphicsitem.h"
class GraphicsItemComposer : public QObject{
    Q_OBJECT;
public:
    virtual QGraphicsItem* getOriginalGraphicsItem() const = 0;
};

#endif // GRAPHICSITEMCOMPOSER_H
