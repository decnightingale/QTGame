#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <QWidget>
#include <QSoundEffect>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QFont>
#include <QPixmap>
#include <QPalette>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QList>
#include <Qvector>
#include <cstdlib>
#include "m_Button.h"
#include "aboutFight.h"


class game_map : public QWidget
{
    Q_OBJECT
public:
    int light_value;
    int life_value;
    int money_value;
    int collection_num;
    int collection_list;
    int collection_list_used;
    int collection_num_used;
    my_point* located_point;
    explicit game_map(QWidget* parent = 0);
    void paintEvent(QPaintEvent* event);
    void set_located_point(my_point* new_point);
    QList<QLine> paths;
private:
    void arrow_connect_tool(m_Button* up,m_Button* down,m_Button* left,m_Button* right,my_point* aim);
    void copy_acc(accident_point* aim);
    void restore_acc(accident_point* aim);
signals:
    void return_called();
    void help_called();
    void up_called();
    void down_called();
    void right_called();
    void left_called();
    void win_sign();
    void lose_sign();
public slots:
};
#endif // GAME_MAP_H
