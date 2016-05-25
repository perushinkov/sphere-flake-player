#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include "App.h"
#include "meshes\Sphere.h"

int main(int argc, char** argv) {
  try {
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