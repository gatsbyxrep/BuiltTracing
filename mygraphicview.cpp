#include "mygraphicview.h"
#include <QDebug>
MyGraphicView::MyGraphicView(QWidget* parent)
    : QGraphicsView(parent)
{

    xScale = 200;
    yScale = 70;
    // Настройка виджетов
    this->setAlignment(Qt::AlignCenter);
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(100);
    this->setMinimumWidth(100);
    // Устанавливаем размеры
    this->resize(parent->width() - 270, parent->height());

    scene = new QGraphicsScene(this);

    this->setScene(scene);
    scene->setSceneRect(0, 0, parent->width(), parent->height());
    group1 = new QGraphicsItemGroup();
    scene->addItem(group1);
}

// Перерисовывает данные на сцене
void MyGraphicView::update()
{
    deleteItemsFromGroup(group1);
    // Сеть
    for(size_t i = 0; i < weightedGraphVisual.getVertexesCount(); i++)
    {
        for(size_t j = i; j < weightedGraphVisual.getVertexesCount(); j++)
        {
            if(weightedGraphVisual.getVisualEdge(i, j).length() == 0.0)
                continue;
            auto startPoint = weightedGraphVisual.getVisualEdge(i, j).p1();
            auto endPoint = weightedGraphVisual.getVisualEdge(i, j).p2();
            auto startPointText = scene->addText(QString::number(startPoint.x()) + "," + QString::number(startPoint.y()));
            startPointText->setPos(startPoint.x() * xScale, -startPoint.y() * yScale + yScale * 10);
            group1->addToGroup(startPointText);
            auto endPointText = scene->addText(QString::number(endPoint.x()) + "," + QString::number(endPoint.y()));
            endPointText->setPos(endPoint.x() * xScale, -endPoint.y() * yScale + yScale * 10);
            group1->addToGroup(endPointText);
            group1->addToGroup(scene->addLine(startPoint.x() * xScale, -startPoint.y() * yScale + yScale * 10, endPoint.x() * xScale, -endPoint.y() * yScale + yScale * 10));
        }
    }

    // Линии пути
    for(auto iterator = path.begin(); iterator != path.end() - 1; iterator++)
    {
        auto startPoint = weightedGraphVisual.getVisualEdge(*iterator, *(iterator + 1)).p1();
        auto endPoint = weightedGraphVisual.getVisualEdge(*iterator, *(iterator + 1)).p2();
        group1->addToGroup(scene->addLine(startPoint.x() * xScale, -startPoint.y() * yScale + yScale * 10, endPoint.x() * xScale, -endPoint.y() * yScale + yScale * 10, QPen(Qt::yellow, 4)));
    }
    // Препятствия
    for(size_t i = 0; i < barriersLines.size(); i++)
    {
        auto startPoint = barriersLines.at(i).getStartPoint();
        auto endPoint = barriersLines.at(i).getEndPoint();
        group1->addToGroup(scene->addLine(startPoint.x * xScale, -startPoint.y * yScale + yScale * 10, endPoint.x * xScale, -endPoint.y * yScale + yScale * 10,  QPen(Qt::red, 3)));
    }
    scene->setSceneRect(scene->itemsBoundingRect());
}


// Деструктор
MyGraphicView::~MyGraphicView()
{
    deleteItemsFromGroup(group1);
    delete group1;
}

// Возвращает масштаб по X
int MyGraphicView::getXScale() const
{
    return xScale;
}
// Устанавливает масштаб по X
void MyGraphicView::setXScale(int value)
{
    xScale = value;
}

// Возвращает масштаб по Y
int MyGraphicView::getYScale() const
{
    return yScale;
}

// Устанавливаем масштаб по Y
void MyGraphicView::setYScale(int value)
{
    yScale = value;
}

// Возвращает путь
std::vector<int> MyGraphicView::getPath() const
{
    return path;
}
// Устанавливает путь
void MyGraphicView::setPath(const std::vector<int> &value)
{
    path = value;
}

// Возвращает линии препятствий
std::vector<Line> MyGraphicView::getBarriersLines() const
{
    return barriersLines;
}

// Устанавливаем линии препятствий для отрисовки
void MyGraphicView::setBarriersLines(const std::vector<Line> &value)
{
    barriersLines = value;
}

// Возвращает взвешенный граф
WeightedGraphVisual MyGraphicView::getWeightedGraphVisual() const
{
    return weightedGraphVisual;
}

// Устанавливаем взвешеный граф для его отрисовки
void MyGraphicView::setWeightedGraphVisual(const WeightedGraphVisual &value)
{
    weightedGraphVisual = value;
}

void MyGraphicView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    auto angle = event->angleDelta().y();
    auto factor = pow(1.0015, angle);
    scale(factor, factor);

    auto targetViewportPos = event->position();
    auto targetScenePos = mapToScene(event->position().toPoint());
    centerOn(targetScenePos);
    QPointF deltaViewportPos = targetViewportPos - QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
    QPointF viewportCenter = mapFromScene(targetScenePos) - deltaViewportPos;
    centerOn(mapToScene(viewportCenter.toPoint()));

}

void MyGraphicView::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    // Перебираем все объекты на сцене и освобождаем память из-под них
    for(auto &item : scene->items())
        if(item->group() == group)
            delete item;
}
