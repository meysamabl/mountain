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
    refinable = calculateAspectRatio() > 0.01;
    centroid = findCentroid();
    crossProductResult = calculateCrossProduct();
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
    Point point = getCentroid();
    double alpha = getShortestSide().getSideLength();
    distr.param(uniform_real_distribution<double>(-alpha, alpha).param());
    alpha = distr(gen)/20;
    point.setX(point.getX() + alpha);
    alpha = distr(gen)/20;
    point.setY(point.getY() + alpha);
    alpha = distr(gen)/20;
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
             neighbor->updateNeighbors(i, updatePointer);
             //cout << neighbor->getId()
             //<< " updating the neghibor pointer: " << neighbor->getNeighbors().at(i)->getId() << endl;
             break;
        }
    }
}

void Triangle::updateNeighbors(unsigned index, Triangle* updatePointer)
{
    neighbors.at(index) = updatePointer;
}

Node Triangle::getNodeRepresentation()
{
    Node nodeRep(id);
    Point myCentroid = getCentroid();
    Point neighborCentroid;
    double distance = 0;
    for(unsigned i = 0; i < neighbors.size(); i++)
    {
        if(neighbors.at(i)->isTraversable())
        {
            neighborCentroid = neighbors.at(i)->getCentroid();
            distance = calculateDistance(neighborCentroid, myCentroid);
            nodeRep.addPath(neighbors.at(i)->getId(), distance);
        }
    }
    return nodeRep;
}

double Triangle::calculateDistance(const Point& point1, const Point& point0)
{
    vector<double> delta = getDelta(point1, point0);
    double a = delta.at(0);
    double b = delta.at(1);
    double c = delta.at(2);
    return sqrt(pow(a , 2.0) + pow(b , 2.0) + pow(c, 2.0));
}

vector<double> Triangle::calculateCrossProduct()
{
    double a,b,c,d,e,f,i,j,k;
    ///Any arbitrary vector should work,
    /// then we choose two arbitrary edges
    vector<double> v0 = edges.at(0).getDeltas();
    a = v0.at(0); b = v0.at(1); c = v0.at(2);
    //cout <<"vector 0 " << a << ", " << b << ", " << c << endl;
    vector<double> v1 = edges.at(1).getDeltas();
    d = v1.at(0); e = v1.at(1); f = v1.at(2);
    //cout <<"vector 1 " << d << ", " << e << ", " << f << endl;
    vector<double> cross;
    i = (b*f - c*e);
    j = (a*f - c*d) * (-1);
    k = (a*e - b*d);
    //cout << "Cross Product : i-> " << i << " j-> " << j << " k-> " << k << endl;
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
    /// any of the sides share point with the longest side
    /// we choose arbitrary shortest side and then find the common point between them
    /// here we are finding the common point for calculating the dotProduct
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

double Triangle::calculateDotProduct(vector<double> vector1, vector<double> vector2)
{
    return (vector1.at(0)*vector2.at(0)) + (vector1.at(1)*vector2.at(1)) + (vector1.at(2)*vector2.at(2));
}

const vector<double> Triangle::getNormalizedCrossProduct()
{
    vector<double> vector1;
    const vector<double> xprod = getCrossProductResult();
    double l = sqrt(pow(xprod.at(0), 2.0)
                    + pow(xprod.at(1), 2.0)
                    + pow(xprod.at(2), 2.0));
    vector1.push_back(xprod.at(0)/l);
    vector1.push_back(xprod.at(1)/l);
    vector1.push_back(xprod.at(2)/l);
    return vector1;

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
    //vector<double> vectors = crossProductResult;
    //double l = sqrt(pow(vectors.at(0), 2.0) + pow(vectors.at(1), 2.0) + pow(vectors.at(2), 2.0));
    //cout << "Unit L-> " << l << endl;
    //cout << "Value to decide : " << vectors.at(2)/l << endl;
    //return abs(vectors.at(2)/l) > COSINE_45;
    return abs(getNormalizedCrossProduct().at(2)) >= COSINE_45;
}

Triangle::~Triangle()
{
    //dtor
}
