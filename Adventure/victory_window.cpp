#include "victory_window.h"

victory_window::victory_window(QWidget* parent):
    QWidget(parent),collection_num(this),life_num(this),light_num(this),mark(this),index(0)
{
    collection_num.move(270,360);

    life_num.move(270,240);

    light_num.move(270,300);

    mark.move(170,480);

    m_Button* quit_button = new m_Button(this,false,":/image/leave_button.png");
    quit_button->move(550,450);
    connect(quit_button,&m_Button::clicked,[=](){
        emit close_called();
    });
}

void victory_window::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage img(":/image/victory_bg_1.png");
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
}


