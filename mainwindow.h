#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QThread>
#include "camera/CameraGrabber.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void onFrameCaptured(const QImage &frame);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage m_lastFrame;
    CameraGrabber *m_cameraGrabber;
    QThread *m_cameraThread;
};

#endif // MAINWINDOW_H
