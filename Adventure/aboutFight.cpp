#include "aboutFight.h"
#include <cstdlib>
#include <ctime>
#include <QPropertyAnimation>
#include "m_Button.h"
#include "game_map.h"
#define max(a,b) (a>b?a:b)
//war_point::clicked_action
void war_point::clicked_action()
{
    if (!can_be_chosen && !explored)
    {
        return;
    }
    if (!explored)
    {
        QWidget* info = new QWidget();
        info->resize(500, 400);
        info->move(300, 50);
        info->setWindowModality(Qt::ApplicationModal);
        info->setWindowTitle("路遇不测");
        info->resize(500, 400);
        QPixmap bg = QPixmap(":/image/war_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //设置说明标签
        QLabel* about_point = new QLabel(info);
        about_point->resize(500, 200);
        about_point->move(0, 0);
        about_point->setWordWrap(true);
        about_point->setText("阴影之中走出了几个面目凶狠的亡命之徒，你有麻烦了");

        //设置退出按钮
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
        });

        //设置选中按钮，选中会改变界面,改变explored状态
        m_Button* step_forward_button = new m_Button(info, false, ":/image/step_button.png");
        step_forward_button->move(300, 300);
        connect(step_forward_button, &m_Button::clicked, [=]() {
            emit got_chosen();
            about_point->setText("你决定给这群家伙一点教训");
            explored = true;
            step_forward_button->hide();
            quit_button->hide();
            m_Button* enter_button = new m_Button(info, false, ":/image/battle_button.png");
            enter_button->move(0, 300);

            connect(enter_button, &m_Button::clicked, [=]() {
                info->close();
                fightWidget* fightW = new fightWidget(collection_list,light_value,false);
                QObject::connect(fightW, &fightWidget::ended_win, [=]() {
                    money+=5;
                    if(collection_list & (1<<6)) light_value += 9;
                    if(light_value>100) light_value =100;
                    if(collection_list & (1<<7)) life_value += 1;
                    emit battle_end();
                });
                QObject::connect(fightW, &fightWidget::ended_lose, [=]() {
                    if(collection_list & (1<<7)) life_value += 1;
                    life_value -= 5;
                    if(life_value < 0) life_value = 0;
                    light_value -= 10;
                    //qDebug()<<light_value;
                    if(light_value < 0) light_value = 0;
                    emit battle_end();
                });
                fightW->oneFight(parentWidget());
            });
            enter_button->show();
        });
        info->show();
    }
    else
    {
        QWidget* info = new QWidget();
        info->setWindowModality(Qt::ApplicationModal);
        info->setWindowTitle("路遇不测");//路遇不测
        info->resize(500, 400);
        QPixmap bg = QPixmap(":/image/war_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //设置说明标签
        QLabel* about_point = new QLabel(info);
        about_point->resize(500, 200);
        about_point->move(0, 0);
        about_point->setWordWrap(true);
        about_point->setText("歹徒已经离开了");

        //设置退出按钮
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
        });

        info->show();
    }
}

//story_point::clicked_action
void story_point::clicked_action()
{
    if (!can_be_chosen && !explored)
    {
        return;
    }
    if (!explored)
    {
        QWidget* info = new QWidget();
        info->resize(500, 400);
        info->move(300, 50);
        info->setWindowModality(Qt::ApplicationModal);
        info->setWindowTitle("深陷险境");
        info->resize(500, 400);
        QPixmap bg = QPixmap(":/image/war_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //设置说明标签
        QLabel* about_point = new QLabel(info);
        about_point->resize(500, 200);
        about_point->move(0, 0);
        about_point->setWordWrap(true);
        about_point->setText("阴影之中走出了一只巨大的怪物，你感到自己遇到了一个大麻烦");

        //设置退出按钮
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
        });

        //设置选中按钮，选中会改变界面,改变explored状态
        m_Button* step_forward_button = new m_Button(info, false, ":/image/step_button.png");
        step_forward_button->move(300, 300);
        connect(step_forward_button, &m_Button::clicked, [=]() {
            emit got_chosen();
            about_point->setText("你决定给这群家伙一点教训");
            explored = true;
            step_forward_button->hide();
            quit_button->hide();
            m_Button* enter_button = new m_Button(info, false, ":/image/battle_button.png");
            enter_button->move(0, 300);

            connect(enter_button, &m_Button::clicked, [=]() {
                info->close();
                fightWidget* fightW = new fightWidget(collection_list,light_value,true);
                QObject::connect(fightW, &fightWidget::ended_win, [=]() {
                    if(collection_list & (1<<6)) light_value += 9;
                    if(light_value>100) light_value =100;
                    if(collection_list & (1<<7)) life_value += 1;
                    money += 15;
                    emit battle_end();
                });
                QObject::connect(fightW, &fightWidget::ended_lose, [=]() {
                    if(collection_list & (1<<7)) life_value += 1;
                    light_value-=10;
                    if(light_value<0)
                        light_value=0;
                    life_value-=5;
                    if(life_value<0)
                        life_value =0;

                    emit battle_end();
                });
                fightW->oneFight(parentWidget());
            });
            enter_button->show();
        });
        info->show();
    }
    else
    {
        QWidget* info = new QWidget();
        info->setWindowModality(Qt::ApplicationModal);
        info->setWindowTitle(" ");//路遇不测
        info->resize(500, 400);
        QPixmap bg = QPixmap(":/image/war_point_bg.png").scaled(info->size());
        QPalette palette(info->palette());
        palette.setBrush(QPalette::Window, QBrush(bg));
        info->setPalette(palette);

        //设置说明标签
        QLabel* about_point = new QLabel(info);
        about_point->resize(500, 200);
        about_point->move(0, 0);
        about_point->setWordWrap(true);
        about_point->setText("歹徒已经离开了");

        //设置退出按钮
        m_Button* quit_button = new m_Button(info, false, ":/image/leave_button.png");
        quit_button->move(0, 300);
        connect(quit_button, &m_Button::clicked, [=]() {
            info->close();
        });

        info->show();
    }
}

