/*! VUT FIT ICP
 * @file mainwindow.h
 * @brief Main window class
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "room.h"
#include "propertyview.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    PropertyView* propertiesWidget;
    Room *currentRoom;

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void handleSaveRoom();
    void handleLoadRoom();
    void handleResetRoom();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void configurePropertyViewConnections();

private slots:
    void handlePropertiesViewToggle();
    void on_actionAdd_robot_triggered();

    void on_actionAdd_block_triggered();
    void on_actionTogglePause_triggered();
};

#endif // MAINWINDOW_H
