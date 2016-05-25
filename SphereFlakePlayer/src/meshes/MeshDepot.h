#ifndef PERUSHINKOV_MESH_DEPOT_H
#define PERUSHINKOV_MESH_DEPOT_H

#include "Mesh.h"

/*
  Serves just as a holder/organizer for all the drawables currently in the program
*/
class MeshDepot
{
public:
  MeshDepot();
  void createDrawables();
  void drawAll();
  ~MeshDepot();
private:
  Mesh* m_samplePolygon;
};

#endif