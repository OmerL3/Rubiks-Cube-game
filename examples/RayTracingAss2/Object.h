#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <Ray.h>



enum opticalT
{
    NORMAL,
    REFLECTIVE,
    TRANSPARENT
};


class Object
{

protected:
    opticalT type;
    glm::vec3 K_da;
    float n_shiny;
    bool is_set = false;

public:
    Object(opticalT t) : type(t){};
    void set_rgb(float r, float g, float b, float n)
    {
        K_da = glm::vec3(r, g, b);
        n_shiny = n;
        is_set = true;
    }

    bool is_rgb_set()
    {
        return is_set;
    }

    glm::vec3 get_rgb() {return K_da;}
    virtual glm::vec3 get_normal(glm::vec3 p);
    float get_shininess() {return n_shiny;}
    bool is_normal() {return type == NORMAL;}
    bool is_reflective() {return type == REFLECTIVE;}


    virtual bool is_plane();

    virtual std::string to_string_print() = 0;

    virtual glm::vec3 get_intersection(Ray ray);

    virtual ~Object() = default;
};

