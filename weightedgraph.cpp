#include "weightedgraph.h"

// Конструктор по умолчанию
WeightedGraph::WeightedGraph()
{
    this->vertexesCount = 0;
}

// Конструктор принимающий в себя матрицу весов
WeightedGraph::WeightedGraph(const std::vector<std::vector<double>> &weightsMatrix) :
    weightsMatrix(weightsMatrix)
{
    this->vertexesCount = weightsMatrix.size();
}

// Конструктор принимающий в себя количество вершин
WeightedGraph::WeightedGraph(size_t size)
{
    this->vertexesCount = size;
    weightsMatrix.resize(size, std::vector<double>(size));
}

// Метод для добавления ребра от from до to с весом weight
void WeightedGraph::addEdge(size_t from, size_t to, double weight)
{
    weightsMatrix.at(from).at(to) = weight;
    weightsMatrix.at(to).at(from) = weight;
}

// Метод для получения веса ребра от from до to
double WeightedGraph::getEdgeWeight(size_t from, size_t to) const
{
    return weightsMatrix.at(from).at(to);
}

// Метод возвращающий ссылку на массив весов всех связных с вершиной ребёр
const std::vector<double> &WeightedGraph::getWeightsFromEdge(size_t from) const
{
    return weightsMatrix.at(from);
}

// Метод для установки веса ребра
void WeightedGraph::setEdgeWeight(size_t from, size_t to, double value)
{
   weightsMatrix.at(from).at(to) = value;
}
// Метод для возвращения количества вершин
size_t WeightedGraph::getVertexesCount() const
{
    return vertexesCount;
}

// Метод для вывода матрицы весов на экран
void WeightedGraph::print()
{
    for(size_t i = 0; i < weightsMatrix.size(); i++)
    {
        for(size_t j = 0; j < weightsMatrix.size(); j++)
        {
            std::cout << weightsMatrix.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

// Метод для добавления вершины в граф
void WeightedGraph::addVertex()
{
    if(vertexesCount != 0)
        for (size_t i = 0; i < vertexesCount; i++)
            weightsMatrix.at(i).resize(vertexesCount + 1);
    vertexesCount++;
    weightsMatrix.push_back(std::vector<double>(vertexesCount, 0));
}

// Метод для добавления n-ого количества вершин в граф
void WeightedGraph::addVertexes(size_t vertexesCount)
{
    for (size_t i = 0; i < vertexesCount; i++)
        addVertex();
}
