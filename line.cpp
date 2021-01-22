#include <iostream>
#include "line.h"
#include <QDebug>
#include <qnumeric.h>
Line::Line(const Point& startPoint, const Point& endPoint)
    : startPoint(startPoint), endPoint(endPoint)
{
}

Line::Line()
{
}

int Line::intersects(const Line &otherLine, Point& point)
{
    // Компоненты уравнения для поиска точки пересечения
    const QPointF a(endPoint.x - startPoint.x, endPoint.y - startPoint.y);
    const QPointF b(otherLine.startPoint.x - otherLine.endPoint.x, otherLine.startPoint.y - otherLine.endPoint.y);
    const QPointF c(startPoint.x - otherLine.startPoint.x, startPoint.y - otherLine.startPoint.y);

    // Знаменатель
    const qreal denominator = a.y() * b.x() - a.x() * b.y();
    // Если знаменатель равен нулю, то пересечения нет
    if(denominator == 0 || !isfinite(denominator))
    {
            return 0;
    }
    const qreal reciprocal = 1 / denominator;
    const qreal na = (b.y() * c.x() - b.x() * c.y())* reciprocal;
    point.x = startPoint.x + a.x() * na;
    point.y = startPoint.y + a.y() * na;
    if(na < 0 || na > 1)
        return 2;
    const qreal nb = (a.x() * c.y() - a.y() * c.x()) * reciprocal;
    // Если найденная точка не выходит за границы отрезка
    if(nb < 0 || nb > 1)
        return 2;
    return 1;
}

Point Line::getStartPoint() const
{
    return startPoint;
}
Point Line::getEndPoint() const
{
    return endPoint;
}

void Line::setStartPoint(const Point& point)
{
    this->startPoint = point;
}

void Line::setEndPoint(const Point& point)
{
    this->endPoint = point;
}

void Line::setLine(const Point& startPoint, const Point& endPoint)
{
    setStartPoint(startPoint);
    setEndPoint(endPoint);
}

void Line::printInfo() const
{
    std::cout << "Line from " << startPoint.x << " " << startPoint.y << " to " << endPoint.x << " " << endPoint.y << std::endl;
}

bool Line::isEnd(const Point& point) const
{
    if (point.x == endPoint.x && point.y == endPoint.y)
        return true;
    return false;
}
bool Line::isStart(const Point& point) const
{
    if (point.x == startPoint.x && point.y == startPoint.y)
        return true;
    return false;
}

QLineF Line::toQLineF() const
{
    return QLineF(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}
