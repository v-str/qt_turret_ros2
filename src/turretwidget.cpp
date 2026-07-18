#include "turretwidget.h"
#include "ui_turretwidget.h"

TurretWidget::TurretWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::turretWidget)
{
    ui->setupUi(this);
    ui->crosshair->setAttribute(Qt::WA_TransparentForMouseEvents);
}

TurretWidget::~TurretWidget()
{
    delete ui;
}

void TurretWidget::setFrame(const QImage &frame)
{
    m_frame = frame;
    update();
}

void TurretWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    if (m_frame.isNull()) {
        p.fillRect(rect(), Qt::black);
        return;
    }

    auto scaled = m_frame.scaled(
        size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    int x = (width() - scaled.width()) / 2;
    int y = (height() - scaled.height()) / 2;
    p.drawImage(x, y, scaled);
}
