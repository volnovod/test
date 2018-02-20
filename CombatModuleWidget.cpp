#include "CombatModuleWidget.h"

template<typename T>
T constrain(T Value, T Min, T Max)
{
    return (Value < Min)? Min : (Value > Max)? Max : Value;
}


CombatModuleWidget::CombatModuleWidget(QString nameControl,QWidget *parent) : QWidget(parent),
    m_alignment(Qt::AlignCenter),
    m_mouseRightActivate(false),
    m_edit(false),
    m_pitch(0.0),
    m_yaw(0.0),
    m_limiterDown(false),
    m_limitertUp(false),
    m_nameControl(nameControl),
    angleToNorth(0.0)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog /*| Qt::NoDropShadowWindowHint*/);
    setAttribute(Qt::WA_TranslucentBackground);
    //setAttribute(Qt::WA_TransparentForMouseEvents);
    setStyleSheet("background:transparent;");

    QString tmp;
    tmp.append("D:/setting.ini");
    m_settings = new QSettings(tmp, QSettings::IniFormat);
    showVerical = m_settings->value(m_nameControl + "/showVertical", 1).toInt() == 0 ? false : true;
    // якщо 1 -- вертикальна орієнтація, 0 -- горизонтальна
    int orientation = m_settings->value(m_nameControl + "/verticalOrientation", 1).toInt();
    if ( orientation != 0)
    {
        verticalOrientation = true;
        horizontalOrientation = false;
    } else if ( orientation == 0)
    {
        verticalOrientation = false;
        horizontalOrientation = true;
    }
    int size = m_settings->value(m_nameControl + "/size",100).toInt();
    QSize currentSize;
    if (verticalOrientation)
    {
        currentSize.setWidth(size);
        currentSize.setHeight(size * 2);
    }else if (horizontalOrientation)
    {
        currentSize.setWidth(size * 2);
        currentSize.setHeight(size);
    }
    resize(currentSize);
    move(m_settings->value(m_nameControl + "/pos",QPoint(100,100)).toPoint());
    setFocusPolicy(Qt::NoFocus);
    setContextMenuPolicy(Qt::NoContextMenu);
    homePixMap = QPixmap("://images/home.png");
    sideView = QPixmap("://images/sideView.png");
    topViewBlue = QPixmap("://images/topViewBlue.png");
    topViewRed = QPixmap("://images/topViewRed.png");
    kompas = QPixmap("://images/compass.png");

    connect(&timer,&QTimer::timeout,[=](){
        if ( m_limiterDown ==false && m_limitertUp == false && m_pitch <= 45)
        {
            m_pitch++;
        }else if ( m_limitertUp == false && m_pitch > 45)
        {
            m_pitch--;
            m_limitertUp = true;
            m_limiterDown = false;
        }else if (m_limiterDown ==false && m_limitertUp == true && m_pitch <= 45 && m_pitch >=-10 )
        {
            m_pitch--;
        }else if (m_limiterDown ==false && m_limitertUp == true && m_pitch <= -10 )
        {
            m_pitch++;
            m_limitertUp = false;
            m_limiterDown = true;
        }else if (m_limiterDown ==true && m_limitertUp == false && m_pitch <= 45 && m_pitch >=-10 )
        {
            m_pitch++;
        }

        if(m_yaw >= 360.0)
            m_yaw = 0.0;
        if(m_pitch >= 360.0)
            m_pitch = 0.0;
        setAngelPitchYaw(m_pitch,m_yaw-0.1);
        setKompasAngle(angleToNorth - 0.1);
    });
    timer.setInterval(10);
    timer.start();
}

void CombatModuleWidget::setKompasAngle(float angle)
{
    angleToNorth = angle;
    update();
}

void CombatModuleWidget::setVerticalVisibility(bool visible)
{
    showVerical = visible;
    if (showVerical)
    {
        m_settings->setValue(m_nameControl + "/showVertical",1);
    } else
    {
        m_settings->setValue(m_nameControl + "/showVertical",0);
    }

}

void CombatModuleWidget::setAngelPitchYaw(float pitch, float yaw)
{
    m_pitch = pitch;

    if(yaw > 180.0f)
        m_yaw = yaw - 360.0f;
    else
        m_yaw = yaw;

    if(m_pitch > 180.0f)
        m_pitch = pitch - 360.0f;
    else
        m_pitch = pitch;

    update();
}

