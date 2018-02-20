#ifndef _CombatModuleWidget_H
#define _CombatModuleWidget_H

#include <QApplication>
#include <QWidget>
#include <QSettings>
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <iostream>

class CombatModuleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CombatModuleWidget(QString nameControl, QWidget *parent = nullptr);

public slots:
    void setAngelPitchYaw(float pitch, float yaw);

    /*  Set the alignment of the quadratic content if the widgets geometry isn quadratic.
     *  Flags can be combined eg. setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    */
    void setAlignment(Qt::Alignment f);
    void setEditControl(bool c);
    void setVerticalVisibility(bool);
    void setVerticalOrientation();
    void setHorizontalOrientation();

    void setLimiter(bool up, bool down);
protected:
    void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void goToHome();
    void setKompasAngle(float angle);

private:
    QPointF rotatePoint(QPointF p1, QPointF p2, float angle);
    QRectF m_bounds;

    QPoint m_lastPos;

    QSettings *m_settings;
    QPoint m_oldPos;
    bool m_mouseRightActivate;
    bool m_edit;
    QString m_nameControl;
    QPoint delta;
    int m_sens;
    float m_pitch;
    float m_yaw;
    float angleToNorth;
    bool m_limiterDown;
    bool m_limitertUp;
    bool showVerical;
    QPixmap sideView;
    QPixmap topViewBlue;
    QPixmap topViewRed;
    QPixmap homePixMap;
    QPixmap kompas;
    QTimer timer;
    bool verticalOrientation;
    bool horizontalOrientation;

    Qt::Alignment m_alignment;
};

#endif // _CombatModuleWidget_H
