#ifndef VICTORY_WINDOW_H
#define VICTORY_WINDOW_H

#include <QWidget>
#include <QSoundEffect>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include "m_Button.h"
class victory_window : public QWidget
{
    Q_OBJECT
public:
    QLabel collection_num;
    QLabel life_num;
    QLabel light_num;
    QLabel mark;
    int index;
    explicit victory_window(QWidget* parent = 0);
    void paintEvent(QPaintEvent* event);
signals:
    void close_called();
public slots:
};

#endif // VICTORY_WINDOW_H