//fightWidget
fightWidget::fightWidget(int c,int light,bool d,QWidget* parentW)
    :QStackedWidget(parentW),light_value(light),collection_list(c),diff(d)
{
    move(450, 30);
    show();
    setWindowTitle("fight");
    QPixmap bg1 = QPixmap(":/image/war_point_bg.png").scaled(1200,800);
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Window, QBrush(bg1));
    setPalette(palette);
    resize(1200, 800);
    setCurrentIndex(0);

    fight = new QWidget();//0
    fight->resize(1200, 800);
    addWidget(fight);

    endW = new QWidget();//1
    endW->resize(640, 500);
    addWidget(endW);

    left[0] = nullptr;
    left[1] = nullptr;
    left[2] = nullptr;
    right[0] = nullptr;
    right[1] = nullptr;
    right[2] = nullptr;

    intoEnd = new m_Button(fight, 0, ":/image/next_button.png");
    intoEnd->setGeometry(270, 280, 40, 40);
    intoEnd->hide();
    QObject::connect(intoEnd, &m_Button::clicked, [=]()
                     {
                         resize(640, 500);
                         setCurrentIndex(1);
                         if(left[0]==nullptr)
                             emit ended_lose();
                         else
                             emit ended_win();
                     });

    endConfirm = new m_Button(endW, 0, ":/image/leave_button.png");
    endConfirm->setGeometry(270, 280, 40, 40);
    endNotice = new QLabel(endW);
    // 修改格式
    endNotice->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(16);  // 设置字号
    font.setBold(true);    // 设置粗体
    endNotice->setFont(font);
    endNotice->setGeometry(220, 250, 200, 20);
    endConfirm->show();
    endNotice->show();

    QObject::connect(endConfirm, &m_Button::clicked, this, &QStackedWidget::close);
}

void fightWidget::checkAlive()
{
    for(int i = 0; i < 3; i++)
    {
        if(left[i] != nullptr)
            if(left[i]->HP <= 0)
            {
                delete left[i];
                left[i] = nullptr;
            }
        if(right[i] != nullptr)
            if(right[i]->HP <= 0)
            {
                delete right[i];
                right[i] = nullptr;
            }
    }
    update();

    if(left[0] == nullptr and left[1] == nullptr and left[2] == nullptr)
    {
        for(int i = 0; i < 3; i++)
            if(right[i] != nullptr)
            {
                right[i]->emit win();
                return;
            }
    }
    if(right[0] == nullptr and right[1] == nullptr and right[2] == nullptr)
    {
        for(int i = 0; i < 3; i++)
            if(left[i] != nullptr)
            {
                left[i]->emit win();
                return;
            }
    }
}

