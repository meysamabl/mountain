#include "Triangle.h"

extern default_random_engine gen;
extern uniform_real_distribution<double> distr;
int Triangle::idCounter = 0;

Triangle::Triangle()
{
    //ctor
}

Triangle::Triangle(vector<Point> verticesVals) : vertices(verticesVals)
{
    id = idCounter;
    idCounter++;
    Edge* eptr = nullptr;
    eptr = new Edge(verticesVals.at(0).getX(),verticesVals.at(0).getY(),verticesVals.at(0).getZ(),
                                verticesVals.at(1).getX(), verticesVals.at(1).getY(), verticesVals.at(1).getZ());
    edges.push_back(*eptr);
    eptr = new Edge(verticesVals.at(0).getX(),verticesVals.at(0).getY(),verticesVals.at(0).getZ(),
                                verticesVals.at(2).getX(), verticesVals.at(2).getY(), verticesVals.at(2).getZ());
    edges.push_back(*eptr);
    eptr = new Edge(verticesVals.at(1).getX(),verticesVals.at(1).getY(),verticesVals.at(1).getZ(),
                                verticesVals.at(2).getX(), verticesVals.at(2).getY(), verticesVals.at(2).getZ());
    edges.push_back(*eptr);
    eptr = nullptr;
    refinable = calculateAspectRatio() > 0.1;
}

bool Triangle::isNeighbor(const Triangle& triangle)
{
    for(unsigned i = 0; i < edges.size(); ++i)
    {
        for(unsigned j=0; j < triangle.edges.size(); ++j)
        {
            if(edges.at(i) == triangle.edges.at(j))
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
    return (edges.at(0) <= edges.at(1) && edges.at(0) <= edges.at(2)) ? edges.at(0)
                            : edges.at(1) <= edges.at(2) ? edges.at(1) : edges.at(2);
}

Edge& Triangle::getLongestSide()
{
    return (edges.at(0) >= edges.at(1) && edges.at(0) >= edges.at(2)) ? edges.at(0)
                            : edges.at(1) >= edges.at(2) ? edges.at(1) : edges.at(2);
}


Point Triangle::getDeviatedCentroid()
{
    Point point = findCentroid();
    double alpha = getShortestSide().getSideLength();
    distr.param(uniform_real_distribution<double>(-alpha, alpha).param());
    alpha = distr(gen)/30;
    point.setX(point.getX() + alpha);
    point.setY(point.getY() + alpha);
    point.setZ(point.getZ() + alpha);
    return point;
}

Point Triangle::findCentroid()
{
    double x,y,z;
    x = (vertices.at(0).getX() + vertices.at(1).getX() + vertices.at(2).getX())/3;
    y = (vertices.at(0).getY() + vertices.at(1).getY() + vertices.at(2).getY())/3;
    z = (vertices.at(0).getZ() + vertices.at(1).getZ() + vertices.at(2).getZ())/3;
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
    points.push_back(vertices.at(0));
    points.push_back(vertices.at(2));
    tptr = new Triangle(points);
    triangles.push_back(*tptr);
    points.clear();
    /// second triangle
    points.push_back(center);
    points.push_back(vertices.at(0));
    points.push_back(vertices.at(1));
    tptr = new Triangle(points);
    triangles.push_back(*tptr);
    points.clear();
    /// third triangle
    points.push_back(center);
    points.push_back(vertices.at(1));
    points.push_back(vertices.at(2));
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
            if(it->addIfNeighbor(neighbors.at(i)))
            {
                //cout << it->getId() << " adding " << neighbors.at(i)->getId() << "*******" << endl;
                updateTargetPointer(neighbors.at(i), &(*it));
            }
        }
    }
    return triangles;
}

void Triangle::updateTargetPointer(Triangle* neighbor, Triangle* updatePointer)
{
    for(unsigned i = 0; i < neighbor->getNeighbors().size();++i)
    {
        if(neighbor->getNeighbors().at(i)==this)
        {
             neighbor->getNeighbors().at(i) = updatePointer;
             //cout << neighbor->getId()
             //<< " updating the neghibor pointer: " << neighbor->getNeighbors().at(i)->getId() << endl;
             break;
        }
    }
}

Node Triangle::getNodeRepresentation()
{

}

vector<double> Triangle::calculateCrossProduct()
{
    double a,b,c,d,e,f,i,j,k;
    vector<double> v0 = edges.at(0).getDeltas();
    a = v0.at(0); b = v0.at(1); c = v0.at(2);
    vector<double> v1 = edges.at(1).getDeltas();
    d = v1.at(0); e = v1.at(1); f = v1.at(2);
    vector<double> cross;
    i = (b*f - c*e);
    j = (a*f - c*d) * (-1);
    k = (a*e - b*d);
    cross.push_back(i);
    cross.push_back(j);
    cross.push_back(k);
    return cross;
}

double Triangle::calculateAspectRatio()
{
    Edge longestSide = getLongestSide();
    Edge shortestSide = getShortestSide();
    pair<Point, Point> lPairs, sPairs;

    if(longestSide.getPoints().at(0) == shortestSide.getPoints().at(0)) {
        lPairs = make_pair(longestSide.getPoints().at(0), longestSide.getPoints().at(1));
        sPairs = make_pair(shortestSide.getPoints().at(0), shortestSide.getPoints().at(1));
    } else if (longestSide.getPoints().at(1) == shortestSide.getPoints().at(1)) {
        lPairs = make_pair(longestSide.getPoints().at(1), longestSide.getPoints().at(0));
        sPairs = make_pair(shortestSide.getPoints().at(1), shortestSide.getPoints().at(0));
    } else {
        lPairs = make_pair(longestSide.getPoints().at(0), longestSide.getPoints().at(1));
        sPairs = make_pair(shortestSide.getPoints().at(1), shortestSide.getPoints().at(0));
    }
    vector<double> lsDelta = getDelta(lPairs.second, lPairs.first);
    vector<double> ssDelta = getDelta(sPairs.second, sPairs.first);
    double dotProduct = (lsDelta.at(0)*ssDelta.at(0)) + (lsDelta.at(1)*ssDelta.at(1)) + (lsDelta.at(2)*ssDelta.at(2));
    double lengthProduct = longestSide.getSideLength() * shortestSide.getSideLength();
    //cout << "Triangle #" << id << endl;
    //cout << "Dot Product => " << dotProduct <<"\tLength Product => " << lengthProduct << endl;
    double alphaAngle = acos(dotProduct/ lengthProduct);
    //cout << "Angle Alpha => " << alphaAngle * 180 / 3.14156592 << " degrees." << endl;
    double height = shortestSide.getSideLength() * sin(alphaAngle);
    //cout << "Height => " << height << "\tLongest Side => " << longestSide.getSideLength() << endl;
    return (height/longestSide.getSideLength());
}

vector<double> Triangle::getDelta(const Point& pointDiff, const Point& pointCommon)
{
    vector<double> deltas;
    double x = pointDiff.getX() - pointCommon.getX();
    double y = pointDiff.getY() - pointCommon.getY();
    double z = pointDiff.getZ() - pointCommon.getZ();
    deltas.push_back(x);
    deltas.push_back(y);
    deltas.push_back(z);
    return deltas;
}

bool Triangle::isTraversable()
{
    vector<double> vectors = calculateCrossProduct();
    double l = sqrt(pow(vectors.at(0), 2.0) + pow(vectors.at(1), 2.0) + pow(vectors.at(2), 2.0));
    return vectors.at(2)/l > COSINE_45;
}

Triangle::~Triangle()
{
    //dtor
}
