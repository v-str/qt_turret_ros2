#ifndef QTROSWORKER_H
#define QTROSWORKER_H

#include <QObject>
#include <thread>
#include <atomic>
#include <memory>
#include "RosHandler.h"

class QtRosWorker : public QObject
{
    Q_OBJECT

public:
    explicit QtRosWorker(QObject *parent = nullptr);
    ~QtRosWorker() override;

    void stop();

public slots:
    void start();
    void publishCommand(float pan, float tilt, float pan_vel, float tilt_vel, bool laser);

signals:
    void statusUpdated(float pan_pos, float tilt_pos, bool laser);
    void finished();

private:
    void rosLoop();

    std::unique_ptr<RosHandler> m_handler;
    std::thread                 m_rosThread;
    std::atomic<bool>           m_running{false};
};

#endif // QTROSWORKER_H
