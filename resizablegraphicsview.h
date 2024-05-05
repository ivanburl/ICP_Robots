#ifndef RESIZABLEGRAPHICSVIEW_H
#define RESIZABLEGRAPHICSVIEW_H

#include <qgraphicsview.h>


class ResizableGraphicsView: public QGraphicsView
{
public :
    ResizableGraphicsView(QWidget* parent = nullptr) : QGraphicsView(parent) {

    }
    ResizableGraphicsView(QGraphicsScene *scene, QWidget* parent = nullptr) : QGraphicsView(scene, parent) {

    }
public:
    ResizableGraphicsView();

    /**
     * Scale scene items to fit them into graphic view
     * @param event
     */
    void resizeEvent(QResizeEvent *event) override;
};

#endif // RESIZABLEGRAPHICSVIEW_H
