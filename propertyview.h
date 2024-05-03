#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

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

    QGroupBox* groupBox;
    bool isPaused;
    void addTextToLayout(QLayout *layout, const QString &text);
public slots:
    void processSelectedItem(QGraphicsItem* selectedItem);
};

#endif // PROPERTYVIEW_H
