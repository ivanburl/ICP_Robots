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
    /**
     * Scene constructor
     * @param w - width of the scene
     * @param h - height of the scene
     */
    Scene(int w, int h);
signals:
    /**
     * Signal that is emitted when clicked on the scene
     * @param item - QGraphicsItem object clicked on
     */
    void itemPressed(QGraphicsItem* item);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};

#endif // SCENE_H
