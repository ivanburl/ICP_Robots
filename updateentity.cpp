#include "updateentity.h"

UpdateEntity::UpdateEntity(std::function<void(long long)> update) {
    this->update = update;
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(updateWrapper()));
}

void UpdateEntity::start(int targetFps) {
    timer.start(1e3 / targetFps);
    elapsedTimer.start();
}

void UpdateEntity::stop() {
    timer.stop();
}


void UpdateEntity::updateWrapper() {
    long long elapsedTimeMillis = this->elapsedTimer.elapsed();
    if (elapsedTimeMillis == 0) return;
    this->elapsedTimer.restart();
    this->update(elapsedTimeMillis);
}
