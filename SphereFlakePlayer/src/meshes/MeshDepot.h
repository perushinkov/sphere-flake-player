#ifndef PERUSHINKOV_MESH_DEPOT_H
#define PERUSHINKOV_MESH_DEPOT_H

#include "Mesh.h"
#include <vector>

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
  void createSpheres(glm::vec3 motherLocation, glm::vec3 bottomToCenter, int depth, std::vector<std::string>& sphereHolder);
};

#endif