#include "Sphere.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "../calc/Calc.h"

#include <iostream>
Sphere::Sphere(int size, const glm::vec3& center, float radius) {
  StripInfo* pInfo = Sphere::generateVertices(size, center, radius);
  m_numberOfIndices = pInfo->indLength;
  m_numberOfVertices = pInfo->vertLength;
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(DirectVertex) * pInfo->vertLength, pInfo->vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * pInfo->indLength, pInfo->indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

Sphere::~Sphere() {
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
}


void Sphere::Draw() {
  glBindVertexArray(m_vao);
  //glDrawArrays(GL_TRIANGLES, 0, 6);
  glDrawElements(GL_TRIANGLE_STRIP, m_numberOfIndices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

}


StripInfo* Sphere::generateVertices(int size, const glm::vec3& center, float radius) {
  // 1 point on top, 1 point on bottom,  [size] meridians with [size]*2 points each
  int numOfRequiredVertices = size * size * 2 + 2;
  int numOfRequiredIndices = (2 * (size * 2) + 1) * (size + 1) + 1;

  DirectVertex* vertices = new DirectVertex[numOfRequiredVertices];
  GLuint* indices = new GLuint[numOfRequiredIndices];

  // First generate the vertices:
  vertices[0].vertex = center + glm::vec3(0.f, 0.f, radius);
  vertices[numOfRequiredVertices - 1].vertex = center + glm::vec3(0.f, 0.f, -radius);

  /*
    Vertices are generated per meridian. First the top and the bottom single vertices are identified.
    They have already been set above.
    Then for each meridian the positions of the 2*size + 1 are calculated
    
    pt. A is the vertex we are calculating.
    pt. O is center of circle.
    pt. Z is the point on the surface of the circle that has the same x,y coordinates as the center.

    cosine(angle(AO,ZO)) * Radius determines the deltaZ of pt. A
    sine(angle(AO,ZO)) * Radius determines the distance of pt. A from the segment OZ.
    It also represents: XYDistanceFromCenter

    Using this distance we calculate the x and y coordinates of equidistant points on
    the circle of the meridian, using the definitions of cos and sin
  */
  for (int meridian = 0; meridian < size; meridian++) {
    float deltaPhi = (meridian + 1) * M_PI / (size + 1);
    float deltaZ = cosf(deltaPhi) * radius;
    float XYDistanceFromCenter = sinf(deltaPhi) * radius;

    for (int par = 1; par <= size * 2; par++) {
      int currentVertexIndex = meridian*size * 2 + par;
      float deltaPhi2 = (float(par) * M_PI) / float(size);
      // Doesn't really matter which is which.. Spheres are symmetrical after all
      float deltaX = sinf(deltaPhi2)*XYDistanceFromCenter;
      float deltaY = cosf(deltaPhi2)*XYDistanceFromCenter;

      vertices[currentVertexIndex].vertex = center + glm::vec3(deltaX, deltaY, deltaZ);
    }
  }

  // Then generate the normals

  for (int i = 0; i < numOfRequiredVertices; i++) {
    vertices[i].normal = Calc::getUnitDirection(vertices[i].vertex - center);
  }

  // Then generate the indices... we'll be generating those as input for 
  // the GL_TRIANGLE_STRIP functionality
  
  // I do apologize for the mystic code below! A short explanation:
  /*
    on each iteration of the outer for cycle we walk through 
    a meridian-pair corridor and connect the dots into triangles as we go.
    It should be noted that when this happens the pair of points at the very
    beginning of the corridor also get visited at the end of the same corridor,
    when the triangles there are stitched.

    Picture:
    ...\/\/\/\/\/\/\ \/...
    ...\/\/\/\/\/\/\ \/...

    As we end the stitching process in the corridor above, we continue with the
    corridor below.
  */
  int counter = 0;
  indices[counter++] = 0;
  for (int offset = 0; offset < size + 1; offset++) {
    for (int par = 1; par <= 2 * size + 1; par++) {
      if (par != 1) {
        indices[counter++] = offset == 0 ? 0 : (offset - 1) * 2 * size + (par - 1) % (2 * size) + 1;
      }
      indices[counter++] = offset == size ? numOfRequiredVertices - 1 : offset * 2 * size + (par - 1) % (2 * size) + 1;
    }
  }



  return new StripInfo(numOfRequiredVertices, vertices, numOfRequiredIndices, indices);
}
