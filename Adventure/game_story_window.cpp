#include "game_story_window.h"
#include <QDebug>

game_story_window::game_story_window(QWidget* parent):QWidget(parent),index(0)
{
    m_Button* story_continue_button = new m_Button(this,false,":/image/next_button.png");
    story_continue_button->move(500,500);
    connect(story_continue_button,&m_Button::clicked,[=](){
        if(index>=15)
            emit continue_called();
        else{
            index++;
            update();
        }
    });

    m_Button* skip_button = new m_Button(this,false,":/image/skip_button.png");
    skip_button->move(50,500);
    connect(skip_button,&m_Button::clicked,[=](){
        emit continue_called();
    });
}

void game_story_window::paintEvent(QPaintEvent* event)
{
    QString bg_path;
    //qDebug()<<index;
    switch (index) {
    case 0:
        bg_path = ":/image/conversation_bg.png";
        break;
    case 1:
        bg_path = ":/image/conversation_1.png";
        break;
    case 2:
        bg_path = ":/image/conversation_2.png";
        break;
    case 3:
        bg_path = ":/image/conversation_3.png";
        break;
    case 4:
        bg_path = ":/image/conversation_4.png";
        break;
    case 5:
        bg_path = ":/image/conversation_5.png";
        break;
    case 6:
        bg_path = ":/image/conversation_6.png";
        break;
    case 7:
        bg_path = ":/image/conversation_7.png";
        break;
    case 8:
        bg_path = ":/image/conversation_8.png";
        break;
    case 9:
        bg_path = ":/image/conversation_9.png";
        break;
    case 10:
        bg_path = ":/image/conversation_10.png";
        break;
    case 11:
        bg_path = ":/image/conversation_11.png";
        break;
    case 12:
        bg_path = ":/image/conversation_12.png";
        break;
    case 13:
        bg_path = ":/image/conversation_13.png";
        break;
    case 14:
        bg_path = ":/image/conversation_14.png";
        break;
    case 15:
        bg_path = ":/image/conversation_15.png";
        break;
    default:
        bg_path = ":/image/conversation_bg.png";
        break;
    }
    QPainter painter(this);
    QImage img(bg_path);
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
}
