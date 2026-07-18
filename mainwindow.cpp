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
    connect(m_cameraGrabber, &CameraGrabber::cameraOpened,
            this, [this](bool ok) {
        if (ok)
            emit m_turretWidget->logRequested("Камера подключена", LogType::Success);
        else
            emit m_turretWidget->logRequested("Ошибка камеры: не удалось открыть", LogType::Error);
    });
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
            this, [this](float pan, float tilt, float pan_vel, float tilt_vel, bool laser) {
        emit publishRequested(pan, tilt, pan_vel, tilt_vel, laser);
    });

    connect(m_turretWidget, &TurretWidget::commandReceived,
            this, [this](int /*cmd*/) {
        // handled entirely in TurretWidget::sendCommand
    });

    connect(m_rosWorker, &QtRosWorker::statusMessage,
            this, [this](const QString &msg, int type) {
        emit m_turretWidget->logRequested(msg, type);
    });
}
