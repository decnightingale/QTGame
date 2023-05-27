#ifndef M_BUTTON_H
#define M_BUTTON_H
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QLabel>

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

class my_point:public m_Button
{
    Q_OBJECT
public:
    bool explored;
    bool can_be_chosen;
    my_point* connected_point[6];
    int connected_num;
    my_point(QWidget* parent,bool mask,QString original_image,QString clicked_image = "");
    void connect_to(my_point* another);
    virtual void change_can_chosen();
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
};

class treasure_point:public my_point
{
    Q_OBJECT
public:
    treasure_point(QWidget* parent);
signals:
    void got_chosen();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
};

class war_point:public my_point
{
    Q_OBJECT
public:
    war_point(QWidget* parent);
signals:
    void got_chosen();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
};

class story_point:public my_point
{
    Q_OBJECT
public:
    story_point(QWidget* parent);
signals:
    void got_chosen();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
};

class accident_point:public my_point
{
    Q_OBJECT
public:
    accident_point(QWidget* parent);
signals:
    void got_chosen();
public slots:
    void clicked_action();
    virtual void change_can_chosen();
};

#endif // M_BUTTON_H
