#pragma once
#include <vector>
#include <iostream>
class WeightedGraph
{
protected:
    // Матрица для хранения весов между ребрами
    std::vector<std::vector<double>> weightsMatrix;
    // Количество вершин в графе
    size_t vertexesCount;
public:
    WeightedGraph(const std::vector<std::vector<double>> &weightsMatrix);
    WeightedGraph(size_t size);
    WeightedGraph();
    // Метод для добавляения вершины
    virtual void addVertex();
    // Метод для добавления n-ого количества вершин
    virtual void addVertexes(size_t vertexesCount);
    // Добавить ребро
    void addEdge(size_t from, size_t to, double weight);
    // Возвращает вес ребра между вершинами from и to
    double getEdgeWeight(size_t from, size_t to) const;
    // Возвращает ссылку на веса от указанной вершины
    const std::vector<double>& getWeightsFromEdge(size_t from) const;
    // Метод для установки веса ребра
    void setEdgeWeight(size_t from, size_t to, double value);
    // Метод для получения количества вершин в графе
    size_t getVertexesCount() const;
    // Метод для вывода информации о графе
    void print();
    virtual ~WeightedGraph() = default;
};

