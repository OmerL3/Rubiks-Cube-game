#include <Light.h>
#include <vector>

class Ambient : public Light
{
    protected:
        glm::vec3 rgb;
        
    public:
        Ambient(float r, float g, float b);

        std::string to_string_print() override;

        bool is_spotlight();
        bool is_ambient();
        bool is_shadowed(Intersection* p, const std::vector<Object*>& objects) override;

        glm::vec3 get_rgb() {return rgb;}

        ~Ambient();

};
