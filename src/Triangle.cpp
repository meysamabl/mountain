#include "Triangle.h"

Triangle::Triangle()
{
    //ctor
}

Triangle::Triangle(vector<Location> vertices, string id) : id(id) {
    this->vertices = vertices;
}

Triangle::~Triangle()
{
    //dtor
}
