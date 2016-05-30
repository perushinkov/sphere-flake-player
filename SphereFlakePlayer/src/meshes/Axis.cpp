#include "Axis.h"
#include <iostream>
#include "../App.h"

Axes::Axes() : m_x(1.f, 0.f, 0.f), m_y(0.f, 1.f, 0.f), m_z(0.f, 0.f, 1.f) {}

void Axes::fixOrthogonality() {
  m_z = glm::cross(m_x, m_y);
  m_y = glm::cross(m_z, m_x);

  m_x = glm::normalize(m_x);
  m_y = glm::normalize(m_y);
  m_z = glm::normalize(m_z);
}

void Axes::rotate(int whichAxis, float howMuch) {
  glm::vec3 &ref0 = whichAxis == 0 ? m_x : whichAxis == 1 ? m_y : m_z;
  glm::vec3 &ref1 = whichAxis == 0 ? m_y : whichAxis == 1 ? m_z : m_x;
  glm::vec3 &ref2 = whichAxis == 0 ? m_z : whichAxis == 1 ? m_x : m_y;

  ref1 = rotatePointAroundAxis(ref1, ref0, howMuch);
  ref2 = rotatePointAroundAxis(ref2, ref0, howMuch);

  if (rand() % PERIOD_OF_SELF_CORRECTION == 0) {
    fixOrthogonality();
  }
}

void Axes::rotateX(float howMuch) {
  rotate(0, howMuch);
}

void Axes::rotateY(float howMuch) {
  rotate(1, howMuch);
}

void Axes::rotateZ(float howMuch) {
  rotate(2, howMuch);
}

/*
  Replaced by glm::lookAt since I didn't have the time to figure out what's wrong.
 
  Returns the two components of the rotation required for a global z and x vectors
  to become the current local z and x vectors.
*/
void Axes::getRotationMatrixFromZUnit(glm::mat4& rotSecond, glm::mat4& rotFirst) const {
 /* glm::vec4 cameraPos(1.f, 0.f, 0.f, 1.f);
  
  glm::vec4 zUnit(0.f, 0.f, 1.f, 1.f);
  glm::vec4 xUnit(1.f, 0.f, 0.f, 1.f);
  glm::vec4 yUnit(0.f, 1.f, 0.f, 1.f);

  

  glm::mat4 rotMatrix;
  glm::vec3 zAxis(0.f, 0.f, 1.f), xAxis(1.f, 0.f, 0.f);

  glm::vec3 cross = glm::cross(zAxis, m_z);
  float dotres = glm::clamp(glm::dot(glm::normalize(zAxis), glm::normalize(m_z)), -0.9999999999f, 0.9999999999f);
  float dot = acosf(dotres);

  if (fabs(dot) > MIN_FLOAT_DIFF) {
    rotFirst = glm::rotate(rotMatrix, dot, cross);
  }

  xAxis = glm::vec3(rotFirst * glm::vec4(xAxis, 1.f));
  glm::vec3 cross2 = glm::normalize(glm::cross(xAxis, m_x));
  float dot2res = glm::clamp(glm::dot(glm::normalize(xAxis), glm::normalize(m_x)), -0.9999999999f, 0.9999999999f);
  float dot2 = acosf(dot2res);
  if (fabs(dot2) > MIN_FLOAT_DIFF) {
      
  rotSecond = glm::rotate(rotMatrix, dot2, cross2);

  // testing... resultZ is supposed to equal m_z
  // testing... resultX is supposed to equal m_X

  glm::mat4 proj = App::getApp().m_translate;
  glm::vec4 resultZF = rotFirst * proj *zUnit; // vertex shader will work this way
  glm::vec4 resultXF = rotFirst * proj *xUnit;
  glm::vec4 resultYF = rotFirst * proj *yUnit;

  glm::vec4 resultZ = rotSecond * resultZF; // vertex shader will work this way
  glm::vec4 resultX = rotSecond * resultXF;
  glm::vec4 resultY = rotSecond * resultYF;
  resultZ += resultX;
  */
}

