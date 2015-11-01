#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Edge.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <random>
#include <exception>

using namespace std;

class Triangle
{
    public:
        static int idStat;
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

        bool isUsable();

        void updateTargetPointer(Triangle* neighbor, Triangle* updatePointer);

        Point getDeviatedCentroid();

        list<Triangle> refineMe();

        string getId() const { return id; }

        void setId(string val) { id = val; }

        vector<Triangle*>& getNeighbors()  { return neighbors; }

        void setNeighbors(vector<Triangle*> val) { neighbors = val; }

        vector<Edge>& getEdges()  { return edges; }

        void setEdges(vector<Edge> val) { edges = val; }

        vector<Point> getVertices() { return vertices;}

    protected:
    private:
        string id;
        vector<Triangle*> neighbors;
        vector<Edge> edges;
        vector<Point> vertices;
        bool isNeighbor(const Triangle& triangle);
        void addNeighbor(Triangle* neighbor);
        Edge& getShortestSide();
        Point findCentroid();
        vector<double> calculateCrossProduct();
        const double COSINE_45 = 0.707;
};

#endif // TRIANGLE_H
