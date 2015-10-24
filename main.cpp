#include <iostream>
#include <vector>

#include "Node.h"
#include "DijkastraAlgorithm.h"

using namespace std;

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
