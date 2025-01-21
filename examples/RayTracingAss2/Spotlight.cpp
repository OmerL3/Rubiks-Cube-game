#include <Spotlight.h>
#include <vector>

Spotlight::Spotlight(glm::vec3 dir)
            : Light(dir)
            {
                angle = -1.0f;
            }


void Spotlight::set_angle(float a)
{
    angle = a;
}

int Spotlight::get_angle()
{
    return angle;
}

void Spotlight::set_point(glm::vec3 p)
{
    point = p;
}

glm::vec3 Spotlight::get_point()
{
    return point;
}


bool Spotlight::is_intensity_set()
{
    return i_is_set;
}

bool Spotlight::is_spotlight() {return true;}
bool Spotlight::is_ambient() {return false;}

std::string Spotlight::to_string_print() 
{
    std::string str = "Spotlight: direction=";

    str += std::to_string(direction.x) + "," + std::to_string(direction.y) + "," + std::to_string(direction.z);

    str += " || point = " + std::to_string(point.x) + "," + std::to_string(point.y) + "," + std::to_string(point.z);

    str += " || angle = " + std::to_string(angle);

    str += " || intensity = " + std::to_string(intensity.x) + "," + std::to_string(intensity.y) + "," + std::to_string(intensity.z);


    return str;
}

bool Spotlight::is_shadowed(Intersection* p, const std::vector<Object*>& objects)
{
    const float epsilon = 1e-4f;

    glm::vec3 to_point = glm::normalize(p->get_point() - point);
    
    if (glm::dot(to_point, glm::normalize(direction)) < angle)
        return true; 
    
    glm::vec3 shadow_dir = glm::normalize(point - p->get_point());
    Ray ray(p->get_point() + epsilon * shadow_dir, shadow_dir);

    float max_dist = glm::length(point - p->get_point());

    for(Object* obj : objects)
    {
        if(obj == p->get_object()) continue;
        
        glm::vec3 hit = obj->get_intersection(ray);
        if (hit != glm::vec3(std::numeric_limits<float>::infinity()) && glm::length(hit) < max_dist)
            return true;
    }

    return false;

}




Spotlight::~Spotlight(){}
