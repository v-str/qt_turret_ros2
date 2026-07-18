#include "mainwindow.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(ui::windowTitle);
    resize(ui::windowWidth, ui::windowHeight);

    m_turretWidget = new TurretWidget(this);
    setCentralWidget(m_turretWidget);

    m_cameraGrabber = new CameraGrabber();
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
    delete m_cameraGrabber;
}

void MainWindow::onFrameCaptured(const QImage &frame)
{
    m_turretWidget->setFrame(frame);
}
