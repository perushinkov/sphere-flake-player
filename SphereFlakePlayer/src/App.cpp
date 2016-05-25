#include "glewInclude.h"
#include "App.h"
#include "meshes\Mesh.h"
#include "meshes\Sphere.h"
#include "meshes\Polygon.h"
#include "meshes\MeshFactory.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>  


App* App::m_app = nullptr;

// Singleton implementation
App& App::getApp() {
  if (m_app == nullptr) {
    m_app = new App();
  }
  return *m_app;
}

void App::initGLFW() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void App::initGLEW() {
  glewExperimental = true;
  GLenum status = glewInit();
  if (status != GLEW_OK)
  {
    throw "Failed to initialize GLEW";
  }
}

void App::initViewport() {
  int vpWidth, vpHeight;
  glfwGetFramebufferSize(m_window, &vpWidth, &vpHeight);
  glViewport(0, 0, vpWidth, vpHeight);
}

App::App() : m_window(nullptr), m_shader(nullptr) {
  initGLFW();
  makeWindow(WIDTH, HEIGHT, "LearnOpenGL");
  initGLEW();
  initViewport();

  m_shader = new Shader("simple");
  m_proj = glm::perspective(70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
  m_translate = glm::translate(m_translate, glm::vec3(0.f, 0.f, 0.f));

  m_meshDepot = new MeshDepot();
}

App::~App() {
  glfwTerminate();
  delete m_shader;
}

void App::makeWindow(int width, int height, const char* title) {
  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (m_window == nullptr)
  {
    throw "Failed to create GLFW window";
  }
  glfwMakeContextCurrent(m_window);
  glfwSetKeyCallback(m_window, App::key_callback);
}


void App::startEventLoop() {
 // m_meshDepot->createDrawables();
  //Sphere sphere(18, glm::vec3(0.5f, 0.3f, 0.0f), 0.01f);
  Sphere sphere2(27, glm::vec3(0.0f, 0.0f, -0.5f), 0.2f);


  glm::mat4 translation(0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // Game loop
  while (!glfwWindowShouldClose(m_window))
  {
    glfwPollEvents();

    // Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    glm::mat4 rota;
    rota = glm::rotate(rota, xRotation, glm::vec3(1.f, 0.f, 0.f));
    rota = glm::rotate(rota, yRotation, glm::vec3(0.f, 1.f, 0.f));
    m_view = rota;

    m_shader->Bind();
    m_shader->setColour(0.3f, 0.9f, 0.2f);
    m_shader->setProjectionMatrix(m_proj);
    // It's a rotation matrix really
    m_shader->setViewMatrix(m_view);
    m_shader->setTranslationMatrix(m_translate);
    m_shader->setScaleMatrix(m_scale);
    //sphere.Draw();
    sphere2.Draw();

    //m_shader->setColour(0.f, 1.f, 0.f);
   // m_meshDepot->drawAll();

    // Swap the screen buffers
    glfwSwapBuffers(m_window);
  }
}

void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  static bool backwards = false;

  App& app = App::getApp();

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  else if (key == GLFW_KEY_DOWN && action != GLFW_PRESS) {
    app.xRotation += 0.03;
  }
  else if (key == GLFW_KEY_UP && action != GLFW_PRESS) {
    app.xRotation -= 0.03;
  }
  else if (key == GLFW_KEY_RIGHT && action != GLFW_PRESS) {
    app.yRotation += 0.03;
  }
  else if (key == GLFW_KEY_LEFT && action != GLFW_PRESS) {
    app.yRotation -= 0.03;
  }
  else if (key == GLFW_KEY_KP_ADD && action != GLFW_PRESS) {
    app.m_scale = glm::scale(app.m_scale, glm::vec3(0.9f, 0.9f, 0.9f));
    std::cout << "SCALE:" << app.m_scale[0][0] << std::endl;
  }
  else if (key == GLFW_KEY_KP_SUBTRACT && action != GLFW_PRESS) {    
    app.m_scale = glm::scale(app.m_scale, glm::vec3(1.1f, 1.1f, 1.1f));
    std::cout << "SCALE:" << app.m_scale[0][0] << std::endl;
  }
  else if (key == GLFW_KEY_SPACE) {
    int sign = backwards ? -1 : 1;

    glm::vec4 unit(0.f, 0.f, (-1.f), 1.f);
    glm::mat4 rota;
    rota = glm::rotate(rota, app.xRotation, glm::vec3((-1.f), 0.f, 0.f));
    rota = glm::rotate(rota, app.yRotation, glm::vec3(0.f, (-1.f), 0.f));
    float scaleFactor = app.m_scale[0][0];
    // The other algorithm resulted in strange effects... maybe gimbal lock?
    // It just rotated all around the x or y axis. But then axis got transformed, too...
    // So a mess! This works... so it's alright!

     app.m_translate = glm::translate(app.m_translate, - glm::vec3(normalize(rota * unit))*0.01f * float(sign) * scaleFactor);

  }
  else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
    backwards = !backwards;
  }

 

}
