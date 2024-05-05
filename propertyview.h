#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include "graphicsitemcomposer.h"
#include <QGroupBox>
#include <QGraphicsItem>

class PropertyView : public QObject
{
    Q_OBJECT
public:
    PropertyView(QGroupBox* groupBox);
    void setPaused(bool isPaused);
private:
    void processPause(bool isPaused);
    void clearView();
    void disconnectAll();
    void addTextToLayout(const QString &text);
    void prepareView(GraphicsItemComposer* robot);

    QGroupBox* groupBox;
    QGraphicsItem* currentObject;
    bool isPaused;
    QVector<QMetaObject::Connection> connections;
    void disconnectObjectConnections(QObject *object);
public slots:
    void processSelectedItem(QGraphicsItem* selectedItem);
signals:
    void itemDeleted(QGraphicsItem* itemToDelete);
};

#endif // PROPERTYVIEW_H
