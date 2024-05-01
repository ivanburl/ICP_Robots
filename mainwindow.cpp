#include "mainwindow.h"
#include "qdebug.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    currentRoom = new Room(800, 600);

    auto *view = ui->graphicsView;
    ui->graphicsView->setScene(currentRoom);


    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    qDebug() << "main windows constructed";
}

MainWindow::~MainWindow() {
    delete currentRoom;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    qDebug() << "Resize event caught" << ui->graphicsView->width() << " " << ui->graphicsView->height();
    ui->graphicsView->fitInView(currentRoom->sceneRect());
}

void MainWindow::on_actionAdd_robot_triggered() {
    qDebug() << "oh fuck I am triggered";
    auto *robot = new Robot(
        currentRoom,
        300, 300, 100, 200, 60, 30,
        100, 90, 180
    );
    currentRoom->addRobot(robot);
    resizeEvent(nullptr);
}


void MainWindow::on_actionAdd_block_triggered() {
    auto *block = new Block(
        currentRoom,
        300, 300, 100, 100);
    currentRoom->addBlock(block);
    resizeEvent(nullptr);
}
