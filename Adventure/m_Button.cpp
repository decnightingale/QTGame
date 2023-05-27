#include "m_Button.h"

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

my_point::my_point(QWidget* parent,bool mask,QString original_image,QString clicked_image):m_Button(parent,mask,original_image,clicked_image),
    explored(false),can_be_chosen(false),connected_num(0){

}

void my_point::connect_to(my_point* another)
{
    connected_point[connected_num]=another;
    connected_num++;
    another->connected_point[another->connected_num]=this;
    another->connected_num++;
}

void my_point::change_can_chosen()
{
    return ;
}

start_point::start_point(QWidget* parent):my_point(parent,true,":/image/start_point.png")
{

}

//设置改变可以选择的状态：如果节点已经探索过，或者已经可见，则忽略//之后的版本可能会涉及贴图改变等情况
void start_point::change_can_chosen()
{
    can_be_chosen = true;
}

//设置初始节点的点击槽响应函数
void start_point::clicked_action()
{
    if(!can_be_chosen)
    {
    return ;
    }
    QWidget* info = new QWidget(0);
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("最初的落脚点");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/start_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("醒来之后，你来到了这片无人海滩。向四周探索以解开真相");

    m_Button* quit_button = new m_Button(info,false,":/image/quit_button.png");
    quit_button->move(0,300);
    connect(quit_button,&m_Button::clicked,[=](){
        info->close();
    });
    info->show();
}

treasure_point::treasure_point(QWidget* parent):my_point(parent,true,":/image/treasure_point.png")
{

}

void treasure_point::change_can_chosen()
{
    can_be_chosen = true;
}

void treasure_point::clicked_action()
{
    if(!can_be_chosen)
    {
    return ;
    }
    if(!explored)
    {
    QWidget* info = new QWidget();
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("遗落的宝物");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/treasure_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    //设置说明标签
    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("艰难的前行过后，你发现泥滩一角有什么东西在发着光。一番挖掘之后，一个宝箱出现在你面前");

    //设置退出按钮
    m_Button* quit_button = new m_Button(info,false,":/image/treasure_quit_button.png");
    quit_button->move(0,300);
    connect(quit_button,&m_Button::clicked,[=](){
        info->close();
    });

    //设置选中按钮，选中会改变界面,改变explored状态,发送chosen信号
    m_Button* step_forward_button = new m_Button(info,false,":/image/treasure_step_forward_button.png");
    step_forward_button->move(300,300);
    connect(step_forward_button,&m_Button::clicked,[=](){
        emit got_chosen();
        about_point->setText("你从箱子里获得了一些物资");
        explored = true;
        step_forward_button->hide();
        quit_button->hide();
        m_Button* quit_button_2 = new m_Button(info,false,":/image/treasure_quit_button_2.png");
        quit_button_2->move(0,300);
        connect(quit_button_2,&m_Button::clicked,[=](){
            info->close();
        });
        quit_button_2->show();
    });

    info->show();
    }
    else
    {
    QWidget* info = new QWidget();
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("遗落的宝物");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/treasure_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    //设置说明标签
    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("这里已经没有任何东西了");

    //设置退出按钮
    m_Button* quit_button = new m_Button(info,false,":/image/treasure_quit_button_2.png");
    quit_button->move(0,300);
    connect(quit_button,&m_Button::clicked,[=](){
        info->close();
    });

    info->show();
    }
}

war_point::war_point(QWidget* parent):my_point(parent,true,":/image/war_point.png")
{

}

void war_point::change_can_chosen()
{
    can_be_chosen = true;
}

