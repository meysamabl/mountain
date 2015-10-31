#include <iostream>
#include <vector>
#include <random>

#include "Node.h"
#include "Triangle.h"
#include "DijkastraAlgorithm.h"

using namespace std;

default_random_engine gen;
uniform_real_distribution<double> distr;

list<Triangle> initialTriangles(double x0, double y0, double z0)
{
    Triangle* tptr = nullptr;
    vector<Edge> edges;
    list<Triangle> tris;
    Edge* eptr = nullptr;

    ///first trianlge
    eptr = new Edge(x0,y0,z0, 0, 0, 0);
    edges.push_back(*eptr);
    eptr = new Edge(x0,y0,z0, 100, 0, 0);
    edges.push_back(*eptr);
    eptr = new Edge(0, 0, 0, 100, 0, 0);
    edges.push_back(*eptr);
    tptr = new Triangle(edges);
    tris.push_back(*tptr);
    edges.clear();
    /// second triangle
    eptr = new Edge(x0,y0,z0, 0, 0, 0);
    edges.push_back(*eptr);
    eptr = new Edge(x0,y0,z0, 0, 100, 0);
    edges.push_back(*eptr);
    eptr = new Edge(0, 0, 0, 0, 100, 0);
    edges.push_back(*eptr);
    tptr = new Triangle(edges);
    tris.push_back(*tptr);
    edges.clear();
    /// third triangle
    eptr = new Edge(x0,y0,z0, 0, 100, 0);
    edges.push_back(*eptr);
    eptr = new Edge(x0,y0,z0, 100, 100, 0);
    edges.push_back(*eptr);
    eptr = new Edge(0, 100, 0, 100, 100, 0);
    edges.push_back(*eptr);
    tptr = new Triangle(edges);
    tris.push_back(*tptr);
    edges.clear();
    /// forth triangle
    eptr = new Edge(x0,y0,z0, 0, 0, 0);
    edges.push_back(*eptr);
    eptr = new Edge(x0,y0,z0, 100, 0, 0);
    edges.push_back(*eptr);
    eptr = new Edge(0, 0, 0, 100, 0, 0);
    edges.push_back(*eptr);
    tptr = new Triangle(edges);
    tris.push_back(*tptr);
     edges.clear();
    return tris;
}

int main ()
{
    double x0,y0,z0;
    list<Triangle> mountain;

    cout << "Please enter initial location(x0,y0,z0) within the range [0,100]: ";
    cin >> x0;
    cin >> y0;
    cin >> z0;
    cout << "Your initial position is: " << "(" << x0 << ", " << y0 << ", " << z0 << ")" << endl;
    list<Triangle> doodooltala = initialTriangles(x0,y0,z0);
    mountain.merge(doodooltala);
    int edgeNum = 1;
    for(list<Triangle>::iterator it = mountain.begin(); it != mountain.end(); ++it)
    {
        cout << it->getId() << endl;
        for(unsigned i = 0; i < it->getEdges().size(); ++i)
        {
            cout << "Edge " << edgeNum << endl;
            it->getEdges()[i].displayEdge();
            edgeNum++;
        }
        cout << endl;
        edgeNum = 1;
    }
    return 0;
}
/*
int main()
{
    vector<Node> myNetwork;
    char startingNode;
    Node * nodePtr = nullptr;

    nodePtr = new Node('a');
    nodePtr->addPath('h', 8);
    nodePtr->addPath('d', 4);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node('b');
    nodePtr->addPath('d',5);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node('c');
    nodePtr->addPath('h', 3);
    nodePtr->addPath('f', 5);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node('d');
    nodePtr->addPath('h', 3);
    nodePtr->addPath('c', 4);
    nodePtr->addPath('f', 10);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node('e');
    nodePtr->addPath('a', 2);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node('f');
    nodePtr->addPath('b', 4);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node('g');
    nodePtr->addPath('f', 2);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node('h');
    nodePtr->addPath('e', 3);
    myNetwork.push_back(*nodePtr);
    for(unsigned i = 0; i < myNetwork.size(); i++)
    {   cout << "Node \"" << myNetwork[i].Getname() << "\" has the following paths:  " << endl;
        for(multimap<char, int>::const_iterator it = myNetwork[i].GetmyPath().cbegin();
                                                it != myNetwork[i].GetmyPath().cend(); it++)
        {
            cout << (*it).first << " ==> " << (*it).second << endl;
        }
    }
    cout << "Please choose your starting node (a-h): ";
    cin >> startingNode;
    cout << "Starting position is: " << startingNode << endl;
    bool found = false;
    for(vector<Node>::const_iterator it = myNetwork.cbegin(); it != myNetwork.cend(); ++it)
    {
        if((*it).Getname() == startingNode) {
            found = true;
            break;
        }
    }
    if(found) {
        vector<pair<char,int>> sol = DijkastraAlgorithm::findShortestPaths(myNetwork, startingNode);
        for(vector<pair<char,int>>::iterator it = sol.begin(); it != sol.end(); ++it)
        {
            cout << it->first << " " << it->second << endl;
        }
    } else {
        cout << "starting node is not in the network!!" << endl;
    }
    return 0;
}
*/
