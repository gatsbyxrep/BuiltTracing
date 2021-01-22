#include "graphalgs.h"
#include <iostream>
#include <QDebug>
// Алгоритм дейкстры
std::vector<double> GraphAlgs::dijkstra(const WeightedGraph &graph, int startVertex, int finishVertex, std::vector<int>& restoredPath)
{
    // Количество вершин в графе
    int vertexesCount = graph.getVertexesCount();
    // Вектор для пометки уже пройденных вершин
    std::vector<int> visited(vertexesCount, 0);
    // Вектор хранящий результат работы алгоритма (кратчайшее растояние от вершины startVertex до всех остальных)
    std::vector<double> result(vertexesCount, UINT_MAX);
    std::vector<int> path(vertexesCount, -1);
    // Помечаем стартувую вершину нулем, потому что расстояние до неё равно нрулю
    result.at(startVertex) = 0;
    int minIndex;
    do
    {
        minIndex = -1;
        double minWeight = UINT_MAX;
        for (int i = 0; i < vertexesCount; i++)
        {
            // Если вершину еще не обошли и её вес меньше предыдущего минимального
            if (result.at(i) < minWeight && visited.at(i) == 0)
            {
                minWeight = result.at(i);
                minIndex = i;
            }
        }
        if (minIndex != -1)
        {
            for (int i = 0; i < vertexesCount; i++)
            {
                if (graph.getEdgeWeight(minIndex, i) > 0)
                {
                    // Суммируем минимальный и текущий вес ребра
                    auto tmp = minWeight + graph.getEdgeWeight(minIndex, i);
                    if (tmp < result.at(i))
                    {
                        result.at(i) = tmp;
                        path.at(i) = minIndex;
                    }
                }
            }
            // Помечаем вершину как пройденную
            visited.at(minIndex) = 1;
        }
    } while (minIndex != -1);

    for(int u = finishVertex; u != -1; u = path.at(u))
        restoredPath.push_back(u);
    std::reverse(restoredPath.begin(), restoredPath.end());
    return result;
}
