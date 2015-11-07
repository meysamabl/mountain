#include "Node.h"

Node::Node()
{
    //ctor
}

Node::~Node()
{
    //dtor
}

Node::Node(int name) : name(name) {}

void Node::addPath(int ch, double dest)
{
    myPath.insert(make_pair(ch, dest));
}