void fightWidget::oneFight(QWidget* parent)
{
    srand(time(nullptr));
    int randomNum = rand() + 1000;
    int num[8] = {randomNum, randomNum / 2, randomNum / 3, randomNum / 5, randomNum / 7, randomNum / 11, randomNum / 13, randomNum / 17};
    left[0] = new fighter(fight, ":/image/warrior.png", QPoint(100, 650), 100, 6, 6, 10, 10, 8, 0, 1);
    left[1] = nullptr;
    left[2] = nullptr;
    if(!diff)
    {//普通关卡
        right[0] = new juniorDemon(fight, ":/image/demon.png", QPoint(1000, 650), 100, num[0] % 5 + 1, num[1] % 5 + 1, 10, num[2] % 5 + 1, num[3] % 5 + 1, 0, 1);
        right[1] = new juniorDemon(fight, ":/image/monster_1.png", QPoint(1000, 450), 100, num[4] % 5 + 1, num[5] % 5 + 1, 10, num[6] % 5 + 1, num[7] % 5 + 1, 0, 1);
        right[2] = new juniorDemon(fight, ":/image/demon.png", QPoint(1000, 250), 100, num[0] % 5 + 1, num[1] % 5 + 1, 10, num[2] % 5 + 1, num[3] % 5 + 1, 0, 1);
    }
    else
    {//精英关卡
        right[0] = nullptr;
        right[2] = nullptr;
        right[1] = new eliteDemon(fight, ":/image/monster_0.png",QPoint(1000, 450), 200, 10, 10, 15, 9, 9, 5, 3);
    }
    //道具效果
    //qDebug()<<collection_list;
    if(collection_list & (1<<2))
    {
        //qDebug()<<"2";
        //单位防御+35%
        if(left[0] != nullptr)
        {
            left[0]->PD += (left[0]->PD * 35 / 100);
            left[0]->SD += (left[0]->SD * 35 / 100);
        }
        if(left[1] != nullptr)
        {
            left[1]->PD += (left[1]->PD * 35 / 100);
            left[1]->SD += (left[1]->SD * 35 / 100);
        }
        if(left[2] != nullptr)
        {
            left[2]->PD += (left[2]->PD * 35 / 100);
            left[2]->SD += (left[2]->SD * 35 / 100);
        }
    }
    if(collection_list & (1<<3))
    {
        //qDebug()<<"3";
        //敌方+40%易伤
        if(left[0] != nullptr)
        {
            left[0]->multiPlier += 0.4;
        }
        if(left[1] != nullptr)
        {
            left[1]->multiPlier += 0.4;
        }
        if(left[2] != nullptr)
        {
            left[2]->multiPlier += 0.4;
        }
    }
    if(collection_list & (1<<4))
    {
        //qDebug()<<"4";
        //敌方-25%攻击
        if(right[0] != nullptr)
        {
            right[0]->PA -= (right[0]->PA * 25 / 100);
            right[0]->SA -= (right[0]->SA * 25 / 100);
        }
        if(right[1] != nullptr)
        {
            right[1]->PA -= (right[1]->PA * 25 / 100);
            right[1]->SA -= (right[1]->SA * 25 / 100);
        }
        if(right[2] != nullptr)
        {
            right[2]->PA -= (right[2]->PA * 25 / 100);
            right[2]->SA -= (right[2]->SA * 25 / 100);
        }
    }
    if(collection_list & (1<<5))
    {
        //qDebug()<<"5";
        //敌方-20%生命
        if(right[0] != nullptr)
        {
            right[0]->HP -= (right[0]->HP * 20 / 100);
        }
        if(right[1] != nullptr)
        {
            right[1]->HP -= (right[1]->HP * 20 / 100);
        }
        if(right[2] != nullptr)
        {
            right[2]->HP -= (right[2]->HP * 20 / 100);
        }
    }
    if(collection_list & (1<<8))
    {
        //qDebug()<<"8";
        //单位暴击+30%
        if(left[0] != nullptr)
        {
            left[0]->CR += 30;
        }
        if(left[1] != nullptr)
        {
            left[1]->CR += 30;
        }
        if(left[2] != nullptr)
        {
            left[2]->CR += 30;
        }
    }
    if(collection_list & (1<<10))
    {
        //qDebug()<<"10";
        //攻击+60%
        if(left[0] != nullptr)
        {
            left[0]->PA += (left[0]->PA * 60 / 100);
            left[0]->SA += (left[0]->SA * 60 / 100);
        }
        if(left[1] != nullptr)
        {
            left[1]->PA += (left[1]->PA * 60 / 100);
            left[1]->SA += (left[1]->SA * 60 / 100);
        }
        if(left[2] != nullptr)
        {
            left[2]->PA += (left[2]->PA * 60 / 100);
            left[2]->SA += (left[2]->SA * 60 / 100);
        }
    }
    for(int i = 0; i < 3; i++)
    {
        if(left[i] != nullptr) left[i]->showAll();
        if(right[i] != nullptr) right[i]->showAll();
    }
    for(int i = 0; i < 3; i++)
    {
        if(left[i] != nullptr)
            QObject::connect(left[i], &abstractFighter::win, [=](){
                intoEnd->raise();
                intoEnd->show();
                endNotice->setText("You won the fight !");

            });
        if(right[i] != nullptr)
            QObject::connect(right[i], &abstractFighter::win, [=](){
                intoEnd->raise();
                intoEnd->show();
                endNotice->setText("You failed !");

            });
    }

    QObject::connect(((fighter*)left[0]), &fighter::turnFinished,[&](){
        if(right[0] != nullptr) right[0]->oneTurn(fight, left, right);
        checkAlive();
        if(left[1] != nullptr) left[1]->oneTurn(fight, right, left);
        checkAlive();
        if(right[1] != nullptr) right[1]->oneTurn(fight, left, right);
        checkAlive();
        if(left[2] != nullptr) left[2]->oneTurn(fight, right, left);
        checkAlive();
        if(right[2] != nullptr) right[2]->oneTurn(fight, left, right);
        checkAlive();
        if(left[0] != nullptr) left[0]->oneTurn(fight, right, left);
        checkAlive();
    });
    left[0]->oneTurn(fight, right, left);
    checkAlive();
}

//stateIcon
void stateIcon::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap pixmap(bg);
    painter.drawPixmap(0, 0, width(), height(), pixmap);
    QLabel::paintEvent(event);
}

stateIcon::stateIcon(QWidget* parent, QPoint pos, QString bgPath, int value)
    :QLabel(parent), bg(bgPath)
{
    setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    move(pos);
    resize(30, 30);
    // 设置显示的内容
    setText(QString::number(value));

    // 修改字号和字体
    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(16);  // 设置字号
    font.setBold(true);    // 设置粗体
    setFont(font);

    hide();

    QFont font2;
    font2.setFamily("Times New Roman");
    font2.setPointSize(12);  // 设置字号
    info = new QLabel(parent);
    info->setGeometry(pos.x() + 40, pos.y() + 6, 110, 30);
    info->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    info->setFont(font2);
    info->hide();
}

void stateIcon::renew(int value)
{
    // 更新显示的内容
    setText(QString::number(value));
}

//HPLine
HPLine::HPLine(QWidget* parent, const QPoint& pos, const QColor& color, int value)
    : QGraphicsView(parent),
    scene(new QGraphicsScene(this)),
    healthRect(new QGraphicsRectItem),
    valueText(new QGraphicsTextItem),
    healthColor(color)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setGeometry(pos.x(), pos.y(), 150, 15);
    // 设置场景和视图
    setScene(scene);
    setAlignment(Qt::AlignLeft);
    //setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿渲染

    // 设置血量矩形
    int width = value * 3 / 2;  // 血条宽度
    int height = 16;  // 血条高度
    healthRect->setRect(0, -8, width, height);
    healthRect->setBrush(healthColor);
    scene->addItem(healthRect);

    // 设置血量文本
    valueText->setPlainText(QString::number(value));
    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(12);  // 设置字号
    font.setBold(true);    // 设置粗体
    valueText->setFont(QFont(font));
    valueText->setDefaultTextColor(Qt::black);
    int textX = (150 - valueText->boundingRect().width()) / 2;
    int textY = (height - valueText->boundingRect().height()) / 2 - 7;
    valueText->setPos(textX, textY);
    scene->addItem(valueText);
}

