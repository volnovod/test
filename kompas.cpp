#include "Kompas.h"

Kompas::Kompas(QWidget *parent) : QWidget(parent),
    angleToNorth(0),
    mouseEdit(false)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog /*| Qt::NoDropShadowWindowHint*/);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(QSize(800,80));
    move(400, 100);
    connect(&timer,&QTimer::timeout,[=](){
        angleToNorth--;
        if(angleToNorth >= 360.0)
            angleToNorth = 0.0;
        setAngleToNorth(angleToNorth);
    });
    timer.setInterval(100);
    timer.start();

}

void Kompas::setAngleToNorth(float angle)
{
    angleToNorth = angle;
    update();
}

void Kompas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QBrush(QColor(60,60,60,100)));
    painter.drawRoundedRect(QRectF(QPoint(0,0), size()), 10,10);

    QPen pen;
    pen.setColor(QColor(Qt::yellow).dark());
    pen.setWidth(size().height() * 0.025);
    painter.setPen(pen);
    painter.drawLine(QPointF(0,size().height()/4), QPoint(size().width(), size().height()/4));
    // значок центра
    painter.drawLine(QPointF(size().width()*0.5,size().height()*0.25), QPoint(size().width()*0.495, 0));
    painter.drawLine(QPointF(size().width()*0.5,size().height()*0.25), QPoint(size().width()*0.505, 0));

    painter.drawLine(QPointF(generatePosition(1),size().height()*0.25), QPoint(generatePosition(1), size().height() * 0.5));
    painter.drawLine(QPointF(generatePosition(2),size().height()*0.25), QPoint(generatePosition(2), size().height() * 0.5));
    QString s;
    s.setNum((angleToNorth - 20.0),'f',2);
    s.append("\302\260");

    QPoint p;
    QFont font("Arial");
    font.setPixelSize(size().height() * 0.25); // Высота шрифта
    font.setBold(true);
    QFontMetrics fm(font);
    p.setX(0 - (fm.width(s))/2);
    p.setY(size().height() * 0.5 + (fm.height()));
    painter.setFont(font);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.drawText(p,s);

    painter.drawLine(QPointF(generatePosition(3),size().height()*0.25), QPoint(generatePosition(3), size().height() * 0.5));
    painter.drawLine(QPointF(generatePosition(4),size().height()*0.25), QPoint(generatePosition(4), size().height() * 0.5));
    s.setNum((angleToNorth - 10.0),'f',2);
    s.append("\302\260");
    p.setX(size().width()*0.25 - (fm.width(s))/2);
    p.setY(size().height() * 0.5 + (fm.height()));
    painter.drawText(p,s);

    painter.drawLine(QPointF(generatePosition(5),size().height()*0.25), QPoint(generatePosition(5), size().height() * 0.5));
    painter.drawLine(QPointF(generatePosition(6),size().height()*0.25), QPoint(generatePosition(6), size().height() * 0.5));
    s.setNum(angleToNorth,'f',2);
    s.append("\302\260");
    p.setX(size().width()*0.5 - (fm.width(s))/2);
    p.setY(size().height() * 0.5 + (fm.height()));
    painter.drawText(p,s);

    painter.drawLine(QPointF(generatePosition(7),size().height()*0.25), QPoint(generatePosition(7), size().height() * 0.5));
    painter.drawLine(QPointF(generatePosition(8),size().height()*0.25), QPoint(generatePosition(8), size().height() * 0.5));
    s.setNum((angleToNorth + 10.0),'f',2);
    s.append("\302\260");
    p.setX(size().width()*0.75 - (fm.width(s))/2);
    p.setY(size().height() * 0.5 + (fm.height()));
    painter.drawText(p,s);

    painter.drawLine(QPointF(generatePosition(9),size().height()*0.25), QPoint(generatePosition(9), size().height() * 0.5));
    s.setNum((angleToNorth + 20.0),'f',2);
    s.append("\302\260");
    p.setX(size().width() - (fm.width(s))/2);
    p.setY(size().height() * 0.5 + (fm.height()));
    painter.drawText(p,s);


}


float Kompas::generatePosition(int number)
{
    float generatedPosition = 0.0;
    float delta = 0.0;
    if ( angleToNorth >= 0 && angleToNorth <= 10)
    {
        delta = angleToNorth/10;
    }else if ( angleToNorth > 10 && angleToNorth < 100)
    {
        int tmp = (int)(angleToNorth/10);
        tmp *= 10;
        delta = (angleToNorth - tmp)/10;
    }else if ( angleToNorth >= 100)
    {
        int tmp = (int)(angleToNorth/10);
        tmp *= 10;
        delta = (angleToNorth - tmp)/10;
    }

    if ( number == 1)
    {
        generatedPosition = 0.0 * 0.125*size().width() + 0.125*size().width()*delta;
    }else if ( number == 2)
    {
        generatedPosition = 1.0 * 0.125*size().width() + 0.125*size().width()*delta;

    }else if ( number == 3)
    {
        generatedPosition = 2.0 * 0.125*size().width() + 0.125*size().width()*delta;
    }else if ( number == 4)
    {
        generatedPosition = 3.0 * 0.125*size().width() + 0.125*size().width()*delta;
    }else if ( number == 5)
    {
        generatedPosition = 4.0 * 0.125*size().width() + 0.125*size().width()*delta;
    }else if ( number == 6)
    {
        generatedPosition = 5.0 * 0.125*size().width() + 0.125*size().width()*delta;
    }else if ( number == 7)
    {
        generatedPosition = 6.0 * 0.125*size().width() + 0.125*size().width()*delta;
    }else if ( number == 8)
    {
        generatedPosition = 7.0 * 0.125*size().width() + 0.125*size().width()*delta;
    }else if ( number == 9)
    {
        generatedPosition = 8.0 * 0.125*size().width() + 0.125*size().width()*delta;
    }
    return generatedPosition;
}

void Kompas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton )
    {
        mouseEdit = true;
        oldPosition = event->pos();
    }
}

void Kompas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouseEdit = false;
    }
}

void Kompas::mouseMoveEvent(QMouseEvent *event)
{
    if ( mouseEdit)
    {
        QPoint current = event->pos();
        move((pos().x() - (oldPosition.x() - current.x())),
             (pos().y() - (oldPosition.y() - current.y())));
    }
}
