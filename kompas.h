#ifndef KOMPAS_H
#define KOMPAS_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>

class Kompas : public QWidget
{
    Q_OBJECT
public:
    explicit Kompas(QWidget *parent = nullptr);

protected:
    void setAngleToNorth(float angle);
    virtual void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    float generatePosition(int number);

private:
    float angleToNorth;
    bool mouseEdit;
    QTimer timer;
    QPoint oldPosition;
};

#endif // KOMPAS_H
