#ifndef PERUSHINKOV_MESH_H
#define PERUSHINKOV_MESH_H
#include "../glewInclude.h"

struct Vertex {
  Vertex() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }
  Vertex(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

class Mesh
{
public:
  virtual void Draw() = 0;
  virtual ~Mesh(){}
private:
};

#endif