#include "mainwindow.h"
#include "constants.h"
#include "ros/QtRosWorker.h"

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
    connect(m_cameraThread, &QThread::started, m_cameraGrabber, [this]() {
        m_cameraGrabber->start();
    });

    m_cameraThread->start();
}

MainWindow::~MainWindow()
{
    QMetaObject::invokeMethod(m_cameraGrabber, "stop", Qt::BlockingQueuedConnection);
    m_cameraThread->quit();
    m_cameraThread->wait();
    delete m_cameraGrabber;
}

void MainWindow::onFrameCaptured(const QImage &frame)
{
    m_turretWidget->setFrame(frame);
}

void MainWindow::setRosWorker(QtRosWorker *worker)
{
    m_rosWorker = worker;

    connect(this, &MainWindow::publishRequested,
            m_rosWorker, &QtRosWorker::publishCommand);

    connect(m_turretWidget, &TurretWidget::aimDeltaReceived,
            this, [this](float dx, float dy, bool laser) {
        float s = combat::speedMultiplier;
        emit publishRequested(0, 0, dx * s, dy * s, laser);
    });

    connect(m_turretWidget, &TurretWidget::commandReceived,
            this, [this](int cmd) {
        if (cmd == 2)
            emit publishRequested(0, 0, 0, 0, false);
    });
}
