#include "Polygon.h"
#include "MeshFactory.h"

Mesh* MeshFactory::createPolygon(Vertex* data, int bytes) {
  return new Polygon((GLfloat*)data, bytes);
}