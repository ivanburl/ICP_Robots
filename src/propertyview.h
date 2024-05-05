/*! VUT FIT ICP
 * @file propertyview.h
 * @brief Property view management class
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include "graphicsitemcomposer.h"
#include <QGroupBox>
#include <QGraphicsItem>

class PropertyView : public QObject
{
    Q_OBJECT
public:
    /**
     * PropertyView constructor
     * @param groupBox - QGroupBox, where game entities' property fields will be placed on 
     */
    PropertyView(QGroupBox* groupBox);
    void setPaused(bool isPaused);
private:
    /**
     * Set property view to disabled if paused
     * @param isPaused - whether simulation is paused 
     */
    void processPause(bool isPaused);
    /**
     * Clears property view
     */
    void clearView();
    /**
     * Disconnects all signals added to connections object field
     */
    void disconnectAll();
    /**
     * Adds text to layout
     */
    void addTextToLayout(const QString &text);
    /**
     * Prepares property view for game entity
     */
    void prepareView(GraphicsItemComposer* robot);

    QGroupBox* groupBox;
    QGraphicsItem* currentObject;
    bool isPaused;
    QVector<QMetaObject::Connection> connections;
public slots:
    /**
     * Processes selected on scene item
     */
    void processSelectedItem(QGraphicsItem* selectedItem);
signals:
    /**
     * Graphics item has to be deleted
     */
    void itemDeleted(QGraphicsItem* itemToDelete);
};

#endif // PROPERTYVIEW_H
