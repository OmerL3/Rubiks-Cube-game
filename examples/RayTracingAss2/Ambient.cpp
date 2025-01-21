#include <Ambient.h>

Ambient::Ambient(float r, float g, float b) 
            : Light(glm::vec3(1.0f,1.0f,1.0f)) 
            {
                rgb = glm::vec3(r,g,b);
                set_intensity(1.0f,1.0f,1.0f);
            }

std::string Ambient::to_string_print()
{
        std::string str = "Ambient: color=";

        str += std::to_string(rgb.r) + "," + std::to_string(rgb.g)  + "," + std::to_string(rgb.b);

        return str;
}

bool Ambient::is_spotlight() {return false;}
bool Ambient::is_ambient() {return true;}

bool Ambient::is_shadowed(Intersection* p, const std::vector<Object*>& objects) {return false;}

Ambient::~Ambient(){}
            
