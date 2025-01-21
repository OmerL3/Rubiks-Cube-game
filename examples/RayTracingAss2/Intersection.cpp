#include <Intersection.h>

Intersection::Intersection(glm::vec3 p, Object* obj) : point(p), object(obj){}

//maybe need copy cons

float Intersection::distance(glm::vec3 v)
{
    return glm::distance2(point, v);
}

Intersection::~Intersection(){}


