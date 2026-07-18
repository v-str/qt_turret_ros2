#include "turretwidget.h"
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include <QVBoxLayout>
#include <QUrl>

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
        if (size)
            *size = QSize(1, 1);
        return QImage(1, 1, QImage::Format_ARGB32);
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
    quickWidget->engine()->rootContext()->setContextProperty("imageProvider", m_imageProvider);

    quickWidget->setSource(QUrl("qrc:/qml/turretwidget.qml"));

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(quickWidget);
}

TurretWidget::~TurretWidget()
{
    delete m_imageProvider;
}

void TurretWidget::setFrame(const QImage &frame)
{
    m_imageProvider->setFrame(frame);
}
