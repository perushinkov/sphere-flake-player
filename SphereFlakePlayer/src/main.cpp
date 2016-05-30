#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include "App.h"
#include "meshes\Sphere.h"
#include "meshes\Axis.h"

int main(int argc, char** argv) {
  try {
    Axes axes;
    axes.rotateX(M_PI * 0.5f);
    axes.rotateY(M_PI * 0.5f);
    axes.rotateZ(M_PI * 0.5f);

    axes.rotateZ(- M_PI * 0.5f);
    axes.rotateY(- M_PI * 0.5f);
    axes.rotateX(- M_PI * 0.5f);

    return 0;

    /*
    glm::vec3 xaxis(1.f, 0.f, 0.f);
    glm::vec3 xresult = Axes::rotatePointAroundAxis(pt, xaxis, M_PI * 0.5f);
    glm::vec3 xresult2 = Axes::rotatePointAroundAxis(pt, xaxis, M_PI * 1.0f);
    glm::vec3 xresult3 = Axes::rotatePointAroundAxis(pt, xaxis, M_PI * 1.5f);
    
    glm::vec3 yaxis(0.f, 1.f, 0.f);
    glm::vec3 yresult = Axes::rotatePointAroundAxis(pt, yaxis, M_PI * 0.5f);
    glm::vec3 yresult2 = Axes::rotatePointAroundAxis(pt, yaxis, M_PI * 1.0f);
    glm::vec3 yresult3 = Axes::rotatePointAroundAxis(pt, yaxis, M_PI * 1.5f);

    glm::vec3 zaxis(0.f, 0.f, 1.f);
    glm::vec3 zresult = Axes::rotatePointAroundAxis(pt, zaxis, M_PI * 0.5f);
    glm::vec3 zresult2 = Axes::rotatePointAroundAxis(pt, zaxis, M_PI * 1.0f);
    glm::vec3 zresult3 = Axes::rotatePointAroundAxis(pt, zaxis, M_PI * 1.5f);
    */
   
    // App singleton encapsulates some glfw and opengl settings
    App& app = App::getApp();
    app.startEventLoop();

  }
  catch (std::exception &e) {
    std::cerr << e.what();
    return -1;
  }

  return 0;
}