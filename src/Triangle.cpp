#include "Triangle.h"

extern default_random_engine gen;
extern uniform_real_distribution<double> distr;
int Triangle::idStat = 0;

Triangle::Triangle()
{
    //ctor
}

Triangle::Triangle(vector<Point> verticesVals) : vertices(verticesVals)
{
    std::ostringstream ss;
    ss << idStat;
    id = "Triangle #" + ss.str();
    idStat++;
    Edge* eptr = nullptr;
    eptr = new Edge(verticesVals[0].getX(),verticesVals[0].getY(),verticesVals[0].getZ(),
                                verticesVals[1].getX(), verticesVals[1].getY(), verticesVals[1].getZ());
    edges.push_back(*eptr);
    eptr = new Edge(verticesVals[0].getX(),verticesVals[0].getY(),verticesVals[0].getZ(),
                                verticesVals[2].getX(), verticesVals[2].getY(), verticesVals[2].getZ());
    edges.push_back(*eptr);
    eptr = new Edge(verticesVals[1].getX(),verticesVals[1].getY(),verticesVals[1].getZ(),
                                verticesVals[2].getX(), verticesVals[2].getY(), verticesVals[2].getZ());
    edges.push_back(*eptr);
    eptr = nullptr;
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
    }
    return false;

}

Edge& Triangle::getShortestSide()
{
    return (edges[0] <= edges[1] && edges[0] <= edges[2]) ? edges[0]
                            : edges[1] <= edges[2] ? edges[1] : edges[2];
}

Point Triangle::getDeviatedCentroid()
{
    Point point = findCentroid();
    double alpha = getShortestSide().getSideLength();
    distr.param(uniform_real_distribution<double>(0, alpha).param());
    alpha = distr(gen)/20;
    cout << "Alpha: " << alpha << endl;
    point.setX(point.getX() + alpha);
    point.setY(point.getY() + alpha);
    point.setZ(point.getZ() + alpha);
    return point;
}

Point Triangle::findCentroid()
{
    double x,y,z;
    x = (vertices[0].getX() + vertices[1].getX() + vertices[2].getX())/3;
    y = (vertices[0].getY() + vertices[1].getY() + vertices[2].getY())/3;
    z = (vertices[0].getZ() + vertices[1].getZ() + vertices[2].getZ())/3;
    Point centeroid(x,y,z);
    return centeroid;
}

list<Triangle> Triangle::refineMe()
{

}

Triangle::~Triangle()
{
    //dtor
}