void HPLine::renew(int value)
{
    valueText->setPlainText(QString::number(value));
    healthRect->setRect(0, -8, value * 3 / 2, 16);
}

void HPLine::setColor(QColor color)
{
    healthColor = color;
    healthRect->setBrush(healthColor);
}

//abstractFighter
void abstractFighter::showAll()
{
    show();
    PDIcon->renew(max(PD + pd, 0));
    PDIcon->show();
    SDIcon->renew(max(SD + sd, 0));
    SDIcon->show();
    PAIcon->renew(max(PA + pa, 0));
    PAIcon->show();
    SAIcon->renew(max(SA + sa, 0));
    SAIcon->show();
    APIcon->renew(AP);
    APIcon->show();
    HPL->renew(HP);
    HPL->show();
    CRIcon->renew(max(CR + cr, 0));
    ERIcon->renew(max(ER + er, 0));
}

abstractFighter::abstractFighter(QWidget* parent, QString bg, const QPoint& pos, int hp, int pd, int sd, int er, int pa, int sa, int cr, int ap)
    :m_Button(parent, 0, bg), iconPath(bg), HP(hp), PD(pd), SD(sd), ER(er), PA(pa), SA(sa), CR(cr), AP(ap)
{
    multiPlier = 1;

    move(pos);

    PDIcon = new stateIcon(parent, QPoint(pos.x() + 100, pos.y() + 50), ":/image/PD.png", PD);
    PDIcon->info->setText("Physical Defense");
    PDIcon->raise();
    PDIcon->info->raise();
    SDIcon = new stateIcon(parent, QPoint(pos.x() + 100, pos.y() + 80), ":/image/SD.png", SD);
    SDIcon->info->setText("Spell Defense");
    SDIcon->raise();
    SDIcon->info->raise();
    PAIcon = new stateIcon(parent, QPoint(pos.x() - 50, pos.y() + 50), ":/image/PA.png", PA);
    PAIcon->info->setText("Physical Attack");
    PAIcon->raise();
    PAIcon->info->raise();
    SAIcon = new stateIcon(parent, QPoint(pos.x() - 50, pos.y() + 80), ":/image/SA.png", SA);
    SAIcon->info->setText("Spell Attack");
    SAIcon->raise();
    SAIcon->info->raise();
    APIcon = new stateIcon(parent, QPoint(pos.x() - 50, pos.y() + 20), ":/image/AP.png", AP);
    APIcon->info->setText("Action Points");
    APIcon->raise();
    APIcon->info->raise();
    CRIcon = new stateIcon(parent, QPoint(pos.x() - 50, pos.y() + 110), ":/image/CR.png", CR);
    CRIcon->info->setText("Critical Rate");
    CRIcon->raise();
    CRIcon->info->raise();
    ERIcon = new stateIcon(parent, QPoint(pos.x() + 100, pos.y() + 110), ":/image/ER.png", ER);
    ERIcon->info->setText("Evasion Rate");
    ERIcon->raise();
    ERIcon->info->raise();
    HPL = new HPLine(parent, QPoint(pos.x() - 25, pos.y() - 30), Qt::yellow, HP);
    showAll();

    sGroup = nullptr;
}

abstractFighter::~abstractFighter()
{
    if(sGroup != nullptr)
    {
        delete sGroup;
        sGroup = nullptr;
    }
    delete PAIcon;
    delete PDIcon;
    delete SAIcon;
    delete SDIcon;
    delete CRIcon;
    delete ERIcon;
    delete APIcon;
    delete HPL;
}

void abstractFighter::mousePressEvent(QMouseEvent* event)
{
    QPixmap t;
    t.load(":/image/transparent.png");
    setIcon(t);
    PDIcon->info->show();
    SDIcon->info->show();
    PAIcon->info->show();
    SAIcon->info->show();
    APIcon->info->show();
    CRIcon->show();
    CRIcon->info->show();
    ERIcon->show();
    ERIcon->info->show();
}

void abstractFighter::mouseReleaseEvent(QMouseEvent* event)
{
    QPixmap t;
    t.load(iconPath);
    setIcon(t);
    PDIcon->info->hide();
    SDIcon->info->hide();
    PAIcon->info->hide();
    SAIcon->info->hide();
    APIcon->info->hide();
    CRIcon->hide();
    CRIcon->info->hide();
    ERIcon->hide();
    ERIcon->info->hide();
}

void abstractFighter::hittenPerformance()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(100);
    animation->setKeyValueAt(0, QPoint(this->x(), this->y()));
    animation->setKeyValueAt(0.1, QPoint(this->x() + 5, this->y()));
    animation->setKeyValueAt(0.2, QPoint(this->x() - 5, this->y()));
    animation->setKeyValueAt(0.3, QPoint(this->x() + 5, this->y()));
    animation->setKeyValueAt(0.4, QPoint(this->x() - 5, this->y()));
    animation->setKeyValueAt(0.5, QPoint(this->x() + 5, this->y()));
    animation->setKeyValueAt(0.6, QPoint(this->x() - 5, this->y()));
    animation->setKeyValueAt(0.7, QPoint(this->x() + 5, this->y()));
    animation->setKeyValueAt(0.8, QPoint(this->x() - 5, this->y()));
    animation->setKeyValueAt(0.9, QPoint(this->x() + 5, this->y()));
    animation->setEndValue(QPoint(this->x(), this->y()));
    animation->start();
}

