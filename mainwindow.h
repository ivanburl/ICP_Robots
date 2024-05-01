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
    Room *currentRoom;

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    Room *getRoom() {
        return currentRoom;
    }

private:
    Ui::MainWindow *ui;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_actionAdd_robot_triggered();

    void on_actionAdd_block_triggered();
};

#endif // MAINWINDOW_H
