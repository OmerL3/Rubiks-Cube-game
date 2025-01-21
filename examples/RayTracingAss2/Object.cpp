#include <Object.h>



bool Object::is_plane()
{
    std::cout << "WRONG is_plane in Object.cpp" << std::endl;
    return false;
}


std::string Object::to_string_print() 
{
    std::string str = "Object ";
    str += std::to_string(K_da.x) + "," + std::to_string(K_da.y) + "," + std::to_string(K_da.z);

    return str;

};

glm::vec3 Object::get_normal(glm::vec3 p)
{
    std::cout << "WRONG get_normal in Object.cpp" << std::endl;
    return glm::vec3(0,0,0);
}

glm::vec3 Object::get_intersection(Ray ray) 
{
    std::cout << "WRONG get_intersection in Object.cpp" << std::endl;

    return glm::vec3(0,0,0);
}

