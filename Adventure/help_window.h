#ifndef HELP_WINDOW_H
#define HELP_WINDOW_H
#include <QWidget>
#include <QSoundEffect>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include "m_Button.h"
class help_window : public QWidget
{
    Q_OBJECT
public:
    explicit help_window(QWidget* parent = 0);
    void paintEvent(QPaintEvent* event);
signals:
    void return_called();
public slots:
};

#endif // HELP_WINDOW_H
