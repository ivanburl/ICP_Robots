#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "room.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Room *currentRoom;

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void handleSaveRoom();
    void handleLoadRoom();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_actionAdd_robot_triggered();

    void on_actionAdd_block_triggered();
    void on_actionTogglePause_triggered();
};

#endif // MAINWINDOW_H
