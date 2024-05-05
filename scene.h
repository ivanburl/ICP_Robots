/*! VUT FIT ICP
 * @file scene.h
 * @brief QGraphicsScene wrapper that emits signal with item pressed on on click 
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(int w, int h);
signals:
    void itemPressed(QGraphicsItem* item);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};

#endif // SCENE_H