void CombatModuleWidget::setLimiter(bool up, bool down)
{
    m_limiterDown = down;
    m_limitertUp = up;
    update();
}

void CombatModuleWidget::setAlignment(Qt::Alignment f)
{
    m_alignment = f;
}

/**
 * @brief JoyPad::resizeEvent
 * @param event
 *
 * calculates a square bounding rect for the background and the knob
 */
void CombatModuleWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    m_bounds = QRectF(QPointF(0,0), QSize(rect().width(), rect().height()));
}

/**
 * @brief JoyPad::paintEvent
 * @param event
 */
void CombatModuleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QColor color = Qt::blue; // Задаем основной цвет
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(m_bounds.width() * 0.01);

    pen.setBrush(color);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);



    if (verticalOrientation)
    {
        painter.translate(m_bounds.width()/2, m_bounds.height()/4);
        if ( angleToNorth <= 0)
        {
            painter.rotate(-angleToNorth+360);
        }else
        {
            painter.rotate(-angleToNorth);
        }
        painter.translate(-m_bounds.width()/2, -m_bounds.height()/4);
        painter.drawPixmap(0, 0, m_bounds.width() , m_bounds.width(), kompas);
        painter.translate(m_bounds.width()/2, m_bounds.height()/4);
        if ( angleToNorth <= 0)
        {
            painter.rotate(angleToNorth+360);
        }else
        {
            painter.rotate(angleToNorth);
        }
        painter.translate(-m_bounds.width()/2, -m_bounds.height()/4);

        if(m_yaw > 30.0f || m_yaw < -30.0f)
        {
            color = Qt::red;
            // малюємо червоний танк
            painter.drawPixmap((m_bounds.width()*0.25), m_bounds.height()*0.1,m_bounds.width()*0.5 , m_bounds.height()*0.3, topViewRed);
        }else
        {
            // малюємо синій танк
            painter.drawPixmap((m_bounds.width()*0.25), m_bounds.height()*0.1,m_bounds.width()*0.5 , m_bounds.height()*0.3, topViewBlue);
        }

        // ствол танка
        pen.setWidth(m_bounds.width() * 0.05);
        pen.setBrush(color.dark());
        painter.setPen(pen);
        painter.drawLine(QPointF(m_bounds.width() * 0.5, m_bounds.height() * 0.25),
                         rotatePoint(QPointF(m_bounds.width() * 0.5, m_bounds.height() * 0.25),
                                     QPointF(m_bounds.width() * 0.5, m_bounds.height() * 0.075),
                                     m_yaw));
        // круг башни горизонт

        painter.setBrush(QBrush(color.dark(),Qt::SolidPattern));
        painter.drawEllipse(QPointF(m_bounds.width() * 0.5, m_bounds.height() * 0.25),
                            m_bounds.height() * 0.05, m_bounds.height() * 0.05); // Закрашенный

        // символ повернення башні
        painter.drawPixmap((m_bounds.width()*0.5-m_bounds.height()*0.05), (m_bounds.height()*0.25-m_bounds.height()*0.05),
                           m_bounds.height()*0.1, m_bounds.height()*0.1, homePixMap);



        QString s;
        s.setNum(m_yaw,'f',2);
        s.append("\302\260");

        QPoint p;
        QFont font("Arial");
        font.setPixelSize(m_bounds.height() * 0.04); // Высота шрифта
        font.setBold(true);
        QFontMetrics fm(font);
        p.setX(m_bounds.width() * 0.50 - (fm.width(s))/2);
        p.setY(m_bounds.width() * 0.8 + (fm.height())/2);

        color.setAlphaF(1.0);
        painter.setPen(color.dark());
        painter.setFont(font);
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.drawText(p,s);

        if (showVerical)
        {
            s.clear();
            color = Qt::blue;
            painter.setPen(color.dark());
            s.setNum(m_pitch,'f',2);
            s.append("\302\260");
            p.setX(m_bounds.width() * 0.50 - (fm.width(s))/2);
            p.setY(m_bounds.height() * 0.85 + (fm.height())/2);
            painter.drawText(p,s);

            // Вертикаль

            pen.setWidth(m_bounds.width() * 0.05);
            pen.setBrush(color.dark());
            painter.setPen(pen);


            painter.drawLine(QPointF(m_bounds.width() * 0.5, m_bounds.height() * 0.65), // Пушка
                            rotatePoint(QPointF(m_bounds.width() * 0.5, m_bounds.height() * 0.65),
                                        QPointF(m_bounds.width() * 0.1, m_bounds.height() * 0.65),
                                        m_pitch));
            painter.drawPixmap((m_bounds.width()*0.1), m_bounds.height()*0.4,m_bounds.height()*0.4 , m_bounds.height()*0.4, sideView);
        }

    } else if ( horizontalOrientation)
    {

        painter.translate(m_bounds.width()/4, m_bounds.height()/2);
        if ( angleToNorth <= 0)
        {
            painter.rotate(-angleToNorth+360);
        }else
        {
            painter.rotate(-angleToNorth);
        }
        painter.translate(-m_bounds.width()/2, -m_bounds.height()/4);
        painter.drawPixmap(0, 0, m_bounds.width() , m_bounds.width(), kompas);
        painter.translate(m_bounds.width()/2, m_bounds.height()/4);
        if ( angleToNorth <= 0)
        {
            painter.rotate(angleToNorth+360);
        }else
        {
            painter.rotate(angleToNorth);
        }
        painter.translate(-m_bounds.width()/4, -m_bounds.height()/2);

        if(m_yaw > 30.0f || m_yaw < -30.0f)
        {
            color = Qt::red;
            // малюємо червоний танк
            painter.drawPixmap(((m_bounds.width() - m_bounds.height())*0.25), (m_bounds.height()*0.5 - m_bounds.width()*0.15),
                               m_bounds.height()*0.5 , m_bounds.width()*0.3, topViewRed);
        }else
        {
            // малюємо синій танк
            painter.drawPixmap(((m_bounds.width() - m_bounds.height())*0.25), (m_bounds.height()*0.5 - m_bounds.width()*0.15),
                               m_bounds.height()*0.5 , m_bounds.width()*0.3, topViewBlue);
        }

        // ствол танка
        pen.setWidth(m_bounds.height() * 0.05);
        pen.setBrush(color.dark());
        painter.setPen(pen);



        painter.drawLine(QPointF(m_bounds.width() * 0.25, m_bounds.height() * 0.5),
                         rotatePoint(QPointF(m_bounds.width() * 0.25, m_bounds.height() * 0.5),
                                     QPointF(m_bounds.width() * 0.075, m_bounds.height() * 0.5),
                                     m_yaw + 90));
        // круг башни горизонт

        painter.setBrush(QBrush(color.dark(),Qt::SolidPattern));
        painter.drawEllipse(QPointF(m_bounds.width() * 0.25, m_bounds.height() * 0.5),
                            m_bounds.width() * 0.05, m_bounds.width() * 0.05); // Закрашенный

        // символ повернення башні
        painter.drawPixmap((m_bounds.width()*0.2), (m_bounds.height()*0.5-m_bounds.width()*0.05),
                           m_bounds.width()*0.1, m_bounds.width()*0.1, homePixMap);



        QString s;
        s.setNum(m_yaw,'f',2);
        s.append("\302\260");

        QPoint p;
        QFont font("Arial");
        font.setPixelSize(m_bounds.width() * 0.04); // Высота шрифта
        font.setBold(true);
        QFontMetrics fm(font);
        p.setX(m_bounds.width() * 0.25 - (fm.width(s))/2);
        p.setY(m_bounds.height() * 0.8 + (fm.height())/2);
        color.setAlphaF(1.0);
        painter.setPen(color.dark());
        painter.setFont(font);
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.drawText(p,s);

        if (showVerical)
        {
            s.clear();
            color = Qt::blue;
            painter.setPen(color.dark());
            s.setNum(m_pitch,'f',2);
            s.append("\302\260");
            p.setX(m_bounds.width() * 0.75 - (fm.width(s))/2);
            p.setY(m_bounds.height() * 0.8 + (fm.height())/2);
            painter.drawText(p,s);

            // Вертикаль



            pen.setWidth(m_bounds.height() * 0.05);
            pen.setBrush(color.dark());
            painter.setPen(pen);
            painter.drawLine(QPointF(m_bounds.width() * 0.75, m_bounds.height()*0.4), // Пушка
                            rotatePoint(QPointF(m_bounds.width() * 0.75, m_bounds.height() * 0.4),
                                        QPointF(m_bounds.width() * 0.55, m_bounds.height() * 0.4),
                                        m_pitch));
            painter.drawPixmap((m_bounds.width()*0.55), (m_bounds.height()*0.3 - m_bounds.width()*0.2),
                               m_bounds.width()*0.4 , m_bounds.width()*0.4, sideView);
        }
    }




}

