#include "mainwindow.h"
#include "robot.h"

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QtGui>
#include <QVBoxLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // auto* scene = new QGraphicsScene();
    // scene->setSceneRect(0, 0, 800, 600);


    // auto* view = new QGraphicsView(scene);
    // view->setMinimumSize(800, 600);
    // view->setFixedSize(800, 600);
    // view->setSceneRect(0, 0, 800, 600);

    // view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // view->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // view->show();

    // auto* robot = new Robot(
    //     nullptr,
    //     300, 300, 100, 200, 60, 30,
    //     100, 90, 180
    // );

    // robot->move(1e9);

    // scene->addItem(robot);

    // auto* robot2 = new Robot(
    //     nullptr,
    //     300, 300, 100, 200, 60, 30,
    //     100, 90, 180
    //     );


    // scene->addItem(robot2);

    // auto* rect = new QGraphicsRectItem(100, 100, 100, 100);
    // rect->setTransform(QTransform().rotate(30), true);

    // scene -> addItem(rect);

    // auto* rect2 = new QGraphicsRectItem(100, 100, 100, 100);
    // scene -> addItem(rect2);

    // QWidget mainWidget;

    // // Outer layout to hold everything
    // QVBoxLayout *outerLayout = new QVBoxLayout();
    // mainWidget.setLayout(outerLayout);

    // // Top section
    // QLabel *topLabel = new QLabel("Top Section");
    // outerLayout->addWidget(topLabel);

    // // Middle section (Horizontal layout for left, center, right)
    // QHBoxLayout *middleLayout = new QHBoxLayout();

    // QLabel *leftLabel = new QLabel("Left Section");
    // middleLayout->addWidget(leftLabel);

    // QLabel *centerLabel = new QLabel("Center Section");
    // middleLayout->addWidget(centerLabel, 1);  // Give more stretch to center part

    // QLabel *rightLabel = new QLabel("Right Section");
    // middleLayout->addWidget(rightLabel);

    // outerLayout->addLayout(middleLayout);

    // // Bottom section
    // QLabel *bottomLabel = new QLabel("Bottom Section");
    // outerLayout->addWidget(bottomLabel);

    // outerLayout->setAlignment(Qt::AlignCenter);
    // middleLayout->setAlignment(Qt::AlignCenter);
    // centerLabel->setAlignment(Qt::AlignCenter);
    // leftLabel->setAlignment(Qt::AlignCenter);
    // rightLabel->setAlignment(Qt::AlignCenter);
    // bottomLabel->setAlignment(Qt::AlignCenter);
    // topLabel->setAlignment(Qt::AlignCenter);

    // // Show the main widget
    // mainWidget.show();
    // mainWidget.setMinimumSize(800, 600);


    MainWindow window;
    window.show();

    return a.exec();
}
