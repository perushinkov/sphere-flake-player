#ifndef PERUSHINKOV_AXIS_H
#define PERUSHINKOV_AXIS_H

#include "../glewInclude.h"


const int PERIOD_OF_SELF_CORRECTION = 10;
/*
  Several of my implementation attempts were halted by the fact that the orthogonality of  any pair of vectors
  will decay over time due to rounding errors, unless there is correction of some sort. That is what this class
  represents:

  Self-correcting Axes class.
  
  A triple of mutually orthogonal vectors with unit size. Each representing a different axis.
  x, y, z

  The axes orientation will follow the right-hand rule.

  The class will be used in the recursive generation of the spheres, as well as in the camera control section.
*/
class Axes
{
public:
  enum {X_AXIS, Y_AXIS, Z_AXIS};

  Axes();
  ~Axes() {}

  void rotateX(float howMuch);
  void rotateY(float howMuch);
  void rotateZ(float howMuch);

  const glm::vec3& x() const;
  const glm::vec3& y() const;
  const glm::vec3& z() const;
 
  static glm::vec3 rotatePointAroundAxis(const glm::vec3& pt, const glm::vec3& axis, float howMuch);
private:
  void rotate(int whichAxis, float howMuch);
  void fixOrthogonality();
  glm::vec3 m_x;
  glm::vec3 m_y;
  glm::vec3 m_z;
  
  // Deprecated...
  void getRotationMatrixFromZUnit(glm::mat4& rotFirst, glm::mat4& rotSecond) const;

  
};

#endif