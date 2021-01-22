#ifndef WEIGHTEDGRAPHVISUAL_H
#define WEIGHTEDGRAPHVISUAL_H

#include "weightedgraph.h"
#include "QLineF"
class WeightedGraphVisual : public WeightedGraph
{
private:
    // Вектор из соответствующих ребрам графических линий
    std::vector<std::vector<QLineF>> edgeLines;
public:
    WeightedGraphVisual();
    // Метод для добавляения вершины
    void addVertex() override;
    // Метод для добавления n-ого количества вершин
    void addVertexes(size_t vertexesCount) override;
    // Добавить ребро
    void addVisualEdge(size_t from, size_t to, const QLineF& line);
    QLineF getVisualEdge(size_t from, size_t to) const;
};

#endif // WEIGHTEDGRAPHVISUAL_H
