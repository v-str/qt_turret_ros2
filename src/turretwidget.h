#ifndef TURRETWIDGET_H
#define TURRETWIDGET_H

#include <QWidget>
#include <QImage>
#include <QMutex>
#include <QQuickImageProvider>
#include <QCursor>
#include "commanddata.h"

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
    Q_PROPERTY(bool fanOn READ fanOn NOTIFY fanOnChanged)
    Q_PROPERTY(bool combatBlocked READ combatBlocked NOTIFY combatBlockedChanged)
    Q_PROPERTY(QString combatBlockedReason READ combatBlockedReason NOTIFY combatBlockedChanged)
    Q_PROPERTY(float temperature READ temperature NOTIFY temperatureChanged)

public:
    explicit TurretWidget(QWidget *parent = nullptr);
    ~TurretWidget() override;

    void setFrame(const QImage &frame);

    bool laserOn() const { return m_laserOn; }
    bool fanOn() const { return m_fanOn; }
    bool combatBlocked() const { return m_cameraError || m_rosError; }
    QString combatBlockedReason() const { return m_blockedReason; }
    float temperature() const { return m_temperature; }

    void setCameraError(bool v);
    void setRosError(bool v);
    void setTemperature(float t);

    Q_INVOKABLE void warpMouse(int x, int y);
    Q_INVOKABLE void sendAimDelta(float dx, float dy);
    Q_INVOKABLE void sendCommand(int cmd);
    Q_INVOKABLE void resetPosition();
    Q_INVOKABLE void toggleLaser();
    Q_INVOKABLE void toggleFan();

signals:
    void aimDeltaReceived(const CommandData &cmd);
    void commandReceived(int cmd);
    void logRequested(const QString &msg, int type);
    void laserOnChanged();
    void fanOnChanged();
    void combatBlockedChanged();
    void temperatureChanged(float temperature);

private:
    void updateBlockedReason();
    CommandData makeCommand(float panVel = 0.0f, float tiltVel = 0.0f) const;
    ImageProvider *m_imageProvider = nullptr;
    float m_panPos = 0.0f;
    float m_tiltPos = 0.0f;
    float m_temperature = 0.0f;
    bool m_laserOn = false;
    bool m_fanOn = false;
    bool m_cameraError = false;
    bool m_rosError = false;
    QString m_blockedReason;
};

#endif
