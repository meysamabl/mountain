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
    if(neighbors.size() > 3)
    {
        throw new exception();
    }
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
    list<Triangle> triangles;
    vector<Point> points;
    Triangle* tptr = nullptr;
    Point center = getDeviatedCentroid();
    /// first triangle
    points.push_back(center);
    points.push_back(vertices[0]);
    points.push_back(vertices[2]);
    tptr = new Triangle(points);
    triangles.push_back(*tptr);
    points.clear();
    /// second triangle
    points.push_back(center);
    points.push_back(vertices[0]);
    points.push_back(vertices[1]);
    tptr = new Triangle(points);
    triangles.push_back(*tptr);
    points.clear();
    /// third triangle
    points.push_back(center);
    points.push_back(vertices[1]);
    points.push_back(vertices[2]);
    tptr = new Triangle(points);
    triangles.push_back(*tptr);
    points.clear();
    tptr = nullptr;
    for(list<Triangle>::iterator it = triangles.begin(); it != triangles.end();++it)
    {
        for(list<Triangle>::iterator itr = triangles.begin(); itr != triangles.end();++itr)
        {
            if((*it) != (*itr))
            {
                it->addIfNeighbor(&(*itr));
                /*
                if(it->addIfNeighbor(&(*itr)))
                {
                    cout << it->getId() << " adding " << (*itr).getId() << "--------" << endl;
                }*/
            }
        }
        for(unsigned i = 0; i < neighbors.size(); ++i)
        {
            if(it->addIfNeighbor(neighbors[i]))
            {
                //cout << it->getId() << " adding " << neighbors[i]->getId() << "*******" << endl;
                updateTargetPointer(neighbors[i], &(*it));
            }
        }
    }
    return triangles;
}

void Triangle::updateTargetPointer(Triangle* neighbor, Triangle* updatePointer)
{
    for(unsigned i = 0; i < neighbor->getNeighbors().size();++i)
    {
        if(neighbor->getNeighbors()[i]==this)
        {
             neighbor->getNeighbors()[i] = updatePointer;
             //cout << neighbor->getId()
             //<< " updating the neghibor pointer: " << neighbor->getNeighbors()[i]->getId() << endl;
             break;
        }
    }
}

Triangle::~Triangle()
{
    //dtor
}
