#ifndef PERUSHINKOV_CALC_H
#define PERUSHINKOV_CALC_H
#include "../glewInclude.h"
class Calc
{
public:
  static glm::vec3 getUnitDirection(const glm::vec3& vec) {
    return vec / sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
  }
private:
  Calc() {}
  ~Calc() {}
};

#endif