void war_point::clicked_action()
{
    if(!can_be_chosen)
    {
    return ;
    }
    if(!explored)
    {
    QWidget* info = new QWidget();
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("路遇不测");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/war_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    //设置说明标签
    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("阴影之中走出了几个面目凶狠的亡命之徒，你有麻烦了");

    //设置退出按钮
    m_Button* quit_button = new m_Button(info,false,":/image/war_quit_button.png");
    quit_button->move(0,300);
    connect(quit_button,&m_Button::clicked,[=](){
        info->close();
    });

    //设置选中按钮，选中会改变界面,改变explored状态
    m_Button* step_forward_button = new m_Button(info,false,":/image/war_step_forward_button.png");
    step_forward_button->move(300,300);
    connect(step_forward_button,&m_Button::clicked,[=](){
        emit got_chosen();
        about_point->setText("你决定给这群家伙一点教训");
        explored = true;
        step_forward_button->hide();
        quit_button->hide();
        m_Button* enter_button = new m_Button(info,false,":/image/war_enter_button.png");
        enter_button->move(0,300);
        connect(enter_button,&m_Button::clicked,[=](){
            info->close();
        });
        enter_button->show();
    });

    info->show();
    }
    else
    {
    QWidget* info = new QWidget();
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("路遇不测");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/war_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    //设置说明标签
    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("歹徒已经离开了");

    //设置退出按钮
    m_Button* quit_button = new m_Button(info,false,":/image/war_quit_button_2.png");
    quit_button->move(0,300);
    connect(quit_button,&m_Button::clicked,[=](){
        info->close();
    });

    info->show();
    }
}

story_point::story_point(QWidget* parent):my_point(parent,true,":/image/story_point.png")
{

}

void story_point::change_can_chosen()
{
    can_be_chosen = true;
}

void story_point::clicked_action()
{
    if(!can_be_chosen)
    {
    return ;
    }
    if(!explored)
    {
    QWidget* info = new QWidget();
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("疑云密布");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/story_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    //设置说明标签
    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("剧情文本。");

    //设置选中按钮，选中会改变界面,改变explored状态
    m_Button* step_forward_button = new m_Button(info,false,":/image/story_step_forward_button.png");
    step_forward_button->move(0,300);
    connect(step_forward_button,&m_Button::clicked,[=](){
        emit got_chosen();
        about_point->setText("剧情文本2");
        explored = true;
        step_forward_button->hide();
        m_Button* enter_button = new m_Button(info,false,":/image/story_quit_button.png");
        enter_button->move(0,300);
        connect(enter_button,&m_Button::clicked,[=](){
            info->close();
        });
        enter_button->show();
    });

    info->show();
    }
    else
    {
    QWidget* info = new QWidget();
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("疑云密布");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/story_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    //设置说明标签
    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("这里已经没有线索了");

    //设置退出按钮
    m_Button* quit_button = new m_Button(info,false,":/image/story_quit_button.png");
    quit_button->move(0,300);
    connect(quit_button,&m_Button::clicked,[=](){
        info->close();
    });

    info->show();
    }
}

accident_point::accident_point(QWidget* parent):my_point(parent,true,":/image/accident_point.png")
{

}

void accident_point::change_can_chosen()
{
    can_be_chosen = true;
}

void accident_point::clicked_action()
{
    if(!can_be_chosen)
    {
    return ;
    }
    if(!explored)
    {
    QWidget* info = new QWidget();
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("不期而遇");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/accident_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    //设置说明标签
    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("事件文本");

    //设置退出按钮
    m_Button* quit_button = new m_Button(info,false,":/image/accident_quit_button_1.png");
    quit_button->move(0,300);
    connect(quit_button,&m_Button::clicked,[=](){
        info->close();
    });

    //设置选中按钮，选中会改变界面,改变explored状态
    m_Button* step_forward_button = new m_Button(info,false,":/image/accident_step_forward_button_1.png");
    step_forward_button->move(300,300);
    connect(step_forward_button,&m_Button::clicked,[=](){
        emit got_chosen();
        about_point->setText("事件结果文本");
        explored = true;
        step_forward_button->hide();
        quit_button->hide();
        m_Button* enter_button = new m_Button(info,false,":/image/accident_quit_button_1.png");
        enter_button->move(0,300);
        connect(enter_button,&m_Button::clicked,[=](){
            info->close();
        });
        enter_button->show();
    });

    info->show();
    }
    else
    {
    QWidget* info = new QWidget();
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("不期而遇");
    info->resize(500,400);
    QPixmap bg = QPixmap(":/image/accident_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    //设置说明标签
    QLabel* about_point = new QLabel(info);
    about_point->resize(500,200);
    about_point->move(0,0);
    about_point->setWordWrap(true);
    about_point->setText("这里曾经发生过什么，但如今什么也没留下");

    //设置退出按钮
    m_Button* quit_button = new m_Button(info,false,":/image/accident_quit_button_1.png");
    quit_button->move(0,300);
    connect(quit_button,&m_Button::clicked,[=](){
        info->close();
    });

    info->show();
    }
}
