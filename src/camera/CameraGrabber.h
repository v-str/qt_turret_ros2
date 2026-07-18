#pragma once

#include <QObject>
#include <QTimer>
#include <QImage>
#include <opencv2/videoio.hpp>
#include "constants.h"

class CameraGrabber : public QObject
{
    Q_OBJECT

public:
    explicit CameraGrabber(QObject *parent = nullptr);
    ~CameraGrabber() override;

    void setFps(int fps);

public slots:
    void start(int deviceId = 0);
    void stop();

signals:
    void frameCaptured(const QImage &frame);
    void cameraOpened(bool ok);

private:
    void grabFrame();

    cv::VideoCapture m_cap;
    QTimer *m_timer = nullptr;
    int m_fps = camera::fpsDefault;
};
