#ifndef M_BUTTON_H
#define M_BUTTON_H
#include <QPushButton>

class m_Button:public QPushButton
{
    Q_OBJECT
public:
    m_Button(QWidget* parent,bool mask,QString original_image,QString clicked_image = "");
    QString original_image_path;
    QString clicked_image_path;
    void mousePressEvent(QMouseEvent *eevent);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
signals:

public slots:
};

#endif // M_BUTTON_H
