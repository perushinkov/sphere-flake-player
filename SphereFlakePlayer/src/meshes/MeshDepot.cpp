#include "MeshDepot.h"
#include "MeshFactory.h"

MeshDepot::MeshDepot() : m_samplePolygon(nullptr) {}


MeshDepot::~MeshDepot()
{
  if (m_samplePolygon != nullptr) {
    delete m_samplePolygon;
  }
}

void MeshDepot::createDrawables() {
  GLfloat vertices[] = {
    // Positions         // Colors
    0.5f, -0.5f, 0.0f,   // Bottom Right
    -0.5f, -0.5f, 0.0f,   // Bottom Left
    0.0f, 0.5f, 0.0f    // Top 
  };
  m_samplePolygon = MeshFactory::createPolygon((Vertex*)vertices, sizeof(vertices));
}

void MeshDepot::drawAll() {
  if (m_samplePolygon != nullptr) {
    m_samplePolygon->Draw();
  }
}
