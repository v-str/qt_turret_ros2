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

public:
    explicit TurretWidget(QWidget *parent = nullptr);
    ~TurretWidget() override;

    void setFrame(const QImage &frame);

    Q_INVOKABLE void warpMouse(int x, int y);
    Q_INVOKABLE void sendAimDelta(float dx, float dy, bool laserOn);
    Q_INVOKABLE void sendCommand(int cmd);

signals:
    void aimDeltaReceived(float dx, float dy, bool laserOn);
    void commandReceived(int cmd);
    void logRequested(const QString &msg);

private:
    ImageProvider *m_imageProvider = nullptr;
};

#endif
