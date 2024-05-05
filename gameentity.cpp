/*! VUT FIT ICP
 * @file gameentity.cpp
 * @brief gameentity.h implementation  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "gameentity.h"


GameEntity::GameEntity(): fixedUpdateEntity([this](long long delta) { this->fixedUpdate(delta); }),
                          updateEntity([this](long long delta) { this->update(delta); }) {
}

void GameEntity::start(int fps) {
    this->fixedUpdateEntity.start(fps);
    this->updateEntity.start(1000);
}

void GameEntity::stop() {
    this->fixedUpdateEntity.stop();
    this->updateEntity.stop();
}

GameEntity::~GameEntity() = default;
