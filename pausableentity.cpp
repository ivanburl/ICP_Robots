/*! VUT FIT ICP
 * @file pausableentity.cpp
 * @brief pausableentity.h implementation
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

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
