#ifndef TURRETWIDGET_H
#define TURRETWIDGET_H

#include <QWidget>
#include <QImage>
#include <QMutex>
#include <QQuickImageProvider>
#include <QCursor>

class ImageProvider : public QQuickImageProvider
{
    Q_OBJECT
    Q_PROPERTY(int counter READ counter NOTIFY counterChanged)

public:
    ImageProvider();

    void setFrame(const QImage &frame);
    int counter() const { return m_counter; }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

signals:
    void counterChanged();

private:
    QImage m_frame;
    QImage m_placeholder;
    QMutex m_mutex;
    int m_counter = 0;
};

class TurretWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool laserOn READ laserOn NOTIFY laserOnChanged)

public:
    explicit TurretWidget(QWidget *parent = nullptr);
    ~TurretWidget() override;

    void setFrame(const QImage &frame);

    bool laserOn() const { return m_laserOn; }

    Q_INVOKABLE void warpMouse(int x, int y);
    Q_INVOKABLE void sendAimDelta(float dx, float dy);
    Q_INVOKABLE void sendCommand(int cmd);
    Q_INVOKABLE void resetPosition();
    Q_INVOKABLE void toggleLaser();

signals:
    void aimDeltaReceived(float pan, float tilt, float pan_vel, float tilt_vel, bool laserOn);
    void commandReceived(int cmd);
    void logRequested(const QString &msg, int type);
    void laserOnChanged();

private:
    ImageProvider *m_imageProvider = nullptr;
    float m_panPos = 0.0f;
    float m_tiltPos = 0.0f;
    bool m_laserOn = false;
};

#endif
