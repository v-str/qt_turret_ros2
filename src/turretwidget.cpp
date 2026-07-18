#include "turretwidget.h"
#include "constants.h"
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include <QVBoxLayout>
#include <QUrl>
#include <QCursor>

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

void ImageProvider::setFrame(const QImage &frame)
{
    QMutexLocker lock(&m_mutex);
    m_frame = frame;
    m_counter++;
    emit counterChanged();
}

QImage ImageProvider::requestImage(const QString &, QSize *size, const QSize &)
{
    QMutexLocker lock(&m_mutex);
    if (m_frame.isNull()) {
        if (m_placeholder.isNull()) {
            m_placeholder = QImage(camera::width, camera::height,
                                   QImage::Format_RGB888);
            m_placeholder.fill(Qt::black);
        }
        if (size)
            *size = m_placeholder.size();
        return m_placeholder;
    }
    if (size)
        *size = m_frame.size();
    return m_frame;
}

TurretWidget::TurretWidget(QWidget *parent)
    : QWidget(parent)
{
    m_imageProvider = new ImageProvider();

    auto *quickWidget = new QQuickWidget(this);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->engine()->addImageProvider("turret", m_imageProvider);

    auto *ctx = quickWidget->engine()->rootContext();
    ctx->setContextProperty("imageProvider", m_imageProvider);
    ctx->setContextProperty("SpaceMill", theme::make());
    ctx->setContextProperty("turretWidget", this);

    quickWidget->setSource(QUrl("qrc:/qml/turretwidget.qml"));

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(quickWidget);
}

void TurretWidget::warpMouse(int x, int y)
{
    QCursor::setPos(mapToGlobal(QPoint(x, y)));
}

void TurretWidget::sendAimDelta(float dx, float dy)
{
    float pan_vel = dx * combat::speedMultiplier;
    float tilt_vel = dy * combat::speedMultiplier;
    m_panPos = qBound(-1.0f, m_panPos + pan_vel, 1.0f);
    m_tiltPos = qBound(-1.0f, m_tiltPos + tilt_vel, 1.0f);
    emit aimDeltaReceived(m_panPos, m_tiltPos, pan_vel, tilt_vel, m_laserOn);
    emit logRequested(
        QString("Прицеливание: pan=%1, tilt=%2, pan_vel=%3, tilt_vel=%4")
            .arg(m_panPos, 0, 'f', 3)
            .arg(m_tiltPos, 0, 'f', 3)
            .arg(pan_vel, 0, 'f', 3)
            .arg(tilt_vel, 0, 'f', 3));
}

void TurretWidget::toggleLaser()
{
    m_laserOn = !m_laserOn;
    emit laserOnChanged();
    emit logRequested(QString("Лазер %1").arg(m_laserOn ? "включён" : "выключен"));
}

void TurretWidget::resetPosition()
{
    m_panPos = 0.0f;
    m_tiltPos = 0.0f;
    if (m_laserOn)
        toggleLaser();
    emit aimDeltaReceived(0, 0, 0, 0, false);
    emit logRequested("Центрирование: pan=0, tilt=0");
}

void TurretWidget::sendCommand(int cmd)
{
    emit commandReceived(cmd);
    switch (cmd) {
        case 0: emit logRequested("Ручное управление"); break;
        case 1: /* Патрулирование — заглушка */ break;
        case 2: resetPosition(); break;
    }
}

TurretWidget::~TurretWidget()
{
    delete m_imageProvider;
}

void TurretWidget::setFrame(const QImage &frame)
{
    m_imageProvider->setFrame(frame);
}
