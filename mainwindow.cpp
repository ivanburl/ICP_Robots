#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsonfileaccessor.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //room = new Room();

    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::handleSaveRoom);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::handleLoadRoom);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleSaveRoom(){
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save JSON File", "", "JSON Files (*.json)");

    if (filePath.isEmpty())
        return;

    auto jsonObject = room->GetDtoObject()->toJsonObject();
    JsonFileAccessor jsonAccessor;

    jsonAccessor.WriteToFile(filePath, jsonObject);
}

void MainWindow::handleLoadRoom(){
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Open JSON File", "", "JSON Files (*.json)");

    if (filePath.isEmpty())
        return;

    JsonFileAccessor jsonAccessor;

    auto* jsonObject = jsonAccessor.ReadFromFile(filePath);

    if(!jsonObject)
        return;

    auto* roomDto = RoomDto::fromJsonObject(*jsonObject);
    room = Room::fromDtoObject(*roomDto);
}
