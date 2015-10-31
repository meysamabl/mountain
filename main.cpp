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
    vector<Point> vertices;
    list<Triangle> tris;
    Point* pptr = nullptr;

    ///first trianlge
    pptr = new Point(x0,y0,z0);
    vertices.push_back(*pptr);
    pptr = new Point(100, 0, 0);
    vertices.push_back(*pptr);
    pptr = new Point(0, 0, 0);
    vertices.push_back(*pptr);
    tptr = new Triangle(vertices);
    tris.push_back(*tptr);
    vertices.clear();
    /// second triangle
    pptr = new Point(x0,y0,z0);
    vertices.push_back(*pptr);
    pptr = new Point(0, 100, 0);
    vertices.push_back(*pptr);
    pptr = new Point(0, 0, 0);
    vertices.push_back(*pptr);
    tptr = new Triangle(vertices);
    tris.push_back(*tptr);
    vertices.clear();
    /// third triangle
    pptr = new Point(x0,y0,z0);
    vertices.push_back(*pptr);
    pptr = new Point(0, 100, 0);
    vertices.push_back(*pptr);
    pptr = new Point(100,100, 0);
    vertices.push_back(*pptr);
    tptr = new Triangle(vertices);
    tris.push_back(*tptr);
    vertices.clear();
    /// forth triangle
    pptr = new Point(x0,y0,z0);
    vertices.push_back(*pptr);
    pptr = new Point(100, 100, 0);
    vertices.push_back(*pptr);
    pptr = new Point(100,0, 0);
    vertices.push_back(*pptr);
    tptr = new Triangle(vertices);
    tris.push_back(*tptr);
    vertices.clear();
    return tris;
}

int main ()
{
    double x0,y0,z0;
    list<Triangle> mountain;
    gen.seed(time(NULL));
    cout << "Please enter initial location(x0,y0,z0) within the range [0,100]: ";
    cin >> x0;
    cin >> y0;
    cin >> z0;
    cout << "Your initial position is: " << "(" << x0 << ", " << y0 << ", " << z0 << ")" << endl;
    mountain.merge(initialTriangles(x0,y0,z0));
    int edgeNum = 1;
    for(list<Triangle>::iterator it = mountain.begin(); it != mountain.end(); ++it)
    {
        for(list<Triangle>::iterator itr = mountain.begin(); itr != mountain.end(); ++itr)
        {
            if((*it)!=(*itr))
            {
                it->addIfNeighbor(&(*itr));
            }
        }
    }
    for(list<Triangle>::iterator it = mountain.begin(); it != mountain.end(); ++it)
    {
        cout << it->getId() << endl;
        list<Triangle> doodooltala = it->refineMe();
        for(list<Triangle>::iterator itr = doodooltala.begin(); itr != doodooltala.end(); ++itr)
        {
            cout << "****** " << itr->getId() << endl;
        }
        /*
        for(unsigned i = 0; i < it->getNeighbors().size(); ++i)
        {
            cout << it->getNeighbors()[i]->getId() << ", ";
            edgeNum++;
        } */

        cout << endl << endl;
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
