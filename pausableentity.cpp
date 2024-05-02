#include "pausableentity.h"

void PausableEntity::togglePause() {
    if (isPaused()) {
        play();
    } else {
        pause();
    }
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
