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

TurretWidget::~TurretWidget()
{
    delete m_imageProvider;
}

void TurretWidget::setFrame(const QImage &frame)
{
    m_imageProvider->setFrame(frame);
}
