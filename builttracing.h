#pragma once
#include <vector>
#include "weightedgraphvisual.h"
#include "line.h"
#include "graphalgs.h"
#include <QLineF>
#include "dataloader.h"
// Класс для строительной трассировки
class BuiltTracing
{
private:
    // Начальная точка
    Point startPoint;
    // Конечная точка
    Point endPoint;
    // Количество препячтствий
    unsigned int barriersCount;
    // Линии препятствий
    std::vector<Line> barriersLines;
    // Линии сети
    std::vector<QLineF> netLines;
    // Взвешанный граф
    WeightedGraphVisual weightedGraphVisual;
    // Метод для конвертации точки препятствий в их линии
    std::vector<Line> convertBarriersPointsToLines(const std::vector<std::vector<Point>> &barriers2DVector);
    // Метод для копирования всех точек в двумерный массив
    std::vector<Point> uniteAllPointsTo1DArray(const std::vector<std::vector<Point>> &barriers2DVector);
public:
    // Конструктор
    BuiltTracing(const Point &startPoint, const Point &endPoint, const std::vector<std::vector<Point>> &barriers2DVector);
    // Метод для вывода информации о состоянии объекта
    void printInfo();
    // Возвращает линии препятствий
    std::vector<Line> getBarriersLines() const;
    // Возвращает линии сети
    std::vector<QLineF> getNetLines() const;
    // Возвращает взвешенный граф
    WeightedGraphVisual getWeightedGraph() const;
};
