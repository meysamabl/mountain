#include "Edge.h"

Edge::Edge()
{
    //ctor
}

Edge::Edge(double x0, double y0, double z0, double x1, double y1, double z1)
{
    Point* pptr = nullptr;
    pptr = new Point(x0, y0, z0);
    points.push_back(*pptr);
    pptr = new Point(x1, y1, z1);
    points.push_back(*pptr);
    pptr = nullptr;
    calculateSideLength();
}

Edge::~Edge()
{
    //dtor
}

vector<double> Edge::getDeltas()
{
    vector<double> deltas;
    double x = points[1].getX() - points[0].getX();
    double y = points[1].getY() - points[0].getY();
    double z = points[1].getZ() - points[0].getZ();
    deltas.push_back(x);
    deltas.push_back(y);
    deltas.push_back(z);
    return deltas;
}

void Edge::calculateSideLength()
{
    vector<double> deltaValues = getDeltas();
    double a = deltaValues[0];
    double b = deltaValues[1];
    double c = deltaValues[2];
    sideLength = sqrt(pow(a , 2.0) + pow(b , 2.0) + pow(c, 2.0));
}
