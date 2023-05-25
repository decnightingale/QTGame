#include "game_map.h"

game_map::game_map(QWidget* parent):QWidget(parent)
{
    m_Button* return_button = new m_Button(this,false,":/image/game_map_return_button.png");
    return_button->move(200,400);
    connect(return_button,&m_Button::clicked,[=](){
        emit return_called();
    });
    m_Button* help_button = new m_Button(this,false,":/image/game_map_help_button.png");
    help_button->move(400,400);
    connect(help_button,&m_Button::clicked,[=](){
        emit help_called();
    });
}

void game_map::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage img(":/image/game_map_bg.png");
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
}
