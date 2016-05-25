#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "glewInclude.h"
#include "meshes/Mesh.h"

class Shader
{
public:
  Shader(const std::string& fileName);
  /* binds vertex and fragment shaders to gpu */
  void Bind();
  void setColour(GLfloat r, GLfloat g, GLfloat b);
  void setProjectionMatrix(const glm::mat4& projMat);
  void setViewMatrix(const glm::mat4& viewMat);
  void setTranslationMatrix(const glm::mat4& transMat);
  void setScaleMatrix(const glm::mat4& scaleMat);

  virtual ~Shader();
private:
  Vertex m_colour;
  static const unsigned int NUM_SHADERS = 2; // shader can be Vertex/Fragment/Geometry
  Shader::Shader(const Shader& other) {}
  Shader& Shader::operator=(const Shader& rhs) {}

  GLuint CreateShader(const std::string& text, GLenum shaderType);
  std::string LoadShader(const std::string& fileName);
  void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
};

#endif