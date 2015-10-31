#include "Triangle.h"

extern default_random_engine gen;
extern uniform_real_distribution<double> distr;
int Triangle::idStat = 1;

Triangle::Triangle()
{
    //ctor
}

Triangle::Triangle(vector<Edge> edgeValues) : edges(edgeValues)
{
    std::ostringstream ss;
    ss << idStat;
    id = "Triangle #" + ss.str();
    idStat++;
}

bool Triangle::isNeighbor(const Triangle& triangle)
{
    for(unsigned i = 0; i < edges.size(); ++i)
    {
        for(unsigned j=0; j < triangle.edges.size(); ++j)
        {
            if(edges[i] == triangle.edges[j])
            {
                return true;
            }
        }
    }
   return false;
}

void Triangle::addNeighbor(Triangle* neighbor)
{
    neighbors.push_back(neighbor);
}

bool Triangle::addIfNeighbor(Triangle* neighbor)
{
    if(isNeighbor(*neighbor))
    {
        addNeighbor(neighbor);
        return true;
    } else {
        return false;
    }

}

Triangle::~Triangle()
{
    //dtor
}
