#include "Polygon.h"


void Polygon::Draw() {
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, m_length);
  glBindVertexArray(0);
  
} 
Polygon::~Polygon() {
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
}


Polygon::Polygon(GLfloat* data, int bytes) {
  m_length = bytes;
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_length, data, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

  glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

}

