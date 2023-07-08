#include "help_window.h"

help_window::help_window(QWidget* parent):QWidget(parent),index(1)
{
    m_Button* continue_button = new m_Button(this,false,":/image/next_button.png");
    continue_button->move(730,500);
    connect(continue_button,&m_Button::clicked,[=](){
        if(index>=5)
            emit return_called();
        else{
            index++;
            update();
        }
    });
}

void help_window::paintEvent(QPaintEvent* event)
{
    QString bg_path;
    //qDebug()<<index;
    switch (index) {
    case 0:
        bg_path = ":/image/help_bg.png";
        break;
    case 1:
        bg_path = ":/image/help_1.png";
        break;
    case 2:
        bg_path = ":/image/help_2.png";
        break;
    case 3:
        bg_path = ":/image/help_3.png";
        break;
    case 4:
        bg_path = ":/image/help_4.png";
        break;
    case 5:
        bg_path = ":/image/help_5.png";
        break;
    default:
        bg_path = ":/image/help_bg.png";
        break;
    }
    QPainter painter(this);
    QImage img(bg_path);
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
}
