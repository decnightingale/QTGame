#include "m_Button.h"

m_board::m_board(QWidget* parent, bool mask, QString bg_image,int w,int h):QPushButton(parent),image_path(bg_image)
{
    QPixmap pix;
    pix.load(image_path);
    if(w!=0&&h!=0)
    {
        pix = pix.scaled(w,h);
    }
    setFixedSize(pix.width(), pix.height());
    setStyleSheet("QPushButton{border:0px;}");
    if (mask)
        setMask(pix.mask());
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));
}

void m_board::mousePressEvent(QMouseEvent* event)
{
    return QPushButton::mousePressEvent(event);
}

void m_board::mouseReleaseEvent(QMouseEvent* event)
{
    return QPushButton::mouseReleaseEvent(event);
}

void m_board::enterEvent(QEnterEvent* event)
{
    return QPushButton::enterEvent(event);
}

void m_board::leaveEvent(QEvent* event)
{
    return QPushButton::leaveEvent(event);
}

m_Button::m_Button(QWidget* parent, bool mask, QString original_image, QString clicked_iamge) :
    QPushButton(parent), original_image_path(original_image), clicked_image_path(clicked_iamge)
{
    setCursor(Qt::PointingHandCursor);
    QPixmap pix;
    pix.load(original_image_path);
    setFixedSize(pix.width(), pix.height());
    setStyleSheet("QPushButton{border:0px;}");
    if (mask)
        setMask(pix.mask());
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));
}

void m_Button::mousePressEvent(QMouseEvent* event)
{
    move(x() + 1, y() + 1);
    return QPushButton::mousePressEvent(event);
}

void m_Button::mouseReleaseEvent(QMouseEvent* event)
{
    move(x() - 1, y() - 1);
    return QPushButton::mouseReleaseEvent(event);
}

void m_Button::enterEvent(QEnterEvent* event)
{
    if (clicked_image_path != "")
    {
        QPixmap pix;
        pix.load(clicked_image_path);
        setIcon(pix);
    }
    return QPushButton::enterEvent(event);
}

void m_Button::leaveEvent(QEvent* event)
{
    if (clicked_image_path != "")
    {
        QPixmap pix;
        pix.load(original_image_path);
        setIcon(pix);
    }
    return QPushButton::leaveEvent(event);
}

collection_symbol::collection_symbol(QWidget* parent):m_Button(parent,true,":/image/collection_symbol.png"),num(0),list(0)
{

}

