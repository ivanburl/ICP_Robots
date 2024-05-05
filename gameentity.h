#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "pausableentity.h"
#include "updateentity.h"

#include <QElapsedTimer>
#include <QObject>
#include <qtimer.h>

/**
 * Entity with ability to peridiocally update and pause
 */
class GameEntity: public QObject, public PausableEntity {
    Q_OBJECT

private:
    UpdateEntity fixedUpdateEntity;
    UpdateEntity updateEntity;

public:
    GameEntity();

    void start(int fps);

    /**
     * main game logic loop of the entity, runs with fixed fps
     * @param deltaMilliseonds milliseconds passed after last frame
     */
    virtual void fixedUpdate(long long deltaMilliseonds) = 0;

    /**
     * Runs with maximum fps (targeting 1000 fps),
     * great for graphical updates and listening to keyborad signals
     * @param deltaMilliseconds
     */
    virtual void update(long long deltaMilliseconds) = 0;

    /**
     * stop all updates of the entity
     */
    void stop();

    ~GameEntity() override;
};

#endif // GAMEENTITY_H
