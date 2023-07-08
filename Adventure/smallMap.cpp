#include "smallMap.h"

smallMap::smallMap(QWidget* parent, QRect rect)
    : QGraphicsView(parent), scene(new QGraphicsScene())
{
    //setMouseTracking(true);
    /*
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(0, 0, 100, 100);
    rectItem->setBrush(Qt::red);
    rectItem->setZValue(1);
    scene->addItem(rectItem);
    */
    bk = QPixmap(":/image/small_map.png");
    /*
    QGraphicsPixmapItem* bkItem= new QGraphicsPixmapItem(bk);
    bkItem->setPos(0, 0);
    scene->addItem(bkItem);
    */

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);
    setGeometry(rect);
    show();
}

void smallMap::mousePressEvent(QMouseEvent* event)
{
    // 按下鼠标左键时进行放大操作
    if (event->button() == Qt::LeftButton)
    {
        resize(500, 400);
    }

    // 调用基类的事件处理程序
    QGraphicsView::mousePressEvent(event);
}

void smallMap::mouseReleaseEvent(QMouseEvent* event)
{
    resize(100, 80);
}

void smallMap::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->drawPixmap(rect.toRect(), bk);
}

void smallMap::wheelEvent(QWheelEvent* event)
{
    QPoint delta = event->angleDelta();
    int x = delta.y() / 120;
    if (x > 0)
    {
        while (x--)
        {
            scale(0.8, 0.8);
        }
    }
    else if (x < 0)
    {
        while (x++)
        {
            scale(1.2, 1.2);
        }
    }
}

void smallMap::addPoint(my_point* point)
{
    QIcon icon_ = point->icon();
    QPixmap pixmap_ = icon_.pixmap(icon_.availableSizes().first());
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap_);

    QPoint position = point->pos();
    pixmapItem->setPos(position);

    scene->addItem(pixmapItem);
}
