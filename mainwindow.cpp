#include "mainwindow.h"
#include "constants.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(ui::windowTitle);
    resize(ui::windowWidth, ui::windowHeight);

    m_cameraGrabber = new CameraGrabber(this);
    m_cameraThread = new QThread(this);
    m_cameraGrabber->moveToThread(m_cameraThread);

    connect(m_cameraGrabber, &CameraGrabber::frameCaptured,
            this, &MainWindow::onFrameCaptured);
    connect(m_cameraThread, &QThread::started, this, [this]() {
        m_cameraGrabber->start();
    });

    m_cameraThread->start();
}

MainWindow::~MainWindow()
{
    m_cameraGrabber->stop();
    m_cameraThread->quit();
    m_cameraThread->wait();
}

void MainWindow::onFrameCaptured(const QImage &frame)
{
    m_lastFrame = frame;
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if (m_lastFrame.isNull()) {
        p.fillRect(rect(), Qt::black);
        return;
    }

    auto scaled = m_lastFrame.scaled(
        size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    int x = (width() - scaled.width()) / 2;
    int y = (height() - scaled.height()) / 2;
    p.drawImage(x, y, scaled);
}
