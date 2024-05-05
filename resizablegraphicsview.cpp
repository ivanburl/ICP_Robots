#include "resizablegraphicsview.h"
#include "qdebug.h"

ResizableGraphicsView::ResizableGraphicsView() {}

void ResizableGraphicsView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    qDebug() << "Resize event caught on graphics view " << this->width() << " " << this->height();
    this->fitInView(this->scene()->sceneRect());
}
