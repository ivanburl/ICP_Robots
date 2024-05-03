#include "scene.h"
#include "qgraphicsitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Scene::Scene(int w, int h) : QGraphicsScene(0, 0, w, h) {}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event){
    auto* item = itemAt(event->scenePos(), QTransform());
    if(item && item->group()){
        item = item->group();
    }
    emit itemPressed(item);
    QGraphicsScene::mousePressEvent(event);
}