//skillUnit
void skillUnit::paintEvent(QPaintEvent* event)
{
    QString bg;
    bg = QString(":/image/skills/skill_") + QString::number(type.x()) + QString::number(type.y()) + QString(".png");
    QPainter painter(this);
    QPixmap pixmap(bg);
    painter.drawPixmap(0, 0, width(), height(), pixmap);
    QLabel::paintEvent(event);
}

skillUnit::skillUnit(QWidget* parentW, const QPoint& p1, const QPoint& p2, int l, QPoint t)
    :QLabel(parentW), level(l), type(t), pos1(p1), pos2(p2)
{
    srand(time(nullptr));
    value = level * 5 + rand() % 5 + 1 + level;
    setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    move(pos1);
    resize(70, 70);
    switch (level) {
    case 0:
        setStyleSheet("color: white;");
        break;
    case 1:
        setStyleSheet("color: lightgreen;");
        break;
    case 2:
        setStyleSheet("color: lightblue;");
        break;
    case 3:
        setStyleSheet("color: orange;");
        break;
    default:
        setStyleSheet("color: red;");
        break;
    }
    // 设置显示的内容
    QString prefix;
    if(type.x() == 0)
    {
        if(type.y() == 0) prefix = "PAttack ";
        else if(type.y() == 1) prefix = "SAttack ";
    }
    else if(type.x() == 1)
    {
        if(type.y() == 0) prefix = "PDefense ";
        else if(type.y() == 1) prefix = "SDefense ";
    }
    else if(type.x() == 2)
    {
        if(type.y() == 0) prefix = "Critical ";
        else if(type.y() == 1) prefix = "Evasion ";
        else if(type.y() == 2) prefix = "Recover ";
        else if(type.y() == 3)
        {
            prefix = "Action ";
            value = 1;
        }
        else if(type.y() == 4) prefix = "AOE ";
    }
    else if(type.x() == 3)
    {
        if(type.y() == 0) prefix = "DePA ";
        else if(type.y() == 1) prefix = "DeSA ";
        else if(type.y() == 2) prefix = "DePD ";
        else if(type.y() == 3) prefix = "DeSD ";
        else if(type.y() == 4)
        {
            value = 1;
            prefix = "Action ";
        }
    }
    setText(prefix + QString::number(value));

    // 修改字号和字体
    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(10);  // 设置字号
    font.setBold(true);    // 设置粗体
    setFont(font);

    show();
}

void skillUnit::mousePressEvent(QMouseEvent* event)
{
    if(pos() != pos2)
    {
        move(pos2);
        emit chosen();
    }
}

//skillGroup
bool randomEvent(int P, int t)
{
    srand(time(nullptr));
    int x = (max(rand() - 150, 0) + 150) / t % 100;
    if(x <= P) return true;
    else return false;
}

