#include "CameraGrabber.h"
#include "constants.h"
#include <opencv2/imgproc.hpp>

CameraGrabber::CameraGrabber(QObject *parent)
    : QObject(parent)
{
}

CameraGrabber::~CameraGrabber()
{
    stop();
}

void CameraGrabber::start(int deviceId)
{
    if (m_cap.isOpened())
        return;

    if (!m_cap.open(deviceId, cv::CAP_V4L2))
        return;

    m_cap.set(cv::CAP_PROP_FRAME_WIDTH, camera::width);
    m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, camera::height);

    m_timer = new QTimer(this);
    m_timer->setTimerType(Qt::CoarseTimer);
    connect(m_timer, &QTimer::timeout, this, &CameraGrabber::grabFrame);
    m_timer->start(1000 / m_fps);
}

void CameraGrabber::stop()
{
    if (m_timer) {
        m_timer->stop();
        delete m_timer;
        m_timer = nullptr;
    }
    if (m_cap.isOpened())
        m_cap.release();
}

void CameraGrabber::grabFrame()
{
    cv::Mat bgr;
    if (!m_cap.read(bgr))
        return;

    cv::Mat rgb;
    cv::cvtColor(bgr, rgb, cv::COLOR_BGR2RGB);

    QImage frame(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    emit frameCaptured(frame.copy());
}

void CameraGrabber::setFps(int fps)
{
    if (fps < camera::fpsMin) fps = camera::fpsMin;
    if (fps > camera::fpsMax) fps = camera::fpsMax;
    m_fps = fps;

    if (m_timer && m_timer->isActive()) {
        m_timer->setInterval(1000 / m_fps);
    }
}