void CombatModuleWidget::mousePressEvent(QMouseEvent *event)
{

    if ((event->button() == Qt::RightButton) && m_edit)
    {
        m_oldPos = event->globalPos();
        m_mouseRightActivate = true;
    }
    else if(event->button() == Qt::LeftButton && !m_mouseRightActivate)
    {
        //обработка кнопки парковки бащни
        if (verticalOrientation && event->pos().x() >= m_bounds.width()*0.25 && event->pos().x() <= (m_bounds.width()*0.75) &&
                event->pos().y() >= m_bounds.height()*0.1 && event->pos().y() <= m_bounds.height()*0.35)
        {
            goToHome();
        } else if ( horizontalOrientation && event->pos().x() >= m_bounds.width()*0.15 && event->pos().x() <= (m_bounds.width()*0.35) &&
                    event->pos().y() >= m_bounds.height()*0.175 && event->pos().y() <= m_bounds.height()*0.725)
        {
            goToHome();
        }
        if (event->pos().x() < m_bounds.width()*0.1)
        {
            if (showVerical)
            {
                setVerticalVisibility(false);
            }else {
                setVerticalVisibility(true);
            }
        }

    }
}

void CombatModuleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Qt::MouseButton mbt;
    mbt = event->button();

    if((mbt == Qt::RightButton) && m_edit)
    {
        m_mouseRightActivate = false;
        m_settings->setValue(m_nameControl + "/pos", pos());
        if ( verticalOrientation)
        {
            m_settings->setValue(m_nameControl + "/size", size().width());
        } else if ( horizontalOrientation)
        {
            m_settings->setValue(m_nameControl + "/size", size().height());
        }

    }
}

void CombatModuleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mouseRightActivate && m_edit)
    {
        delta = event->globalPos() - m_oldPos;
        move(x()+delta.x(), y()+delta.y());
        m_oldPos = event->globalPos();
    }
}

void CombatModuleWidget::wheelEvent(QWheelEvent *event)
{
    if(event->buttons() == Qt::RightButton && m_edit)
    {

        if(event->angleDelta().y() > 0)
        {
            resize(size() * 1.05);
        }
        else
        {
            resize(size() * 0.95);
        }
        if (verticalOrientation)
        {
            move(event->globalPos().x() - m_bounds.width()/2, event->globalPos().y() - m_bounds.height()/4);
        } else if ( horizontalOrientation)
        {
            move(event->globalPos().x() - m_bounds.width()/4, event->globalPos().y() - m_bounds.height()/2);
        }


    }
    event->ignore();
}

void CombatModuleWidget::setEditControl(bool c)
{
    m_edit = c;
}

QPointF CombatModuleWidget::rotatePoint(QPointF p1, QPointF p2, float angle)
{
    QPointF p;

    p.setX(p1.rx() + (p2.rx() - p1.rx()) * qCos(qDegreesToRadians(angle))-
           (p2.ry() - p1.ry()) * qSin(qDegreesToRadians(angle)));

    p.setY(p1.ry() + (p2.rx() - p1.rx()) * qSin(qDegreesToRadians(angle))+
           (p2.ry() - p1.ry()) * qCos(qDegreesToRadians(angle)));
    return p;
}

void CombatModuleWidget::goToHome()
{
    m_yaw = 0;
    m_pitch = 0;
//    if ( verticalOrientation == true && horizontalOrientation == false)
//    {
//        setHorizontalOrientation();
//    }else if (verticalOrientation == false && horizontalOrientation == true)
//    {
//        setVerticalOrientation();
//    }

}

void CombatModuleWidget::setVerticalOrientation()
{
    if (verticalOrientation == false && horizontalOrientation == true)
    {
        verticalOrientation = true;
        horizontalOrientation = false;
        int size = m_settings->value(m_nameControl + "/size", 100).toInt();
        resize(size, size * 2);
        m_settings->setValue(m_nameControl + "/verticalOrientation", 1);
    }

}

void CombatModuleWidget::setHorizontalOrientation()
{
    if ( verticalOrientation == true && horizontalOrientation == false)
    {
        verticalOrientation = false;
        horizontalOrientation = true;
        int size = m_settings->value(m_nameControl + "/size", 100).toInt();
        resize(size * 2, size);
        m_settings->setValue(m_nameControl + "/verticalOrientation", 0);
    }

}