void skillGroup::generate(QWidget* parentW, int l)
{
    skillUnit* choose[4];
    srand(time(nullptr));
    int randomNum = rand() + 1000;
    int num[8] = {randomNum, randomNum / 2, randomNum / 3, randomNum / 5, randomNum / 7, randomNum / 11, randomNum / 13, randomNum / 17};

    switch(l)
    {
    case(0):
        choose[0] = new skillUnit(parentW, QPoint(300, 700), QPoint(200, 200), l, QPoint(num[0] % 2, num[1] % 2));
        choose[1] = new skillUnit(parentW, QPoint(400, 700), QPoint(200, 200), l, QPoint(num[2] % 2, num[3] % 2));
        choose[2] = new skillUnit(parentW, QPoint(500, 700), QPoint(200, 200), l, QPoint(num[4] % 2, num[5] % 2));
        choose[3] = new skillUnit(parentW, QPoint(600, 700), QPoint(200, 200), l, QPoint(num[6] % 2 + 2, num[7] % 5));
        break;
    case(1):
        choose[0] = new skillUnit(parentW, QPoint(300, 700), QPoint(300, 200), l, QPoint(num[0] % 2, num[1] % 2));
        choose[1] = new skillUnit(parentW, QPoint(400, 700), QPoint(300, 200), l, QPoint(num[2] % 2, num[3] % 2));
        choose[2] = new skillUnit(parentW, QPoint(500, 700), QPoint(300, 200), l, QPoint(num[4] % 2, num[5] % 2));
        choose[3] = new skillUnit(parentW, QPoint(600, 700), QPoint(300, 200), l, QPoint(num[6] % 2 + 2, num[7] % 5));
        break;
    case(2):
        choose[0] = new skillUnit(parentW, QPoint(300, 700), QPoint(400, 200), l, QPoint(num[0] % 2, num[1] % 2));
        choose[1] = new skillUnit(parentW, QPoint(400, 700), QPoint(400, 200), l, QPoint(num[2] % 2, num[3] % 2));
        choose[2] = new skillUnit(parentW, QPoint(500, 700), QPoint(400, 200), l, QPoint(num[4] % 2 + 2, num[5] % 5));
        choose[3] = new skillUnit(parentW, QPoint(600, 700), QPoint(400, 200), l, QPoint(num[6] % 2 + 2, num[7] % 5));
        break;
    case(3):
        choose[0] = new skillUnit(parentW, QPoint(300, 700), QPoint(500, 200), l, QPoint(num[0] % 2, num[1] % 2));
        choose[1] = new skillUnit(parentW, QPoint(400, 700), QPoint(500, 200), l, QPoint(num[2] % 2, num[3] % 2));
        choose[2] = new skillUnit(parentW, QPoint(500, 700), QPoint(500, 200), l, QPoint(num[4] % 2 + 2, num[5] % 5));
        choose[3] = new skillUnit(parentW, QPoint(600, 700), QPoint(500, 200), l, QPoint(num[6] % 2 + 2, num[7] % 5));
        break;
    case(4):
        choose[0] = new skillUnit(parentW, QPoint(300, 700), QPoint(600, 200), l, QPoint(num[0] % 2, num[1] % 2));
        choose[1] = new skillUnit(parentW, QPoint(400, 700), QPoint(600, 200), l, QPoint(num[2] % 2, num[3] % 2));
        choose[2] = new skillUnit(parentW, QPoint(500, 700), QPoint(600, 200), l, QPoint(num[4] % 2 + 2, num[5] % 5));
        choose[3] = new skillUnit(parentW, QPoint(600, 700), QPoint(600, 200), l, QPoint(num[6] % 2 + 2, num[7] % 5));
        break;
    default:
        choose[0] = new skillUnit(parentW, QPoint(300, 700), QPoint(200 + l * 100, 200), l, QPoint(num[0] % 2, num[1] % 2));
        choose[1] = new skillUnit(parentW, QPoint(400, 700), QPoint(200 + l * 100, 200), l, QPoint(num[2] % 2 + 2, num[3] % 5));
        choose[2] = new skillUnit(parentW, QPoint(500, 700), QPoint(200 + l * 100, 200), l, QPoint(num[4] % 2 + 2, num[5] % 5));
        choose[3] = new skillUnit(parentW, QPoint(600, 700), QPoint(200 + l * 100, 200), l, QPoint(num[6] % 2 + 2, num[7] % 5));
        break;
    }

    QObject::connect(choose[0], &skillUnit::chosen, [=](){
        choose[1]->hide();
        delete choose[1];
        choose[2]->hide();
        delete choose[2];
        choose[3]->hide();
        delete choose[3];

        this->group[l] = choose[0];
        if(l < level) generate(parentW, l + 1);
        else emit groupFinished();
    });
    QObject::connect(choose[1], &skillUnit::chosen, [=](){
        choose[0]->hide();
        delete choose[0];
        choose[2]->hide();
        delete choose[2];
        choose[3]->hide();
        delete choose[3];

        this->group[l] = choose[1];
        if(l < level) generate(parentW, l + 1);
        else emit groupFinished();
    });
    QObject::connect(choose[2], &skillUnit::chosen, [=](){
        choose[0]->hide();
        delete choose[0];
        choose[1]->hide();
        delete choose[1];
        choose[3]->hide();
        delete choose[3];

        this->group[l] = choose[2];
        if(l < level) generate(parentW, l + 1);
        else emit groupFinished();
    });
    QObject::connect(choose[3], &skillUnit::chosen, [=](){
        choose[0]->hide();
        delete choose[0];
        choose[1]->hide();
        delete choose[1];
        choose[2]->hide();
        delete choose[2];

        this->group[l] = choose[3];
        if(l < level) generate(parentW, l + 1);
        else emit groupFinished();
    });
}

skillGroup::skillGroup(QWidget* parentW, const int l)
{
    level = l;
    for(int i = 0; i < 100; i++)
        group[i] = nullptr;
}

skillGroup::~skillGroup()
{
    for(int i = 0; i <= level; i++)
        if(group[i] != nullptr) delete group[i];
}

