#ifndef ABOUTFIGHT_H
#define ABOUTFIGHT_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include "m_Button.h"

//前向声明
class skillGroup;

class stateIcon : public QLabel
{
    Q_OBJECT
public:
    QString bg;
    QLabel* info;
    stateIcon(QWidget* parent, QPoint pos, QString bg, int value = 0);
    void renew(int value);
    void paintEvent(QPaintEvent* event);
};

class HPLine : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene* scene;
    QGraphicsRectItem* healthRect;  // 血量矩形
    QGraphicsTextItem* valueText;  // 显示血量的文本
    QColor healthColor;
    HPLine(QWidget* parent, const QPoint& pos, const QColor& color, int value = 100);
    void setColor(QColor color);
    void renew(int value);
};

class skillUnit : public QLabel
{
    /*
    攻击类：增加物攻      增加法强      均衡增加攻击（二阶）      牺牲防御大幅增加攻击（二阶）
    防御类：提高物抗      提高法抗      均衡增加防御（二阶）      牺牲攻击大幅增加防御（二阶）
    辅助类：提高暴击率    增加闪避      回复生命        提升行动点数      造成范围效果      吸血效果（二阶）
    减益类：减少对方物攻  减少对方法强  减少对方物抗      减少对方法抗              跳过对方回合
    */
    Q_OBJECT
public:
    int level;
    QPoint type;
    int value;
    QPoint pos1, pos2;
    skillUnit(QWidget* parentW, const QPoint& p1, const QPoint& p2, int level, QPoint type);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void chosen();
};

class abstractFighter : public m_Button
{
    Q_OBJECT
public:
    int HP;//Health Points
    int PD;//Physical Defense
    int SD;//Spell Defense
    int ER;//Evasion Rate

    int PA;//Physical Attack
    int SA;//Spell Attack
    int CR;//Critical Rate

    int AP;//Action Points
    double multiPlier;
    //以下为临时属性
    int pa = 0, sa = 0, pd = 0, sd = 0,    cr = 0, er = 0, ap = 0, hp = 0;
    int depa = 0, desa = 0, depd = 0, desd = 0;
    int aoe = 0, skip = 0;

    skillGroup* sGroup;
    QString iconPath;
    stateIcon* PDIcon, * SDIcon, * PAIcon, * SAIcon, * APIcon, * CRIcon, * ERIcon;
    HPLine* HPL;

    void showAll();
    abstractFighter(QWidget* parent, QString bg, const QPoint& pos, int hp = 100, int pd = 0, int sd = 0, int er = 0, int pa = 0, int sa = 0, int cr = 0, int ap = 1);
    ~abstractFighter();
    virtual void oneTurn(QWidget* parent, abstractFighter* opponent[3], abstractFighter* ally[3]) = 0;
    void hittenPerformance();

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
signals:
    void win();
};

class skillGroup : public QObject
{
    Q_OBJECT
public:
    int level;
    skillUnit* group[100];
    void generate(QWidget* parentW, int l);
    skillGroup(QWidget* parentW, const int level);
    ~skillGroup();
    void skillEffect(abstractFighter* self, abstractFighter* opponent[3], abstractFighter* ally[3]);
signals:
    void groupFinished();
};

class fighter : public abstractFighter
{
    Q_OBJECT
public:
    m_Button* endTurn;
    fighter(QWidget* parent, QString bg, const QPoint& pos, int hp = 100, int pd = 0, int sd = 0, int er = 0, int pa = 0, int sa = 0, int cr = 0, int ap = 1);
    void oneTurn(QWidget* parent, abstractFighter* opponent[3], abstractFighter* ally[3]) override;
signals:
    void turnFinished();
};

class juniorDemon :public abstractFighter
{
    Q_OBJECT
public:
    juniorDemon(QWidget* parent, QString bg, const QPoint& pos, int hp = 100, int pd = 0, int sd = 0, int er = 0, int pa = 0, int sa = 0, int cr = 0, int ap = 1);
    void oneTurn(QWidget* parent, abstractFighter* opponent[3], abstractFighter* ally[3]) override;
};

class eliteDemon :public abstractFighter
{
    Q_OBJECT
public:
    eliteDemon(QWidget* parent, QString bg, const QPoint& pos, int hp = 100, int pd = 0, int sd = 0, int er = 0, int pa = 0, int sa = 0, int cr = 0, int ap = 1);
    void oneTurn(QWidget* parent, abstractFighter* opponent[3], abstractFighter* ally[3]) override;
};

class fightWidget : public QStackedWidget
{
    Q_OBJECT
public:
    int light_value;
    int life_value;
    int collection_list;
    bool diff;
    fightWidget(int c,int light,bool d,QWidget* parentW = nullptr);
    void oneFight(QWidget* parentW);
    void checkAlive();
    QWidget* fight, *endW;
    m_Button* endConfirm, * intoEnd;
    QLabel* endNotice;
    abstractFighter* left[3], * right[3];
signals:
    void ended_win();
    void ended_lose();
};

#endif // ABOUTFIGHT_H
