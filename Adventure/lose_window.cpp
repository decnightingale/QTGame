#include "lose_window.h"

lose_window::lose_window(QWidget* parent):
    QWidget(parent),collection_num(this),life_num(this),light_num(this),mark(this),index(0)
{
    collection_num.move(250,410);

    life_num.move(250,290);

    light_num.move(250,350);

    mark.move(150,470);

    m_Button* quit_button = new m_Button(this,false,":/image/leave_button.png");
    quit_button->move(550,450);
    connect(quit_button,&m_Button::clicked,[=](){
        emit close_called();
    });
}

void lose_window::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage img(":/image/lose_bg_1.png");
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
}


