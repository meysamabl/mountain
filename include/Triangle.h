#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Location.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <random>

using namespace std;

class Triangle
{
    public:
        /** Default constructor */
        Triangle();

        Triangle(vector<Location> vertices, string id);
        /** Default destructor */
        virtual ~Triangle();

        bool operator== (const Triangle& rhs)
        {
            if(this == &rhs) { return true;}
            else { return false;}
        }

        bool operator!= (const Triangle& rhs)
        {
            if(this != &rhs) { return true;}
            else { return false;}
        }

        bool isNeighbor(vector<Location> verts);

        void addNeighor(Triangle& neighbor);

        Location findCentroid();

        Location getRandomCentroid();

        double getShortestSide();
        /** Access ID
        * \return value of id
        */
        string Getid() { return id; }

        /**
        * \return void
        */
        void Setid(string val) { id = val; }

        /** Access vertices
         * \return The current value of vertices
         */
        vector<Location> Getvertices() { return vertices; }
        /** Set vertices
         * \param val New value to set
         */
        void Setvertices(vector<Location> val) { vertices = val; }
        /** Access neighbors
         * \return The current value of neighbors
         */
        list<Triangle*> Getneighbors() { return neighbors; }
        /** Set neighbors
         * \param val New value to set
         */
        void Setneighbors(list<Triangle*> val) { neighbors = val; }
    protected:
    private:
        string id;
        vector<Location> vertices; //!< Member variable "vertices"
        list<Triangle*> neighbors; //!< Member variable "neighbors"
        const vector<double> getDeltaValues(const Location& loc1, const Location& loc2);
        double calculateDistance(const vector<double> deltaValues);
};

#endif // TRIANGLE_H
