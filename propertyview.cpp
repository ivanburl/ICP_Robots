#include "propertyview.h"
#include "block.h"
#include "robot.h"

#include <QLayoutItem>
#include <QLayout>
#include <QLabel>
#include <QDebug>

PropertyView::PropertyView(QGroupBox* groupBox) {
    this->groupBox = groupBox;
    QVBoxLayout *layout = new QVBoxLayout; // Create a QVBoxLayout
    groupBox->setLayout(layout);
}

void PropertyView::clearView(){
    QLayout *layout = groupBox->layout();
    if (!layout)
        return;

    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        QWidget *widget = item->widget();
        if (widget) {
            delete widget;
        }
        delete item;
    }
}

void PropertyView::addTextToLayout(QLayout *layout, const QString &text) {
    QLabel *label = new QLabel(text);
    if(layout){
        layout->addWidget(label);
    }
    else{
        qDebug() << "Its empty";
    }
}

void PropertyView::setPaused(bool isPaused)
{
    processPause(isPaused);
    this->isPaused = isPaused;
}

void PropertyView::processPause(bool isPaused)
{

}

void PropertyView::processSelectedItem(QGraphicsItem *selectedItem)
{
    qDebug() << "Some item selected";
    clearView();
    QLayout* layout = groupBox->layout();

    if(auto* block = dynamic_cast<Block*>(selectedItem); block){
        qDebug() << "Some block selected";

        // Set stretch factor for the groupBox
        // groupBox->setStretchFactor(groupBox, 1);
        groupBox->show();
        addTextToLayout(layout, "Block");
    }
    else if(auto* robot = dynamic_cast<Robot*>(selectedItem); robot){
        qDebug() << "Some robot selected";
        groupBox->show();
        addTextToLayout(layout, "Robot");
    }
    else{
        groupBox->hide();
    }
}
