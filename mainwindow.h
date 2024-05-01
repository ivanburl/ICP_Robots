#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "room.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleSaveRoom();
    void handleLoadRoom();

private:
    Ui::MainWindow *ui;
    Room* room;
};

#endif // MAINWINDOW_H
