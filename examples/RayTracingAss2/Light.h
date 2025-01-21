#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <vector>

#include <Object.h>
#include <Intersection.h>
#include <Ray.h>


class Light
{
    protected:
        glm::vec3 direction;
        glm::vec3 intensity;
        bool i_is_set = false;

    public:
        Light(glm::vec3 dir) : 
            direction(glm::normalize(dir)) {};

        void set_intensity(float r, float g, float b)
        {
            intensity = glm::vec3(r, g, b);
            i_is_set = true;
        }

        bool is_intensity_set()
        {
            return i_is_set;
        }

        virtual std::string to_string_print() = 0;

        virtual bool is_shadowed(Intersection* p, const std::vector<Object*>& objects) = 0;

        virtual bool is_spotlight() = 0;
        virtual bool is_ambient() = 0;

        glm::vec3 get_intensity() {return intensity;}
        glm::vec3 get_direction() {return direction;}

        virtual ~Light() = default;
};



