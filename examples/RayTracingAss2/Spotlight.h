#include <Light.h>
#include <vector>

class Spotlight : public Light
{
    private:
        glm::vec3 point;
        float angle;

    public:
        Spotlight(glm::vec3 dir);
        
        void set_angle(float a);
        int get_angle();
        void set_point(glm::vec3 p);
        glm::vec3 get_point();

        bool is_intensity_set();
        bool is_spotlight();
        bool is_ambient();
        std::string to_string_print() override;

        bool is_shadowed(Intersection* p, const std::vector<Object*>& objects) override;

        ~Spotlight();
};