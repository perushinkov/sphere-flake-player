#ifndef PERUSHINKOV_SPHERE_H
#define PERUSHINKOV_SPHERE_H

#include "../glewInclude.h"
#include "Mesh.h"

struct DirectVertex {

  glm::vec3 vertex;
  glm::vec3 normal;
};

struct StripInfo {
  StripInfo(int vertLength, DirectVertex* vertices, int indLength, GLuint* indices)
    : vertLength(vertLength), vertices(vertices), indLength(indLength), indices(indices)
  {}

  int vertLength;
  DirectVertex* vertices;
  int indLength;
  GLuint* indices;
};
/*
  I had no time for a parallel-meridian sphere, or an equalitateral triangles sphere
  Instead I pick an easy-to-implement cube sphere:
  
  1. Start with cube
  2. split each side horizontally and vertically into N*N pieces
  3. Normalize each vertex
  4. generate indices array for GL_TRIANGLES
*/



class Sphere: public Mesh
{
public:
  
  /*
    detailLevel determines the number of divisions per cube side at the beginning of 
    the sphere generation.

    This means that in the end the number of triangles is x*x*2 * 6, where x is detailLevel
  */
  Sphere(int size, const glm::vec3& center, float radius);
  ~Sphere();
  virtual void Draw();

  static StripInfo* generateVertices(int size, const glm::vec3& center, float radius);
private:
  GLuint m_vao;
  GLuint m_vbo;
  GLuint m_ebo;
  float m_radius;
  int m_numberOfIndices;
  int m_numberOfVertices;

  
};

#endif