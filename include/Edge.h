#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <math.h>
#include "Point.h"
#include <iostream>

using namespace std;

class Edge
{
    public:
        /** Default constructor */
        Edge();

        Edge(double x0, double y0, double z0, double x1, double y1, double z1);

        /** Default destructor */
        virtual ~Edge();

        void calculateSideLength();

        bool operator== (const Edge& rhs)
        {
            return this->points[0] == rhs.points[0] && this->points[1] == rhs.points[1];
        }
        /** Access points
         * \return The current value of points
         */
        vector<Point> getPoints() { return points; }
        /** Set points
         * \param val New value to set
         */
        void setPoints(vector<Point> val) { points = val; }
        /** Access sideLength
         * \return The current value of sideLength
         */
        double getSideLength() { return sideLength; }
        /** Set sideLength
         * \param val New value to set
         */
        void setSideLength(double val) { sideLength = val; }

        void displayEdge() { cout << "\tPoint 1: (" << points[0].getX() << ", " << points[0].getY() <<
                                ", " << points[0].getZ() << ")" <<
                                "\n\tPoint 2: (" << points[1].getX() << ", " << points[1].getY() <<
                                ", " << points[1].getZ() << ")" << endl; }
    protected:
    private:
        vector<Point> points; //!< Member variable "points"
        double sideLength; //!< Member variable "sideLength"
        vector<double> getDeltas();
};

#endif // EDGE_H
