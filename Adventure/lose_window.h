#ifndef LOSE_WINDOW_H
#define LOSE_WINDOW_H

#include <QWidget>
#include <QSoundEffect>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include "m_Button.h"
    class lose_window : public QWidget
{
    Q_OBJECT
public:
    QLabel collection_num;
    QLabel life_num;
    QLabel light_num;
    QLabel mark;
    int index;
    explicit lose_window(QWidget* parent = 0);
    void paintEvent(QPaintEvent* event);
signals:
    void close_called();
public slots:
};

#endif // LOSE_WINDOW_H