void collection_symbol::clicked_action()
{
    QWidget* info = new QWidget(0);
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("收藏品");
    info->resize(800, 600);
    QPixmap bg = QPixmap(":/image/collection_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
    quit_button->move(350, 450);
    connect(quit_button, &m_Button::clicked, [=]() {
        info->close();
    });

    m_board* inform = new m_board(info,true, ":/image/unknown.png");
    inform->move(50,300);
    m_board* interpret = new m_board(info,false, ":/image/info_default.png");
    interpret->move(150,300);

    m_Button* collection_1 = new m_Button(info, true, ":/image/collection_1.png");
    collection_1->move(0,0);
    if(!(list&1))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_1->setFixedSize(un.size());
        collection_1->setMask(un.mask());
        collection_1->setIcon(un);
    }
    else
    {
        connect(collection_1,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_1.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_1.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_2 = new m_Button(info, true, ":/image/collection_2.png");
    collection_2->move(133,0);
    if(!(list&(1<<1)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_2->setFixedSize(un.size());
        collection_2->setMask(un.mask());
        collection_2->setIcon(un);
    }
    else
    {
        connect(collection_2,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_2.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_2.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_3 = new m_Button(info, true, ":/image/collection_3.png");
    collection_3->move(266,0);
    if(!(list&(1<<2)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_3->setFixedSize(un.size());
        collection_3->setMask(un.mask());
        collection_3->setIcon(un);
    }
    else
    {
        connect(collection_3,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_3.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_3.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_4 = new m_Button(info, true, ":/image/collection_4.png");
    collection_4->move(400,0);
    if(!(list&(1<<3)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_4->setFixedSize(un.size());
        collection_4->setMask(un.mask());
        collection_4->setIcon(un);
    }
    else
    {
        connect(collection_4,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_4.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_4.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_5 = new m_Button(info, true, ":/image/collection_5.png");
    collection_5->move(533,0);
    if(!(list&(1<<4)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_5->setFixedSize(un.size());
        collection_5->setMask(un.mask());
        collection_5->setIcon(un);
    }
    else
    {
        connect(collection_5,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_5.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_5.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_6 = new m_Button(info, true, ":/image/collection_6.png");
    collection_6->move(666,0);
    if(!(list&(1<<5)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_6->setFixedSize(un.size());
        collection_6->setMask(un.mask());
        collection_6->setIcon(un);
    }
    else
    {
        connect(collection_6,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_6.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_6.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_7 = new m_Button(info, true, ":/image/collection_7.png");
    collection_7->move(0,100);
    if(!(list&(1<<6)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_7->setFixedSize(un.size());
        collection_7->setMask(un.mask());
        collection_7->setIcon(un);
    }
    else
    {
        connect(collection_7,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_7.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_7.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_8 = new m_Button(info, true, ":/image/collection_8.png");
    collection_8->move(133,100);
    if(!(list&(1<<7)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_8->setFixedSize(un.size());
        collection_8->setMask(un.mask());
        collection_8->setIcon(un);
    }
    else
    {
        connect(collection_8,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_8.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_8.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_9 = new m_Button(info, true, ":/image/collection_9.png");
    collection_9->move(266,100);
    if(!(list&(1<<8)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_9->setFixedSize(un.size());
        collection_9->setMask(un.mask());
        collection_9->setIcon(un);
    }
    else
    {
        connect(collection_9,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_9.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_9.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_10 = new m_Button(info, true, ":/image/collection_10.png");
    collection_10->move(400,100);
    if(!(list&(1<<9)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_10->setFixedSize(un.size());
        collection_10->setMask(un.mask());
        collection_10->setIcon(un);
    }
    else
    {
        connect(collection_10,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_10.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_10.png");
            interpret->setIcon(new_info);
        });
    }

    m_Button* collection_11 = new m_Button(info, true, ":/image/collection_11.png");
    collection_11->move(533,100);
    if(!(list&(1<<10)))
    {
        QPixmap un;
        un.load(":image/unknown.png");
        un.scaled(50,50);
        collection_11->setFixedSize(un.size());
        collection_11->setMask(un.mask());
        collection_11->setIcon(un);
    }
    else
    {
        connect(collection_11,&m_Button::clicked,[=](){
            QPixmap new_collection;
            new_collection.load(":/image/collection_11.png");
            inform->setFixedSize(new_collection.width(),new_collection.height());
            inform->setMask(new_collection.mask());
            inform->setIcon(new_collection);
            QPixmap new_info;
            new_info.load(":/image/info_1_11.png");
            interpret->setIcon(new_info);
        });
    }

    info->show();
}

goods::goods(QWidget* parent,int p,QString goods_image,QString goods_info):m_Button(parent,true,goods_image),money(0),price(p),info_path(goods_info)
{

}

void goods::clicked_action()
{
    QWidget* info = new QWidget(0);
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("商品信息");
    info->resize(800, 600);
    QPixmap bg = QPixmap(":/image/goods_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    m_board* image = new m_board(info,true,original_image_path);
    image->move(0,100);

    m_board* about = new m_board(info,true,info_path);
    about->move(100,100);

    QLabel* price_label = new QLabel(info);
    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(16);  // 设置字号
    font.setBold(true);    // 设置粗体
    price_label->setFont(font);
    price_label->resize(100, 100);
    price_label->move(10, 200);
    price_label->setWordWrap(true);
    QString price_info("价格：");
    QString temp;
    temp.setNum(price);
    price_info += temp;
    price_label->setText(price_info);

    m_Button* buy_button = new m_Button(info,true,":/image/buy_button.png");
    buy_button->move(300,400);
    connect(buy_button,&m_Button::clicked,[=](){
        emit buy_callled();
        info->close();
    });

    if(money<price)
    {
        buy_button->hide();
    }

    m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
    quit_button->move(0, 400);
    connect(quit_button, &m_Button::clicked, [=]() {
        info->close();
    });
    info->show();
}

//贴图外观改动，现在一开始看不到节点
my_point::my_point(QWidget* parent, bool mask, QString original_image,QString located_image,QString explored_image,QString forbid_iamge, QString clicked_image) :m_Button(parent, mask, original_image, clicked_image),
    explored(false), can_be_chosen(false), forward_num(0), connected_num(0), located_image_path(located_image),explored_image_path(explored_image),forbid_image_path(forbid_iamge) {
    QPixmap masked;
    masked.load(":/image/unknown.png");
    setIcon(masked);
}

void my_point::change_located()
{
    QPixmap sec;
    sec.load(located_image_path);
    setMask(sec.mask());
    setIcon(sec);
}

void my_point::restore_located()
{
    QPixmap ori;
    ori.load(explored_image_path);
    setMask(ori.mask());
    setIcon(ori);
}


void my_point::connect_to(my_point* another)
{
    connected_point[connected_num] = another;
    connected_num++;
    another->connected_point[another->connected_num] = this;
    another->connected_num++;
}

void my_point::add_forward_point(my_point* another)
{
    forward_point[forward_num] = another;
    forward_num++;
}

void my_point::change_can_chosen()
{
    return;
}

void my_point::close_can_chosen()
{
    return;
}

start_point::start_point(QWidget* parent) :my_point(parent, false, ":/image/start_point.png",":/image/start_point_located.png",":/image/start_point_explored.png",":/image/start_point_forbid.png")
{

}

//设置改变可以选择的状态：如果节点已经探索过，或者已经可见，则忽略//之后的版本可能会涉及贴图改变等情况
void start_point::change_can_chosen()
{
    can_be_chosen = true;
    QPixmap chs;
    chs.load(original_image_path);
    setIcon(chs);
}

void start_point::close_can_chosen()
{
    can_be_chosen = false;
    QPixmap cls;
    cls.load(forbid_image_path);
    setIcon(cls);
}

//设置初始节点的点击槽响应函数
void start_point::clicked_action()
{
    if (!can_be_chosen)
    {
        return;
    }
    QWidget* info = new QWidget(0);
    info->setWindowModality(Qt::ApplicationModal);
    info->setWindowTitle("最初的落脚点");
    info->resize(500, 400);
    QPixmap bg = QPixmap(":/image/start_point_bg.png").scaled(info->size());
    QPalette palette(info->palette());
    palette.setBrush(QPalette::Window, QBrush(bg));
    info->setPalette(palette);

    QLabel* about_point = new QLabel(info);
    about_point->resize(500, 200);
    about_point->move(0, 0);
    about_point->setWordWrap(true);
    about_point->setText("醒来之后，你来到了这片无人海滩。向四周探索以解开真相");

    m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
    quit_button->move(0, 300);
    connect(quit_button, &m_Button::clicked, [=]() {
        info->close();
        });
    info->show();
}

treasure_point::treasure_point(QWidget* parent,int r) :my_point(parent, false, ":/image/treasure_point.png",":/image/treasure_point_located.png",":/image/treasure_point_explored.png",":/image/treasure_point_forbid.png")
{
    rank = r;
}

void treasure_point::change_can_chosen()
{
    can_be_chosen = true;
    QPixmap chs;
    chs.load(original_image_path);
    setIcon(chs);
}

void treasure_point::close_can_chosen()
{
    can_be_chosen = false;
    QPixmap cls;
    cls.load(forbid_image_path);
    setIcon(cls);
}

void treasure_point::clicked_action()
{
    if (!can_be_chosen&&!explored)
    {
        return;
    }
    if (!explored)
    {
        QWidget* info = new QWidget();
        info->setWindowModality(Qt::ApplicationModal);
        info->setWindowTitle("遗落的宝物");
        info->resize(618, 400);
        QPixmap bg = QPixmap(":/image/treasure_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //设置说明标签
        m_Button* about_point = new m_Button(info,false,":/image/treasure_point_info1.png");
        about_point->resize(500, 200);
        about_point->move(0, 0);

        //设置退出按钮
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
            });

        //设置选中按钮，选中会改变界面,改变explored状态,发送chosen信号
        m_Button* step_forward_button = new m_Button(info, false, ":/image/got_treasure_button.png");
        step_forward_button->move(300, 300);
        connect(step_forward_button, &m_Button::clicked, [=]() {
            emit got_chosen();
            QPixmap new_info;
            new_info.load(":/image/treasure_point_info2");
            about_point->setIcon(new_info);

            QString treasure_here;
            switch(rank)
            {
            case 0:
                treasure_here = ":/image/collection_1.png";
                break;
            case 1:
                treasure_here = ":/image/collection_2.png";
                break;
            case 2:
                treasure_here = ":/image/collection_3.png";
                break;
            case 3:
                treasure_here = ":/image/collection_4.png";
                break;
            case 4:
                treasure_here = ":/image/collection_5.png";
                break;
            case 5:
                treasure_here = ":/image/collection_6.png";
                break;
            case 6:
                treasure_here = ":/image/collection_7.png";
                break;
            case 7:
                treasure_here = ":/image/collection_8.png";
                break;
            }

            m_Button* got_treasure = new m_Button(info, true, treasure_here);
            got_treasure->move(200,150);
            got_treasure->show();

            explored = true;
            step_forward_button->hide();
            quit_button->hide();
            m_Button* quit_button_2 = new m_Button(info, false, ":/image/leave_button.png");
            quit_button_2->move(0, 300);
            connect(quit_button_2, &m_Button::clicked, [=]() {
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
        info->resize(500, 400);
        QPixmap bg = QPixmap(":/image/treasure_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //设置说明标签
        m_Button* about_point = new m_Button(info,false,":/image/treasure_point_info3.png");
        about_point->resize(500, 200);
        about_point->move(0, 0);

        //设置退出按钮
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
            });

        info->show();
    }
}

war_point::war_point(QWidget* parent) :my_point(parent, false, ":/image/war_point.png",":/image/war_point_located.png",":/image/war_point_explored.png",":/image/war_point_forbid.png")
{

}

void war_point::change_can_chosen()
{
    can_be_chosen = true;
    QPixmap chs;
    chs.load(original_image_path);
    setIcon(chs);
}

void war_point::close_can_chosen()
{
    can_be_chosen = false;
    QPixmap cls;
    cls.load(forbid_image_path);
    setIcon(cls);
}

story_point::story_point(QWidget* parent) :my_point(parent, false, ":/image/story_point.png",":/image/story_point_located.png",":/image/story_point_explored.png",":/image/story_point_forbid.png")
{

}

void story_point::change_can_chosen()
{
    can_be_chosen = true;
    QPixmap chs;
    chs.load(original_image_path);
    setIcon(chs);
}

void story_point::close_can_chosen()
{
    can_be_chosen = false;
    QPixmap cls;
    cls.load(forbid_image_path);
    setIcon(cls);
}

QString kst(int kk){

    QString act_string;
    act_string.setNum(kk,10);
    act_string = ":/image/action_" + act_string + ".png";
    //qDebug(act_string);
    return act_string;
}



action_button::action_button(QWidget* parent, an_action acc)
    :m_Button(parent,true,acc.path), ACC(acc){

}



accident_point::accident_point(QWidget* parent):
    my_point(parent, false, ":/image/accident_point.png",":/image/accident_point_located.png"
               ,":/image/accident_point_explored.png",":/image/accident_point_forbid.png")
{
    typ = -1;
}

QVector<an_action> accident_point::actions = QVector<an_action>();
QVector<an_incident> accident_point::incidents = QVector<an_incident>();

void accident_point::change_can_chosen()
{
    can_be_chosen = true;
    QPixmap chs;
    chs.load(original_image_path);
    setIcon(chs);
}

void accident_point::close_can_chosen()
{
    can_be_chosen = false;
    QPixmap cls;
    cls.load(forbid_image_path);
    setIcon(cls);
}

void accident_point::clicked_action()
{
    if (!can_be_chosen&&!explored)
    {
        return;
    }
    if (!explored)
    {
        srand(time(NULL));
        QWidget* info = new QWidget();
        info->setWindowModality(Qt::ApplicationModal);
        info->setWindowTitle("不期而遇");
        info->resize(500, 400);
        if (typ == -1){
            //qDebug("siz=%d", incidents.size());
            typ = rand() % 3;
            if(typ==2)
            typ = 4;
        }
        //qDebug("%d\n", typ);
        QPixmap bg = QPixmap(":/image/accident_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //
        QLabel* about_point = new QLabel(info);
        about_point->resize(500, 200);
        about_point->move(0, 0);
        about_point->setWordWrap(true);
        about_point->setText(incidents[typ].descri);

        //
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 280);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
            });

        QLabel* descs[4];
        //
        for (int i = 0; i < incidents[typ].num; i++){
            int kk = incidents[typ].choices[i];
            step_forward_buttons[i] = new action_button(info,actions[kk]);
            step_forward_buttons[i]->move(120, 250 + i * 70);
            descs[i] = new QLabel(info);
            descs[i]->resize(200, 300);
            descs[i]->move(280, 120 + i * 60);
            descs[i]->raise();
            descs[i]->setText(step_forward_buttons[i]->ACC.descri);
            descs[i]->setWordWrap(true);
        }
        for (int i = 0; i < incidents[typ].num; i++){

            connect(step_forward_buttons[i], &m_Button::clicked, [=]() {
                int r = rand() % 10 + 1;
                int judge = rand() % 100;
                if(judge < light_value)
                {
                    if(step_forward_buttons[i]->ACC.tar == 2)
                        r++;
                    if(step_forward_buttons[i]->ACC.tar == 3)
                        r--;
                }
                //qDebug("hp=%d",game->player_health);
                about_point->setText(step_forward_buttons[i]->ACC._move);
                //qDebug("health=%d", life_value);
                if (r <= step_forward_buttons[i]->ACC.chc){
                    if (step_forward_buttons[i]->ACC.tar == 2){
                        life_value += step_forward_buttons[i]->ACC.val;
                        if (life_value < 1){
                            life_value = 1;
                        }
                    }
                    else if (step_forward_buttons[i]->ACC.tar == 1){
                        light_value += step_forward_buttons[i]->ACC.val;
                        if (light_value > 100){
                            light_value = 100;
                        }
                        if (light_value < 0){
                            light_value = 0;
                        }
                    }
                    else if (step_forward_buttons[i]->ACC.tar == 3)
                    {
                        money_value += step_forward_buttons[i]->ACC.val;
                        if(money_value<0)
                            money_value = 0;
                    }
                    else if (step_forward_buttons[i]->ACC.tar == 4)
                    {
                        collection_list_used ^= (1<<9);
                        collection_num_used++;
                        collection_list ^= (1<<9);
                        collection_num++;
                        life_value +=6;
                        light_value-=30;
                        if(light_value<0)
                            light_value = 0;
                    }
                    else if (step_forward_buttons[i]->ACC.tar == 5)
                    {
                        collection_list_used ^= (1<<10);
                        collection_num_used++;
                        collection_list ^= (1<<10);
                        collection_num++;
                        life_value = 1;
                    }
                    descs[i]->setText(step_forward_buttons[i]->ACC.result1);
                }
                else{
                    descs[i]->setText(step_forward_buttons[i]->ACC.result2);
                }
                emit got_chosen();
                //qDebug("health=%d", game->player_health);
                explored = true;
                for (int j = 0; j < incidents[typ].num; j++){
                    step_forward_buttons[j]->hide();
                    if (j != i){
                        descs[j]->hide();
                    }
                    else{
                        descs[i]->resize(400, 300);
                        descs[i]->move(0, 30);
                        descs[i]->raise();
                    }
                }
                quit_button->hide();
                m_Button* enter_button = new m_Button(info, false, ":/image/leave_button.png");
                enter_button->move(0, 300);
                connect(enter_button, &m_Button::clicked, [=]() {
                    info->close();
                });
                enter_button->show();
            });
        }

        info->show();
    }
    else
    {
        QWidget* info = new QWidget();
        info->setWindowModality(Qt::ApplicationModal);
        info->setWindowTitle("不期而遇");
        info->resize(500, 400);
        QPixmap bg = QPixmap(":/image/accident_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //
        QLabel* about_point = new QLabel(info);
        about_point->resize(500, 200);
        about_point->move(0, 0);
        about_point->setWordWrap(true);
        about_point->setText("这里曾经发生过什么，但什么也没留下");

        //
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
            });

        info->show();
    }
}

branch_point::branch_point(QWidget* parent) :my_point(parent, false, ":/image/branch_point.png",":/image/branch_point_located.png",":/image/branch_point_explored.png",":/image/branch_point_forbid.png")
    ,used_num(0),used_list(0),money(0),life_value(0),light_value(0),buy_sum(0)
{

}

void branch_point::change_can_chosen()
{
    can_be_chosen = true;
    QPixmap chs;
    chs.load(original_image_path);
    setIcon(chs);
}

void branch_point::close_can_chosen()
{
    can_be_chosen = false;
    QPixmap cls;
    cls.load(forbid_image_path);
    setIcon(cls);
}

void branch_point::clicked_action()
{
    if(!can_be_chosen&&!explored)
    {
        return ;
    }
    if(!explored)
    {
        QWidget* info = new QWidget();
        info->setWindowModality(Qt::ApplicationModal);
        info->setWindowTitle("奇怪的鼠鼠");
        info->resize(800, 600);
        QPixmap bg = QPixmap(":/image/branch_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //设置说明标签
        m_Button* about_point = new m_Button(info,false,":/image/branch_point_info1.png");
        about_point->resize(500, 200);
        about_point->move(0, 0);

        //设置退出按钮
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
        });

        //设置选中按钮，选中会改变界面,改变explored状态,发送chosen信号
        m_Button* step_forward_button = new m_Button(info, false, ":/image/shop_button.png");
        step_forward_button->move(300, 300);
        connect(step_forward_button, &m_Button::clicked, [=]() {
            about_point->hide();
            int goods_list[7];
            int goods_num=0;
            for (int var = 0; var <= 8; ++var)
            {
                if(used_list&(1<<var))
                    continue;
                else
                {
                    goods_list[goods_num]=var;
                    goods_num++;
                }
            }
            QString path_list[9]={":/image/collection_1.png",":/image/collection_2.png",":/image/collection_3.png",":/image/collection_4.png",
                                    ":/image/collection_5.png",":/image/collection_6.png",":/image/collection_7.png",":/image/collection_8.png",
                                    ":/image/collection_9.png"};
            QString info_list[9]={":/image/info_1_1.png",":/image/info_1_2.png",":/image/info_1_3.png",":/image/info_1_4.png",
                                    ":/image/info_1_5.png",":/image/info_1_6.png",":/image/info_1_7.png",":/image/info_1_8.png",
                                    ":/image/info_1_9.png"};
            int prices_list[9]={12,12,16,16,16,16,16,16,20};

            m_board* money_icon = new m_board(info,true,":/image/money_icon.png");
            money_icon->move(20,220);
            money_icon->show();

            QLabel* price_label = new QLabel(info);
            QFont font;
            font.setFamily("Times New Roman");
            font.setPointSize(16);  // 设置字号
            font.setBold(true);    // 设置粗体
            price_label->setFont(font);
            price_label->setNum(money);
            price_label->move(80,230);
            price_label->show();

            if(goods_num>0)
                {
            goods* goods_1 = new goods(info,prices_list[goods_list[0]],path_list[goods_list[0]],info_list[goods_list[0]]);
            connect(goods_1,&goods::clicked,[=](){
                goods_1->money = money;
            });
            connect(goods_1,&goods::clicked,goods_1,&goods::clicked_action);
            connect(goods_1,&goods::buy_callled,[=](){
                if(goods_list[0]==0)
                    light_value+=30;
                if(goods_list[0]==1)
                    life_value+=6;
                if(light_value>100)
                    light_value=100;
                money-=prices_list[goods_list[0]];
                price_label->setNum(money);
                buy_rank[buy_sum]=goods_list[0];
                buy_sum++;
                goods_1->hide();
            });
            goods_1->move(0,0);
            goods_1->show();
            }

            if(goods_num>1)
            {
            goods* goods_2 = new goods(info,prices_list[goods_list[1]],path_list[goods_list[1]],info_list[goods_list[1]]);
            connect(goods_2,&goods::clicked,[=](){
                goods_2->money = money;
            });
            connect(goods_2,&goods::clicked,goods_2,&goods::clicked_action);
            connect(goods_2,&goods::buy_callled,[=](){
                if(goods_list[1]==0)
                    light_value+=30;
                if(goods_list[1]==1)
                    life_value+=6;
                if(light_value>100)
                    light_value=100;
                money-=prices_list[goods_list[1]];
                price_label->setNum(money);
                buy_rank[buy_sum]=goods_list[1];
                buy_sum++;
                goods_2->hide();
            });
            goods_2->move(200,0);
            goods_2->show();
            }

            if(goods_num>2)
            {
            goods* goods_3 = new goods(info,prices_list[goods_list[2]],path_list[goods_list[2]],info_list[goods_list[2]]);
            connect(goods_3,&goods::clicked,[=](){
                goods_3->money = money;
            });
            connect(goods_3,&goods::clicked,goods_3,&goods::clicked_action);
            connect(goods_3,&goods::buy_callled,[=](){
                if(goods_list[2]==0)
                    light_value+=30;
                if(goods_list[2]==1)
                    life_value+=6;
                if(light_value>100)
                    light_value=100;
                money-=prices_list[goods_list[2]];
                price_label->setNum(money);
                buy_rank[buy_sum]=goods_list[2];
                buy_sum++;
                goods_3->hide();
            });
            goods_3->move(400,0);
            goods_3->show();
            }

            if(goods_num>3)
            {
            goods* goods_4 = new goods(info,prices_list[goods_list[3]],path_list[goods_list[3]],info_list[goods_list[3]]);
            connect(goods_4,&goods::clicked,[=](){
                goods_4->money = money;
            });
            connect(goods_4,&goods::clicked,goods_4,&goods::clicked_action);
            connect(goods_4,&goods::buy_callled,[=](){
                if(goods_list[3]==0)
                    light_value+=30;
                if(goods_list[3]==1)
                    life_value+=6;
                if(light_value>100)
                    light_value=100;
                money-=prices_list[goods_list[3]];
                price_label->setNum(money);
                buy_rank[buy_sum]=goods_list[3];
                buy_sum++;
                goods_4->hide();
            });
            goods_4->move(600,0);
            goods_4->show();
            }

            if(goods_num>4)
            {
            goods* goods_5 = new goods(info,prices_list[goods_list[4]],path_list[goods_list[4]],info_list[goods_list[4]]);
            connect(goods_5,&goods::clicked,[=](){
                goods_5->money = money;
            });
            connect(goods_5,&goods::clicked,goods_5,&goods::clicked_action);
            connect(goods_5,&goods::buy_callled,[=](){
                if(goods_list[4]==0)
                    light_value+=30;
                if(goods_list[4]==1)
                    life_value+=6;
                if(light_value>100)
                    light_value=100;
                money-=prices_list[goods_list[4]];
                price_label->setNum(money);
                buy_rank[buy_sum]=goods_list[4];
                buy_sum++;
                goods_5->hide();
            });
            goods_5->move(0,100);
            goods_5->show();
            }

            if(goods_num>5)
            {
            goods* goods_6 = new goods(info,prices_list[goods_list[5]],path_list[goods_list[5]],info_list[goods_list[5]]);
            connect(goods_6,&goods::clicked,[=](){
                goods_6->money = money;
            });
            connect(goods_6,&goods::clicked,goods_6,&goods::clicked_action);
            connect(goods_6,&goods::buy_callled,[=](){
                if(goods_list[5]==0)
                    light_value+=30;
                if(goods_list[5]==1)
                    life_value+=6;
                if(light_value>100)
                    light_value=100;
                money-=prices_list[goods_list[5]];
                price_label->setNum(money);
                buy_rank[buy_sum]=goods_list[5];
                buy_sum++;
                goods_6->hide();
            });
            goods_6->move(200,100);
            goods_6->show();
            }

            if(goods_num>6)
            {
            goods* goods_7 = new goods(info,prices_list[goods_list[6]],path_list[goods_list[6]],info_list[goods_list[6]]);
            connect(goods_7,&goods::clicked,[=](){
                goods_7->money = money;
            });
            connect(goods_7,&goods::clicked,goods_7,&goods::clicked_action);
            connect(goods_7,&goods::buy_callled,[=](){
                if(goods_list[6]==0)
                    light_value+=30;
                if(goods_list[6]==1)
                    life_value+=6;
                if(light_value>100)
                    light_value=100;
                money-=prices_list[goods_list[6]];
                price_label->setNum(money);
                buy_rank[buy_sum]=goods_list[6];
                buy_sum++;
                goods_7->hide();
            });
            goods_7->move(400,100);
            goods_7->show();
            }

            explored = true;
            step_forward_button->hide();
            quit_button->hide();
            m_Button* quit_button_2 = new m_Button(info, false, ":/image/leave_button.png");
            quit_button_2->move(0, 300);
            connect(quit_button_2, &m_Button::clicked, [=]() {
                emit buy_end();
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
        info->setWindowTitle("奇怪的鼠鼠");
        info->resize(500, 400);
        QPixmap bg = QPixmap(":/image/branch_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //设置说明标签
        m_Button* about_point = new m_Button(info,false,":/image/treasure_point_info3.png");
        about_point->resize(500, 200);
        about_point->move(0, 0);

        //设置退出按钮
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
        });

        info->show();
    }
}

