#include "mainwindow.h"
#include "qdebug.h"
#include "ui_mainwindow.h"
#include "jsonfileaccessor.h"
#include "propertyview.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->ui->groupBox->hide();

    currentRoom = new Room(800, 600);
    propertiesWidget = new PropertyView(this->ui->groupBox);

    auto *view = ui->graphicsView;
    ui->graphicsView->setScene(currentRoom->scene());


    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    qDebug() << "main windows constructed";

    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::handleSaveRoom);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::handleLoadRoom);
    connect(ui->actionReset, &QAction::triggered, this, &MainWindow::handleResetRoom);
    configurePropertyViewConnections();
    currentRoom->start(60);
}

MainWindow::~MainWindow() {
    delete currentRoom;
    delete ui;
}

void MainWindow::handleSaveRoom(){
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save JSON File", "", "JSON Files (*.json)");

    if (filePath.isEmpty())
        return;

    auto dtoObject = currentRoom->GetDtoObject();

    auto jsonObject = dtoObject->toJsonObject();

    JsonFileAccessor jsonAccessor;

    jsonAccessor.WriteToFile(filePath, jsonObject);
}

void MainWindow::handleLoadRoom(){
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open JSON File", "", "JSON Files (*.json)");

    if (filePath.isEmpty())
        return;

    JsonFileAccessor jsonAccessor;

    auto* jsonObject = jsonAccessor.ReadFromFile(filePath);

    if(!jsonObject)
        return;

    disconnect(currentRoom, &Room::itemSelected, propertiesWidget, &PropertyView::processSelectedItem);
    disconnect(currentRoom, &Room::itemSelected, this, &MainWindow::handlePropertiesViewToggle);

    auto* roomDto = RoomDto::fromJsonObject(*jsonObject);

    currentRoom = Room::fromDtoObject(*roomDto);

    ui->graphicsView->setScene(currentRoom->scene());
    currentRoom->start(60);
    configurePropertyViewConnections();
    resizeEvent(nullptr);
}

void MainWindow::handleResetRoom(){
    currentRoom->reset();
    resizeEvent(nullptr);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    qDebug() << "Resize event caught" << ui->graphicsView->width() << " " << ui->graphicsView->height();
    ui->graphicsView->fitInView(currentRoom->scene()->sceneRect());
}

void MainWindow::configurePropertyViewConnections()
{
    connect(currentRoom, &Room::itemSelected, propertiesWidget, &PropertyView::processSelectedItem);
    connect(currentRoom, &Room::itemSelected, this, &MainWindow::handlePropertiesViewToggle);
}

void MainWindow::handlePropertiesViewToggle()
{
    ui->graphicsView->fitInView(currentRoom->scene()->sceneRect());
}

void MainWindow::on_actionAdd_robot_triggered() {
    if (currentRoom == nullptr) return;
    if (!currentRoom->isPaused()) {
        QMessageBox msgbox;
        msgbox.setText("Adding of robot is possible only during pause");
        msgbox.exec();
        return;
    }

    double size = (currentRoom->scene()->width() + currentRoom->scene()->height()) / 2;
    auto *robot = new Robot(
        currentRoom,
        currentRoom->scene()->width()/2, currentRoom->scene()->height()/2,  size*0.07, size*0.1, 90, 0,
        size/10, 12, 180
    );
    currentRoom->addRobot(robot);
    resizeEvent(nullptr);
}


void MainWindow::on_actionAdd_block_triggered() {
    if (currentRoom == nullptr) return;
    if (!currentRoom->isPaused()) {
        QMessageBox msgbox;
        msgbox.setText("Adding of block is possible only during pause");
        msgbox.exec();
        return;
    }
    double size = (currentRoom->scene()->width() + currentRoom->scene()->height()) / 2;
    auto *block = new Block(
        currentRoom,
        currentRoom->scene()->width()/2, currentRoom->scene()->height()/2, size*0.05, size*0.05);
    currentRoom->addBlock(block);
    resizeEvent(nullptr);
}

void MainWindow::on_actionTogglePause_triggered()
{
    if (currentRoom == nullptr)
        return;

    if (currentRoom->isPaused() && !currentRoom->isValidState()) {
        QMessageBox msgbox;
        msgbox.setText("Please fix errors to continue simulation:\n"
                       "Possible fixes are:\n"
                       "1) Robot is colliding with some collider (colliding robot is red)\n"
                       "2) Robot is out of room bounds (robot also red)\n");
        msgbox.exec();
        return;
    }

    currentRoom->togglePause();
    propertiesWidget->setPaused(currentRoom->isPaused());

    if (currentRoom->isPaused()) {
        ui->actionTogglePause->setText("Play");
        qDebug() << "game is paused";
    } else {
        ui->actionTogglePause->setText("Pause");
        qDebug() << "playing";
    }
}

