#include "Triangle.h"

Triangle::Triangle()
{
    //ctor
}

Triangle::Triangle(vector<Location> vertices, string id) : id(id) {
    this->vertices = vertices;
}

bool Triangle::isNeighbor(vector<Location> verts)
{
    int sideEqual = 0;
    for(unsigned i = 0; i < verts.size(); ++i)
    {
        for(unsigned j = 0; j < vertices.size(); ++j)
        {
            if(verts[i] == vertices[j])
            {
                sideEqual++;
                break;
            }
        }
    }
    return sideEqual > 1;
}

void Triangle::addNeighor(Triangle& neighbor)
{
    neighbors.push_back(&neighbor);
}

Triangle::~Triangle()
{
    //dtor
}
