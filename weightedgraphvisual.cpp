#include "weightedgraphvisual.h"

WeightedGraphVisual::WeightedGraphVisual()
{

}

void WeightedGraphVisual::addVertex()
{
    if(vertexesCount != 0)
    {
        for (size_t i = 0; i < vertexesCount; i++)
        {
            weightsMatrix.at(i).resize(vertexesCount + 1);
            edgeLines.at(i).resize(vertexesCount + 1);
        }
    }
    vertexesCount++;
    weightsMatrix.push_back(std::vector<double>(vertexesCount, 0));
    edgeLines.push_back(std::vector<QLineF>(vertexesCount));
}

void WeightedGraphVisual::addVertexes(size_t vertexesCount)
{
    for (size_t i = 0; i < vertexesCount; i++)
        addVertex();

}

void WeightedGraphVisual::addVisualEdge(size_t from, size_t to, const QLineF& line)
{
    WeightedGraph::addEdge(from, to, line.length());
    edgeLines.at(from).at(to) = line;
    edgeLines.at(to).at(from) = line;
}

QLineF WeightedGraphVisual::getVisualEdge(size_t from, size_t to) const
{
    return edgeLines.at(from).at(to);
}
