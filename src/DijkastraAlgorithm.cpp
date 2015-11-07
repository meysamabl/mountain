#include "DijkastraAlgorithm.h"

struct comparison
{
  bool operator()(const pair<int,double>& lhs, const pair<int,double>& rhs) const
  {
    return lhs.second > rhs.second;
  }
};

DijkastraAlgorithm::DijkastraAlgorithm()
{
    //ctor
}

DijkastraAlgorithm::~DijkastraAlgorithm()
{
    //dtor
}

vector<pair<int,double>> DijkastraAlgorithm::findShortestPaths(const vector<Node>& network, const int& startingNode)
{
    vector<pair<int, double>> solution;
    priority_queue<pair<int, double>, vector<pair<int,double>>, comparison> que;
    que.push(make_pair(startingNode, 0));
    pair<int,double> frontQue;
    bool found = false;
    while(!que.empty()) {
        found = false;
        frontQue = que.top();
        ///Check to see if it is inside the solution?
        for(unsigned i = 0; i < solution.size(); i++)
        {
            if(solution[i].first == frontQue.first) {
                found = true;
                break;
            }
        }
        if(!found) {
            solution.push_back(frontQue);
            que.pop();
            for (unsigned i = 0; i < network.size(); i++)
            {
                if(network[i].Getname() == solution.back().first)
                {
                    for(multimap<int,double>::const_iterator pit = network[i].GetmyPath().cbegin();
                                                    pit != network[i].GetmyPath().cend(); ++pit)
                    {
                        que.push(make_pair((*pit).first, (*pit).second + solution.back().second));
                    }
                    break;
                }
            }

        } else {
            que.pop();
        }
    }
    return solution;
}
