#include "Ray.h"

Ray::Ray(glm::vec3 s, glm::vec3 d)
    : startP(s), directionV(d) {}


glm::vec3 Ray::at(float t)
{
    return startP + t*directionV;
}





Ray::~Ray() {}
