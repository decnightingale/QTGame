#ifndef GET_START_H
#define GET_START_H
#include <QWidget>
#include <QSoundEffect>
#include <QImage>
#include <QBitmap>
#include <QPainter>
#include "m_Button.h"
class get_start : public QWidget
{
    Q_OBJECT
public:
    explicit get_start(QWidget* parent = 0);
    void paintEvent(QPaintEvent* event);
signals:
    void play_called();
    void quit_called();
    void help_called();
public slots:
};

#endif // GET_START_H