void skillGroup::skillEffect(abstractFighter* self, abstractFighter* opponent[3], abstractFighter* ally[3])
{
    //self->hittenPerformance(); //测试用

    //获取技能组数据
    for(int i = 0; i <= level; i++)
    {
        if(group[i]->type.x() == 0)
        {
            if(group[i]->type.y() == 0) self->pa += group[i]->value;
            else if(group[i]->type.y() == 1) self->sa += group[i]->value;
        }
        else if(group[i]->type.x() == 1)
        {
            if(group[i]->type.y() == 0) self->pd += group[i]->value;
            else if(group[i]->type.y() == 1) self->sd += group[i]->value;
        }
        else if(group[i]->type.x() == 2)
        {
            if(group[i]->type.y() == 0) self->cr += group[i]->value;
            else if(group[i]->type.y() == 1) self->er += group[i]->value;
            else if(group[i]->type.y() == 2) self->hp += group[i]->value;
            else if(group[i]->type.y() == 3) self->ap += 1;
            else if(group[i]->type.y() == 4) self->aoe += 1;
        }
        else if(group[i]->type.x() == 3)
        {
            if(group[i]->type.y() == 0) self->depa += group[i]->value;
            else if(group[i]->type.y() == 1) self->desa += group[i]->value;
            else if(group[i]->type.y() == 2) self->depd += group[i]->value;
            else if(group[i]->type.y() == 3) self->desd += group[i]->value;
            else if(group[i]->type.y() == 4) self->ap += group[i]->value;
        }
    }

    //计算暴击事件
    int critMultiplier = self->multiPlier;
    if(randomEvent(self->CR + self->cr, 1))
        critMultiplier +=1;

    if(self->aoe)
    {
        self->HP += self->hp;
        self->CR += self->cr;
        self->ER += self->er;
        self->AP += self->ap;
        self->pa += self->pa;
        self->sa += self->sa;
        self->pd += self->pd;
        self->sd += self->sd;

        if(ally[0] != nullptr and ally[0] != self)
        {
            ally[0]->HP += self->hp;
            ally[0]->CR += self->cr;
            ally[0]->ER += self->er;
            ally[0]->AP += self->ap;
            ally[0]->pa += self->pa;
            ally[0]->sa += self->sa;
            ally[0]->pd += self->pd;
            ally[0]->sd += self->sd;
        }
        if(ally[1] != nullptr and ally[1] != self)
        {
            ally[1]->HP += self->hp;
            ally[1]->CR += self->cr;
            ally[1]->ER += self->er;
            ally[1]->AP += self->ap;
            ally[1]->pa += self->pa;
            ally[1]->sa += self->sa;
            ally[1]->pd += self->pd;
            ally[1]->sd += self->sd;
        }
        if(ally[2] != nullptr and ally[2] != self)
        {
            ally[2]->HP += self->hp;
            ally[2]->CR += self->cr;
            ally[2]->ER += self->er;
            ally[2]->AP += self->ap;
            ally[2]->pa += self->pa;
            ally[2]->sa += self->sa;
            ally[2]->pd += self->pd;
            ally[2]->sd += self->sd;
        }

        if(opponent[0] != nullptr)
        {
            if(!randomEvent(opponent[0]->ER + opponent[0]->er, 2))
            {
                opponent[0]->pa -= self->depa;
                opponent[0]->sa -= self->desa;
                opponent[0]->pd -= self->depd;
                opponent[0]->sd -= self->desd;
                opponent[0]->HP -= max(0, ((self->PA + self->pa) * critMultiplier * (self->aoe + 1) - (opponent[0]->PD + opponent[0] -> pd)));
                opponent[0]->HP -= max(0, ((self->SA + self->sa) * critMultiplier * (self->aoe + 1) - (opponent[0]->SD + opponent[0] -> sd)));
                opponent[0]->showAll();
                opponent[0]->hittenPerformance();
            }
        }
        if(opponent[1] != nullptr)
        {
            if(!randomEvent(opponent[1]->ER + opponent[1]->er, 3))
            {
                opponent[1]->pa -= self->depa;
                opponent[1]->sa -= self->desa;
                opponent[1]->pd -= self->depd;
                opponent[1]->sd -= self->desd;
                opponent[1]->HP -= max(0, ((self->PA + self->pa) * critMultiplier * (self->aoe + 1) - (opponent[1]->PD + opponent[1] -> pd)));
                opponent[1]->HP -= max(0, ((self->SA + self->sa) * critMultiplier * (self->aoe + 1) - (opponent[1]->SD + opponent[1] -> sd)));
                opponent[1]->showAll();
                opponent[1]->hittenPerformance();
            }
        }
        if(opponent[2] != nullptr)
        {
            if(!randomEvent(opponent[2]->ER + opponent[2]->er, 5))
            {
                opponent[2]->pa -= self->depa;
                opponent[2]->sa -= self->desa;
                opponent[2]->pd -= self->depd;
                opponent[2]->sd -= self->desd;
                opponent[2]->HP -= max(0, ((self->PA + self->pa) * critMultiplier * (self->aoe + 1) - (opponent[2]->PD + opponent[2] -> pd)));
                opponent[2]->HP -= max(0, ((self->SA + self->sa) * critMultiplier * (self->aoe + 1) - (opponent[2]->SD + opponent[2] -> sd)));
                opponent[2]->showAll();
                opponent[2]->hittenPerformance();
            }
        }
    }
    else
    {
        self->HP += self->hp;
        self->CR += self->cr;
        self->ER += self->er;
        self->AP += self->ap;
        self->pa += self->pa;
        self->sa += self->sa;
        self->pd += self->pd;
        self->sd += self->sd;

        if(opponent[0] != nullptr)
        {
            if(!randomEvent(opponent[0]->ER + opponent[0]->er, 2))
            {
                opponent[0]->pa -= self->depa;
                opponent[0]->sa -= self->desa;
                opponent[0]->pd -= self->depd;
                opponent[0]->sd -= self->desd;
                opponent[0]->HP -= max(0, ((self->PA + self->pa) * critMultiplier * (self->aoe + 1) - (opponent[0]->PD + opponent[0] -> pd)));
                opponent[0]->HP -= max(0, ((self->SA + self->sa) * critMultiplier * (self->aoe + 1) - (opponent[0]->SD + opponent[0] -> sd)));
                opponent[0]->showAll();
                opponent[0]->hittenPerformance();
            }
        }
        else if(opponent[1] != nullptr)
        {
            if(!randomEvent(opponent[1]->ER + opponent[1]->er, 3))
            {
                opponent[1]->pa -= self->depa;
                opponent[1]->sa -= self->desa;
                opponent[1]->pd -= self->depd;
                opponent[1]->sd -= self->desd;
                opponent[1]->HP -= max(0, ((self->PA + self->pa) * critMultiplier * (self->aoe + 1) - (opponent[1]->PD + opponent[1] -> pd)));
                opponent[1]->HP -= max(0, ((self->SA + self->sa) * critMultiplier * (self->aoe + 1) - (opponent[1]->SD + opponent[1] -> sd)));
                opponent[1]->showAll();
                opponent[1]->hittenPerformance();
            }
        }
        else if(opponent[2] != nullptr)
        {
            if(!randomEvent(opponent[2]->ER + opponent[2]->er, 5))
            {
                opponent[2]->pa -= self->depa;
                opponent[2]->sa -= self->desa;
                opponent[2]->pd -= self->depd;
                opponent[2]->sd -= self->desd;
                opponent[2]->HP -= max(0, ((self->PA + self->pa) * critMultiplier * (self->aoe + 1) - (opponent[2]->PD + opponent[2] -> pd)));
                opponent[2]->HP -= max(0, ((self->SA + self->sa) * critMultiplier * (self->aoe + 1) - (opponent[2]->SD + opponent[2] -> sd)));
                opponent[2]->showAll();
                opponent[2]->hittenPerformance();
            }
        }
    }
}

