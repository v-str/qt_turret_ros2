#ifndef TURRETWIDGET_H
#define TURRETWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>

namespace Ui { class turretWidget; }

class TurretWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TurretWidget(QWidget *parent = nullptr);
    ~TurretWidget() override;
    void setFrame(const QImage &frame);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage m_frame;
    Ui::turretWidget *ui;
};

#endif // TURRETWIDGET_H
