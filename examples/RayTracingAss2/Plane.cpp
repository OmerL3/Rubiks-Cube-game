#include <Plane.h>

Plane::Plane(glm::vec3 n, float d, opticalT t) 
            : Object(t), normal(n), d(-1*d) {
                // std::cout<<"A Plane created"<<std::endl;
            }


std::string Plane::to_string_print() 
{
    std::string str = "Plane: c=";
    str += std::to_string(K_da.x) + "," + std::to_string(K_da.y) + "," + std::to_string(K_da.z);


    str += " || n=" + std::to_string(normal.x) + "," + std::to_string(normal.y) + "," + std::to_string(normal.z);

    str += " || d=" + std::to_string(d);

    str += " || shininess= " + std::to_string(n_shiny);

    str += " || type = " + std::to_string(type);


    return str;

};

glm::vec3 Plane::get_point_on_plane()
{
    glm::vec3 p(0,0,0);

    if(normal.x != 0) p.x = d / normal.x;
    else if(normal.y != 0) p.y = d / normal.y;
    else if(normal.z != 0) p.z = d / normal.z;
    else throw std::invalid_argument("Plane get_point_on_plane failed");

    return p;
}


glm::vec3 Plane::get_intersection(Ray ray)
{
    glm::vec3 ray_V = ray.get_direction();
    glm::vec3 ray_P0 = ray.get_start();

    glm::vec3 Q0 = get_point_on_plane();

    float NV = glm::dot(normal, ray_V);
    if(std::abs(NV) < 1e-6) return glm::vec3(std::numeric_limits<float>::infinity());

    float t = glm::dot(normal, (Q0 - ray_P0)) / NV; //N*((Q0-PO)/N*V)
    if(t < 0) return glm::vec3(std::numeric_limits<float>::infinity());

    return ray.at(t);
}



glm::vec3 Plane::get_normal(glm::vec3 p)
{
    return glm::normalize(-normal);
}

bool Plane::is_plane() {return true;}


Plane::~Plane() {}