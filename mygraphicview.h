#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include "builttracing.h"
#include <QWheelEvent>
#include <QScrollBar>


class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    // Конструктор принимающий в себя вектор линий сети для их отрисовки
    explicit MyGraphicView(QWidget* parent);
    ~MyGraphicView();
    int getXScale() const;
    void setXScale(int value);
    void update();

    int getYScale() const;
    void setYScale(int value);

    std::vector<int> getPath() const;
    void setPath(const std::vector<int> &value);

    std::vector<Line> getBarriersLines() const;
    void setBarriersLines(const std::vector<Line> &value);

    WeightedGraphVisual getWeightedGraphVisual() const;
    void setWeightedGraphVisual(const WeightedGraphVisual &value);
protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    std::vector<int> path;
    std::vector<Line> barriersLines;
    WeightedGraphVisual weightedGraphVisual;
    QGraphicsScene* scene;     // Сцена для отрисовки
    QGraphicsItemGroup* group1; // Группа объектов на сцене
    int xScale; // Масштаб по X
    int yScale; // Масштаб по Y
    // Метод для освобождения памяти из под объектовна сцене
    void deleteItemsFromGroup(QGraphicsItemGroup* group);
};

#endif // MYGRAPHICVIEW_H
