/*! VUT FIT ICP
 * @file resizablegraphicsview.cpp
 * @brief resizablegraphicsview.h implementation
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "resizablegraphicsview.h"
#include "qdebug.h"

ResizableGraphicsView::ResizableGraphicsView() {}

void ResizableGraphicsView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    qDebug() << "Resize event caught on graphics view " << this->width() << " " << this->height();
    this->fitInView(this->scene()->sceneRect());
}
