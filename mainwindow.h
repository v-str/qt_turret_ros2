#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "camera/CameraGrabber.h"
#include "turretwidget.h"

class QtRosWorker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setRosWorker(QtRosWorker *worker);

public slots:
    void onFrameCaptured(const QImage &frame);

signals:
    void publishRequested(float pan, float tilt, float pan_vel, float tilt_vel, bool laser);

private:
    TurretWidget *m_turretWidget;
    CameraGrabber *m_cameraGrabber;
    QThread *m_cameraThread;
    QtRosWorker *m_rosWorker = nullptr;
};

#endif // MAINWINDOW_H
