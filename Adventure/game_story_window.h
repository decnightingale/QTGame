#ifndef GAME_STORY_WINDOW_H
#define GAME_STORY_WINDOW_H
#include <QWidget>
#include <QSoundEffect>
#include <QImage>
#include <QBitmap>
#include <QPainter>
#include "m_Button.h"
class game_story_window : public QWidget
{
    Q_OBJECT
public:
    int index;
    explicit game_story_window(QWidget* parent = 0);
    void paintEvent(QPaintEvent* event);
signals:
    void continue_called();
public slots:
};
#endif // GAME_STORY_WINDOW_H
