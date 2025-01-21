#include <Light.h>
#include <string>
#include <vector>

class Directional : public Light
{
    private:

    public:
        Directional(glm::vec3 dir);

        bool is_intensity_set();

        bool is_spotlight();
        bool is_ambient();
        std::string to_string_print() override;

        bool is_shadowed(Intersection* p, const std::vector<Object*>& objects) override;

        ~Directional();

};