#include "Compass.h"

Compass::Compass(QString name, QWidget *parent) : QWidget(parent),
    nameControl(name),
    angleToNorth(0.0),
    editControl(false),
    mouseEdit(false)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog /*| Qt::NoDropShadowWindowHint*/);
    setAttribute(Qt::WA_TranslucentBackground);
    settings = new QSettings("D:/setting.ini", QSettings::IniFormat);
    widgetSize= settings->value(nameControl+"/size", 800).toInt();
    position = settings->value(nameControl+"/position", QPoint(100,100)).toPoint();
    resize(QSize(widgetSize, widgetSize*0.05));
    move(position);
    generateTextPositions();
    connect(&timer,&QTimer::timeout,[=](){
        setAngleToNorth(angleToNorth-0.1);
        if(angleToNorth >= 360.0)
        {
            angleToNorth = 0.0;
        } else if ( angleToNorth < 0){
            angleToNorth += 360;
        }

    });
    timer.setInterval(10);
    timer.start();

}

void Compass::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QBrush(QColor(60,60,60,100)));
    if ( editControl)
    {
        painter.drawRoundedRect(QRectF(QPoint(0,0), size()), 10,10);
    }

    QPen pen;
    pen.setColor(QColor(Qt::yellow).dark());
    pen.setWidth(size().height() * 0.025);
    painter.setPen(pen);
    painter.drawLine(QPointF(0,size().height()/4), QPoint(size().width(), size().height()/4));
    // значок центра
    painter.drawLine(QPointF(size().width()*0.5,size().height()*0.25), QPoint(size().width()*0.495, 0));
    painter.drawLine(QPointF(size().width()*0.5,size().height()*0.25), QPoint(size().width()*0.505, 0));
    painter.drawLine(QPointF(textPositions[0],size().height()*0.25), QPoint(textPositions[0], size().height() * 0.4));
    QString s;
    s.setNum((angles[0]),'f',1);
    s.append("\302\260");

    QPoint p;
    QFont font("Arial");
    font.setPixelSize(size().height() * 0.25); // Высота шрифта
    font.setBold(true);
    QFontMetrics fm(font);
    p.setX(textPositions[0] - (fm.width(s))/2);
    p.setY(size().height() * 0.4 + (fm.height()));
    painter.setFont(font);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.drawText(p,s);
    painter.drawLine(QPointF(textPositions[1], size().height()*0.25), QPoint(textPositions[1], size().height() * 0.4));
    s.setNum(angles[1],'f',1);
    s.append("\302\260");
    p.setX(textPositions[1] - (fm.width(s))/2);
    p.setY(size().height() * 0.4 + (fm.height()));
    painter.drawText(p,s);
    painter.drawLine(QPointF(textPositions[2],size().height()*0.25), QPoint(textPositions[2], size().height() * 0.4));
    s.setNum(angles[2],'f',1);
    s.append("\302\260");
    p.setX(textPositions[2] - (fm.width(s))/2);
    p.setY(size().height() * 0.4 + (fm.height()));
    painter.drawText(p,s);
    painter.drawLine(QPointF(textPositions[3],size().height()*0.25), QPoint(textPositions[3], size().height() * 0.4));
    s.setNum(angles[3],'f',1);
    s.append("\302\260");
    p.setX(textPositions[3] - (fm.width(s))/2);
    p.setY(size().height() * 0.4 + (fm.height()));
    painter.drawText(p,s);
    painter.drawLine(QPointF(textPositions[4],size().height()*0.25), QPoint(textPositions[4], size().height() * 0.4));
    s.setNum(angles[4],'f',1);
    s.append("\302\260");
    p.setX(textPositions[4] - (fm.width(s))/2);
    p.setY(size().height() * 0.4 + (fm.height()));
    painter.drawText(p,s);


}


void Compass::generateTextPositions()
{

    textPositions[0] = 0;
    textPositions[1] = 0.25 * size().width();
    textPositions[2] = 0.5 * size().width();
    textPositions[3] = 0.75 * size().width();
    textPositions[4] = size().width();

    float shift = 0.0;

    float delta = 0.0;
    if ( angleToNorth >= 0 && angleToNorth <= 10)
    {
        delta = angleToNorth;
    }else if ( angleToNorth > 10 )
    {
        int tmp = (int)(angleToNorth/10);
        tmp *= 10;
        delta = (angleToNorth - tmp);
    }
    int centralAngle = 0;

    if (delta >= 0 && delta <= 5)
    {
        centralAngle = (int)angleToNorth - (((int)angleToNorth)%10);
    }else if ( delta > 5 && delta <= 10)
    {
        centralAngle = (int)angleToNorth - (((int)angleToNorth)%10) ;
    }

    angles[0] = centralAngle - 20;
    angles[1] = centralAngle - 10;
    angles[2] = centralAngle;
    angles[3] = centralAngle + 10;
    angles[4] = centralAngle + 20;

    for (int i = 0; i < 5; i++)
    {
        textPositions[i] -= delta * 0.025 * size().width();
        if (angles[i] < 0)
        {
            angles[i] += 360;
        }else if (angles[i] >= 360)
        {
            angles[i] -= 360;
        }
    }


}

void Compass::setEditControl(bool value)
{
    editControl = value;
}

void Compass::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && editControl)
    {
        mouseEdit = true;
        oldPosition = event->globalPos();
    }
}

void Compass::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && mouseEdit && editControl)
    {
        QPoint current = event->globalPos();
        move((x() + ( current.x() - oldPosition.x())),
             (y() + ( current.y() - oldPosition.y())));
        settings->setValue(nameControl + "/position", pos());
        mouseEdit = false;
    }
}

void Compass::mouseMoveEvent(QMouseEvent *event)
{
    if ( mouseEdit && editControl)
    {
        QPoint current = event->globalPos();
        move((x() + ( current.x() - oldPosition.x())),
             (y() + ( current.y() - oldPosition.y())));
        oldPosition = current;
    }
}

void Compass::wheelEvent(QWheelEvent *event)
{
    if  (mouseEdit && editControl)
    {
        if (event->delta() > 0)
        {
            resize( size() * 1.05);
        } else
        {
            resize( size() * 0.95);
        }
        move(event->globalPos().x() - size().width()/2, event->globalPos().y() - size().height()/2);
    }
}

void Compass::resizeEvent(QResizeEvent *event)
{
    settings->setValue(nameControl + "/size", size().width());
}

void Compass::setAngleToNorth(float angle)
{
    angleToNorth = angle;
    generateTextPositions();
    update();
}
