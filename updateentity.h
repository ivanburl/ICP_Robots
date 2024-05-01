#ifndef UPDATEENTITY_H
#define UPDATEENTITY_H

#include<QObject>
#include <qelapsedtimer.h>
#include <qtimer.h>


class UpdateEntity : public QObject {
    Q_OBJECT

private:
    QTimer timer;
    QElapsedTimer elapsedTimer;
    std::function<void(long long)> update;

public:
    UpdateEntity(std::function<void(long long)> update);

    void start(int fps);

    void stop();

private:
    void updateWrapper();
};

#endif // UPDATEENTITY_H
