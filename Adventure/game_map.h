#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <QWidget>
#include <QSoundEffect>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include "m_Button.h"
class game_map : public QWidget
{
    Q_OBJECT
public:
    explicit game_map(QWidget* parent = 0);
    void paintEvent(QPaintEvent* event);
signals:
    void return_called();
    void help_called();
public slots:
};
#endif // GAME_MAP_H
