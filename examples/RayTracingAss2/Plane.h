#include <Object.h>
#include <string>
#include <Ray.h>
#include <Intersection.h>

class Plane : public Object
{
    private:
        glm::vec3 normal;
        float d;

    public:
        Plane(glm::vec3 n, float d, opticalT t);

        std::string to_string_print();
        glm::vec3 get_point_on_plane();
        glm::vec3 get_intersection(Ray ray);

        bool is_plane();
        glm::vec3 get_normal(glm::vec3 p) override;

        ~Plane();

};


