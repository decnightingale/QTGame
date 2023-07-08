#pragma once
#ifndef SMALLMAP_H
#define SMALLMAP_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "m_Button.h"
class smallMap : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene* scene;
    QPixmap bk;
    smallMap(QWidget* parent, QRect rect);
    void addPoint(my_point* point);
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void drawBackground(QPainter* painter, const QRectF& rect) override;
};
















#endif //SMALLMAP_H
