#ifndef PERUSHINKOV_APP_H
#define PERUSHINKOV_APP_H

#include "meshes\MeshDepot.h"
#include "Shader.h"
#include <glm\gtc\quaternion.hpp>

class App
{
public:
  static App& getApp();

  void startEventLoop();
  void testLoop();
  GLuint shaderProgram;

  const int WIDTH = 800;
  const int HEIGHT = 600;
  glm::mat4 m_view;
private:
  GLFWwindow* m_window;
  Shader* m_shader;
  MeshDepot* m_meshDepot;
  glm::mat4 m_proj;
  glm::mat4 m_translate;
  glm::mat4 m_scale;

  float xRotation = 0.f;
  float yRotation = 0.f;
  glm::vec3 m_camXAxis = glm::vec3(1.f, 0.f, 0.f);
  glm::vec3 m_camYAxis = glm::vec3(0.f, 1.f, 0.f);

 

  static App* m_app;
  App();
  ~App();
  void initGLFW();
  void initGLEW();
  void initViewport();
  void makeWindow(int width, int height, const char* title);
  void terminateGLFW();

  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

#endif