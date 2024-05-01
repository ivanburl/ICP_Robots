#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "pausableentity.h"
#include "updateentity.h"

#include <QElapsedTimer>
#include <QObject>
#include <qtimer.h>


class GameEntity: public QObject, PausableEntity {
    Q_OBJECT

private:
    UpdateEntity fixedUpdateEntity;
    UpdateEntity updateEntity;

public:
    GameEntity();

    void start(int fps);

    virtual void fixedUpdate(long long deltaMilliseonds) = 0;

    virtual void update(long long deltaMilliseconds) = 0;

    void stop();

    ~GameEntity() override;
};

#endif // GAMEENTITY_H
