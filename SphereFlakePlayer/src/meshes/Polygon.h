#ifndef PERUSHINKOV_POLYGON_H
#define PERUSHINKOV_POLYGON_H

#include "../glewInclude.h"
#include "Mesh.h"

class Polygon : public Mesh
{
public:
  virtual void Draw();
  Polygon(GLfloat* data, int bytes);
  ~Polygon();
private:
  GLuint m_vao;
  GLuint m_vbo;
  int m_length;
};

#endif