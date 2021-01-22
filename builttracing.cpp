#include <iostream>
#include "line.h"
#include "builttracing.h"
#include <QDebug>

// Метод для объединения всех данных вершин в одномерный вектор
std::vector<Point> BuiltTracing::uniteAllPointsTo1DArray(const std::vector<std::vector<Point>> &barriers2DVector)
{
    int pointsCount = 0;
    for(size_t i = 0; i < barriers2DVector.size(); i++)
        pointsCount += barriers2DVector.at(i).size();


    std::vector<Point> points(pointsCount + 2);
    for(size_t i = 0; i < barriers2DVector.size(); i++)
    {
        for(size_t j = 0; j < barriers2DVector.at(i).size(); j++)
        {
            points.at(i * barriers2DVector.at(i).size() + j) = barriers2DVector.at(i).at(j);
        }
    }

    points.at(pointsCount) = startPoint;
    points.at(pointsCount + 1) = endPoint;
    return points;
}

// Конструктор принимающий в себя начальную, конечную точку и двумерный вектор с координатами препятствий
BuiltTracing::BuiltTracing(const Point &startPoint, const Point &endPoint, const std::vector<std::vector<Point>> &barriers2DVector) :
    startPoint(startPoint), endPoint(endPoint)
{
    // Количество препятствий
    barriersCount = barriers2DVector.size();
    // Конвертируем точки препятствий в линии препятствий
    barriersLines = convertBarriersPointsToLines(barriers2DVector);
    // Объединяем все точки в одномерный массив
    auto points = uniteAllPointsTo1DArray(barriers2DVector);
    // Добавляем в взвешенный граф необходимое количство точек (нужно для алгоритма дейкстры)
    weightedGraphVisual.addVertexes(points.size());

    // Перебор вершин откуда стреляют
    for(size_t i = 0; i < points.size(); i++)
    {
        // Перебор вершин куда стреляют
        for(size_t j = i + 1; j < points.size(); j++)
        {
            bool canDraw = true;
            // Линия пути
            //QLineF firstLine(points.at(i).x, points.at(i).y, points.at(j).x, points.at(j).y);
            Line firstLine(points.at(i), points.at(j));
            // Перебор линий препятствий
            for(size_t k = 0; k < barriersLines.size(); k++)
            {
                auto startPoint = barriersLines.at(k).getStartPoint();
                auto endPoint = barriersLines.at(k).getEndPoint();


                Point intersectionPoint;
                //QLineF secondLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
                Line secondLine1(startPoint, endPoint);
                 // Проверка на пересечение двух линий
                //if(firstLine.intersects(secondLine, &intersectionPoint) == 1 && intersectionPoint != endPoint.toQPointF() && intersectionPoint != startPoint.toQPointF())
                if(firstLine.intersects(secondLine1, intersectionPoint) == 1 && !firstLine.isEnd(intersectionPoint) && !firstLine.isStart(intersectionPoint))
                {
                    // Если линии не пересекаютс, то помечаем, что её можно взять в сеть
                    canDraw = false;
                    break;
                }
            }
            // Если можно взять линию в сеть, то добавляем её в вектор линийд ля отрисовки, а её длину в взвешенный граф
            if(canDraw)
            {
                 weightedGraphVisual.addVisualEdge(i, j, firstLine.toQLineF());
            }
        }
    }


}
// Метод для вывода информации об исходных данных алгоритма на экран
void BuiltTracing::printInfo()
{
    std::cout << "Barriers count: " << barriersCount << std::endl;
    std::cout << "Start point: " << startPoint.x << " " << startPoint.y << std::endl;
    std::cout << "End point: " << endPoint.x << " " << endPoint.y << std::endl;
}

std::vector<Line> BuiltTracing::getBarriersLines() const
{
    return barriersLines;
}
// Возвращает вектор линий построенной сети
std::vector<QLineF> BuiltTracing::getNetLines() const
{
    return netLines;
}
// Возвращает расчитанные взешенный граф
WeightedGraphVisual BuiltTracing::getWeightedGraph() const
{
    return weightedGraphVisual;
}
// Конвертирурет координаты препятствий в вектор линий
std::vector<Line> BuiltTracing::convertBarriersPointsToLines(const std::vector<std::vector<Point>> &barriers2DVector)
{
    std::vector<std::vector<Line>> lines2D(barriers2DVector.size());
    for (size_t i = 0; i < barriers2DVector.size(); i++)
    {
        lines2D.at(i) = std::vector<Line>(barriers2DVector.at(i).size());
        for (size_t j = 0; j < barriers2DVector.at(i).size() - 1; j++)
            lines2D.at(i).at(j).setLine(barriers2DVector.at(i).at(j), barriers2DVector.at(i).at(j + 1));

        lines2D.at(i).at(barriers2DVector.at(i).size() - 1).setLine(barriers2DVector.at(i).at(barriers2DVector.at(i).size() - 1), barriers2DVector.at(i).at(0));
    }
    int pointsCount = 0;
    for(size_t i = 0; i < lines2D.size(); i++)
        pointsCount += lines2D.at(i).size();

    std::vector<Line> lines1D(pointsCount);
    for(size_t i = 0; i < lines2D.size(); i++)
    {
        for(size_t j = 0; j < lines2D.at(i).size(); j++)
        {
            lines1D.at(i * lines2D.at(i).size() + j) = lines2D.at(i).at(j);
        }
    }
    return lines1D;
}