/*
  So far I am not too familiar with glm... I'll implement this from ground zero.

  NOTE: 
    There is most likely a formula that does what I need much faster, 
    but deadline is coming, so I'm saving some (time)/(mental energy) for other stuff.

  NOTE (2): 
    The current solution is somewhat verbose since I'm trying to avoid calls to 
    sin/asin and its like. Haven't checked how fast those are.
  
  NOTE (3):
    the direction in which rotations take place is determinable via the right-hand rule:
    xy yz zx coordinate systems rotate clockwise for the same sign of the angleValue

  1. rotate axis to match x axis via a xy and xz rotation
  2. Repeat those rotations on pt.
  3. now rotate pt around x axis the required amount (Trivial now that we are rotating in the yz plane)
  4. Apply on the pt the negatives of the original xy xz rotations in reverse order.
  5. Enjoy

*/
glm::vec3 Axes::rotatePointAroundAxis(const glm::vec3& pt, const glm::vec3& axis, float howMuch) {
  //1. rotate axis to match x axis
  //1.1. XY rotation until y is zero. SAVE ANGLE info as XY_angle_[etc];
  float XY_x = axis.x;
  float XY_y = axis.y;
  float XY_hypo = sqrt(XY_x*XY_x + XY_y*XY_y);
  
  
  bool XY_ROTATES = fabs(XY_hypo) > MIN_FLOAT_DIFF;
  float newX = 0.;
  float XY_sin = 0.;
  float XY_cos = 0.;
  if (XY_ROTATES) {
    XY_sin = XY_y / XY_hypo;
    XY_cos = XY_x / XY_hypo;
    newX = XY_x * XY_cos + XY_y * XY_sin;
  }
  

  //float newY = - XY_x * XY_sin + XY_y * XY_cos; //Not reallly needed since newY is zero... 
  
  //1.2 XZ rotation until z is zero SAVE ANGLE as 
  float XZ_x = newX;
  float XZ_z = axis.z;
  float XZ_hypo = sqrt(XZ_x*XZ_x + XZ_z*XZ_z);


  bool XZ_ROTATES = fabs(XZ_hypo) > MIN_FLOAT_DIFF;

  float XZ_sin = 0.f;
  float XZ_cos = 0.f;
  float finalX = XZ_x;
  if (XZ_ROTATES) {
    XZ_sin = XZ_z / XZ_hypo;
    XZ_cos = XZ_x / XZ_hypo;
    finalX = XZ_x * XZ_cos + XZ_z * XZ_sin;
  }

  //float finalZ = - XZ_x * XZ_sin + XZ_z * XZ_cos; //Not really needed since finalZ is zero... 
  
  //2. Apply the xy,xz rotations on pt.
  float pt_XY_x = pt.x;
  float pt_XY_y = pt.y;

  float pt_XZ_x = pt_XY_x;
  float pt_adjustedY = pt_XY_y;
  if (XY_ROTATES) {
    pt_XZ_x = pt_XY_x * XY_cos + pt_XY_y * XY_sin;
    pt_adjustedY = -pt_XY_x * XY_sin + pt_XY_y * XY_cos; // Needed here. Likely nonzero after all.
  }

  float pt_XZ_z = pt.z;

  float pt_adjustedX = pt_XZ_x;
  float pt_adjustedZ = pt_XZ_z;
  if (XZ_ROTATES) {
    pt_adjustedX = pt_XZ_x * XZ_cos + pt_XZ_z * XZ_sin;
    pt_adjustedZ = -pt_XZ_x * XZ_sin + pt_XZ_z * XZ_cos; //needed 
  }

  //3. now rotate pt around x axis the required amount. A yz rotation!
  // Working with pt_adjustedXYZ
  float pt_rotatedX = pt_adjustedX; // Magic! :D
  
  float cosInput = cos(-howMuch);
  float sinInput = sin(-howMuch);
  
  float pt_rotatedY = pt_adjustedY * cosInput + pt_adjustedZ * sinInput;
  float pt_rotatedZ = -pt_adjustedY * sinInput + pt_adjustedZ * cosInput;
  
  // 4. Apply on the pt the negatives of the original xy xz rotations in reverse order.
  // 4.1 Rotate reverse xz
  // Working with pt_rotatedXYZ
  float XZ_cosReverse = XZ_cos;
  float XZ_sinReverse = -XZ_sin;

  float pt_revX = pt_rotatedX;
  float pt_revY = pt_rotatedY;
  float pt_revZ = pt_rotatedZ;
  if (XZ_ROTATES) {
    pt_revX = pt_rotatedX * XZ_cosReverse + pt_rotatedZ * XZ_sinReverse;
    pt_revZ = -pt_rotatedX * XZ_sinReverse + pt_rotatedZ * XZ_cosReverse;
  }
  // 4.2 Rotate reverse xy
  // Working with pt_revXYZ
  float XY_cosReverse = XY_cos;
  float XY_sinReverse = -XY_sin;

  float pt_finalX = pt_revX;
  float pt_finalY = pt_revY;
  float pt_finalZ = pt_revZ;

  if (XY_ROTATES) {
    pt_finalX = pt_revX * XY_cosReverse + pt_revY * XY_sinReverse;
    pt_finalY = -pt_revX * XY_sinReverse + pt_revY * XY_cosReverse;
  }

  return glm::vec3(pt_finalX, pt_finalY, pt_finalZ);
}

const glm::vec3& Axes::x() const {
  return m_x;
}

const glm::vec3& Axes::y() const {
  return m_y;
}

const glm::vec3& Axes::z() const {
  return m_z;
}
