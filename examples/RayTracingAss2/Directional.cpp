#include <Directional.h>
#include <vector>

Directional::Directional(glm::vec3 dir)
            : Light(dir) 
            {
            }


bool Directional::is_intensity_set()
{
    return i_is_set;
}

bool Directional::is_spotlight() {return false;}
bool Directional::is_ambient() {return false;}

std::string Directional::to_string_print() 
{
    std::string str = "Directional: direction=";

    str += std::to_string(direction.x) + "," + std::to_string(direction.y) + "," + std::to_string(direction.z);

    str += " || intensity = " + std::to_string(intensity.x) + "," + std::to_string(intensity.y) + "," + std::to_string(intensity.z);

    return str;
}

bool Directional::is_shadowed(Intersection* p, const std::vector<Object*>& objects)
{
    const float epsilon = 1e-4f; 
    glm::vec3 origin = p->get_point();
    glm::vec3 shadow_dir = glm::normalize(-direction);

    Ray shadow_ray(origin + epsilon * shadow_dir, shadow_dir);

    for (Object* obj : objects)
    {
        glm::vec3 intersection = obj->get_intersection(shadow_ray);
        if (intersection != glm::vec3(std::numeric_limits<float>::infinity()))
        {
            return true; 
        }
    }

    return false; 
}


Directional::~Directional(){}   


