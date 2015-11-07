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

        vector<double> getDeltas();

        bool operator== (const Edge& rhs)
        {
            return (this->points.at(0) == rhs.points.at(0) && this->points.at(1) == rhs.points.at(1))
                || (this->points.at(0) == rhs.points.at(1) && this->points.at(1) == rhs.points.at(0));
        }

        bool operator<= (const Edge& rhs)
        {
            return sideLength <= rhs.sideLength;
        }

        bool operator>= (const Edge& rhs)
        {
            return sideLength >= rhs.sideLength;
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

        void displayEdge() { cout << "\tPoint 1: (" << points.at(0).getX() << ", " << points.at(0).getY() <<
                                ", " << points.at(0).getZ() << ")" <<
                                "\n\tPoint 2: (" << points.at(1).getX() << ", " << points.at(1).getY() <<
                                ", " << points.at(1).getZ() << ")\nLength: " << sideLength << endl; }
    protected:
    private:
        vector<Point> points; //!< Member variable "points"
        double sideLength; //!< Member variable "sideLength"
};

#endif // EDGE_H
