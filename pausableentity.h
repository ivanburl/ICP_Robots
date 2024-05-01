#ifndef PAUSABLEENTITY_H
#define PAUSABLEENTITY_H

class PausableEntity
{
private:
    bool isPause;
public:
    PausableEntity() : isPause(false) {

    };
    void togglePause();
    void play();
    void pause();
    bool isPaused() const;
};

#endif // PAUSABLEENTITY_H
