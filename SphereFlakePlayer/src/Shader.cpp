#include <iostream>
#include <fstream>

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& fileName)
{
  m_program = glCreateProgram();
  // 0th shader is vertexShader
  m_shaders[0] = CreateShader(LoadShader(std::string(".\\shaders\\") + fileName + ".vert"), GL_VERTEX_SHADER);
  m_shaders[1] = CreateShader(LoadShader(std::string(".\\shaders\\") + fileName + ".frag"), GL_FRAGMENT_SHADER);

  for (unsigned int i = 0; i < NUM_SHADERS; i++) {
    glAttachShader(m_program, m_shaders[i]);
  }

  glBindAttribLocation(m_program, 0, "position");

  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");
}

Shader::~Shader()
{
  glDeleteProgram(m_program);
  for (unsigned int i = 0; i < NUM_SHADERS; i++) {
    glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType) {
  GLuint shader = glCreateShader(shaderType);

  if (shader == 0) {
    std::cerr << "Error: Shader creation failed!" << std::endl;
  }

  const GLchar* shaderSourceStrings[1];
  GLint shaderSourceStringLengths[1];
  
  shaderSourceStrings[0] = text.c_str();
  shaderSourceStringLengths[0] = text.length();

  glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
  glCompileShader(shader);

  CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

  return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
  std::ifstream file;
  file.open((fileName).c_str());

  std::string output;
  std::string line;

  if (file.is_open())
  {
    while (file.good())
    {
      getline(file, line);
      output.append(line + "\n");
    }
  }
  else
  {
    std::cerr << "Unable to load shader: " << fileName << std::endl;
  }

  return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
  GLint success = 0;
  GLchar error[1024] = { 0 };

  if (isProgram)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if (success == GL_FALSE)
  {
    if (isProgram)
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    else
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);

    std::cerr << errorMessage << ": '" << error << "'" << std::endl;
  }
}

void Shader::Bind() {
  glUseProgram(m_program);
}

void Shader::setColour(GLfloat r, GLfloat g, GLfloat b) {
  GLint uniColor = glGetUniformLocation(m_program, "ourColor");
  glUniform3f(uniColor, r, g, b);
}

void Shader::setProjectionMatrix(const glm::mat4& projMat) {
  GLint projMatLoc = glGetUniformLocation(m_program, "projection");
  glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
}

void Shader::setViewMatrix(const glm::mat4& viewMat) {
  GLint projMatLoc = glGetUniformLocation(m_program, "view");
  glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
}

void Shader::setTranslationMatrix(const glm::mat4& transMat) {
  GLint projMatLoc = glGetUniformLocation(m_program, "translation");
  glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(transMat));

  GLint cameraPosition = glGetUniformLocation(m_program, "cameraPos");
  glUniform3f(cameraPosition, -transMat[3][0], -transMat[3][1], -transMat[3][2]);
}

void Shader::setScaleMatrix(const glm::mat4& scaleMat) {
  GLint projMatLoc = glGetUniformLocation(m_program, "scale");
  glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(scaleMat));
}