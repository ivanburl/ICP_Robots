#include "pausableentity.h"

void PausableEntity::togglePause() {
    isPause = !isPause;
}

void PausableEntity::play() {
    isPause = false;
}

void PausableEntity::pause() {
    isPause = true;
}

bool PausableEntity::isPaused() const {
    return isPause;
}
