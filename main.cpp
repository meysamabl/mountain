#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
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
    pptr = new Point(0, 0, 0);
    vertices.push_back(*pptr);
    pptr = new Point(100, 0, 0);
    vertices.push_back(*pptr);
    pptr = new Point(x0,y0,z0);
    vertices.push_back(*pptr);
    tptr = new Triangle(vertices);
    tris.push_back(*tptr);
    vertices.clear();
    /// second triangle
    pptr = new Point(0, 100, 0);
    vertices.push_back(*pptr);
    pptr = new Point(0, 0, 0);
    vertices.push_back(*pptr);
    pptr = new Point(x0,y0,z0);
    vertices.push_back(*pptr);
    tptr = new Triangle(vertices);
    tris.push_back(*tptr);
    vertices.clear();
    /// third triangle
    pptr = new Point(0, 100, 0);
    vertices.push_back(*pptr);
    pptr = new Point(100,100, 0);
    vertices.push_back(*pptr);
    pptr = new Point(x0,y0,z0);
    vertices.push_back(*pptr);
    tptr = new Triangle(vertices);
    tris.push_back(*tptr);
    vertices.clear();
    /// forth triangle
    pptr = new Point(100, 100, 0);
    vertices.push_back(*pptr);
    pptr = new Point(100,0, 0);
    vertices.push_back(*pptr);
    pptr = new Point(x0,y0,z0);
    vertices.push_back(*pptr);
    tptr = new Triangle(vertices);
    tris.push_back(*tptr);
    vertices.clear();
    for(list<Triangle>::iterator it = tris.begin(); it != tris.end(); ++it)
    {
        for(list<Triangle>::iterator itr = tris.begin(); itr != tris.end(); ++itr)
        {
            if((*it)!=(*itr))
            {
                it->addIfNeighbor(&(*itr));
            }
        }
    }
    return tris;
}

int main ()
{
    double x0,y0,z0;
    unsigned numberOfTriangles;
    list<Triangle> mountain;
    fstream fout("test_output.dat", ios::out);
    gen.seed(time(NULL));
    cout << "Please enter initial location(x0,y0,z0) within the range [0,100]: ";
    cin >> x0;
    cin >> y0;
    cin >> z0;
    cout << "Your initial position is: " << "(" << x0 << ", " << y0 << ", " << z0 << ")" << endl;
    mountain.merge(initialTriangles(x0,y0,z0));
    cout << "Please indicate how many triangle to generate: ";
    cin >> numberOfTriangles;
    list<Triangle>::iterator it = mountain.begin();
    list<Triangle> refinedList;
    while(it != mountain.end() && mountain.size() < numberOfTriangles)
    {

        if(!it->isRefinable())
        {
            ++it;
        }
        refinedList = it->refineMe();
        mountain.erase(it++);
        mountain.merge(refinedList);
        /*
        for(list<Triangle>::iterator itr = refinedList.begin(); itr != refinedList.end(); ++itr)
        {
            mountain.push_back(*itr);
        }

        refinedList.clear();
        */
    }
    //cout << "----------size: " << mountain.size() << endl;
    vector<Node> network;
    for(list<Triangle>::iterator itr = mountain.begin(); itr != mountain.end();++itr)
    {
        //cout << "Triangle #" << itr->getId() << endl;
        network.push_back(itr->getNodeRepresentation());
        for(unsigned i = 0; i < itr->getVertices().size(); ++i)
        {
            fout << itr->getVertices().at(i).getX() << " "
            << itr->getVertices().at(i).getY() << " "
            << itr->getVertices().at(i).getZ() << endl;
            /*
            cout << itr->getVertices().at(i).getX() << " "
            << itr->getVertices().at(i).getY() << " "
            << itr->getVertices().at(i).getZ() << endl;
            */
        }
        /*
        cout << "Pointing at ==> ";
        for(unsigned i = 0; i < itr->getNeighbors().size(); ++i)
        {
            cout << "Triangle #" << itr->getNeighbors().at(i)->getId() << ", ";
        }
        cout << endl << endl;
        */
    }
    /*
    for(vector<Node>::iterator it = network.begin(); it != network.end(); ++it)
    {
        cout << "Triangle #" << it->Getname() << " my Path ==> ";
        for(multimap<int, double>::const_iterator mit = it->GetmyPath().cbegin(); mit != it->GetmyPath().cend(); ++mit)
        {
            cout << "Triangle #" << (*mit).first << " -> " << (*mit).second << ", ";
        }
        cout << endl << endl;
    }*/
    cout << "Do you want to generate the graph or use Dijkastra Algorithm to calculate the path"<< endl;
    cout << "1) Generate the graph" << endl;
    cout << "2) Use Dijkastra Algorithm" << endl;
    cout << "Your choice: ";
    cin >> numberOfTriangles;
    if(numberOfTriangles == 1)
    {
        system("gnuplot command.txt ");
    }
    else if (numberOfTriangles == 2)
    {
        it = mountain.begin();
        unsigned startingNode;
        cout << "Please choose one triangle within range [0 - " << mountain.size() -1 << "] ";
        cin >> startingNode;
        if(startingNode<0 || startingNode > mountain.size() -1)
        {
            cout << "Sorry! The triangle is not within the range." << endl;
            return 0;
        }
        std::advance(it, startingNode);
        cout << "Starting Triangle #" << it->getId() << endl;
        vector<pair<int,double>> sol = DijkastraAlgorithm::findShortestPaths(network, it->getId());
        for(vector<pair<int,double>>::iterator it = sol.begin(); it != sol.end(); ++it)
        {
            cout << "To-> " << it->first << ", Cost-> " << it->second << endl;
        }
    }
    return 0;
}
/*
int main()
{
    vector<Node> myNetwork;
    int startingNode;
    Node * nodePtr = nullptr;

    nodePtr = new Node(1);
    nodePtr->addPath(8, 8);
    nodePtr->addPath(4, 4);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node(2);
    nodePtr->addPath(4,5);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node(3);
    nodePtr->addPath(8, 3);
    nodePtr->addPath(6, 5);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node(4);
    nodePtr->addPath(8, 3);
    nodePtr->addPath(3, 4);
    nodePtr->addPath(6, 10);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node(5);
    nodePtr->addPath(1, 2);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node(6);
    nodePtr->addPath(2, 4);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node(7);
    nodePtr->addPath(6, 2);
    myNetwork.push_back(*nodePtr);
    nodePtr = new Node(8);
    nodePtr->addPath(5, 3);
    myNetwork.push_back(*nodePtr);
    for(unsigned i = 0; i < myNetwork.size(); i++)
    {   cout << "Node \"" << myNetwork[i].Getname() << "\" has the following paths:  " << endl;
        for(multimap<int, double>::const_iterator it = myNetwork[i].GetmyPath().cbegin();
                                                it != myNetwork[i].GetmyPath().cend(); it++)
        {
            cout << "Triangle #\"" << (*it).first <<"\"" << " ==> " << (*it).second << endl;
        }
    }
    cout << "Please choose your starting node (1-8): ";
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
        vector<pair<int,double>> sol = DijkastraAlgorithm::findShortestPaths(myNetwork, startingNode);
        for(vector<pair<int,double>>::iterator it = sol.begin(); it != sol.end(); ++it)
        {
            cout << it->first << " " << it->second << endl;
        }
    } else {
        cout << "starting node is not in the network!!" << endl;
    }
    return 0;
}
*/
