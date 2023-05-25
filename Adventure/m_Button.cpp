#include "m_Button.h"
#include <QWidget>
#include <QString>
#include <QPixmap>


m_Button::m_Button(QWidget* parent,bool mask,QString original_image,QString clicked_iamge):
    QPushButton(parent),original_image_path(original_image),clicked_image_path(clicked_iamge)
{
    setCursor(Qt::PointingHandCursor);
    QPixmap pix;
    pix.load(original_image_path);
    setFixedSize(pix.width(),pix.height());
    setStyleSheet("QPushButton{border:0px;}");
    if(mask)
    setMask(pix.mask());
    setIcon(pix);
    setIconSize(QSize(pix.width(),pix.height()));
}

void m_Button::mousePressEvent(QMouseEvent *event)
{
    move(x()+1,y()+1);
    return QPushButton::mousePressEvent(event);
}

void m_Button::mouseReleaseEvent(QMouseEvent *event)
{
    move(x()-1,y()-1);
    return QPushButton::mouseReleaseEvent(event);
}

void m_Button::enterEvent(QEnterEvent *event)
{
    if(clicked_image_path!="")
    {
    QPixmap pix;
    pix.load(clicked_image_path);
    setIcon(pix);
    }
    return QPushButton::enterEvent(event);
}

void m_Button::leaveEvent(QEvent *event)
{
    if(clicked_image_path!="")
    {
    QPixmap pix;
    pix.load(original_image_path);
    setIcon(pix);
    }
    return QPushButton::leaveEvent(event);
}
