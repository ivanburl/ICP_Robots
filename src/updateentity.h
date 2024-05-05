/*! VUT FIT ICP
 * @file updateentity.h
 * @brief entity with ability to periodically update
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef UPDATEENTITY_H
#define UPDATEENTITY_H

#include<QObject>
#include <qelapsedtimer.h>
#include <qtimer.h>

/**
 * Entity with ability to periodically update
 */
class UpdateEntity : public QObject {
    Q_OBJECT

private:
    QTimer timer;
    QElapsedTimer elapsedTimer;
    std::function<void(long long)> update;

public:
    UpdateEntity(std::function<void(long long)> update);

    /**
     * Start the game logic loop of the entity whith specific fps
     * @param fps - desired fps for main game logic loop
     */
    void start(int fps);

    /**
     * Stop the updates of the entity
     */
    void stop();

private slots:
    void updateWrapper();
};

#endif // UPDATEENTITY_H
