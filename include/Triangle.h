#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Edge.h"
#include <list>
#include <vector>
#include <iostream>
#include <random>
#include <exception>
#include <math.h>
#include <Node.h>

using namespace std;

class Triangle
{
    public:
        static int idCounter;
        /** Default constructor */
        Triangle();

        Triangle(vector<Point> verticesVal);
        /** Default destructor */
        virtual ~Triangle();

        bool operator== (const Triangle& rhs)
        {
            if(this == &rhs) { return true;}
            else { return false;}
        }

        bool operator< (const Triangle& rhs)
        {
            return this->id < rhs.id;
        }

        bool operator!= (const Triangle& rhs)
        {
            if(this != &rhs) { return true;}
            else { return false;}
        }

        bool addIfNeighbor(Triangle* neighbor);

        bool isTraversable();

        bool isRefinable() const { return refinable; }

        void updateTargetPointer(Triangle* neighbor, Triangle* updatePointer);

        Node getNodeRepresentation();

        Point getDeviatedCentroid();

        list<Triangle> refineMe();

        int getId() const { return id; }

        void setId(int val) { id = val; }

        vector<Triangle*>& getNeighbors()  { return neighbors; }

        void setNeighbors(vector<Triangle*> val) { neighbors = val; }

        vector<Edge>& getEdges()  { return edges; }

        void setEdges(vector<Edge> val) { edges = val; }

        vector<Point> getVertices() { return vertices;}

        Point getCentroid() const { return centroid; }

        const vector<double>& getCrossProductResult() const { return crossProductResult; }

    protected:
    private:
        int id;
        bool refinable;
        vector<Triangle*> neighbors;
        vector<Edge> edges;
        vector<Point> vertices;
        Point centroid;
        vector<double> crossProductResult;
        bool isNeighbor(const Triangle& triangle);
        void addNeighbor(Triangle* neighbor);
        Edge& getShortestSide();
        Edge& getLongestSide();
        Point findCentroid();
        vector<double> calculateCrossProduct();
        double calculateDotProduct(vector<double> vector1, vector<double> vector2);
        const vector<double> getNormalizedCrossProduct();
        double calculateAspectRatio();
        double calculateDistance(const Point& point1, const Point& point0);
        vector<double> getDelta(const Point& pointDiff, const Point& pointCommon);
        const double COSINE_45 = 0.707;
};

#endif // TRIANGLE_H
