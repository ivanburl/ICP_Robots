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
    void resizeEvent(QResizeEvent *event) override;
};

#endif // RESIZABLEGRAPHICSVIEW_H
