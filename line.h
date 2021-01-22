#pragma once
#include <QPointF>
#include <QLineF>
struct Point
{
    double x, y;
    QPointF toQPointF() const
    {
        return QPointF(x, y);
    }
    Point(double x, double y)
        : x(x), y(y)
    {}
    Point()
        : x(0.0), y(0.0)
    {}
};
// Класс линии (для строительной трассировки)
class Line
{
private:
    // Начальная и конечная точка линии
    Point startPoint;
    Point endPoint;
public:
    Line(const Point &startPoint, const Point &endPoint);
    Line();
    // Метод вощвращающий информацию о перечении двух линий
    int intersects(const Line &otherLine, Point& point);
    // Возвращает стартовую точку линии
    Point getStartPoint() const;
    // Возвращает конечную точку линии
    Point getEndPoint() const;
    // Устанавливает стартовую точку
    void setStartPoint(const Point &point);
    void setEndPoint(const Point &endPoint);
    void setLine(const Point& startPoint, const Point& endPoint);
    void printInfo() const;
    bool isEnd(const Point &point) const;
    bool isStart(const Point &point) const;
    QLineF toQLineF() const;
};

