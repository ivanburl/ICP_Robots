/*! VUT FIT ICP
 * @file updateentity.h
 * @brief idk 
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

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

private slots:
    void updateWrapper();
};

#endif // UPDATEENTITY_H
