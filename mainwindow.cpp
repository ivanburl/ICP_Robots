#include "mainwindow.h"
#include "qdebug.h"
#include "ui_mainwindow.h"
#include "jsonfileaccessor.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>

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

    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::handleSaveRoom);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::handleLoadRoom);
    connect(ui->actionReset, &QAction::triggered, this, &MainWindow::handleResetRoom);
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

    auto* roomDto = RoomDto::fromJsonObject(*jsonObject);

    currentRoom = Room::fromDtoObject(*roomDto);

    ui->graphicsView->setScene(currentRoom);
    resizeEvent(nullptr);
}

void MainWindow::handleResetRoom(){
    currentRoom->reset();
    resizeEvent(nullptr);
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
        300, 300, 30, 30);
    currentRoom->addBlock(block);
    resizeEvent(nullptr);
}

void MainWindow::on_actionTogglePause_triggered()
{
    if (currentRoom == nullptr)
        return;
    currentRoom->togglePause();

    if (currentRoom->isPaused()) {
        ui->actionTogglePause->setText("Play");
        qDebug() << "game is paused";
    } else {
        ui->actionTogglePause->setText("Pause");
        qDebug() << "playing";
    }
}