//fighter
fighter::fighter(QWidget* parent, QString bg, const QPoint& pos, int hp, int pd, int sd, int er, int pa, int sa, int cr, int ap)
    :abstractFighter(parent, bg, pos, hp, pd, sd, er, pa, sa, cr, ap)
{
    HPL->setColor(Qt::green);
    endTurn = new m_Button(parent, 0, ":/image/damage_button.png");
    endTurn->setGeometry(800, 700, 30, 30);
    endTurn->hide();
}

void fighter::oneTurn(QWidget* parent, abstractFighter* opponent[3], abstractFighter* ally[3])
{
    sGroup = new skillGroup(parent, AP);
    sGroup->generate(parent, 0);

    QObject::connect(sGroup, &skillGroup::groupFinished, [=](){
        m_Button* previous = endTurn;
        QObject::connect(previous, &m_Button::clicked, [=](){
            //回合开始时重置临时属性
            pa = 0;
            sa = 0;
            pd = 0;
            sd = 0;
            cr = 0;
            er = 0;
            ap = 0;
            hp = 0;
            depa = 0;
            desa = 0;
            depd = 0;
            desd = 0;
            aoe = 0;
            skip = 0;

            sGroup->skillEffect(this, opponent, ally);
            delete sGroup;
            sGroup = nullptr;
            emit turnFinished();

            if(previous != nullptr) previous->hide();
        });
        previous->show();

        endTurn = new m_Button(parent, 0, ":\\image\\damage_button");
        endTurn->setGeometry(800, 700, 30, 30);
        endTurn->hide();
    });
}

//juniorDemon
juniorDemon::juniorDemon(QWidget* parent, QString bg, const QPoint& pos, int hp, int pd, int sd, int er, int pa, int sa, int cr, int ap)
    :abstractFighter(parent, bg, pos, hp, pd, sd, er, pa, sa, cr, ap)
{
    HPL->setColor(Qt::red);
}

void juniorDemon::oneTurn(QWidget* parent, abstractFighter* opponent[3], abstractFighter* ally[3])
{
    sGroup = new skillGroup(parent, AP);
    sGroup->group[0] = new skillUnit(parent, QPoint(0, 0), QPoint(0, 0), 0, QPoint(0, 0));
    sGroup->group[1] = new skillUnit(parent, QPoint(0, 0), QPoint(0, 0), 0, QPoint(0, 1));
    sGroup->group[0]->hide();
    sGroup->group[1]->hide();

    sGroup->skillEffect(this, opponent, ally);

    //重置临时属性
    pa = 0;
    sa = 0;
    pd = 0;
    sd = 0;
    cr = 0;
    er = 0;
    ap = 0;
    hp = 0;
    depa = 0;
    desa = 0;
    depd = 0;
    desd = 0;
    aoe = 0;
    skip = 0;

    delete sGroup;
    sGroup = nullptr;
}

//eliteDemon
eliteDemon::eliteDemon(QWidget* parent, QString bg, const QPoint& pos, int hp, int pd, int sd, int er, int pa, int sa, int cr, int ap)
    :abstractFighter(parent, bg, pos, hp, pd, sd, er, pa, sa, cr, ap)
{
    HPL->setColor(Qt::red);
}

void eliteDemon::oneTurn(QWidget* parentW, abstractFighter* opponent[3], abstractFighter* ally[3])
{
    if(opponent[0] == nullptr and opponent[1] == nullptr and opponent[2] == nullptr) emit win();
    srand(time(nullptr));
    int randomNum = rand() + 1000;
    int num[8] = {randomNum, randomNum / 2, randomNum / 3, randomNum / 5, randomNum / 7, randomNum / 11, randomNum / 13, randomNum / 17};
    sGroup = new skillGroup(parentW, 3);
    sGroup->group[0] = new skillUnit(parentW, QPoint(300, 700), QPoint(200, 200), 0, QPoint(num[0] % 2, num[1] % 2));
    sGroup->group[1] = new skillUnit(parentW, QPoint(400, 700), QPoint(200, 200), 1, QPoint(num[2] % 2, num[3] % 2));
    sGroup->group[2] = new skillUnit(parentW, QPoint(500, 700), QPoint(200, 200), 2, QPoint(num[4] % 2, num[5] % 2));
    sGroup->group[3] = new skillUnit(parentW, QPoint(600, 700), QPoint(200, 200), 0, QPoint(num[6] % 2 + 2, num[7] % 5));

    sGroup->group[0]->hide();
    sGroup->group[1]->hide();
    sGroup->group[2]->hide();
    sGroup->group[3]->hide();

    sGroup->skillEffect(this, opponent, ally);

    //重置临时属性
    pa = 0;
    sa = 0;
    pd = 0;
    sd = 0;
    cr = 0;
    er = 0;
    ap = 0;
    hp = 0;
    depa = 0;
    desa = 0;
    depd = 0;
    desd = 0;
    aoe = 0;
    skip = 0;

    delete sGroup;
    sGroup = nullptr;
}

