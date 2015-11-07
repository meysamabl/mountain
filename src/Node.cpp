#include "Node.h"

Node::Node()
{
    //ctor
}

Node::~Node()
{
    //dtor
}

Node::Node(char name) : name(name) {}

void Node::addPath(char ch, double dest)
{
    myPath.insert(make_pair(ch, dest));
}
