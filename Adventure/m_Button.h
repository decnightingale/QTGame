#ifndef M_BUTTON_H
#define M_BUTTON_H
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QStackedWidget>
#include <windows.h>
#include <Qvector>
#include <vector>


class m_board:public QPushButton
{
    Q_OBJECT
public:
    QString image_path;
    m_board(QWidget* parent,bool mask,QString bg_image,int width=0,int height=0);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
signals:
public slots:
};

class m_Button:public QPushButton
{
    Q_OBJECT
public:
    m_Button(QWidget* parent,bool mask,QString original_image,QString clicked_image = "");
    QString original_image_path;
    QString clicked_image_path;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
signals:

public slots:
};

class collection_symbol:public m_Button
{
    Q_OBJECT
public:
    int num;
    int list;
    collection_symbol(QWidget* parent);
public slots:
    void clicked_action();
};

class goods:public m_Button
{
    Q_OBJECT
public:
    int money;
    int price;
    QString info_path;
    goods(QWidget* parent,int p,QString goods_image,QString goods_info);
signals:
    void buy_callled();
public slots:
    void clicked_action();
};

class my_point:public m_Button
{
    Q_OBJECT
public:
    bool explored;
    bool can_be_chosen;
    my_point* connected_point[6];
    my_point* forward_point[6];
    int forward_num;
    int connected_num;
    QString located_image_path;
    QString explored_image_path;
    QString forbid_image_path;
    my_point(QWidget* parent,bool mask,QString original_image,QString located_image,QString explored_image,QString forbid_image,QString clicked_image = "");
    void connect_to(my_point* another);
    void add_forward_point(my_point* another);
    virtual void change_can_chosen();
    virtual void close_can_chosen();
    void change_located();
    void restore_located();
signals:
};

class start_point:public my_point
{
    Q_OBJECT
public:
    start_point(QWidget* parent);
signals:
    void got_chosen();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
    virtual void close_can_chosen();
};

class treasure_point:public my_point
{
    Q_OBJECT
public:
    int rank;
    treasure_point(QWidget* parent,int r);
signals:
    void got_chosen();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
    virtual void close_can_chosen();
};

class war_point:public my_point
{
    Q_OBJECT
public:
    int light_value;
    int life_value;
    int collection_list;
    int money;
    war_point(QWidget* parent);
signals:
    void got_chosen();
    void battle_end();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
    virtual void close_can_chosen();
};

class story_point:public my_point
{
    Q_OBJECT
public:
    int money;
    int light_value;
    int life_value;
    int collection_list;
    story_point(QWidget* parent);
signals:
    void got_chosen();
    void battle_end();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
    virtual void close_can_chosen();
};

QString kst(int kk);

class an_incident{
public:
    QString descri;
    int choices[4], num;
    an_incident(QString dd, int aa, int bb = -1, int cc = -1):descri(dd){
        choices[0] = aa;
        choices[1] = bb;
        choices[2] = cc;
        num = 1;
        if (bb != -1){
            num = 2;
        }
        if (cc != -1){
            num = 3;
        }
    }
};

class an_action{
public:
    QString path, descri, _move, result1, result2;
    int chc, tar, val;//c=1~10
    an_action(int kk, QString dd, QString mm, QString r1, QString r2, int cc, int tt, int vv):
        path(kst(kk)), descri(dd), _move(mm), result1(r1), result2(r2), chc(cc), tar(tt), val(vv){
    }
};

class action_button : public m_Button{
    Q_OBJECT;
public:
    explicit action_button(QWidget* parent, an_action acc);
    an_action ACC;
};

class accident_point:public my_point
{
    Q_OBJECT
public:
    accident_point(QWidget* parent);
    static QVector<an_action> actions;
    static QVector<an_incident> incidents;
    int light_value;
    int life_value;
    int money_value;
    int collection_list;
    int collection_num;
    int collection_list_used;
    int collection_num_used;
    action_button* step_forward_buttons[4];
    int typ;
signals:
    void got_chosen();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
    virtual void close_can_chosen();
};

class branch_point:public my_point
{
    Q_OBJECT
public:
    int used_num;
    int used_list;
    int money;
    int life_value;
    int light_value;
    int buy_sum;
    int buy_rank[8];
    branch_point(QWidget* parent);
signals:
    void got_chosen();
    void buy_end();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
    virtual void close_can_chosen();

};

#endif // M_BUTTON_H
