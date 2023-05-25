#include "game_story_window.h"

game_story_window::game_story_window(QWidget* parent):QWidget(parent)
{
    m_Button* story_continue_button = new m_Button(this,false,":/image/story_continue_button.png");
    story_continue_button->move(200,400);
    connect(story_continue_button,&m_Button::clicked,[=](){
        emit continue_called();
    });
}

void game_story_window::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage img(":/image/story_bg.png");
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
}
