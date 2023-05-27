#include "game_map.h"
#include <QDebug>

game_map::game_map(QWidget* parent):QWidget(parent),light_value(100),life_value(10),located_point(0)
{
    //生命值,灯火值声明
    QString life_string;
    life_string.setNum(life_value,10);
    QString light_string;
    light_string.setNum(light_value,10);
    QLabel* life_label = new QLabel(this);
    life_label->setText(life_string);
    life_label->move(50,20);
    QLabel* light_label = new QLabel(this);
    light_label->setText(light_string);
    light_label->move(150,20);

    //设置上下左右移动按钮
    m_Button* up_button = new m_Button(this,true,":/image/up_arrow.png");
    up_button->move(680,-40);

    m_Button* right_button = new m_Button(this,true,":/image/right_arrow.png");
    right_button->move(725,0);

    m_Button* left_button = new m_Button(this,true,":/image/left_arrow.png");
    left_button->move(640,0);

    m_Button* down_button = new m_Button(this,true,":/image/down_arrow.png");
    down_button->move(680,40);

    //设置左下角返回主菜单按钮
    m_Button* return_button = new m_Button(this,false,":/image/game_map_return_button.png");
    return_button->move(0,500);
    connect(return_button,&m_Button::clicked,[=](){
        emit return_called();
    });

    //设置帮助按钮//注：目前帮助仍然是主界面的帮助菜单，应该要加一个有关游戏地图的动态帮助窗口，类似于节点说明
    m_Button* help_button = new m_Button(this,false,":/image/game_map_help_button.png");
    help_button->move(130,500);
    connect(help_button,&m_Button::clicked,[=](){
        emit help_called();
    });

    //初始节点设置，按动会跳出节点说明动态窗口
    start_point* start_point_ = new start_point(this);
    start_point_->move(333,91);
    connect(start_point_,&start_point::clicked,start_point_,&start_point::clicked_action);
    arrow_connect_tool(up_button,down_button,left_button,right_button,start_point_);
    start_point_->change_can_chosen();

    //宝藏节点设置
    treasure_point* treasure_point_1 = new treasure_point(this);
    treasure_point_1->move(367,754);
    connect(treasure_point_1,&treasure_point::clicked,treasure_point_1,&treasure_point::clicked_action);
    connect(treasure_point_1,&treasure_point::got_chosen,[=](){
        set_located_point(treasure_point_1);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,treasure_point_1);

    treasure_point* treasure_point_2 = new treasure_point(this);
    treasure_point_2->move(490,1249);
    connect(treasure_point_2,&treasure_point::clicked,treasure_point_2,&treasure_point::clicked_action);
    connect(treasure_point_2,&treasure_point::got_chosen,[=](){
        set_located_point(treasure_point_2);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,treasure_point_2);

    treasure_point* treasure_point_3 = new treasure_point(this);
    treasure_point_3->move(965,1100);
    connect(treasure_point_3,&treasure_point::clicked,treasure_point_3,&treasure_point::clicked_action);
    connect(treasure_point_3,&treasure_point::got_chosen,[=](){
        set_located_point(treasure_point_3);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,treasure_point_3);



    //战斗节点设置
    war_point* war_point_1 = new war_point(this);
    war_point_1->move(727,257);
    connect(war_point_1,&war_point::clicked,war_point_1,&war_point::clicked_action);
    connect(war_point_1,&war_point::got_chosen,[=](){
        set_located_point(war_point_1);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_1);

    war_point* war_point_2 = new war_point(this);
    war_point_2->move(560,988);
    connect(war_point_2,&war_point::clicked,war_point_2,&war_point::clicked_action);
    connect(war_point_2,&war_point::got_chosen,[=](){
        set_located_point(war_point_2);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_2);

    war_point* war_point_3 = new war_point(this);
    war_point_3->move(206,1234);
    connect(war_point_3,&war_point::clicked,war_point_3,&war_point::clicked_action);
    connect(war_point_3,&war_point::got_chosen,[=](){
        set_located_point(war_point_3);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_3);

    war_point* war_point_4 = new war_point(this);
    war_point_4->move(1242,863);
    connect(war_point_4,&war_point::clicked,war_point_4,&war_point::clicked_action);
    connect(war_point_4,&war_point::got_chosen,[=](){
        set_located_point(war_point_4);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_4);

    war_point* war_point_5 = new war_point(this);
    war_point_5->move(1213,396);
    connect(war_point_5,&war_point::clicked,war_point_5,&war_point::clicked_action);
    connect(war_point_5,&war_point::got_chosen,[=](){
        set_located_point(war_point_5);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,war_point_5);

    //剧情节点设置
    story_point* story_point_1 = new story_point(this);
    story_point_1->move(724,650);
    connect(story_point_1,&story_point::clicked,story_point_1,&story_point::clicked_action);
    connect(story_point_1,&story_point::got_chosen,[=](){
        set_located_point(story_point_1);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_1);

    story_point* story_point_2 = new story_point(this);
    story_point_2->move(225,982);
    connect(story_point_2,&story_point::clicked,story_point_2,&story_point::clicked_action);
    connect(story_point_2,&story_point::got_chosen,[=](){
        set_located_point(story_point_2);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_2);

    story_point* story_point_3 = new story_point(this);
    story_point_3->move(631,1736);
    connect(story_point_3,&story_point::clicked,story_point_3,&story_point::clicked_action);
    connect(story_point_3,&story_point::got_chosen,[=](){
        set_located_point(story_point_3);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_3);

    story_point* story_point_4 = new story_point(this);
    story_point_4->move(1540,1281);
    connect(story_point_4,&story_point::clicked,story_point_4,&story_point::clicked_action);
    connect(story_point_4,&story_point::got_chosen,[=](){
        set_located_point(story_point_4);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_4);

    story_point* story_point_5 = new story_point(this);
    story_point_5->move(1474,427);
    connect(story_point_5,&story_point::clicked,story_point_5,&story_point::clicked_action);
    connect(story_point_5,&story_point::got_chosen,[=](){
        set_located_point(story_point_5);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,story_point_5);


    //事件节点设置
    accident_point* accident_point_1 = new accident_point(this);
    accident_point_1->move(240,496);
    connect(accident_point_1,&accident_point::clicked,accident_point_1,&accident_point::clicked_action);
    connect(accident_point_1,&accident_point::got_chosen,[=](){
        set_located_point(accident_point_1);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_1);

    accident_point* accident_point_2 = new accident_point(this);
    accident_point_2->move(575,442);
    connect(accident_point_2,&accident_point::clicked,accident_point_2,&accident_point::clicked_action);
    connect(accident_point_2,&accident_point::got_chosen,[=](){
        set_located_point(accident_point_2);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_2);

    accident_point* accident_point_3 = new accident_point(this);
    accident_point_3->move(-80,1426);
    connect(accident_point_3,&accident_point::clicked,accident_point_3,&accident_point::clicked_action);
    connect(accident_point_3,&accident_point::got_chosen,[=](){
        set_located_point(accident_point_3);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_3);

    accident_point* accident_point_4 = new accident_point(this);
    accident_point_4->move(518,1501);
    connect(accident_point_4,&accident_point::clicked,accident_point_4,&accident_point::clicked_action);
    connect(accident_point_4,&accident_point::got_chosen,[=](){
        set_located_point(accident_point_4);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_4);

    accident_point* accident_point_5 = new accident_point(this);
    accident_point_5->move(1279,1257);
    connect(accident_point_5,&accident_point::clicked,accident_point_5,&accident_point::clicked_action);
    connect(accident_point_5,&accident_point::got_chosen,[=](){
        set_located_point(accident_point_5);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_5);

    accident_point* accident_point_6 = new accident_point(this);
    accident_point_6->move(930,820);
    connect(accident_point_6,&accident_point::clicked,accident_point_6,&accident_point::clicked_action);
    connect(accident_point_6,&accident_point::got_chosen,[=](){
        set_located_point(accident_point_6);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_6);

    accident_point* accident_point_7 = new accident_point(this);
    accident_point_7->move(968,353);
    connect(accident_point_7,&accident_point::clicked,accident_point_7,&accident_point::clicked_action);
    connect(accident_point_7,&accident_point::got_chosen,[=](){
        set_located_point(accident_point_7);
    });
    arrow_connect_tool(up_button,down_button,left_button,right_button,accident_point_7);


    //连接各节点，制成地图
    start_point_->connect_to(accident_point_1);
    start_point_->connect_to(accident_point_2);
    start_point_->connect_to(war_point_1);
    accident_point_1->connect_to(accident_point_2);
    accident_point_2->connect_to(war_point_1);
    story_point_1->connect_to(accident_point_1);
    story_point_1->connect_to(accident_point_2);
    story_point_1->connect_to(war_point_1);
    treasure_point_1->connect_to(accident_point_1);
    treasure_point_1->connect_to(story_point_1);
    treasure_point_1->connect_to(accident_point_6);
    treasure_point_1->connect_to(story_point_2);
    treasure_point_1->connect_to(war_point_2);
    story_point_2->connect_to(war_point_2);
    story_point_2->connect_to(treasure_point_2);
    story_point_2->connect_to(war_point_3);
    war_point_3->connect_to(accident_point_3);
    war_point_3->connect_to(accident_point_4);
    accident_point_3->connect_to(story_point_3);
    story_point_3->connect_to(accident_point_4);
    accident_point_5->connect_to(treasure_point_3);
    accident_point_5->connect_to(accident_point_4);
    accident_point_5->connect_to(story_point_3);
    accident_point_5->connect_to(story_point_4);
    treasure_point_3->connect_to(war_point_4);
    accident_point_6->connect_to(treasure_point_3);
    accident_point_6->connect_to(war_point_4);
    accident_point_6->connect_to(accident_point_7);
    accident_point_7->connect_to(war_point_5);
    war_point_5->connect_to(story_point_5);

    //设置初始节点为start_point;
    set_located_point(start_point_);
}

//设置当前节点
void game_map::set_located_point(my_point* new_point)
{
    if(!new_point->can_be_chosen)
        return;
    located_point = new_point;
    int sum = new_point->connected_num;
    for(int i=0;i<sum;i++)
        new_point->connected_point[i]->change_can_chosen();
}

//工具函数，建立各个节点和视野移动按钮之间的联系
void game_map::arrow_connect_tool(m_Button* up,m_Button* down,m_Button* left,m_Button* right,my_point* aim)
{
    connect(up,&m_Button::clicked,[=](){
        aim->move(aim->x(),aim->y()+50);
    });
    connect(down,&m_Button::clicked,[=](){
        aim->move(aim->x(),aim->y()-50);
    });
    connect(right,&m_Button::clicked,[=](){
        aim->move(aim->x()-50,aim->y());
    });
    connect(left,&m_Button::clicked,[=](){
        aim->move(aim->x()+50,aim->y());
    });
}

//绘制窗口背景
void game_map::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage img(":/image/game_map_bg.png");
    img=img.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,img);
    QPixmap life_icon = QPixmap(":/image/life_icon.png").scaled(50,50);
    QPixmap light_icon = QPixmap(":/image/light_icon.png").scaled(50,50);
    painter.drawPixmap(0,0,life_icon);
    painter.drawPixmap(100,0,light_icon);
}
