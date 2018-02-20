#ifndef KOMPAS_H
#define KOMPAS_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QSettings>

class Compass : public QWidget
{
    Q_OBJECT
public:
    explicit Compass(QString nameControl, QWidget *parent = nullptr);

public slots:
    void setEditControl(bool value);
    void setAngleToNorth(float angle);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void generateTextPositions();


private:
    int widgetSize;
    float angleToNorth;
    float textPositions[5];
    float angles[5];
    bool editControl;
    bool mouseEdit;
    QTimer timer;
    QPoint oldPosition;
    QPoint position;
    QSettings* settings;
    QString nameControl;
};

#endif // KOMPAS_H
