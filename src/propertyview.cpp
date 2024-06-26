/*! VUT FIT ICP
 * @file propertyview.cpp
 * @brief propertyview.h implementation
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "propertyview.h"
#include "block.h"
#include "blockcomposer.h"
#include "qobjectdefs.h"
#include "robot.h"
#include "robotcomposer.h"

#include <QLayoutItem>
#include <QLayout>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include <QIntValidator>
#include <QMetaMethod>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QPushButton>

PropertyView::PropertyView(QGroupBox* groupBox) {
    this->groupBox = groupBox;
    QFormLayout *layout = new QFormLayout;
    groupBox->setLayout(layout);
}

void PropertyView::clearView(){
    disconnectAll();

    QLayout *layout = groupBox->layout();
    if (!layout)
        return;

    QLayoutItem *item;

    if(layout->count() != 0){
        while ((item = layout->takeAt(0)) != nullptr) {
            QWidget *widget = item->widget();
            if (widget) {
                delete widget;
            }
            delete item;
        }
    }
}

void PropertyView::disconnectAll() {
    for (const auto &connection : connections) {
        QObject::disconnect(connection);
    }

    connections.clear();
}

void PropertyView::addTextToLayout(const QString &text) {
    QLayout* layout = groupBox->layout();
    QLabel *label = new QLabel(text);
    if(layout){
        layout->addWidget(label);
    }
}


void PropertyView::prepareView(GraphicsItemComposer *object)
{
    auto* layout = groupBox->layout();

    const QMetaObject *metaObject = object->metaObject();

    for (int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i) {
        const QMetaProperty metaProperty = metaObject->property(i);

        QWidget *widget = nullptr;
        if (metaProperty.isReadable() && metaProperty.isWritable()) {
            QMetaMethod notifySignalMethod = metaProperty.notifySignal();

            QByteArray notifySignalSignature = notifySignalMethod.methodSignature();

            const QString signalName(notifySignalSignature);

            if (metaProperty.type() == QVariant::Int) {
                QSpinBox *spinBox = new QSpinBox(groupBox);
                spinBox->setMaximum(1000);
                spinBox->setValue(metaProperty.read(object).toInt());
                connections.append(QObject::connect(spinBox, &QSpinBox::editingFinished,
                                                    object, [object, metaProperty, spinBox]() {
                                                        metaProperty.write(object, spinBox->value());
                                                    }));

                const auto* signalNameChar = ("2" + signalName).toUtf8().constData();

                connections.append(QObject::connect(object, signalNameChar,
                                                    spinBox, SLOT(setValue(int))));
                widget = spinBox;
            } else if (metaProperty.type() == QVariant::Double) {
                QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(groupBox);
                doubleSpinBox->setMaximum(1000);
                doubleSpinBox->setMinimum(-360);
                doubleSpinBox->setValue(metaProperty.read(object).toDouble());
                connections.append(QObject::connect(doubleSpinBox, &QDoubleSpinBox::editingFinished,
                                                    object, [object, metaProperty, doubleSpinBox]() {
                                                        metaProperty.write(object, doubleSpinBox->value());
                                                    }));

                const auto* signalNameChar = ("2" + signalName).toUtf8().constData();
                connections.append(QObject::connect(object, signalNameChar,
                                                    doubleSpinBox, SLOT(setValue(double))));
                widget = doubleSpinBox;
            } else if (metaProperty.type() == QVariant::Bool) {
                QCheckBox *checkBox = new QCheckBox(groupBox);
                checkBox->setChecked(metaProperty.read(object).toBool());
                connections.append(QObject::connect(checkBox, &QCheckBox::toggled,
                                                    object, [object, metaProperty, checkBox]() {
                                                        metaProperty.write(object, checkBox->isChecked());
                                                    }));
                const auto* signalNameChar = ("2" + signalName).toUtf8().constData();
                connections.append(QObject::connect(object, signalNameChar,
                                                    checkBox, SLOT(setChecked(bool))));
                widget = checkBox;
            } else if (metaProperty.type() == QVariant::String) {
                QLineEdit *lineEdit = new QLineEdit(groupBox);
                lineEdit->setText(metaProperty.read(object).toString());
                connections.append(QObject::connect(lineEdit, &QLineEdit::editingFinished,
                                                    object, [object, metaProperty, lineEdit]() {
                                                        metaProperty.write(object, lineEdit->text());
                                                    }));
                const auto* signalNameChar = ("2" + signalName).toUtf8().constData();
                connections.append(QObject::connect(object, signalNameChar,
                                                    lineEdit, SLOT(setText(QString))));
                widget = lineEdit;
            }
        }

        if (widget) {
            static_cast<QFormLayout*>(layout)->addRow(new QLabel(metaProperty.name()), widget);
        }
    }

    auto* deleteBtn = new QPushButton("Delete");
    groupBox->layout()->addWidget(deleteBtn);

    connections.append(connect(deleteBtn, &QPushButton::clicked, this, [object, this](){
        this->groupBox->hide();
        this->clearView();
        emit itemDeleted(object->getOriginalGraphicsItem());
    }));
}

void PropertyView::setPaused(bool isPaused)
{
    processPause(isPaused);
    this->isPaused = isPaused;
}

void PropertyView::processPause(bool isPaused)
{
    if(this->isPaused != isPaused){
        groupBox->setEnabled(isPaused);
    }
}

void PropertyView::processSelectedItem(QGraphicsItem *selectedItem)
{
    if(currentObject == selectedItem){
        return;
    }
    currentObject = selectedItem;
    clearView();

    if(auto* block = dynamic_cast<Block*>(selectedItem); block){
        qDebug() << "Some block selected";

        auto* composer = new BlockComposer(block);
        this->prepareView(composer);
        groupBox->show();
    }
    else if(auto* robot = dynamic_cast<Robot*>(selectedItem); robot){
        qDebug() << "Some robot selected";

        auto* composer = new RobotComposer(robot);
        this->prepareView(composer);
        groupBox->show();
    }
    else{
        groupBox->hide();
    }
}
