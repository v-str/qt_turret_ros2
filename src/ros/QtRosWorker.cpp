#include "QtRosWorker.h"
#include "constants.h"

QtRosWorker::QtRosWorker(QObject *parent)
    : QObject(parent)
{
}

QtRosWorker::~QtRosWorker()
{
    stop();
}

void QtRosWorker::start()
{
    m_handler = std::make_unique<RosHandler>();
    m_handler->setStatusCallback([this](float pan, float tilt, bool laser) {
        // TODO: queue for main thread when we add status display
    });

    try {
        m_handler->init();
        emit statusMessage("Турель подключена", LogType::Success);
    } catch (const std::exception &e) {
        emit statusMessage(QString("Ошибка ROS: %1").arg(e.what()), LogType::Error);
        return;
    }

    m_running = true;
    m_rosThread = std::thread(&QtRosWorker::rosLoop, this);
}

void QtRosWorker::rosLoop()
{
    while (m_running)
        m_handler->run();
}

void QtRosWorker::stop()
{
    m_running = false;
    if (m_rosThread.joinable())
        m_rosThread.join();
    if (m_handler) {
        m_handler->stop();
        m_handler.reset();
    }
    emit finished();
}

void QtRosWorker::publishCommand(float pan, float tilt, float pan_vel, float tilt_vel, bool laser)
{
    if (m_handler)
        m_handler->publishCommand(pan, tilt, pan_vel, tilt_vel, laser);
}
