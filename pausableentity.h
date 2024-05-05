/*! VUT FIT ICP
 * @file pausableentity.h
 * @brief idk
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef PAUSABLEENTITY_H
#define PAUSABLEENTITY_H

class PausableEntity
{
private:
    bool isPause;
public:
    PausableEntity() : isPause(true) {
    };
    void togglePause();
    virtual void play();
    virtual void pause();
    bool isPaused() const;
};

#endif // PAUSABLEENTITY_H
