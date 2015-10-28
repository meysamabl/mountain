#include <iostream>
#include <vector>
#include <random>

#include "Node.h"
#include "Triangle.h"
#include "DijkastraAlgorithm.h"

using namespace std;

default_random_engine gen;
uniform_real_distribution<double> distr;

int main ()
{
    double x0,y0,z0;
    Triangle* triPtr = nullptr;
    Location* locPtr = nullptr;
    vector<Location> vertices;
    list<Triangle> mountain;

    cout << "Please enter initial location(x0,y0,z0) within the range [0,100]: ";
    cin >> x0;
    cin >> y0;
    cin >> z0;
    cout << "Your initial position is: " << "(" << x0 << ", " << y0 << ", " << z0 << ")" << endl;

    ///creating the pyramid ---------------
    /* ------ trianle 0 ------- */
    locPtr = new Location(0.0, 0.0, 0.0);
    vertices.push_back(*locPtr);
    locPtr = new Location(100.0, 0.0, 0.0);
    vertices.push_back(*locPtr);
    locPtr = new Location(x0,y0,z0);
    vertices.push_back(*locPtr);
    triPtr = new Triangle(vertices, "triangle#0");
    mountain.push_back(*triPtr);
    vertices.clear();
    /* ------ trianle 1 ------- */
    locPtr = new Location(0.0, 0.0, 0.0);
    vertices.push_back(*locPtr);
    locPtr = new Location(0.0, 100.0, 0.0);
    vertices.push_back(*locPtr);
    locPtr = new Location(x0,y0,z0);
    vertices.push_back(*locPtr);
    triPtr = new Triangle(vertices, "triangle#1");
    mountain.push_back(*triPtr);
    vertices.clear();
    /* ------ trianle 2 ------- */
    locPtr = new Location(0.0, 100.0, 0.0);
    vertices.push_back(*locPtr);
    locPtr = new Location(100.0, 100.0, 0.0);
    vertices.push_back(*locPtr);
    locPtr = new Location(x0,y0,z0);
    vertices.push_back(*locPtr);
    triPtr = new Triangle(vertices, "triangle#2");
    mountain.push_back(*triPtr);
    vertices.clear();
    /* ------ trianle 3 ------- */
    locPtr = new Location(100.0, 100.0, 0.0);
    vertices.push_back(*locPtr);
    locPtr = new Location(100.0, 0.0, 0.0);
    vertices.push_back(*locPtr);
    locPtr = new Location(x0,y0,z0);
    vertices.push_back(*locPtr);
    triPtr = new Triangle(vertices, "triangle#3");
    mountain.push_back(*triPtr);
    vertices.clear();
    for(list<Triangle>::iterator it = mountain.begin(); it != mountain.end(); ++it)
    {
        for(list<Triangle>::iterator itr = mountain.begin(); itr != mountain.end(); ++itr)
        {
            if((*it) != (*itr))
            {
                if((*it).isNeighbor((*itr).Getvertices()))
                {
                    (*it).addNeighor(*itr);
                }
            }
        }
    }
    for(list<Triangle>::iterator it = mountain.begin(); it != mountain.end(); ++it)
    {   cout << "Name: " << it->Getid() << endl;
        for(unsigned i = 0; i < it->Getvertices().size(); ++i)
        {
            cout << "(" << it->Getvertices()[i].Getx() <<
                    ", " << it->Getvertices()[i].Gety() <<
                    ", " << it->Getvertices()[i].Getz() << ") " << endl;
        }
    }
    /*
    for(list<Triangle>::iterator it = mountain.begin(); it != mountain.end(); ++it)
    {   list<Triangle*> temp = it->Getneighbors();
     cout << "Name: " << it->Getid() << endl;
        for(list<Triangle*>::iterator itr = temp.begin(); itr != temp.end(); ++itr)
        {
            cout << "Point: " << (*itr)->Getid() << endl;
        }
    }*/
    int iterationNumber = 0;
    list<Triangle>::iterator it = mountain.begin();

    while(iterationNumber <=100)
    {
        while(it != mountain.end())
        {
            it->getRandomCentroid();
            it++;
        }
        iterationNumber++;
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
