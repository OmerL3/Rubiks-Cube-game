#include <Object.h>
#include <string>
#include <Ray.h>

class Sphere : public Object
{
private:
    glm::vec3 center;
    float radius;

public:
    Sphere(glm::vec3 c, float r, opticalT t);


    std::string to_string_print();
    glm::vec3 get_intersection(Ray ray);
    glm::vec3 get_furthest_intersection(Ray ray);

    bool is_plane();
    Ray calc_snell(glm::vec3 point, glm::vec3 L);
    
    glm::vec3 get_normal(glm::vec3 p) override;

    ~Sphere();

};


