#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Edge.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <random>

using namespace std;

class Triangle
{
    public:
        static int idStat;
        /** Default constructor */
        Triangle();

        Triangle(vector<Edge> edgeValues);
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

        Point findCentroid();

        string getId() const { return id; }

        void setId(string val) { id = val; }

        vector<Triangle*>& getNeighbors()  { return neighbors; }

        void setNeighbors(vector<Triangle*> val) { neighbors = val; }

        vector<Edge>& getEdges()  { return edges; }

        void setEdges(vector<Edge> val) { edges = val; }


    protected:
    private:
        string id;
        vector<Triangle*> neighbors;
        vector<Edge> edges;
        bool isNeighbor(const Triangle& triangle);
        void addNeighbor(Triangle* neighbor);
};

#endif // TRIANGLE_H
