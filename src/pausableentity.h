/*! VUT FIT ICP
 * @file pausableentity.h
 * @brief Entity with ability to pause logic
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef PAUSABLEENTITY_H
#define PAUSABLEENTITY_H

/**
 * Entity with ability to pause logic
 */
class PausableEntity
{
private:
    bool isPause;
public:
    PausableEntity() : isPause(true) {
    };

    /**
     * toggle pause
     */
    void togglePause();

    /**
     * resume entity work
     */
    virtual void play();

    /**
     * pause entity work
     */
    virtual void pause();

    /**
     * Whether entity is pause
     * @return true if pause, otherwise false
     */
    bool isPaused() const;
};

#endif // PAUSABLEENTITY_H
