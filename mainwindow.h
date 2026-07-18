#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "camera/CameraGrabber.h"
#include "turretwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void onFrameCaptured(const QImage &frame);

private:
    TurretWidget *m_turretWidget;
    CameraGrabber *m_cameraGrabber;
    QThread *m_cameraThread;
};

#endif // MAINWINDOW_H
