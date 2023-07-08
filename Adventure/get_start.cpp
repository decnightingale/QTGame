#include "get_start.h"
#include <QDebug>

get_start::get_start(QWidget* Parent):QWidget(Parent)
{
    m_Button* play_button = new m_Button(this,false,":/image/game_start_button.png");
    play_button->move(450,400);
    connect(play_button,&m_Button::clicked,[=](){
        emit play_called();});
    m_Button* help_button = new m_Button(this,false,":/image/enter_help_button.png");
    help_button->move(550,400);
    connect(help_button,&m_Button::clicked,[=](){
        emit help_called();});
    m_Button* quit_button = new m_Button(this,false,":/image/quit_game_button.png");
    quit_button->move(650,400);
    connect(quit_button,&m_Button::clicked,[=](){
        emit quit_called();
    });
}

void get_start::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage img(":/image/title_bg.png");
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
}
