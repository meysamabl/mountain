#include "Triangle.h"

extern default_random_engine gen;
extern uniform_real_distribution<double> distr;

Triangle::Triangle()
{
    //ctor
}

Triangle::Triangle(vector<Location> vertices, string id) : id(id) {
    this->vertices = vertices;
}

bool Triangle::isNeighbor(vector<Location> verts)
{
    int sideEqual = 0;
    for(unsigned i = 0; i < verts.size(); ++i)
    {
        for(unsigned j = 0; j < vertices.size(); ++j)
        {
            if(verts[i] == vertices[j])
            {
                sideEqual++;
                break;
            }
        }
    }
    return sideEqual > 1;
}

void Triangle::addNeighor(Triangle& neighbor)
{
    neighbors.push_back(&neighbor);
}

Location Triangle::findCentroid()
{
    double x,y,z;
    x = (vertices[0].Getx() + vertices[1].Getx() + vertices[2].Getx())/3;
    y = (vertices[0].Gety() + vertices[1].Gety() + vertices[2].Gety())/3;
    z = (vertices[0].Getz() + vertices[1].Getz() + vertices[2].Getz())/3;
    Location loc(x,y,z);
    cout << "Centroid: (" << x << ", " << y << ", " << z << ")" << endl;
    return loc;
}

double Triangle::calculateDistance(const vector<double> deltaValues)
{
    double a = deltaValues[0];
    double b = deltaValues[1];
    double c = deltaValues[2];
    double d = sqrt(pow(a , 2.0) + pow(b , 2.0) + pow(c, 2.0));
    return d;
}

const vector<double> Triangle::getDeltaValues(const Location& loc1, const Location& loc2)
{
    vector<double> deltaValues;
    deltaValues.push_back(loc2.Getx() - loc1.Getx());
    deltaValues.push_back(loc2.Gety() - loc1.Gety());
    deltaValues.push_back(loc2.Getz() - loc1.Getz());
    return deltaValues;
}

double Triangle::getShortestSide()
{
    double x = calculateDistance(getDeltaValues(vertices[0],vertices[1]));
    double y = calculateDistance(getDeltaValues(vertices[1],vertices[2]));
    double z = calculateDistance(getDeltaValues(vertices[2],vertices[0]));
    return (x <= y && x <= z) ? x : y <= z ? y : z;
}

Location Triangle::getRandomCentroid()
{
    Location loc = findCentroid();
    double shortestPath = getShortestSide();
    cout << "shortest distance: " << shortestPath << endl;
    distr.param(uniform_real_distribution<double>(shortestPath - 1, shortestPath + 1).param());
    loc.Setx(loc.Getx() + distr(gen));
    loc.Sety(loc.Gety() + distr(gen));
    loc.Setz(loc.Getz() + distr(gen));
    cout << "Random Centroid: (" << loc.Getx() << ", " << loc.Gety() << ", " << loc.Getz() << ")" << endl;
    return loc;
}

Triangle::~Triangle()
{
    //dtor
}
