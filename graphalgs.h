#ifndef GRAPHALGS_H
#define GRAPHALGS_H
#include "weightedgraph.h"
// Класс для алгоритмов на взвешенных графах
class GraphAlgs
{
public:
    // Алгоритм дейкстры, возвращает кратчайшее растояние от startVertex до остальных вершин
    static std::vector<double> dijkstra(const WeightedGraph &graph, int startVertex, int finishVertex, std::vector<int>& restoredPath);
};


#endif // GRAPHALGS_H
