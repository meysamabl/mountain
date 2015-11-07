#ifndef DIJKASTRAALGORITHM_H
#define DIJKASTRAALGORITHM_H

#include <map>
#include <vector>
#include <set>
#include <queue>
#include "Node.h"
#include <iostream>

using namespace std;

class DijkastraAlgorithm
{
    public:
        /** Default constructor */
        DijkastraAlgorithm();
        /** Default destructor */
        virtual ~DijkastraAlgorithm();
        static vector<pair<int,double>> findShortestPaths(const vector<Node>& nodes, const int& startingNode);
    protected:
    private:
};

#endif // DIJKASTRAALGORITHM_H
