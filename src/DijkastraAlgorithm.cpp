#include "DijkastraAlgorithm.h"

struct comparison
{
  bool operator()(const pair<char,double>& lhs, const pair<char,double>& rhs) const
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

vector<pair<char,double>> DijkastraAlgorithm::findShortestPaths(const vector<Node>& network, const char& startingNode)
{
    /// normal map becuase we should not have same char keys
    vector<pair<char, double>> solution;
    priority_queue<pair<char, double>, vector<pair<char,double>>, comparison> que;
    que.push(make_pair(startingNode, 0));
    pair<char,double> frontQue;
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
                    for(multimap<char,double>::const_iterator pit = network[i].GetmyPath().cbegin();
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
