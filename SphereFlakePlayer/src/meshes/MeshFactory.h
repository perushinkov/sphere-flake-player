#ifndef PERUSHINKOV_MESH_FACTORY_H
#define PERUSHINKOV_MESH_FACTORY_H

#include "Mesh.h"
#include "Polygon.h"

// Holds easy to use adapters for mesh creation. Abstracts the type of the different meshes away.
class MeshFactory
{
public:
  static Mesh* createPolygon(Vertex* data, int length);
private:
  MeshFactory(){}
};

#endif