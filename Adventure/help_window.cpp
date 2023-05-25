#include "help_window.h"

help_window::help_window(QWidget* parent):QWidget(parent)
{
    QLabel* help_text = new QLabel(this);
    help_text->setText("这是帮助");
    help_text->move(100,100);
    m_Button* return_button = new m_Button(this,false,":/image/help_return_button.png");
    return_button->move(200,400);
    connect(return_button,&m_Button::clicked,[=](){
        emit return_called();
    });
}

void help_window::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage img(":/image/help_bg.png");
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
}
